%module CosmicStringCusp
%{
#include "Declarations.h"
%}

// the following three lines allow the automatic conversion of a numpy array
// into a pointer to an array of doubles without the long length of the array

%include numpy_typemaps.i
%typemap(in) double *hp = double *carray;
%typemap(in) double *hc = double *carray;

// the following include defines all the calls that need to be wrapped by SWIG
// the include at the top serves only to provide definitions for this one;
// since it is between braces %{ %}, its content goes straight into
// the CPP wrapper file

%include "Declarations.h"

// and here we can add some Python to the interface code

%pythoncode %{
import lisaxml
import numpy
import math

lisaxml.SourceClassModules['CosmicStringCusp'] = 'CosmicStringCusp'

# generic CoherentWave    

class CosmicStringCusp(lisaxml.Source):
    """Returns a MLDC source that models the waveform emitted by a
	 cosmicstringcusp (by Neil Cornish)."""
    
    # this is the list of parameters that will be recorded in the lisaXML SourceData sections
    # give ParameterName, DefaultUnit, DefaultValue (a string), Description

    outputlist = (('EclipticLatitude',                 'Radian',        None, 'standard ecliptic latitude'),
                  ('EclipticLongitude',                'Radian',        None, 'standard ecliptic longitude'),
                  ('Polarization',                     'Radian',        None, 'standard source polarization'),
                  ('Amplitude',                        '1',             None, 'overall signal amplitude'),
                  ('CentralTime',                      'Second',        None, 'central time of the burst'),
                  ('MaximumFrequency',                 'Hertz',         None, 'maximum burst frequency'))
    
    dopolarization = True
    
    def  __init__(self,name=''):
        super(CosmicStringCusp, self).__init__('CosmicStringCusp',name)
        
        # pre-define variables here if used later, so that they will not be included in parameters when they are set
    
    def waveforms(self,samples,deltat,inittime):
        Cusp = Cusp_structure()
        
        Cusp.Amplitude          = self.Amplitude
        Cusp.CentralTime        = self.CentralTime
        Cusp.Polarization       = self.Polarization
        Cusp.MaximumFrequency   = self.MaximumFrequency
        
        # not needed for generation, but we'll leave them
        Cusp.EclipticLatitude   = self.EclipticLatitude
        Cusp.EclipticLongitude  = self.EclipticLongitude
        
        # The signal generated by CosmicStringCusp is for the time of observation, plus two padding periods;
        # but the standard interface specifies an inittime, usually = -Tpad, and the total number
        # of samples. A positive inittime does not really fit this scheme...
        
        if inittime > 0:
            raise NotImplementedError, "Sorry, FastSpinBlackHoleBinary currently supports only negative inittime (used for padding)"
        
        Cusp.Samples = int(samples + 2 * inittime / deltat)
        Cusp.Cadence = 1.0 / deltat
        Cusp.Tpad    = -inittime
        
        hp = numpy.empty(samples,'d')
        hc = numpy.empty(samples,'d')
        
        Cusp_Barycenter(Cusp, hp, hc, samples);
        
        return (hp,hc)
    
%}

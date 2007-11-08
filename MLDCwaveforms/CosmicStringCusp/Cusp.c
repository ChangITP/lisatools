#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <fftw3.h>
#include "Constants.h" 
#include "Declarations.h"

void Cusp_Barycenter(Cusp_structure Cusp, double *hp, double *hc, int n)
{ 
 
  double f, c2psi, s2psi;
  char Gfile[50]; 
  double Tobs, fix, t, fmax, Dt;
  double Tburst, T0;
  double ts, delt, B; 
  long M, N, q; 
  long i, j, back, cnt, mult; 
  FILE* Infile; 
  FILE* Outfile; 

 // used by fftw3
  fftw_complex *out;
  fftw_plan plan_reverse;
  int nc;
  double *in;

  if(((double)(Cusp.Samples)-pow(2.0,rint(log((double)(Cusp.Samples))/log(2.0)))) > 1.0e-10)
    {
      KILL("Number of Samples is not a power of 2\n");
    }

  N = 2*Cusp.Samples;   // have to double observation time to allow for Tpad.

  c2psi = cos(2.0*Cusp.Polarization);
  s2psi = sin(2.0*Cusp.Polarization);

  Tburst = (double)(N)/Cusp.Cadence;

  T0 = Tburst/4.0;
  ts = T0 + Cusp.CentralTime;

  back = N/4 - (int)(Cusp.Tpad*Cusp.Cadence);

  printf("%d\n", back);

  nc = N/2+1;
  in = fftw_malloc ( sizeof ( double ) * N);
  out = fftw_malloc ( sizeof ( fftw_complex ) * nc );
  plan_reverse = fftw_plan_dft_c2r_1d(N, out, in, FFTW_ESTIMATE);

   out[0][0] = 0.0;
   out[0][1] = 0.0;
 
   for(i=1; i<= (nc-1); i++) 
    { 
      f = (double)(i)/Tburst; 
      B = Cusp.Amplitude*pow((1+pow((FLOW/f),2.0)),-4.0) * pow(f,-4.0/3.0);
      if(f >= Cusp.MaximumFrequency) B *= exp(1.0-f/Cusp.MaximumFrequency);
      out[i][0] = -B*cos(-TPI*f*ts);
      out[i][1] = -B*sin(-TPI*f*ts);
    } 

   out[nc-1][1] = 0.0;
 
   fftw_execute ( plan_reverse);

   printf("here\n");

 
  for(i=0; i< n; i++) 
    { 
      hp[i] = 0.0;
      hc[i] = 0.0;
      j = back + i;
      if((j >= 0) && (j < N))
	{
	  hp[i] = in[j]*c2psi/(double)(N);
          hc[i] = -in[j]*s2psi/(double)(N);
        }
    } 
 

  fftw_free ( in );
  fftw_free ( out );
  fftw_destroy_plan ( plan_reverse ); 
 
    return; 
 
} 
	 
 
void KILL(char* Message) 
{ 
  printf("\a\n"); 
  printf(Message); 
  printf("Terminating the program.\n\n\n"); 
  exit(1); 
 
  
  return; 
}

void Jump_Prep(double **EigenVecs, double *EigenVals, double *Params, double *shf, double flow, double fmax, int n);
void Uncertainties(double **EigenVecs, double *EigenVals, double *Sigma);
void Fisher_Matrix(double **Fisher, double *Params, double *shf, double flow, double fmax, int n);
void Normal_Distribution(double *Jump, double **EigenVecs, double *EigenVals, long *rSeed);
void Log_Likelihood(double *logL, double *template1, double *template2, double *signal1, double *signal2, double *shf, double flow, double fmax, int n);
double Sum(double *CA1, double *CA2, double *shf, int n, double flow, double fmax);
void Mh_Normal(double **EigenVecs, double *EigenVals, double *ParamsX, double *LogLX, int *Accept, double *sig1, double *sig2, double *shf, double flow, double fmax, double *Pmin, double *Pmax, int n, long *rseed);
void dfour1(double data[], unsigned long nn, int isign);
void drealft(double data[], unsigned long n, int isign);
void Fourier_Scaling(double *ft, int n);
void jacobi(double **a, int n, double e[], double **v, int *nrot);
void LISA_Noise_PSD(double *LPSD, double f);
void LISA_Noise_PSD_Array(double *shf, int n);
int *ivector(long nl, long nh);
void free_ivector(int *v, long nl, long nh);
double *dvector(long nl, long nh);
void free_dvector(double *v, long nl, long nh);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
double ***d3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_d3tensor(double ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
double gasdev2(long *idum);
void Noise_Generator(double *REn, double *IMn, long *rseed, int n);
double ran2(long *idum);
void Basic_Signal(double *shp, double *shc, double *c2psi, double *s2psi, double* sigpar, int n, double fmax);
void Signal_Generator(double* sig1, double* sig2, double* sigpar, int n, double fmax);
void D_Plus(double *Dplus, double *params, double lambda, int n);
void D_Cross(double *Dcross, double *params, double lambda, int n);
void rkckstep(double outputvals[], double fourthorderoutputvals[], double *outputthomas, double h, double currentvals[], double currentthomas, double t, double m1, double m2, double Mtot, double Mchirp, double mu, double eta, double chi1, double chi2, double N[], double tc);
void calcderivvals(double derivvals[], double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double S1xdot(double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double S1ydot(double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double S1zdot(double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double S2xdot(double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double S2ydot(double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double S2zdot(double inputs[], double r, double m1, double m2, double Mtot, double mu, double chi1, double chi2);
double calcLdotS1(double inputs[]);
double calcLdotS2(double inputs[]);
double calcSdotS(double inputs[]);
double calcLdotN(double inputs[], double nvec[]);
void calcLcrossN(double output[], double inputs[], double nvec[]);
double Time(double f, double Mtot, double Mchirp, double eta, double beta, double sigma, double tc);
double Time_deriv(double f, double Mtot, double Mchirp, double eta, double beta, double sigma);  
double Freq(double t, double Mtot, double Mchirp, double eta, double beta, double sigma, double tc);
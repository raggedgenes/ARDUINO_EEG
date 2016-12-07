#include "spectrogram.h"

Spectrogram::Spectrogram(QObject *parent) :
    QObject(parent)
{
}
void Spectrogram::doFFTW3() { //kell a méret, és az adatsor| visszaad egy adatsort (magnitude)
    //    extern int optind;
    int FFT_SIZE = display->getSampleSize();
    double in[FFT_SIZE];
    power_spectrum = new double[FFT_SIZE];
    fftw_complex *out;
    fftw_plan plan;
    out = (fftw_complex *)fftw_malloc(sizeof (fftw_complex) * FFT_SIZE);
    for (int i=0; i<(0+FFT_SIZE); i++)
    {
        in[i-0] = data[(FFT_SIZE-FFT_SIZE)+i-0]; //ADC resol = 1024
    }

    plan = fftw_plan_dft_r2c_1d(FFT_SIZE,in,out,FFTW_ESTIMATE);
    fftw_execute(plan); //fftw_one(p, in, out);

    //process results
    double r, i;
    for (int k = 0; k < FFT_SIZE/2+1; k++) {
        r = out[k][0];
        i = out[k][1];
        power_spectrum[k] = sqrt((r * r) + (i * i));
//        printf("%i %lf\n", k, power_spectrum[k]);
    }
    fftw_destroy_plan(plan);

}

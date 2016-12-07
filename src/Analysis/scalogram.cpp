#include "scalogram.h"
#include "fftw3.h"
#include "math.h"
#include "rgmath.h"

/**
  * Find the next highest power of two. For example, if 40 it passed in, it
  * will return 64.
  */
static int round_2_up(int num)
{
    return (int)pow( 2, ceil(log((double)num)/log((double)2)) );
}

/**
  * Calculate the morlet wavelet in the Fourier domain, using the given scale
  * and f0 values.
  */
static float FTWavelet( float x, float scale, float f0 )
{
    //if ( x < 0.9 / scale ||  x > 1.1 / scale ) {
    //    return (float)0.0;
    //}

    static const float pi = (float)3.14159265358979323846;
    static const double two_pi_f0 = 2.0 * pi * f0;
    static const double multiplier = 1.8827925275534296252520792527491;

    scale *= (float)f0;

    // 1.88279*exp(-0.5*(2*pi*x*10-2*pi*10)^2)

    float basic = (float)(multiplier * exp(-0.5*(2*pi*x*scale-two_pi_f0)*(2*pi*x*scale-two_pi_f0)));

    // pi^0.25*sqrt(2.0)*exp(-0.5*(2*pi*x*scale-2*pi*0.849)^2)
    return sqrt(scale)*basic;
}
static float calcLinear(float* data)
{
    return sqrt(data[0]*data[0]+data[1]*data[1]);
}

static float calcLog(float* data)
{
    return log(sqrt(data[0]*data[0]+data[1]*data[1]));
}

static float calcLogReal(float* data)
{
    if ( data[0] == 0.0 ) {
        return 0.0;
    }
    return log(fabs(data[0]));
}

static float calcLogComplex(float* data)
{
    return log(fabs(data[1]));
}
const static float pi = (float)3.14159265358979323846;
static float phase( float x, float y )
{
    if ( y == 0.0 ) {
        if ( x >= 0 ) {
            return 0.0;
        } else {
            return pi;
        }
    } else {
        float sgn = 1.0;
        if ( y < 0.0 ) {
            sgn = -1.0;
        }

        if ( x >= 0.0 ) {
            return abs(atan( y / x ))*sgn;
        } else if ( x == 0.0 ) {
            return (float)pi/2*sgn;
        } else {
            return (float)(pi - abs(atan( y / x )))*sgn;
        }
    }
}

static float calcPhase(float* data)
{
    return (phase( data[0], data[1]) + pi) / (2 * pi);
}
Scalogram::Scalogram(QObject *parent) :
    QObject(parent),    bands(0),
    samples(1500),
    sampleRate(1000),
    mmin((float)1.0e36),
    mmax((float)0.0)
{
        map = ColourMap(0);
        this->image = new QImage(1,1,QImage::Format_RGB888);
        lowerScale = new float();
        upperScale = new float();
        f0 = 0.849;
}

Scalogram::~Scalogram()
{

}

unsigned Scalogram::calcBands( float sampleRate, float* upperScale, float* lowerScale )
{
    float lowFreq = 2;
    float highFreq = 100;
    *upperScale = sampleRate / lowFreq;
    *lowerScale = qMax( sampleRate / highFreq, (float)2.0 );
    printf("sampleRate: %g upperScale:%g lowerScale:%g\n", sampleRate,*upperScale, *lowerScale);
    return (unsigned)(*upperScale - *lowerScale)+1;
}

double Scalogram::getFrequency(int row) const
{

    return 2*pow(df,(bands-row));
}
void Scalogram::run(float *eegreading, unsigned numSamples, unsigned sr, float xresol)
{

    this->sampleRate = sr;
    samples = numSamples;
    bands = calcBands(sampleRate, upperScale, lowerScale);

    this->image->~QImage();
    this->image = new QImage(this->samples*xresol,bands,QImage::Format_RGB888);

    //standardize
    float* processed = RGMath::Standardize(eegreading, samples);


    avoid_overlap = (unsigned)(*upperScale * 20);

    df = pow(*upperScale/(*lowerScale), 1.0 / (*upperScale - *lowerScale));
    N = round_2_up( samples + avoid_overlap )*2;

    fftwf_plan plan_forward;
    fftwf_plan plan_inverse;
    fftwf_complex* data = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * N);
    fftwf_complex* ans = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * N);
    printf("The value of N: %i \n", N);
    printf("The value of df: %f \n", (float)df);
    plan_forward = fftwf_plan_dft_1d(N, data, data, FFTW_FORWARD, FFTW_ESTIMATE );
    plan_inverse = fftwf_plan_dft_1d(N, ans, ans, FFTW_BACKWARD,  FFTW_ESTIMATE);

    memset( data, 0, sizeof(fftwf_complex)*N);
    memset( ans, 0, sizeof(fftwf_complex)*N);

    printf("\n");

    //Itt teszi be az adatokat!!
    for( unsigned i =0 ; i < samples; i++ ) {
        data[i][0] = processed[i];
    }

    fftwf_execute(plan_forward);

    // for each scale level,
    int row = 0;

    // for each scale factor,
    for ( double period = (double) *lowerScale; period <= *upperScale; period *= df, row += 1 )
    {

        // Multiply the fourier transform of the sound with the fourier
        // transform of the wavelet.
        memset( ans, 0, sizeof(fftwf_complex)*N);
        int start = (unsigned)(0.9 * N / period);
        int end = (unsigned)(1.1 * N / period);
        int x;
        for( x =start; x < end; x++ ) {
            ans[x][0] = FTWavelet((float)x, (float)period/(N), (float)f0) * data[x][0];
//            ans[i][1] = 0;
//            ans[N-i-1][0] = 0;
//            ans[N-i-1][1] = 0;
//            printf("Period: %d ------ WT: %f\n", period, ans[x][0]);
        }
        //calculate magnitude
        double r, i;
        r = data[x][0];
        i = data[x][1];
        //power_spectrum[k] = sqrt((r * r) + (i * i));

        // Perform inverse fourier transform of the result.
        fftwf_execute(plan_inverse);

        this->makeVertexBuffer(row,(float*)ans,samples);
    }
    this->scaloIsDone();
    fftwf_destroy_plan(plan_forward);
    fftwf_destroy_plan(plan_inverse);
    fftwf_free(data);
    fftwf_free(ans);
    free(processed);
}

void Scalogram::makeVertexBuffer(int row, float *samples, int length) {

    this->findMaxInRow(samples);
    if ( mmax <= mmin ) {
        return;
    }

    if ( samples == 0 ) {
        return;
    }
    int img_width = this->image->width(); //a kép szélessége
    double filter = (float)img_width / length;
//    int lastpix = 0;
//    double value = 0.0;
    double val = 0.0;
    double mymax = mmax;
    double mymin = mmin;


    func = &calcLinear;

    int offset = 0;
//    mymax = log(mymax);
//    if ( mymin != 0.0 ) {
//        mymin = log(mymin);
//    } else {
//        mymin = 0.0;
//    }
    int index;
    QColor cl;
    for( int j = 0; j < img_width; j++ ) {
        index = (int)((double)j/filter)+offset;
        val = func(&samples[index*2]);
        cl = map.map((float)(val-mymin) / (float)(mymax-mymin));
        this->image->setPixel(j,row,cl.rgb());
    }
//    free(cl);
}

void Scalogram::findMaxInRow( float* data )
{
    for ( unsigned i = 0; i < samples; i += 2 ) {
        float val = (float)fabs( data[i*2] );
        if ( val < mmin ) {
            mmin = val;
        }

        if ( val > mmax ) {
            mmax = val;
        }
    }
}


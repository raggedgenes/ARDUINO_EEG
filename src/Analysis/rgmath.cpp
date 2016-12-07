#include "math.h"
#include "rgmath.h"
#include "stdio.h"

RGMath::RGMath()
{
}

float * RGMath::Standardize(float *value, unsigned count) {

    float mean = CalculateMean(value, count);
    float stddev = GetStandardDeviation(value, count);
    float *stded = new float[count];
    for (unsigned i = 0; i < count; i++) {
        stded[i] = (value[i]-mean)/stddev;
//        printf("%f\n",stded[i]);
    }
    return stded;
}

float *RGMath::Normalize(float *value, unsigned count)
{
    float* maxmin = RGMath::findMaxMin(value, count);
    float diff = maxmin[0] - maxmin[1];
    float* normed = new float[count];
    for (unsigned i = 0; i < count; i++) {
        normed[i] = (value[i]-maxmin[1])/diff;
    }
    return normed;
}

float RGMath::CalculateMean(float *value, unsigned count)

{

    float sum = 0;

    for(unsigned i = 0; i < count; i++)

        sum += value[i];

    return (sum / count);

}

float RGMath::CalculateVariane(float *value, unsigned count)

{

    float mean = CalculateMean(value, count);



    float temp = 0;

    for(unsigned i = 0; i < count; i++)

    {

        temp += (value[i] - mean) * (value[i] - mean) ;

    }

    return temp / count;

}



float RGMath::CalculateSampleVariane(float *value, unsigned count)

{

    float mean = CalculateMean(value, count);



    float temp = 0;

    for(unsigned i = 0; i < count; i++)

    {

        temp += (value[i] - mean) * (value[i] - mean) ;

    }

    return temp / (count - 1);

}



int RGMath::SetValues(float *p, unsigned count, float *value)

{

    if(count > 100)

        return -1;

    for(unsigned i = 0; i < count; i++)

        value[i] = p[i];

    return 0;

}



float RGMath::GetStandardDeviation(float *value, unsigned count)

{

    return sqrt(CalculateVariane(value, count));

}



float RGMath::GetSampleStandardDeviation(float *value, unsigned count)

{

    return sqrt(CalculateSampleVariane(value, count));

}
float* RGMath::findMaxMin( float* data, unsigned count )
{
    float * ret = new float(2);
    float mmin = 1023;
    float mmax = 0;
    for ( unsigned i = 0; i < count; i ++ ) {
        float val = (float)fabs( data[i] );
        if ( val < mmin ) {
            mmin = val;
        }

        if ( val > mmax ) {
            mmax = val;
        }
    }
    ret[0] = mmax;
    ret[1] = mmin;
    printf("Max: %f; min: %f\n",ret[0], ret[1]);
    return ret;
}

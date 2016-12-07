#ifndef RGMATH_H
#define RGMATH_H

class RGMath
{
public:
    RGMath();
    static float *Standardize(float *value, unsigned count);
    static float *Normalize(float*value, unsigned count);
    static float CalculateMean(float *value, unsigned count);
    static float CalculateVariane(float *value, unsigned count);
    static float CalculateSampleVariane(float *value, unsigned count);
    static int SetValues(float *p, unsigned count, float *value);
    static float GetStandardDeviation(float *value, unsigned count);
    static float GetSampleStandardDeviation(float *value, unsigned count);
    static float *findMaxMin(float *data, unsigned count);
private:

};

#endif // RGMATH_H

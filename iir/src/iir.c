#include "iir.h"

#ifdef TEST
#include <stdio.h>
#endif

//from https://stackoverflow.com/questions/50588879/how-to-implement-iir-filter-in-c
void iir_process(const float *input, float *output, int len, float *coef, float *w, int coeff_len)
{
    int filterLength = coeff_len/2;

    float *out = output;
    const float *in = input;
    float *b = coef;
    float *a = &coef[filterLength];


    const float a0 = a[0];
    const float *a_end = &a[filterLength-1];
    const float *out_start = out;
    a++;
    out--;
    size_t m;
    for (m = 0; m < len; m++) {
        const float *b_macc = b;
        const float *in_macc = in;
        const float *a_macc = a;
        const float *out_macc = out;
        float b_acc = (*in_macc--) * (*b_macc++);
        float a_acc = 0;
        while (a_macc <= a_end && out_macc >= out_start) {
            b_acc += (*in_macc--) * (*b_macc++);
            a_acc += (*out_macc--) * (*a_macc++);
        }
        *++out = (b_acc - a_acc) / a0;
        in++;
    }
}

#include "iir.h"

#ifdef TEST
#include <stdio.h>
#endif

float get_state_term(int i, float *w, int coeff_len)
{
    i += 1;
    if( i < coeff_len/2 - 1 )
    {
        return w[i];
    }
    else
    {
        return 0;
    }
}

void iir_process(const float *input, float *output, int len, float *coef, float *w, int coeff_len)
{
    float tmp;
    float *b = coef;
    float *a = &coef[coeff_len/2];
    for(int i = 0; i < len; i++)
    {
        //calculate output
        output[i] = (w[0] + b[0] * input[i])/a[0];

        for(int j = 0; j < coeff_len/2; j++)
        {
            //update the state
            w[j] = 0;
            w[j] -= a[j+1] * output[i];
            w[j] += b[j+1] * input[i];
            w[j] += get_state_term(j, w, coeff_len);
        }
    }
}

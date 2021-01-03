#include "iir.h"

#ifdef TEST
#include <stdio.h>
#endif

void iir_process(const float *input, float *output, int len, float *coef, float *w, int coeff_len)
{
    /* for each sample */
    for(int i = 0; i < len; i++)
    {
        float sum;
        float tmp;

        //update the state for the next sample
        for(int j = 0; j < coeff_len/2; j++)
        {
            if(j == 0)
            {
                //input sample * a0
                sum = coef[coeff_len/2] * input[i];
                // first tap gets its sample from the input summed with all taps
                for(int k = coeff_len/2 + 1; k < coeff_len; k++)
                {
                    sum -= coef[k] * w[k - coeff_len/2];
                }
                tmp = w[0];
                w[0] = sum;
            }
            else
            {
                // the others get it from the previous tap
                float t;
                t = tmp;
                tmp = w[j];
                w[j] = t;
                
            }
        }

        //calculate the output sample
        sum = 0;
        for(int j = 0; j < coeff_len/2; j++)
        {
            sum += coef[j] * w[j];
        }
        output[i] = sum;
#ifdef TEST
        printf("\nSample %d\n", i);
        printf("%s", "State is:\n");
        for(int j = 0; j < coeff_len/2; j++)
        {
            printf("%d = %f\n", j, w[j]);
        }
        printf("Output %f\n", output[i]);
#endif
    }
}

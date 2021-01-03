#pragma once

void iir_process(const float *input, float *output, int len, float *coef, float *w, int coeff_len);

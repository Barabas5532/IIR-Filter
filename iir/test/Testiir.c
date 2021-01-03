#define UNITY_INCLUDE_FLOAT
#include "unity.h"
#include "iir.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

void setUp (void) {}
void tearDown (void) {}

void test_unity_filter_response(void)
{
    /* create a coefficient array that corresponds to an FIR filter with an
     * impulse response of [ 1, 0, 0 ...] */

    /* 1 + 0 * z**-1
     * -------------
     * 1 + 0 * z**-1
     */
    float coeff[] = {1, 0, 1, 0};
    float impulse[] = {1, 0, 0, 0};
    float output[ARRAY_SIZE(impulse)] = {0};
    float w[ARRAY_SIZE(impulse)] = {0};
    iir_process(impulse, output, ARRAY_SIZE(impulse), coeff, w, ARRAY_SIZE(coeff));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(impulse, output, ARRAY_SIZE(impulse));
}

void test_delay_filter_response(void)
{
    /* create a coefficient array that corresponds to an FIR filter with an
     * impulse response of [ 0, 1, 0, 0 ...] */

    /* 0 + 1 * z**-1
     * -------------
     * 1 + 0 * z**-1
     */
    float coeff[] = {0, 1, 1, 0};
    float impulse[] = {1, 0, 0, 0};
    float expected[] = {0, 1, 0, 0};
    float output[ARRAY_SIZE(impulse)] = {0};
    float w[ARRAY_SIZE(impulse)] = {0};
    iir_process(impulse, output, ARRAY_SIZE(impulse), coeff, w, ARRAY_SIZE(coeff));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, output, ARRAY_SIZE(impulse));
}

void test_div_by_two_unity_filter_response(void)
{
    /* create a coefficient array that corresponds to an FIR filter with an
     * impulse response of [ 1/2, 0, 0, 0 ...] */

    /* 1   + 0 * z**-1
     * -------------
     * 1/2 + 0 * z**-1
     */
    float coeff[] = {0.5, 0, 1, 0};
    float impulse[] = {1, 0, 0, 0};
    float expected[] = {0.5, 0, 0, 0};
    float output[ARRAY_SIZE(impulse)] = {0};
    float w[ARRAY_SIZE(impulse)] = {0};
    iir_process(impulse, output, ARRAY_SIZE(impulse), coeff, w, ARRAY_SIZE(coeff));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, output, ARRAY_SIZE(impulse));
}

void test_convolution_filter_response(void)
{
    /* create a coefficient array that corresponds to an FIR filter with an
     * impulse response of [ 1, 1, 0, 0 ...] */

    /* 1 + 1 * z**-1
     * -------------
     * 1 + 0 * z**-1
     */
    float coeff[] = {1, 1, 1, 0};
    float input[] = {1, 1, 0, 0};
    float expected[] = {1, 2, 1, 0};
    float output[ARRAY_SIZE(input)] = {0};
    float w[ARRAY_SIZE(input)] = {0};
    iir_process(input, output, ARRAY_SIZE(input), coeff, w, ARRAY_SIZE(coeff));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, output, ARRAY_SIZE(input));
}

void test_third_order_impulse(void)
{
    /* This filter and expected impulse response can be created using the
     * following python script */

    float coeff[] = {0.03168934384971104, 0.09506803154913313, 0.09506803154913313, 0.03168934384971104, 1.0, -1.459029062228061, 0.9103690002900686, -0.19782518726431944};
    float input[] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float expected[] = {0.03168934384971104, 0.1413037051887996,
        0.2723852477397881, 0.3067377739755946, 0.22752167297501763,
        0.10660083515409813, 0.009085496154783684, -0.03878057523175791,
        -0.043764810187733885, -0.02675215648417989};
    float output[ARRAY_SIZE(input)] = {0};
    float w[ARRAY_SIZE(coeff)/2] = {0};
    iir_process(input, output, ARRAY_SIZE(input), coeff, w, ARRAY_SIZE(coeff));
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, output, ARRAY_SIZE(input));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_unity_filter_response);
    RUN_TEST(test_delay_filter_response);
    RUN_TEST(test_div_by_two_unity_filter_response);
    RUN_TEST(test_convolution_filter_response);
    RUN_TEST(test_third_order_impulse);
    return UNITY_END();
}

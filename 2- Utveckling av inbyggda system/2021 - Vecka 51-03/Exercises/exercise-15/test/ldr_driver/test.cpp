#include <unity.h>
#include "ldr_driver.h"
#include "bsp_analog.h"

#ifndef DEVENV
#include "bsp_time.h"
#endif

void setUp(void) {}

void tearDown(void) {}

void test_ldr_driver(void)
{
    uint8_t ldr_pin = 33;
    ldr_driver_init(ldr_pin);
    TEST_ASSERT_EQUAL_UINT8(ADC_RESOLUTION, double_get_resolutuin());

    double_stub_digital_value(1000);
    TEST_ASSERT_EQUAL_UINT8(0, ldr_driver_get_intensity());
    TEST_ASSERT_EQUAL_UINT8(ldr_pin, double_get_pin_num());

    double_stub_digital_value(3000);
    TEST_ASSERT_EQUAL_UINT8(93, ldr_driver_get_intensity());

    double_stub_digital_value(4000);
    TEST_ASSERT_EQUAL_UINT8(100, ldr_driver_get_intensity());
}

int main(void)
{
#ifndef DEVENV
    bsp_time_delay(2000);
#endif

    UNITY_BEGIN();

    RUN_TEST(test_ldr_driver);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();

    while (1)
    {
        ;
    }

    return 0;
#endif
}

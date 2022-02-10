#include <unity.h>
#include "led_driver.h"
#include "bsp_analog.h"

#ifndef DEVENV
#include "bsp_time.h"
#endif

void setUp(void) {}

void tearDown(void) {}

void test_led_driver(void)
{
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_intensity(50));

    uint8_t led_pin = 30;
    led_driver_init(led_pin);

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_intensity(50));
    TEST_ASSERT_EQUAL_UINT8(led_pin, double_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(127, double_get_pin_pwm());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_intensity(100));
    TEST_ASSERT_EQUAL_UINT8(255, double_get_pin_pwm());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_intensity(25));
    TEST_ASSERT_EQUAL_UINT8(63, double_get_pin_pwm());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_intensity(125));
}

int main(void)
{
#ifndef DEVENV
    bsp_time_delay(2000);
#endif

    UNITY_BEGIN();

    RUN_TEST(test_led_driver);

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

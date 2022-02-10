#include <unity.h>
#include "Arduino.h"
#include "led_driver.h"

void setUp(void) {}

void tearDown(void) {}

void test_led_driver(void)
{
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_intensity(50));

    uint8_t led_pin = 30;
    led_driver_init(led_pin);

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_intensity(50));
    TEST_ASSERT_EQUAL_UINT8(led_pin, arduino_pin_num());
    TEST_ASSERT_EQUAL_UINT8(127, arduino_pin_pwm());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_intensity(100));
    TEST_ASSERT_EQUAL_UINT8(255, arduino_pin_pwm());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_intensity(25));
    TEST_ASSERT_EQUAL_UINT8(63, arduino_pin_pwm());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_intensity(125));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_led_driver);

    return UNITY_END();
}

#include <unity.h>
#include "led_driver.h"
#ifndef DEVENV
#include <Arduino.h>
#endif
#include "bsp_dio.h"

void test_led_driver(void)
{
    // Test for an uninitialized condition
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_state(LED_DRIVER_HIGH));

    led_driver_init();
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, double_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(OUTPUT, double_get_pin_mode());

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_state(LED_DRIVER_HIGH));
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, double_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_HIGH, bsp_dio_read(LED_PIN));

    double_invert_read_pin_state();
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_state(LED_DRIVER_HIGH));
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, double_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, bsp_dio_read(LED_PIN));
    double_invert_read_pin_state();

#ifndef DEVENV
    delay(2000);
#endif

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, led_driver_set_state(LED_DRIVER_LOW));
    TEST_ASSERT_EQUAL_UINT8(LED_PIN, double_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, bsp_dio_read(LED_PIN));

    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_state(0xF0));
}

#ifdef DEVENV
int main(void)
{
#else
void loop()
{
}

void setup()
{
    delay(2000);
#endif

    UNITY_BEGIN();

    RUN_TEST(test_led_driver);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}

#ifndef DEVENV
#include <Arduino.h>
#endif

#include "bsp.h"
#include <unity.h>
#include "led_driver.h"

static uint8_t pin = 13;

void test_uninitialized_led_driver(void)
{
    TEST_ASSERT_EQUAL_INT(LED_DRIVER_UNINITIALIZED, led_driver_set_state(LED_DRIVER_LOW));
}

void test_initialized_led_driver(void)
{
    led_driver_init(pin);

    TEST_ASSERT_EQUAL_UINT8(pin, bsp_get_pin_num());

    TEST_ASSERT_EQUAL_UINT8(pin, bsp_get_pin_num());
    TEST_ASSERT_EQUAL_UINT8(OUTPUT, bsp_get_pin_mode());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, bsp_get_pin_state());
}

void test_set_state_valid_arg(void)
{
    uint8_t state = LED_DRIVER_HIGH;
    TEST_ASSERT_EQUAL_INT(LED_DRIVER_OK, led_driver_set_state(state));
    TEST_ASSERT_EQUAL_UINT8(state, bsp_get_pin_state());
    TEST_ASSERT_EQUAL_UINT8(pin, bsp_get_pin_num());

#ifndef DEVENV
    delay(2000);
#endif

    state = LED_DRIVER_LOW;
    TEST_ASSERT_EQUAL_INT(LED_DRIVER_OK, led_driver_set_state(state));
    TEST_ASSERT_EQUAL_UINT8(state, bsp_get_pin_state());
    TEST_ASSERT_EQUAL_UINT8(pin, bsp_get_pin_num());
}

void test_set_state_invalid_arg(void)
{
    TEST_ASSERT_EQUAL_INT(LED_DRIVER_ERROR, led_driver_set_state(10));
}

void test_pin_port_error(void)
{
    bsp_set_pin_status(false);
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, led_driver_set_state(LED_DRIVER_HIGH));
    TEST_ASSERT_EQUAL_UINT8(pin, bsp_get_pin_num());
    bsp_set_pin_status(true);
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

    RUN_TEST(test_uninitialized_led_driver);
    RUN_TEST(test_initialized_led_driver);
    RUN_TEST(test_set_state_valid_arg);
    RUN_TEST(test_set_state_invalid_arg);
    RUN_TEST(test_pin_port_error);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}

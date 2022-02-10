#include <unity.h>
#include "terminal.h"
#include "led_driver.h"
#include "bsp_serial.h"

#ifndef DEVENV
#include <Arduino.h>
#endif

#define DONE_MSG "1 => done\n"
#define FAILED_MSG " => faild\n"
#define COMMAND_MSG "Enter the command [0: Off, 1: On]: "

void test_terminal_without_initialization(void)
{
    terminal_run();
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, double_get_led_init());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_ERROR, double_get_led_state());
    TEST_ASSERT_EQUAL_STRING("", double_get_serial_outbuf());
    TEST_ASSERT_FALSE(double_get_serial_init());
}

void test_terminal_init(void)
{
    terminal_init();
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_OK, double_get_led_init());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, double_get_led_state());
    TEST_ASSERT_TRUE(double_get_serial_init());
}

void test_terminal_waiting_on_user(void)
{
    terminal_run();
    TEST_ASSERT_EQUAL_STRING(COMMAND_MSG, double_get_serial_outbuf());
    terminal_run();
    TEST_ASSERT_EQUAL_STRING("", double_get_serial_outbuf());
    terminal_run();
    TEST_ASSERT_EQUAL_STRING("", double_get_serial_outbuf());

    double_set_serial_inbuf("\n");
    TEST_ASSERT_EQUAL_UINT8(1, bsp_serial_available());
    terminal_run();
    TEST_ASSERT_EQUAL_UINT8(0, bsp_serial_available());
    TEST_ASSERT_EQUAL_STRING("\n", double_get_serial_outbuf());
    terminal_run();
    TEST_ASSERT_EQUAL_STRING(COMMAND_MSG, double_get_serial_outbuf());
    terminal_run();
    TEST_ASSERT_EQUAL_STRING("", double_get_serial_outbuf());
}

void test_terminal_led_on(void)
{
    double_set_serial_inbuf("1");
    double_set_led_driver_status(LED_DRIVER_OK);
    TEST_ASSERT_EQUAL_UINT8(1, bsp_serial_available());
    terminal_run();
    TEST_ASSERT_EQUAL_UINT8(0, bsp_serial_available());
    TEST_ASSERT_EQUAL_STRING("1 => done\n", double_get_serial_outbuf());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_HIGH, double_get_led_state());

#ifndef DEVENV
    delay(2000);
#endif

    double_set_serial_inbuf("1");
    double_set_led_driver_status(LED_DRIVER_ERROR);
    TEST_ASSERT_EQUAL_UINT8(1, bsp_serial_available());
    terminal_run();
    TEST_ASSERT_EQUAL_UINT8(0, bsp_serial_available());
    TEST_ASSERT_EQUAL_STRING("1 => faild\n", double_get_serial_outbuf());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_HIGH, double_get_led_state());
}

void test_terminal_led_off(void)
{
    double_set_serial_inbuf("0");
    double_set_led_driver_status(LED_DRIVER_OK);
    TEST_ASSERT_EQUAL_UINT8(1, bsp_serial_available());
    terminal_run();
    TEST_ASSERT_EQUAL_UINT8(0, bsp_serial_available());
    TEST_ASSERT_EQUAL_STRING("0 => done\n", double_get_serial_outbuf());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, double_get_led_state());

    double_set_serial_inbuf("0");
    double_set_led_driver_status(LED_DRIVER_ERROR);
    TEST_ASSERT_EQUAL_UINT8(1, bsp_serial_available());
    terminal_run();
    TEST_ASSERT_EQUAL_UINT8(0, bsp_serial_available());
    TEST_ASSERT_EQUAL_STRING("0 => faild\n", double_get_serial_outbuf());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, double_get_led_state());
}

void test_terminal_invalid_input(void)
{
    terminal_run();
    TEST_ASSERT_EQUAL_STRING(COMMAND_MSG, double_get_serial_outbuf());
    double_set_serial_inbuf("p");
    TEST_ASSERT_EQUAL_UINT8(1, bsp_serial_available());
    TEST_ASSERT_EQUAL_STRING("", double_get_serial_outbuf());
    TEST_ASSERT_EQUAL_UINT8(LED_DRIVER_LOW, double_get_led_state());

    terminal_run();
    TEST_ASSERT_EQUAL_STRING("", double_get_serial_outbuf());
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

    RUN_TEST(test_terminal_without_initialization);
    RUN_TEST(test_terminal_init);
    RUN_TEST(test_terminal_waiting_on_user);
    RUN_TEST(test_terminal_led_on);
    RUN_TEST(test_terminal_led_off);
    RUN_TEST(test_terminal_invalid_input);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}

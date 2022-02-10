#include <string.h>
#include "bsp_serial.h"
#ifndef DEVENV
#include <Arduino.h>
#endif

#define IOBUF_SIZE 64

static char outbuf[IOBUF_SIZE] = "";
static char inbuf[IOBUF_SIZE] = "";
static char temp[IOBUF_SIZE] = "";
static bool serial_init = false;

void bsp_serial_begin(void)
{
    serial_init = true;
}

uint8_t bsp_serial_available(void)
{
    return strlen(inbuf);
}

char bsp_serial_read(void)
{
    char ch = inbuf[0];
    strcpy(inbuf, inbuf + 1);
    return ch;
}

void bsp_serial_print(const char *str)
{
    strcpy(outbuf, "");
    strncpy(outbuf, str, sizeof(outbuf) - 1);
}

void double_set_serial_inbuf(const char *str)
{
    strcpy(inbuf, "");
    strncpy(inbuf, str, sizeof(inbuf) - 1);
}

bool double_get_serial_init(void)
{
    return serial_init;
}

char *double_get_serial_outbuf(void)
{
    strcpy(temp, outbuf);
    strcpy(outbuf, "");
    return temp;
}

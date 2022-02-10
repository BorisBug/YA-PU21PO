#include "mmetro.h"
#include <stdlib.h>
#include <stdbool.h>

struct mmetro
{
    bool mu;
    uint32_t interval;
    uint32_t previous;
};

static bool initialized = false;
static bsp_interface_t bsp = {NULL};

void mmetro_init(bsp_interface_t *bsp_ptr)
{
    initialized = false;
    if ((bsp_ptr != NULL) && (bsp_ptr->malloc != NULL) && (bsp_ptr->micros != NULL) && (bsp_ptr->millis != NULL))
    {
        bsp.malloc = bsp_ptr->malloc;
        bsp.micros = bsp_ptr->micros;
        bsp.millis = bsp_ptr->millis;
        initialized = true;
    }
}

mmetro_t *mmetro_create(bool mu, uint32_t interval)
{
    mmetro_t *ptr = NULL;

    if (initialized && (interval > 0))
    {
        ptr = (mmetro_t *)bsp.malloc(sizeof(mmetro_t));

        if (ptr != NULL)
        {
            ptr->mu = mu;
            ptr->interval = interval;
            ptr->previous = mu ? bsp.millis() : bsp.micros();
        }
    }

    return ptr;
}

uint8_t mmetro_check(mmetro_t *metro)
{
    uint8_t status = MMETRO_ERROR;

    if (initialized && (metro != NULL))
    {
        status = MMETRO_NO;
        uint32_t now = (metro->mu) ? bsp.millis() : bsp.micros();
        uint32_t passed = now - metro->previous;

        if (metro->previous > now) // The timer register has been overflowed
        {
            passed = (0xFFFFFFFFu - metro->previous) + 1u + now;
        }

        if (passed >= metro->interval)
        {
            status = MMETRO_YES;
            metro->previous = now;
        }
    }

    return status;
}

void mmetro_reset(mmetro_t *metro)
{
    if (initialized && (metro != NULL))
    {
        metro->previous = (metro->mu) ? bsp.millis() : bsp.micros();
    }
}
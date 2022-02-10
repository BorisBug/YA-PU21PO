#include "RNGA.h"
#include <kinetis.h>

#define RNGA_CR_GO ((uint32_t)0x00000001)       // Mask for the GO field
#define RNGA_CR_HA ((uint32_t)0x00000002)       // Mask for the HA field
#define RNGA_CR_INTM ((uint32_t)0x00000004)     // Mask for the INTM field
#define RNGA_CR_SLP ((uint32_t)0x00000010)      // Mask for the SLP field
#define RNGA_SR_OREG_LVL ((uint32_t)0x0000FF00) // Mask for the OREG_LVL field

void rnga_init(void)
{
    SIM_SCGC6 |= SIM_SCGC6_RNGA; // enable RNGA clock
    RNG_CR |= RNGA_CR_GO;        // Random-data generation and loading into the OR register is enabled
    RNG_CR |= RNGA_CR_HA;        // Enables notification of security violations
    RNG_CR |= RNGA_CR_INTM;      // Error interrupt is masked
    RNG_CR |= RNGA_CR_SLP;       // Sleep mode
}

void rnga_start(void)
{
    RNG_CR &= ~RNGA_CR_SLP; // Normal mode
}

void rnga_seed(uint32_t entropy)
{
    RNG_ER = entropy; // Fill the entropy register with entropy value
}

uint32_t rnga_generate(uint32_t min, uint32_t max)
{
    uint32_t value = 0;
    if ((RNG_CR & RNGA_CR_SLP) == 0)
    {
        while ((RNG_SR & RNGA_SR_OREG_LVL) == 0)
        {
        }
        value = (min + (RNG_OR % (max - min)));
    }
    return value;
}

void rnga_stop(void)
{
    RNG_CR |= RNGA_CR_SLP; // Sleep mode
}

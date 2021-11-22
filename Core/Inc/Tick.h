#pragma once
#include <stdint.h>

namespace core
{
    void updateTick(uint32_t clockspeed, uint32_t frequency);
    void initTick(uint32_t clockspeed, uint32_t frequency);
    void delay(uint32_t ms);
    extern "C" void SysTick_Handler(void);
}

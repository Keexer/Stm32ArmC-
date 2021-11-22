#include "Tick.h"
#include <cassert>
#include "Interrupts.h"

namespace
{
  static volatile uint32_t msTick = 0;
}

namespace core
{
    void updateTick(uint32_t clockspeed, uint32_t frequency)
    {
      uint32_t ticks = clockspeed / frequency;
        /* Configure the SysTick to have interrupt in 1ms time basis*/
      assert((ticks - 1UL) < 0xFFFFFFUL);
      REMOVE_MACRO(SysTick)->RVR = ticks - 1UL;
      REMOVE_MACRO(SysTick)->CVR = 0UL;
    }

    void initTick(uint32_t clockspeed, uint32_t frequency)
    {
      uint32_t ticks = clockspeed / frequency;
      assert((ticks - 1UL) < 0xFFFFFFUL);
      REMOVE_MACRO(SysTick)->RVR = (uint32_t)(ticks - 1UL); /* set reload value register */
      REMOVE_MACRO(SysTick)->CVR = 0UL; /* Clear current count, any value writte will clear the register. Use 0 for readability */
      REMOVE_MACRO(SysTick)->CSR = (1UL << 2U) | (1UL << 1U) | 1UL; /* Clock source = Processor clock | Enable SysTick exception request (Interrupt) | Enable counter */

      core::configIrqPriority(core::SysTick_IRQ_Number, 0U, 0U);
    }
    
    void delay(uint32_t ms)
    {
      uint32_t start = msTick;
      while (msTick - start < ms);
    }

    extern "C" void SysTick_Handler(void)
    {
      msTick++;
    }
}
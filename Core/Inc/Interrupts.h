#pragma once

#include "Irq.h"
#include "Registers.h"

namespace core
{
    template <uint8_t preemptGroupBits, uint8_t subprioGroupBits>
    void configInterruptGroupPriority()
    {
        static_assert((preemptGroupBits + subprioGroupBits == 4U));
        constexpr uint32_t priorityGroup = 7UL - preemptGroupBits; // Set number of bits for preempt and subgroup priorities
        
        uint32_t reg_value = REMOVE_MACRO(SCB)->AIRCR; /* read old register configuration */
        reg_value &= ~(static_cast<uint32_t>((0xFFFFU << 16U) | (7U << 8U))); /* clear bits to change */
        reg_value |= (static_cast<uint32_t>(0x5FAUL) << 16U) | (priorityGroup << 8U); /* Insert write key and priority group */
        REMOVE_MACRO(SCB)->AIRCR = reg_value;
    }

    void configIrqPriority(core::Irq irq, uint32_t preemptPriority, uint32_t subgroupPriority);
}

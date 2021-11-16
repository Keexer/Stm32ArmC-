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
    // {
    //     const uint32_t priorityGroup = (REMOVE_MACRO(SCB)->AIRCR & (0x7L << 8U)) >> 8UL;
    //     constexpr uint32_t priorityBits = 4UL;

    //     const uint32_t preemptPriorityBits = ((7UL - priorityGroup) > priorityBits) ? priorityBits : static_cast<uint32_t>(7UL - priorityGroup);
    //     const uint32_t subPriorityBits = ((priorityGroup + priorityBits) < 7UL) ? 0UL : static_cast<uint32_t>((priorityGroup - 7UL) + priorityBits);

    //     assert(preemptPriority <= preemptPriorityBits);
    //     assert(subgroupPriority <= subPriorityBits);

    //     uint32_t priority (
    //         ((preemptPriority & static_cast<uint32_t>((1UL << (preemptPriorityBits)) - 1UL)) << subPriorityBits) |
    //         ((subgroupPriority & static_cast<uint32_t>((1UL << (subPriorityBits)) - 1UL))));
            
    //     if ((int32_t)(irq) >= 0)
    //     {
    //         REMOVE_MACRO(NVIC)->IPR[((uint32_t)irq)] = static_cast<uint8_t>((priority << (8U - priorityBits)) & static_cast<uint32_t>(0xFFUL));
    //     }
    //     else
    //     {
    //         // Bit shift magic, -1 (SysTick irq) will result in element 11 (little endianess, MSB)
    //         REMOVE_MACRO(SCB)->SHPR[(static_cast<uint32_t>(irq) & 0xFUL)-4UL] =
    //             static_cast<uint8_t>((priority << (8U - priorityBits)) & static_cast<uint32_t>(0xFFUL));
    //     }
    // }
}

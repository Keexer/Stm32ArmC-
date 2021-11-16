#include "Interrupts.h"
#include "Registers.h"

namespace core
{
    /**
     * Sets the amount of Group and Subgroups priorities.
     * For STM32 only 4 bits are used of the eight available.
     * Gives bits [4,0], [3,1], [2,2], [1,3], [0,4] to be used for (MSB) group Priority and (LSB) Subgroup priority.
     * E.g [3,1] gives 3 bits (8) possible group priorities, and 1 bit (2) possible subgroup priority within the same group priority.
     * Hard coded to 4 bit group priorities.
     */
    void setInterruptGroupPriority()
    {
    constexpr uint32_t priorityGroup = 0x03; // 4 bits for pre-emption priority, 0 bits for subpriority 
    volatile uint32_t* const SCB_AIRCR = (volatile uint32_t*)0xE000ED0C;        // Application interrupt and reset control register
    
    uint32_t reg_value  =  *SCB_AIRCR;                                                   /* read old register configuration    */
    reg_value &= ~((uint32_t)((0xFFFF << 16) | (7 << 8))); /* clear bits to change               */
    reg_value  =  (reg_value                                   |
                    ((uint32_t)0x5FAUL << 16) |
                    (priorityGroup << 8U)  );              /* Insert write key and priority group */
    *SCB_AIRCR =  reg_value;
    }


    void setIrqPriorityConfig(core::Irq irq, uint32_t priority)
    {
    constexpr uint32_t priorityBits = 4UL;
        
    if ((int32_t)(irq) >= 0)
    {
        REMOVE_MACRO(NVIC_Type)* nvic = (REMOVE_MACRO(NVIC_Type)*)0xE000E100;
        nvic->ipr[((uint32_t)irq)] = (uint8_t)((priority << (8U - priorityBits)) & (uint32_t)0xFFUL);
    }
    else
    {
        SHPR* shpr = (SHPR*)(0xE000ED18);
        // Bit shift magic, -1 (SysTick irq) will result in element 11 (little endianess, MSB)
        shpr->shpr[(((uint32_t)irq) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - priorityBits)) & (uint32_t)0xFFUL);
    }
    }

}

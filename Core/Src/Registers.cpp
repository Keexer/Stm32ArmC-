#include "Registers.h"

constexpr uint32_t SCB_Base = 0xE000ED00;
constexpr uint32_t SysTick_Base = 0xE000E010;
constexpr uint32_t NVIC_Base = 0xE000E100UL;
constexpr uint32_t RCC_Base = 0x40023800;

REMOVE_MACRO(SCB_Type)* REMOVE_MACRO(SCB) = reinterpret_cast<REMOVE_MACRO(SCB_Type)*>(SCB_Base);
REMOVE_MACRO(SysTick_Type)* REMOVE_MACRO(SysTick) = reinterpret_cast<REMOVE_MACRO(SysTick_Type)*>(SysTick_Base);
REMOVE_MACRO(NVIC_Type)* REMOVE_MACRO(NVIC) = reinterpret_cast<REMOVE_MACRO(NVIC_Type)*>(NVIC_Base);
REMOVE_MACRO(RCC_Type)* REMOVE_MACRO(RCC) = reinterpret_cast<REMOVE_MACRO(RCC_Type)*>(RCC_Base);
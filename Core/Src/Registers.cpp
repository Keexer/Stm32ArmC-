#include "Registers.h"

constexpr uint32_t SCB_Base = 0xE000ED00;
constexpr uint32_t SysTick_Base = 0xE000E010;
constexpr uint32_t NVIC_Base = 0xE000E100UL;
constexpr uint32_t RCC_Base = 0x40023800;
constexpr uint32_t GPIO_A_Base = 0x40020000;
constexpr uint32_t GPIO_B_Base = 0x40020400;
constexpr uint32_t GPIO_C_Base = 0x40020800;
constexpr uint32_t GPIO_D_Base = 0x40020C00;
constexpr uint32_t GPIO_E_Base = 0x40021000;
constexpr uint32_t GPIO_F_Base = 0x40021400;
constexpr uint32_t GPIO_G_Base = 0x40021800;
constexpr uint32_t GPIO_H_Base = 0x40021C00;

REMOVE_MACRO(SCB_Type)* REMOVE_MACRO(SCB) = reinterpret_cast<REMOVE_MACRO(SCB_Type)*>(SCB_Base);
REMOVE_MACRO(SysTick_Type)* REMOVE_MACRO(SysTick) = reinterpret_cast<REMOVE_MACRO(SysTick_Type)*>(SysTick_Base);
REMOVE_MACRO(NVIC_Type)* REMOVE_MACRO(NVIC) = reinterpret_cast<REMOVE_MACRO(NVIC_Type)*>(NVIC_Base);
REMOVE_MACRO(RCC_Type)* REMOVE_MACRO(RCC) = reinterpret_cast<REMOVE_MACRO(RCC_Type)*>(RCC_Base);
REMOVE_MACRO(GPIO_Type)* REMOVE_MACRO(GPIO)[8] = {reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_A_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_B_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_C_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_D_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_E_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_F_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_G_Base),
                                                  reinterpret_cast<REMOVE_MACRO(GPIO_Type)*>(GPIO_H_Base)};
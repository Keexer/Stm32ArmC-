#pragma once
#include <stdint.h>
#include <string>

#define REMOVE_MACRO(a) a##_Temp

using Reg32 = volatile uint32_t;
using Reg8 = volatile uint8_t;
using Reg8c = const volatile uint8_t;
using Reg32c = const volatile uint32_t;

struct REMOVE_MACRO(SCB_Type)
{
  Reg32c CPUID;         /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  Reg32 ICSR;           /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  Reg32 VTOR;           /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  Reg32 AIRCR;          /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  Reg32 SCR;            /*!< Offset: 0x010 (R/W)  System Control Register */
  Reg32 CCR;            /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  Reg8 SHPR[12U];        /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  Reg32 SHCSR;          /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  Reg32 CFSR;           /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  Reg32 HFSR;           /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  Reg32 DFSR;           /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  Reg32 MMFAR;          /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  Reg32 BFAR;           /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  Reg32 AFSR;           /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  Reg32c PFR[2U];       /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  Reg32c DFR;           /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  Reg32c AFR;           /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  Reg32c MMFR[4U];      /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  Reg32c ISAR[5U];      /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  Reg32c RESERVED0[5U];
  Reg32 CPACR;          /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
};

struct REMOVE_MACRO(SysTick_Type)
{
  Reg32 CSR;
  Reg32 RVR;
  Reg32 CVR;
  Reg32 CALIB;
};

struct REMOVE_MACRO(NVIC_Type)
{
  Reg32 ISER[8U];
  uint32_t reserved0[24U];
  Reg32 ICER[8U];
  uint32_t reserved1[24U];
  Reg32 ISPR[8U];
  uint32_t reserved2[24U];
  Reg32 ICPR[8U];
  uint32_t reserved3[24U];
  Reg32c IABR[8U];
  uint32_t reserved4[56U];
  Reg8 IPR[240U];
  uint32_t reserved5[644U];
  Reg32 STIR; // EF00
};

struct SHPR
{
  Reg8 shpr[12U];
};

constexpr uint32_t SCB_Base = 0xE000ED00;
constexpr uint32_t SysTick_Base = 0xE000E010;
constexpr uint32_t NVIC_Base = 0xE000E100UL;

static REMOVE_MACRO(SCB_Type)* REMOVE_MACRO(SCB) = reinterpret_cast<REMOVE_MACRO(SCB_Type)*>(SCB_Base);
static REMOVE_MACRO(SysTick_Type)* REMOVE_MACRO(SysTick) = reinterpret_cast<REMOVE_MACRO(SysTick_Type)*>(SysTick_Base);
static REMOVE_MACRO(NVIC_Type)* REMOVE_MACRO(NVIC) = reinterpret_cast<REMOVE_MACRO(NVIC_Type)*>(NVIC_Base);

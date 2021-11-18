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

struct REMOVE_MACRO(RCC_Type)
{
  Reg32 CR;                     /* Offset: 0x000 Clock Control Register */
  Reg32 PLLCFGR;                /* Offset: 0x004 PLL Configuration Register  */
  Reg32 CFGR;                   /* Offset: 0x008 Clock Configuration Register */
  Reg32 CIR;                    /* Offset: 0x00C Clock Interrupt Register */
  Reg32 AHB1RSTR;               /* Offset: 0x01C AHB1 Peripheral Reset Register */
  Reg32 AHB2RSTR;               /* Offset: 0x014 AHB2 Peripheral Reset Register */
  Reg32 AHB3RSTR;               /* Offset: 0x018 AHB3 Peripheral Reset Register */
  const uint32_t reserved0;     /* Offset: 0x01C */
  Reg32 APB1RSTR;               /* Offset: 0x020 APB1 Peripheral Reset Register */
  Reg32 APB2RSTR;               /* Offset: 0x024 APB2 Peripheral Reset Register */
  const uint32_t reserved1[2];  /* Offset: 0x028 */
  Reg32 AHB1ENR;                /* Offset: 0x030 AHB1 Peripheral Clock Enable Register */
  Reg32 AHB2ENR;                /* Offset: 0x034 AHB2 Peripheral Clock Enable Register */
  Reg32 AHB3ENR;                /* Offset: 0x038 AHB3 Peripheral Clock Enable Register */
  const uint32_t reserved2;     /* Offset: 0x03C */
  Reg32 APB1ENR;                /* Offset: 0x040 APB1 Peripheral Clock Enable Register */
  Reg32 APB2ENR;                /* Offset: 0x044 APB2 Peripheral Clock Enable Register */
  const uint32_t reserved3[2];  /* Offset: 0x048 */
  Reg32 AHB1LPENR;              /* Offset: 0x050 AHB1 Peripheral Clock Enable In Low Power Mode Register */
  Reg32 AHB2LPENR;              /* Offset: 0x054 AHB2 Peripheral Clock Enable In Low Power Mode Register */
  Reg32 AHB3LPENR;              /* Offset: 0x058 AHB3 Peripheral Clock Enable In Low Power Mode Register */
  const uint32_t reserved4;     /* Offset: 0x05C */
  Reg32 APB1LPENR;              /* Offset: 0x060 APB1 Peripheral Clock Enable In Low Power Mode Register */
  Reg32 APB2LPENR;              /* Offset: 0x064 APB2 Peripheral Clock Enable In Low Power Mode Register */
  const uint32_t reserved5[2];  /* Offset: 0x068 */
  Reg32 BDCR;                   /* Offset: 0x070 Backup Domain Control Register */
  Reg32 CSR;                    /* Offset: 0x074 Clock Control & Status Register */
  const uint32_t reserved6[2];  /* Offset: 0x078 */
  Reg32 SSCGR;                  /* Offset: 0x080 Spread Spectrum Clock Generation Register */
  Reg32 PLLI2SCFGR;             /* Offset: 0x084 PLLI2S configuration Register */
  const uint32_t reserved7;     /* Offset: 0x088 */
  Reg32 DCKCFGR;                /* Offset: 0x08C Dedicated Clocks Configuration Register */
  Reg32 CKGATENR;               /* Offset: 0x090 Clocks Gated Enable Register */
  Reg32 DCKCFGR2;               /* Offset: 0x094 Dedicated Clocks Configuration Register */
};

struct REMOVE_MACRO(GPIO_Type)
{
  Reg32 MODER;    /* Offset: 0x00 Port Mode Register */
  Reg32 OTYPER;   /* Offset: 0x04 Port Output Type Register */
  Reg32 OSPEEDR;  /* Offset: 0x08 Port Output Speed Register */
  Reg32 PUPDR;    /* Offset: 0x0C Port Pull-Up/Pull-Down Register */
  Reg32 IDR;      /* Offset: 0x10 Port Input Data Register */
  Reg32 ODR;      /* Offset: 0x14 Port Output Data Register */
  Reg32 BSRR;     /* Offset: 0x18 Port Bit Set/Reset Register */
  Reg32 LCKR;     /* Offset: 0x1C Port Configuration Lock Register */
  Reg32 AFRL;     /* Offset: 0x20 Alternate Function Low Register */
  Reg32 AFRH;     /* Offset: 0x24 Alternate Function High Register */
};

struct SHPR
{
  Reg8 shpr[12U];
};

extern REMOVE_MACRO(SCB_Type)* REMOVE_MACRO(SCB);
extern REMOVE_MACRO(SysTick_Type)* REMOVE_MACRO(SysTick);
extern REMOVE_MACRO(NVIC_Type)* REMOVE_MACRO(NVIC);
extern REMOVE_MACRO(RCC_Type)* REMOVE_MACRO(RCC);
extern REMOVE_MACRO(GPIO_Type)* REMOVE_MACRO(GPIO)[8];

#pragma once
#include <stdint.h>
#include <string>

#define REMOVE_MACRO(a) a##_Temp

constexpr uint32_t NVIC_Base = 0xE000E100UL;

struct REMOVE_MACRO(NVIC_Type)
{
  volatile uint32_t iser[8U];
  uint32_t reserved0[24U];
  volatile uint32_t icer[8U];
  uint32_t reserved1[24U];
  volatile uint32_t ispr[8U];
  uint32_t reserved2[24U];
  volatile uint32_t icpr[8U];
  uint32_t reserved3[24U];
  volatile uint32_t iabr[8U];
  uint32_t reserved4[56U];
  volatile uint8_t ipr[240U];
  uint32_t reserved5[644U];
  volatile uint32_t stir;
};

static REMOVE_MACRO(NVIC_Type)* REMOVE_MACRO(NVIC) = reinterpret_cast<REMOVE_MACRO(NVIC_Type)*>(NVIC_Base);

struct SHPR
{
  volatile uint8_t shpr[12U];
};

#pragma once

static core::IOPin led1, led2, led3;

static inline void initLeds()
{
  led1 = core::configureOutput(core::PORT_B, core::PIN_0, core::PUSH_PULL, core::NO_PULL);
  led2 = core::configureOutput(core::PORT_B, core::PIN_7, core::PUSH_PULL, core::NO_PULL);
  led3 = core::configureOutput(core::PORT_B, core::PIN_14, core::PUSH_PULL, core::NO_PULL);
}

static inline void setLeds()
{
  core::setOutput(led1);
  core::setOutput(led2);
  core::setOutput(led3);
}

static inline void clearLeds()
{
  core::clearOutput(led1);
  core::clearOutput(led2);
  core::clearOutput(led3);
}

static inline void enableDataInstructionCachePrefetch()
{
  static constexpr uint32_t ICEN = 1 << 9; // Enable instruction cache
  static constexpr uint32_t DCEN = 1 << 10; // Enable data cache
  static constexpr uint32_t PRFTEN = 1 << 8; // Enable prefetch
  REMOVE_MACRO(FLASH)->ACR |= ICEN | DCEN | PRFTEN;
}
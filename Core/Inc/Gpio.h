#pragma once

#include <stdint.h>

namespace core
{

  enum Port : uint32_t
  {
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H
  };

  enum Pin : uint32_t
  {
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15
  };

  enum PinMode : uint32_t
  {
    INPUT = 0,
    OUTPUT,
    ALTERNATE_FUNCTION,
    ANALOG
  };

  enum PullMode : uint32_t
  {
    NO_PULL = 0,
    PULL_UP,
    PULL_DOWN
  };

  enum Speed : uint32_t
  {
    LOW_SPEED = 0,
    MEDIUM_SPEED,
    FAST_SPEED,
    HIGH_SPEED
  };

  enum OutputType : uint32_t
  {
    PUSH_PULL = 0,
    OPEN_DRAIN
  };

  struct IOPin
  {
    Port port;
    Pin pin;
  };

  IOPin configureInput(Port port, Pin pin, PullMode mode, Speed speed = LOW_SPEED);
  IOPin configureOutput(Port port, Pin pin, OutputType type, PullMode mode, Speed speed = LOW_SPEED);
  void setOutput(IOPin pin);
  void clearOutput(IOPin pin);
  bool readInput(IOPin pin);

}

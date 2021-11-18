#pragma once

#include <stdint.h>

namespace core
{

  enum class Port
  {
    PORT_A,
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
    PIN_14
  };

  void configureInput(Port port, Pin pin);
  void configureOutput(Port port, Pin pin);

}

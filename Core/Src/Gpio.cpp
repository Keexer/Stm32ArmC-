#include "Gpio.h"

namespace
{
  static void enableGpioPort(core::Port port)
  {
    if (!isGpioPortEnabled)
    {

    }
  }

  static bool isGpioPortEnabled(core::Port port)
  {
    
  }
}

namespace core
{

  void configureInput(Port port, Pin pin)
  {
    enableGpioPort(port);
  }

  void configureOutput(Port port, Pin pin)
  {
    enableGpioPort(port);
  }

}

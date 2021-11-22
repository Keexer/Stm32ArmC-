#include "Gpio.h"
#include "Registers.h"

namespace
{
  static bool isGpioPortEnabled(core::Port port)
  {
    uint32_t portsEnabled = REMOVE_MACRO(RCC)->AHB1LPENR & 0xFFU;
    return (portsEnabled & (1U << port)) == port;
  }
  
  static void enableGpioPort(core::Port port)
  {
    if (!isGpioPortEnabled(port))
    {
      REMOVE_MACRO(RCC)->AHB1ENR |= (1U << port);
    }
  }

  static void setPinMode(REMOVE_MACRO(GPIO_Type)* gpio, core::Pin pin, core::PinMode pinMode, core::PullMode pullMode,
                          core::Speed speed, core::OutputType type)
  {
    gpio->MODER &= ~(0x3U << (pin * 2));
    gpio->MODER |= pinMode << (pin * 2);
    gpio->PUPDR &= ~(0x3U << (pin * 2));
    gpio->PUPDR |= pullMode << (pin * 2);
    gpio->OSPEEDR &= ~(0x3U << (pin * 2));
    gpio->OSPEEDR |= speed << (pin * 2);
    gpio->OTYPER &= ~(1U << pin);
    gpio->OTYPER |= type << pin;
  }
}

namespace core
{

  IOPin configureInput(Port port, Pin pin, PullMode mode, Speed speed)
  {
    enableGpioPort(port);
    setPinMode(REMOVE_MACRO(GPIO)[port], pin, INPUT, mode, speed, PUSH_PULL);
    return IOPin{port, pin};
  }

  IOPin configureOutput(Port port, Pin pin, OutputType type, PullMode pullMode, Speed speed)
  {
    enableGpioPort(port);
    setPinMode(REMOVE_MACRO(GPIO)[port], pin, OUTPUT, pullMode, speed, type);
    return IOPin{port, pin};
  }

  void setOutput(IOPin pin)
  {
    REMOVE_MACRO(GPIO)[pin.port]->ODR |= 1 << pin.pin;
  }

  void clearOutput(IOPin pin)
  {
    REMOVE_MACRO(GPIO)[pin.port]->ODR &= ~(1 << pin.pin);
  }

  bool readInput(IOPin pin)
  {
    const volatile bool value = (REMOVE_MACRO(GPIO)[pin.port]->IDR & (1 << pin.pin)) >> pin.pin;
    return value;
  }

}

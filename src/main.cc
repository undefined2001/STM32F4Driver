#include "stm32f446xx.h"
#include "gpio.hh"
#include "rcc.hh"

using hardware::gpio;
using hardware::rcc;

gpio led{gpio::create(GPIOA, gpio::pins::pin5)};

int main()
{
    rcc::enable_gpio(GPIOA);
    led.set_mode(gpio::mode::output);

    for (;;)
    {
        led.set_value(gpio::value::high);
        for (int i = 0; i < 500000; i++)
            ;
        led.set_value(gpio::value::low);
        for (int i = 0; i < 500000; i++)
            ;
    }

    return 0;
}
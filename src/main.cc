#include "stm32f446xx.h"
#include "gpio.hh"
#include "rcc.hh"

using hardware::gpio;
using hardware::rcc;

gpio led{gpio::create(GPIOA, gpio::pins::pin5)};

int main()
{
    rcc::enable_gpio(GPIOA);

    led.config(gpio::mode::output, gpio::otype::push_pull, gpio::pupd::none, gpio::ospeed::high);

    for (;;)
    {
        led.toggle();
        for (int i = 0; i < 500000; i++)
            ;
    }

    return 0;
}
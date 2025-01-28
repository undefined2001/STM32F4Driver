#ifndef __RCC_HH__
#define __RCC_HH__
#include "stm32f446xx.h"

namespace hardware
{
    class rcc
    {
    public:
        static void enable_gpio(GPIO_TypeDef *port);
    };
}

#endif
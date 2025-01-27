#ifndef __RCC_H__
#define __RCC_H__
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
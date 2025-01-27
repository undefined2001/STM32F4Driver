#ifndef __GPIO_HH__
#define __GPIO_HH__

#include "stm32f446xx.h"

#define REG_MSK_2BITS(pos) (~(3u << (pos)))

namespace hardware
{
    class gpio
    {
    public:
        enum class mode // enum for all the mode of stm32f4
        {
            input = 0u,
            output = 1u,
            altfn = 2u,
            analog = 3u
        };
        enum class pupd // enum for all the pullup/down options of stm32f4
        {
            nopupd = 0u,
            pullup = 1u,
            pulldown = 2u,

        };
        enum class otype // enum for all the otype for stm32f4
        {
            open_drain = 0u,
            push_pull = 1u
        };
        enum class ospeed // enum for all the ospeed options for stm32f4
        {
            low = 0u,
            medium = 1u,
            fast = 2u,
            high = 3u
        };

        enum class value // enum for stm32f4 pin state
        {
            low = 0u,
            high = 1u
        };

        enum class pins
        {
            pin0 = 0u,
            pin1 = 1u,
            pin2 = 2u,
            pin3 = 3u,
            pin4 = 4u,
            pin5 = 5u,
            pin6 = 6u,
            pin7 = 7u,
            pin8 = 8u,
            pin9 = 9u,
            pin10 = 10u,
            pin11 = 11u,
            pin12 = 12u,
            pin13 = 13u,
            pin14 = 14u,
            pin15 = 15u,

        };

    public:
        static gpio create(GPIO_TypeDef *port, pins pin);
        void set_mode(mode _m);
        void set_value(value _v);

    private:
        GPIO_TypeDef *m_port;
        uint8_t m_pin;
        gpio(GPIO_TypeDef *port, pins pin);
    };
}

#endif
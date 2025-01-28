#ifndef __GPIO_HH__
#define __GPIO_HH__

#include "stm32f446xx.h"
#include "common.hh"

namespace hardware
{
    class gpio
    {
    public:
        enum class mode : uint32_t
        {
            input = 0b00,
            output = 0b01,
            alternate = 0b10,
            analog = 0b11
        };
        enum class pupd : uint32_t
        {
            none = 0b00,
            pullup = 0b01,
            pulldown = 0b10,
            reserved = 0b11
        };
        enum class ospeed : uint32_t
        {
            low = 0b00,    // Low speed
            medium = 0b01, // Medium speed
            fast = 0b10,   // High speed
            high = 0b11    // Very high speed
        };
        enum class otype : uint32_t
        {
            push_pull = 0,
            open_drain = 1
        };
        enum class value : uint32_t
        {
            low = 0,
            high = 1
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

        static gpio create(GPIO_TypeDef *port, pins pin);

        void config(mode _m, otype _ot, pupd _p, ospeed _os);
        void set_mode(mode _m);
        void set_pupd(pupd _p);
        void set_otype(otype _ot);
        void set_ospeed(ospeed _os);
        void set_value(value _v);
        void toggle();
        value read() const;

    private:
        gpio(GPIO_TypeDef *port, pins pin);
        GPIO_TypeDef *m_port;
        uint32_t m_pin;
    };

}

#endif
#include "gpio.hh"

using namespace hardware;

gpio::gpio(GPIO_TypeDef *port, pins pin) : m_port(port), m_pin(static_cast<uint32_t>(pin)) {}

gpio gpio::create(GPIO_TypeDef *port, pins pin)
{
    return gpio(port, pin);
}

void gpio::set_mode(mode _m)
{
    this->m_port->MODER &= REG_MSK_2BITS(this->m_pin * 2);
    this->m_port->MODER |= static_cast<uint32_t>(_m) << (this->m_pin * 2);
}

void gpio::set_value(value _v)
{
    if (_v == value::high)
    {
        this->m_port->BSRR |= 1 << this->m_pin;
    }
    else if (_v == value::low)
    {
        this->m_port->BSRR |= 1 << (this->m_pin + 16);
    }
}
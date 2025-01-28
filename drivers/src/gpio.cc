#include "gpio.hh"

using namespace hardware;

gpio gpio::create(GPIO_TypeDef *port, pins pin)
{
    return gpio(port, pin);
}

// Implementation
gpio::gpio(GPIO_TypeDef *port, pins pin) : m_port(port), m_pin(static_cast<uint32_t>(pin))
{
    if (m_port == nullptr || m_pin > 15)
    {
        // Handle error
    }
}

void gpio::set_mode(mode _m)
{
    uint32_t mask = 0b11 << (m_pin * 2);
    CLEAR_BITS(m_port->MODER, mask);
    SET_BITS(m_port->MODER, mask, static_cast<uint32_t>(_m) << (m_pin * 2));
}

void gpio::set_pupd(pupd _p)
{
    uint32_t mask = 0b11 << (m_pin * 2);
    CLEAR_BITS(m_port->PUPDR, mask);
    SET_BITS(m_port->PUPDR, mask, static_cast<uint32_t>(_p) << (m_pin * 2));
}

void gpio::set_otype(otype _ot)
{
    CLEAR_BITS(m_port->OTYPER, 1 << m_pin);
    SET_BITS(m_port->OTYPER, 1 << m_pin, static_cast<uint32_t>(_ot) << m_pin);
}

void gpio::set_ospeed(ospeed _os)
{
    // Clear the 2 bits corresponding to the pin's position in the OSPEEDR register
    CLEAR_BITS(m_port->OSPEEDR, (1 << m_pin * 2));

    // Set the new output speed for the pin
    m_port->OSPEEDR |= SCAST_UINT(_os) << (m_pin * 2);
}

void gpio::config(mode _m, otype _ot, pupd _p, ospeed _os)
{
    set_mode(_m);
    set_otype(_ot);
    set_pupd(_p);
    set_ospeed(_os);
}

void gpio::set_value(value _v)
{
    m_port->BSRR = (_v == value::high) ? (1 << m_pin) : (1 << (m_pin + 16));
}

void gpio::toggle()
{
    m_port->ODR ^= (1 << m_pin);
}

gpio::value gpio::read() const
{
    return (m_port->IDR & (1 << m_pin)) ? value::high : value::low;
}
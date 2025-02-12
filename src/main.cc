#include "stm32f446xx.h"

#define MPU_ADDR 0x77
#define MPU_WHOAMI_REG 0xD0

void i2c_init();
void i2c_gpio_init();
void i2c_gpio_init();
void i2c_send_byte(uint8_t data);
uint8_t i2c_recv_byte();
void i2c_send_addr(uint8_t addr, uint8_t rw);
void i2c_start();
void i2c_stop();

uint8_t res;

int main()
{
    i2c_gpio_init();
    i2c_init();
    i2c_start();
    i2c_send_addr(MPU_ADDR, 0x0U);
    i2c_send_byte(MPU_WHOAMI_REG);
    i2c_stop();

    i2c_start();
    i2c_send_addr(MPU_ADDR, 0x1U);
    res = i2c_recv_byte();
    i2c_stop();

    while (true)
    {
    }

    return 0;
}
void i2c_gpio_init()
{
    /* Enable GPIOB clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* Configure PB8 (SCL) and PB9 (SDA) as Alternate Function */
    GPIOB->MODER &= ~(GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
    GPIOB->MODER |= (GPIO_MODER_MODE8_1 | GPIO_MODER_MODE9_1); /* AF mode */

    /* Enable pull-up resistors for PB8 and PB9 */
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPD8_0 | GPIO_PUPDR_PUPD9_0); /* Pull-up */

    /* Set PB8 and PB9 as open-drain */
    GPIOB->OTYPER |= (GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);

    /* Set high speed for PB8 and PB9 */
    GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9);

    /* Set PB8 and PB9 to AF4 (I2C1) */
    GPIOB->AFR[1] &= ~((0xF << GPIO_AFRH_AFSEL8_Pos) | (0xF << GPIO_AFRH_AFSEL9_Pos));
    GPIOB->AFR[1] |= ((0x4 << GPIO_AFRH_AFSEL8_Pos) | (0x4 << GPIO_AFRH_AFSEL9_Pos));
}

void i2c_init()
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; /*Enabling I2C clock*/

    /*Reseting I2C peripheral*/
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    /*Disabling I2C Peripheral*/
    I2C1->CR1 &= ~I2C_CR1_PE;

    /*Setting the Bus Frequency*/
    I2C1->CR2 |= 16U << I2C_CR2_FREQ_Pos;

    /*Setting CCR value*/
    I2C1->CCR = 80U;

    /*Setting TRISE*/
    I2C1->TRISE = 17;

    /*Enabling I2C Peripheral*/
    I2C1->CR1 |= I2C_CR1_PE;

    /*Enabling ACK*/
    I2C1->CR1 |= I2C_CR1_ACK;
}

void i2c_start()
{
    /* Generate START condition */
    I2C1->CR1 |= I2C_CR1_START;

    /* Wait until START condition is generated */
    while (!(I2C1->SR1 & I2C_SR1_SB))
        ;
}

void i2c_send_byte(uint8_t data)
{
    while (!(I2C1->SR1 & I2C_SR1_TXE))
        ;
    I2C1->DR = data;
}

void i2c_send_addr(uint8_t addr, uint8_t rw)
{
    /* Send the 7-bit address + Read/Write bit */
    I2C1->DR = (addr << 1U) | (rw & 0x1U);

    /* Wait until address is acknowledged */
    while (!(I2C1->SR1 & I2C_SR1_ADDR))
        ;

    /* Clear ADDR flag by reading SR1 and SR2 */
    (void)I2C1->SR1;
    (void)I2C1->SR2;
}

void i2c_stop()
{

    I2C1->CR1 |= I2C_CR1_STOP;
}

uint8_t i2c_recv_byte()
{
    I2C1->CR1 &= ~I2C_CR1_ACK;
    while (!(I2C1->SR1 & I2C_SR1_RXNE))
        ;
    return I2C1->DR;
}
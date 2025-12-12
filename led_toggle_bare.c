//stm32f4 series
#include <stdint.h>
#define PERIPH_BASE       0x40000000U
#define AHB1_OFFSET       0x00020000U
#define AHB1_BASE         (PERIPH_BASE + AHB1_OFFSET)
#define GPIOA_BASE        (AHB1_BASE + 0x0000U)
#define RCC_BASE          (PERIPH_BASE + 0x00023800U)
#define RCC_AHB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x30U))
#define GPIOA_MODER       (*(volatile uint32_t *)(GPIOA_BASE + 0x00U))
#define GPIOA_ODR         (*(volatile uint32_t *)(GPIOA_BASE + 0x14U))
#define GPIOAEN           (1U << 0)
#define PIN5              (1U << 5)
static void delay(volatile uint32_t t)
{
    while(t--) { }
}
int main(void)
{
    /* Enable clock for GPIOA */
    RCC_AHB1ENR |= GPIOAEN;
    delay(1000);   // small wait after enabling clock

    //Set PA5 → OUTPUT mode
      // MODER5 = 01 → bits 11:10

    GPIOA_MODER &= ~(3U << (5 * 2));   // clear bits
    GPIOA_MODER |=  (1U << (5 * 2));   // set output mode

    while(1)
    {
        GPIOA_ODR ^= PIN5; // toggle PA5
        delay(100000);
    }
}

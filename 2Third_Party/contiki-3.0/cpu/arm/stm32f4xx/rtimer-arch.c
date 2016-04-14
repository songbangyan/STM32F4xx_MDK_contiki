#include <contiki.h>
#include <stm32f4xx.h>
#include <rtimer-arch.h>
#include <debug-uart.h>

#include <stdio.h>

#define PRESCALER ( MCK / 2 / RTIMER_ARCH_SECOND - 1 )

void
TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__ ((interrupt));

void
rtimer_arch_init(void)
{
	/* we're using TIM14 output compare mode here.
	 * TIM ticks every 1e-4 seconds */

	/* enable TIM14 clock */
	RCC->APB1ENR |= (1 << 8);

	/* prescaler, autoreload value, reload mode - immediate */
	TIM14->PSC = PRESCALER;
	TIM14->ARR = 0xffff; 
	TIM14->EGR |= (1 << 0);

	/* set channel 1 output compare mode */
	/* disable channel 1, reset output compare mode bits */
	TIM14->CCER &= ~(1 << 0);
	TIM14->CCMR1 &= ~((7 << 4) | (3 << 0));
	TIM14->CCMR1 |= ((1 < 0) | (1 << 4));
	
	/* polarity high */
	TIM14->CCER &= ~(1 << 1);
	
  /* capture/compare value */
	TIM14->CCR1 = 0;

	/* output enable */
	TIM14->CCER |= (1 << 0);	

	/* TIM14 interrupt has position 45 in nvic vector table,
	 * so it's bit 13 in NVIC->ISER1 - let's enable it */
	NVIC->ISER[1] |= (1 << 13);

	/* compare interrupt enable, update interrupt disable */
	TIM14->DIER |= (1 << 1);
	TIM14->DIER &= ~(1 << 0);

	/* enable counter */
	TIM14->CR1 |= (1 << 0);
}

rtimer_clock_t
rtimer_arch_now(void)
{
	return TIM14->CNT;
}

void
rtimer_arch_schedule(rtimer_clock_t time)
{
	printf("rtimer_arch_schedule(%u)\n", time);

	TIM14->CCR1 = time;
	printf("TIM14->CCR1=%u, time=%u\n", (unsigned int)TIM14->CCR1, (unsigned int)time);

	/* enable timer */
	TIM14->CR1 |= (1 << 0);
}

void
TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	/* disable TIM14 interrupts */
	TIM14->DIER &= ~(1 << 1);

	TIM14->SR &= ~(1 << 1);

	printf("Handling interrupt, TIM14->CNT=%u\n", (unsigned int)TIM14->CNT);

	rtimer_run_next();

	/* enable TIM14 interrupts */
	TIM14->DIER |= (1 << 1);
}

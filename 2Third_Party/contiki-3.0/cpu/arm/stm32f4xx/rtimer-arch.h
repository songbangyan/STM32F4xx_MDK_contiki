/**
 * \file
 *         Header file for the STM32F4xx rtimer arch dependent code
 * \author
 *         Radek Krahl <radek@krahl.pl>
 */

#ifndef __RTIMER_ARCH_H__
#define __RTIMER_ARCH_H__

#include "sys/rtimer.h"

/* our timer ticks every 1e-4 second */
#define RTIMER_ARCH_SECOND (10000)

void rtimer_arch_init(void);

rtimer_clock_t rtimer_arch_now(void);

void rtimer_arch_schedule(rtimer_clock_t time);

#endif /* __RTIMER_ARCH_H__ */


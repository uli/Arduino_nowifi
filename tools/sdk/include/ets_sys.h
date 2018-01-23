/*
 * copyright (c) 2008 - 2011 Espressif System
 *
 * Define user specified Event signals and Task priorities here
 *
 */

#ifndef _ETS_SYS_H
#define _ETS_SYS_H

#include "c_types.h"
#include "hw/eagle_soc.h"

typedef uint32_t ETSSignal;
typedef uint32_t ETSParam;

typedef struct ETSEventTag ETSEvent;

struct ETSEventTag {
    ETSSignal sig;
    ETSParam  par;
};

typedef void (*ETSTask)(ETSEvent *e);

/* timer related */
typedef uint32_t ETSHandle;
typedef void ETSTimerFunc(void *timer_arg);

typedef struct _ETSTIMER_ {
    struct _ETSTIMER_    *timer_next;
    uint32_t              timer_expire;
    uint32_t              timer_period;
    ETSTimerFunc         *timer_func;
    void                 *timer_arg;
} ETSTimer;

/* interrupt related */

typedef void (*int_handler_t)(void*);

#define ETS_SLC_INUM        1
#define ETS_SDIO_INUM       1
#define ETS_SPI_INUM        2
#define ETS_GPIO_INUM       4
#define ETS_UART_INUM       5
#define ETS_UART1_INUM      5
#define ETS_CCOMPARE0_INUM  6
#define ETS_SOFT_INUM       7
#define ETS_WDT_INUM        8
#define ETS_FRC_TIMER1_INUM 9  /* use edge*/

#define ETS_INTR_LOCK() \
    ets_intr_lock()

#define ETS_INTR_UNLOCK() \
    ets_intr_unlock()

#define ETS_INTR_ENABLE(inum) \
    ets_isr_unmask((1<<inum))

#define ETS_INTR_DISABLE(inum) \
    ets_isr_mask((1<<inum))

static inline bool ETS_INTR_WITHINISR()
{
    uint32_t ps;
    __asm__ __volatile__("rsr %0,ps":"=a" (ps));
    // PS.INTLEVEL check
    return ((ps & 0x0f) != 0);
}

inline uint32_t ETS_INTR_ENABLED(void)
{
    uint32_t enabled;
    __asm__ __volatile__("esync; rsr %0,intenable":"=a" (enabled));
    return enabled;
}

inline uint32_t ETS_INTR_PENDING(void)
{
    uint32_t pending;
    __asm__ __volatile__("esync; rsr %0,interrupt":"=a" (pending));
    return pending;
}

#define ETS_CCOMPARE0_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_CCOMPARE0_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_CCOMPARE0_ENABLE() \
    ETS_INTR_ENABLE(ETS_CCOMPARE0_INUM)

#define ETS_CCOMPARE0_DISABLE() \
    ETS_INTR_DISABLE(ETS_CCOMPARE0_INUM)


#define ETS_FRC_TIMER1_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_FRC_TIMER1_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_FRC_TIMER1_NMI_INTR_ATTACH(func) \
    NmiTimSetFunc(func)

#define ETS_GPIO_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_GPIO_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_GPIO_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_GPIO_INUM)

#define ETS_GPIO_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_GPIO_INUM)


#define ETS_UART_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_UART_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_UART_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_UART_INUM)

#define ETS_UART_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_UART_INUM)

#define ETS_FRC1_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_FRC_TIMER1_INUM)

#define ETS_FRC1_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_FRC_TIMER1_INUM)


#define ETS_SPI_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_SPI_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_SPI_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_SPI_INUM)

#define ETS_SPI_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_SPI_INUM)


#define ETS_SLC_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_SLC_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_SLC_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_SLC_INUM)

#define ETS_SLC_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_SLC_INUM)


#define ETS_SDIO_INTR_ATTACH(func, arg) \
    ets_isr_attach(ETS_SDIO_INUM, (int_handler_t)(func), (void *)(arg))

#define ETS_SDIO_INTR_ENABLE() \
    ETS_INTR_ENABLE(ETS_SDIO_INUM)

#define ETS_SDIO_INTR_DISABLE() \
    ETS_INTR_DISABLE(ETS_SDIO_INUM)


#endif /* _ETS_SYS_H */

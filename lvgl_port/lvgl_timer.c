/* ========== lvgl_timer.c ========== */
#include "lvgl_timer.h"
#include "lvgl/lvgl.h"
#include <ti/devices/msp/msp.h>
#include "../config/app_config.h"

void LVGL_Tick_Handler(void) {
    lv_tick_inc(LVGL_TICK_MS);
}

void LVGL_Timer_Setup(void) {
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);
}

/* Timer Interrupt Handler - Called from main ISR */
void TIMA0_0_IRQHandler(void) {
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            LVGL_Tick_Handler();
            DL_TimerG_clearInterruptStatus(TIMER_0_INST, DL_TIMER_INTERRUPT_ZERO_EVENT);
            break;
        default:
            break;
    }
}
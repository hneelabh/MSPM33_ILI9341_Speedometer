/* ========== lvgl_timer.h ========== */
#ifndef LVGL_TIMER_H
#define LVGL_TIMER_H

/* Setup and start the LVGL tick timer */
void LVGL_Timer_Setup(void);

/* Timer interrupt handler - call this from ISR */
void LVGL_Tick_Handler(void);

#endif /* LVGL_TIMER_H */
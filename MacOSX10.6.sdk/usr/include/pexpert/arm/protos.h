/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
#ifndef _PEXPERT_ARM_PROTOS_H
#define _PEXPERT_ARM_PROTOS_H

extern uint32_t pe_arm_get_soc_base_phys(void);
extern uint32_t pe_arm_init_interrupts(void *args);

extern void cnputc(char);
int serial_init(void);
int serial_getc(void);
void serial_putc(char);
void uart_putc(char);
int uart_getc(void);

void vc_progress_initialize(void *, const unsigned char *, const unsigned char *);
void vc_display_icon(void *, const unsigned char *);

int switch_to_serial_console(void);
void switch_to_old_console(int);

#endif /* _PEXPERT_ARM_PROTOS_H */

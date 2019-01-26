/*
 * lab3.asm
 *
 * Author:	Jake O´Donnell and Stefan von Freytag-Loringhoven
 *
 * Date:	2017-11-28
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	.DEF DICE		= R25

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG	RESET
	RJMP	init

	.ORG	PM_START			; Every file included in main program
	.INCLUDE "keyboard.inc"
	.INCLUDE "lcd.inc"
	.INCLUDE "tarning.inc"
	.INCLUDE "stat_data.inc"
	.INCLUDE "delay.inc"	
	.INCLUDE "stats.inc"
	.INCLUDE "monitor.inc"
;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	LDI	TEMP, LOW(RAMEND)
	OUT SPL, TEMP
	LDI TEMP, HIGH(RAMEND)
	OUT SPH, TEMP
	CALL init_pins
	CALL lcd_init
	CALL init_monitor
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:
	LDI	TEMP,	0xC0	
	OUT DDRD,	TEMP	
	LDI TEMP,	0x00 
	OUT DDRE,	TEMP
	LDI TEMP,	0xFF
	OUT DDRF,	TEMP	
	OUT DDRB,	TEMP	
	RET

;==============================================================================
; Main part of program
;==============================================================================
main:	
	RCALL clear						;Clear display everytime we call clear
	PRINTSTRING Hello_str			;Writes string 
	RCALL delay_1sek				;Delays
	RCALL delay_1sek
roll_screen:						;Clears and writes new string
	RCALL clear
	PRINTSTRING Press_str

READ:								
	RCALL read_keyboard				;Reads keyboard 
	RCALL buttonpressed				;Checks key and has instruktion for the keys.
	RJMP READ


;==============================================================================
; Clear
;==============================================================================

clear:								;Clear routine
	LDI		R24, 0x01
	RCALL	lcd_write_instr
	LDI		R24, 100
	RCAll	delay_ms
	RET

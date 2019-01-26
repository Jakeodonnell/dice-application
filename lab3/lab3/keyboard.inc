/*
 * keyboard.inc
 * This file contains subrutines for the keyboard.
 *
 * Author:	Jake O´Donnell and Stefan von Freytag-Loringhoven
 *
 * Date:	2017-11-21
 */ 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU NO_KEY		= 0x0F
map_table: 
	.DB "147*2580369#"

;==============================================================================
; External rotines 
;==============================================================================
read_keyboard:
	LDI R18, 0		; reset counter
scan_key:
	MOV R19, R18	;copy counter to R19
	LSL R19			;Shift R19 4steps left
	LSL R19
	LSL R19
	LSL R19
	OUT PORTB, R19		; set address to read
	LDI R24, 15
	RCALL delay_micros
	SBIC PINE, 6	;check if key is pressed
	RJMP return_key_val
	INC R18			;increment counter
	CPI R18, 12		;if 12, no key is pressed
	BRNE scan_key
	LDI R18, NO_KEY		; no key was pressed!
return_key_val:
	MOV RVAL, R18		;copy counter to return value
	RET					;return

remap:
	LDI ZH, high(map_table <<1) ;Initialize Z pointer
	LDI ZL, low(map_table <<1)
	ADD ZL, RVAL ;Add index
	LDI RVAL, 0x00
	ADC ZH, RVAL ;Add 0 to catch Carry, if present
	LPM RVAL, Z
	RET
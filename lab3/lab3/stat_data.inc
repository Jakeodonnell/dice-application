/*
 * stat_data.inc
 *	
 * Author:	Jake O´Donnell and Stefan von Freytag-Loringhoven
 *
 *	Date: 2017-11-28
 */ 

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
 .DSEG

 .ORG		0x100

stats_data:
.BYTE		0x07
.CSEG
;==============================================================================
; External - Subrutines
;==============================================================================
store_stat:
	LDI YH, HIGH(stats_data)		
	LDI YL, LOW(stats_data)
	LD	R20, Y			;set pointer
	INC R20				;increase address
	ST	Y, R20			;store R20 in Y
	ADD YL, R24			;Add index
	LDI RVAL, 0x00
	ADC YH, RVAL		;Add 0 to catch Carry, if there is one
	LD	R20, Y			
	INC R20			
	ST	Y, R20
	RET

get_stat:
	LDI YH, HIGH(stats_data)
	LDI YL, LOW(stats_data)
	LDI R20, 255
	ADD YL, R24			;Add index
	LDI RVAL, 0x00
	ADC YH, RVAL		;Add 0 to catch Carry, if there is one
	LD R24, Y
	RET

clear_stat:
	LDI YH, HIGH(stats_data)
	LDI YL, LOW(stats_data)
	LDI R20, 0
	LDI R24, 0
clear_loop:
	ST Y+, R20
	INC R24
	CPI R24, 7
	BRNE clear_loop
	RET

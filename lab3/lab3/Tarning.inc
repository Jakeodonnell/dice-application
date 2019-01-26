/*
 * tarning.inc
 *
 *  Created: 2017-11-28 14:32:01
* Author:	Jake O´Donnell and Stefan von Freytag-Loringhoven
 */ 
;==============================================================================
;	Constants
;==============================================================================
dice_table: 
	.DB "123456"
;==============================================================================
;	External Subrutines
;==============================================================================
Buttonpressed:				; Checks what button is pressed and if so sends program to a routine
	CPI	 R24, 0x4
	BREQ beforeroll
	CPI R24, 0x08
	BREQ Show_stat
	CPI R24, 0x06
	BREQ clear_stats
	CPI R24, 0xa
	BREQ monitoring
	RET

monitoring:
	RCALL monitor
	RJMP roll_screen

clear_stats:
	RCALL clearstat
	RJMP roll_screen

show_stat:
	RCALL showstat
	RJMP roll_screen
beforeroll:
	RCALL clear
	PRINTSTRING Roll_str

roll_dice:					
	LDI		R16, 1				;set dice to 1
test:
	NOP
	NOP
	CPI		R16, 7				; ses if dice is max value
	BREQ	roll_dice			; if so set dice to 1
	RCALL	read_keyboard		; readkeyboard to see if button is pressed
	CPI		R24, 0x4			; if no then print value
	BRNE	roll_print
	INC		R16					;increse value
	RJMP	test

roll_print:	
	MOV RVAL, R16				;move value
	RCALL store_stat			;store stat
	RCALL clear					;clear
	PRINTSTRING Score_str		;print score

	CPI R16, 1					;check what the value is and writes the value 
	BREQ numone

	CPI R16, 2
	BREQ numtwo

	CPI R16, 3
	BREQ numthree
	
	CPI R16, 4
	BREQ numfour

	CPI R16, 5
	BREQ numfive
	
	CPI R16, 6
	BREQ numsix

numone:
	PRINTSTRING one
	RCALL delay_2sek
	RJMP roll_screen
numtwo:
	PRINTSTRING two
	RCALL delay_2sek
	RJMP roll_screen
numthree:
	PRINTSTRING three
	RCALL delay_2sek
	RJMP roll_screen
numfour:
	PRINTSTRING four
	RCALL delay_2sek
	RJMP roll_screen
numfive:
	PRINTSTRING five
	RCALL delay_2sek
	RJMP roll_screen
numsix:
	PRINTSTRING six
	RCALL delay_2sek
	RJMP roll_screen

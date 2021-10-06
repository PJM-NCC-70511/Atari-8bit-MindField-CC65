    	.import         __LOWCODE_LOAD__, __LOWCODE_RUN__, __LOWCODE_SIZE__
      .import         __BANK0_LOAD__
      .import         __BSS_LOAD__
      .import         __RESERVED_MEMORY__, __MAKE_CARTRIDGE__
      .import         __STACK_START__, __STACK_SIZE__
    	.import         __INIT_LOAD__, __INIT_RUN__, __INIT_SIZE__
    	.import         __CODE_LOAD__, __CODE_RUN__, __CODE_SIZE__
    	.import         __RODATA_LOAD__, __RODATA_RUN__, __RODATA_SIZE__
    	.import         __DATA_LOAD__, __DATA_RUN__, __DATA_SIZE__      
;//      .ifdef          __BANK0_LOAD__
      
;//_CARTADDR                               =__BANK0_LOAD__
;//      .endif      
      .include "mindfield_ml.asm"            
; ------------------------------------------------------------------------
; Actual code
    
	.segment        "LOWCODE"

	rts     ; fix for SpartaDOS / OS/A+
		; they first call the entry point from AUTOSTRT and
		; then the load addess (this rts here).
		; We point AUTOSTRT directly after the rts.

; Real entry point:


; Copy the data segement

	lda     #<__CODE_LOAD__         ; Source pointer
	sta     ptr1
	lda     #>__CODE_LOAD__
	sta     ptr1+1

	lda     #<__CODE_RUN__          ; Target pointer
	sta     ptr2
	lda     #>__CODE_RUN__
	sta     ptr2+1

	ldx     #<~__CODE_SIZE__
	lda     #>~__CODE_SIZE__        ; Use -(__DATASIZE__+1)

	jsr copyseg

	lda     #<__RODATA_LOAD__         ; Source pointer
	sta     ptr1
	lda     #>__RODATA_LOAD__
	sta     ptr1+1

	lda     #<__RODATA_RUN__          ; Target pointer
	sta     ptr2
	lda     #>__RODATA_RUN__
	sta     ptr2+1

	ldx     #<~__RODATA_SIZE__
	lda     #>~__RODATA_SIZE__        ; Use -(__DATASIZE__+1)

	jsr copyseg

	lda     #<__DATA_LOAD__         ; Source pointer
	sta     ptr1
	lda     #>__DATA_LOAD__
	sta     ptr1+1

	lda     #<__DATA_RUN__          ; Target pointer
	sta     ptr2
	lda     #>__DATA_RUN__
	sta     ptr2+1

	ldx     #<~__DATA_SIZE__
	lda     #>~__DATA_SIZE__        ; Use -(__DATASIZE__+1)

	jsr copyseg
	


; Clear the BSS data

        jsr     zerobss

        lda     #<(__STACK_START__ + __STACK_SIZE__ - 1)
        sta     sp
        lda     #>(__STACK_START__ + __STACK_SIZE__ - 1)
        sta     sp+1

; Call module constructors

        jsr     initlib
.ifdef  DYNAMIC_DD
	      jsr     __getdefdev
.endif

      	jsr     callmain

; Call module destructors. This is also the _exit entry.

_exit:  jsr     donelib         ; Run module destructors

; Restore system stuff

;        ldx     spsave
;        txs                     ; Restore stack pointer

; restore left margin

;        lda     old_lmargin
;        sta     LMARGN

; restore kb mode

;        lda     old_shflok
;        sta     SHFLOK

; restore APPMHI

;        lda     appmsav
;        sta     APPMHI
;        lda     appmsav+1
;        sta     APPMHI+1

; Copy back the zero page stuff

;        ldx     #zpspace-1
;L2:     lda     zpsave,x
;        sta     sp,x
;        dex
;        bpl     L2

; turn on cursor

;        inx
;        stx     CRSINH

; Back to DOS

;        rts
END:     jmp END            ; loop forever


copyseg:
	sta     tmp1
	ldy     #$00

; Copy loop

@L1:    inx
	beq     @L3

@L2:    lda     (ptr1),y
	sta     (ptr2),y
	iny
	bne     @L1
	inc     ptr1+1
	inc     ptr2+1                  ; Bump pointers
	bne     @L1                     ; Branch always (hopefully)

; Bump the high counter byte

@L3:    inc     tmp1
	bne     @L2

; Done

	rts

; Cartridge vectors at $BFFA
;
    	.segment "VECTORS"
    
    	; Start Address
    	.word __LOWCODE_LOAD__+1
    	; Cart present
    	.byte $00
    	; Init & Start
    	.byte $04
    	; Init Address
     	.word __LOWCODE_LOAD__
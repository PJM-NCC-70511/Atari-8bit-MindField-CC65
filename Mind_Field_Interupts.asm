
_GAME_VBI:
      .export _GAME_VBI 
		lda #<_GAME00_DLI
		sta VDSLST+0
		lda #>_GAME00_DLI
		sta VDSLST+1
		lda #$22
		sta COLBAK
		lda _mind_color
		sta COLPF3		
  ;//  inc_RTCLOCK
  ;//bne no_inc_other_clock
  ;//inc RTCLOCK+1
  ;//no_inc_other_clock:
      
	  	LDA _prior_py
	  	STA _NDX2
	  	LDA #>_PMBNK0
	  	STA _NDX3
	  	
	  	LDA #0
	  	LDY #13
Clear_Character_Prior_Loop:
      STA (_NDX2),Y
      DEY
      BPL Clear_Character_Prior_Loop   	
      	
      LDA _character_py
      STA _NDX2
      LDA #>_PMBNK0
      STA _NDX3
        
      LDY _character_frame  
        
             
      LDA _SPRITEADDR_PLY0LO,Y
      STA _NDX0
        
      LDA _SPRITEADDR_PLY0HI,Y
      STA _NDX1
        	
      LDY #13
Copy_Character_Image_Loop:
		LDA (_NDX0),Y
		STA (_NDX2),Y
		DEY
		BPL Copy_Character_Image_Loop
		
		LDA _character_px
		STA HPOSP0   	
    
    LDA _character_py 
		STA _prior_py 



		JSR _PROCESS_SOUNDS      



		jmp XITVBV	


_TITLE_VBI:
      .export _TITLE_VBI 
		lda #<_TITLE00_DLI
		sta VDSLST+0
		lda #>_TITLE00_DLI
		sta VDSLST+1
		lda #$22
		sta COLBAK
		lda #$36
		sta COLPF3				
		inc _RTCLOCK+2
		jmp XITVBV


_PAUSE_VBI:
      .export _PAUSE_VBI

		jmp XITVBV

_TITLE00_DLI:
      .export _TITLE00_DLI 
	pha	
	lda #$D8
	sta WSYNC
	sta COLPF0
	lda #$06
	sta COLPF1
	lda #$AA
	sta COLPF1
	lda #>_CHARSET_TITLE
	sta CHBASE
	lda #<_TITLE01_DLI
	sta VDSLST+0
	lda #>_TITLE01_DLI
	sta VDSLST+1
	pla
	rti

_TITLE01_DLI:
      .export _TITLE01_DLI 
	pha	
	lda #142
	sta WSYNC
	sta COLPF0
	lda #216
	sta COLPF1
	lda #56
	sta COLPF2
	lda #>_CHARSET_GAME
 	sta CHBASE
	lda #<_TITLE00_DLI
	sta VDSLST+0
	lda #>_TITLE00_DLI
	sta VDSLST+1
	pla
	rti

_TITLE02_DLI:
      .export _TITLE02_DLI 
	PHA
  PLA
  RTI


_TITLE03_DLI:
      .export _TITLE03_DLI 
	PHA
  PLA
  RTI


_GAME00_DLI:
      .export _GAME00_DLI 
	PHA
  PLA
  RTI

_GAME01_DLI:
      .export _GAME01_DLI 
	PHA
  PLA
  RTI

_GAME02_DLI:
      .export _GAME02_DLI 
	PHA
  PLA
  RTI

_GAME03_DLI:
      .export _GAME03_DLI 
	PHA
  PLA
  RTI

_GAME04_DLI:
      .export _GAME04_DLI 
	PHA
  PLA
  RTI

      .import         initlib, donelib, callmain
      .import         zerobss, pushax
      .import         copysegs
      .import         _main, __filetab, getfd

_PMBANK                                 =$1800                                        
_VARBANK                                =$0600                                                                                                                                       
_SCREEN_ADDR                            =$0800                                         
_GAME_SCREEN_ADDR                       =$0840                                        

_RTCLOCK                                =$12
_PMBANK_HI                              = >_PMBANK   

                                       

_M0		        	          	            =$C0
_M1		        	          	            =$C1
_M2		        	          	            =$C2
_M3		        	          	            =$C3
_M4		        	          	            =$C4
_M5		        	          	            =$C5
_M6		        	          	            =$C6
_M7		        	          	            =$C7
_M8		        	          	            =$C8
_M9		        	          	            =$C9
_NDX0									                  =$CA
_NDX1									                  =$CB
_NDX2									                  =$CC
_NDX3									                  =$CD
_HOLDX									                =$CE
_HOLDY									                =$CF
                        
              ;PLAY_SOUNDS                                      =SOUND_COMMANDER + $0000	    
              ;START_SOUND                                      =SOUND_COMMANDER + $009F      
              ;GET_NEXT_MUSIC_NOTE                              =SOUND_COMMANDER + $00F6      
              ;STOP_SOUND                                       =SOUND_COMMANDER + $0189      
              ;SILENCE                                          =SOUND_COMMANDER + $019E      

_SPRITENUM	                                     =_PMBANK+$0180
_SETSP0COLOR                                     =_PMBANK+$0190
_SETSP1COLOR                                     =_PMBANK+$01A0
_SETSPWIDTH                                      =_PMBANK+$01B0
_SPRITENHOZ                                      =_PMBANK+$01C0
_SPRITENVRT                                      =_PMBANK+$01E0
_SPHOZNEXT                                       =_PMBANK+$01F0

_SPRHZ0	                            	           =_PMBANK+$0200 
_SPRHZ1	                            	           =_PMBANK+$0210 
_SPRHZ2	                            	           =_PMBANK+$0220 
_SPRHZ3	                            	           =_PMBANK+$0230 
_SPZONT                                          =_PMBANK+$0240
_SPZONB                                          =_PMBANK+$0250
_SPSRC0                                          =_PMBANK+$0260 
_SPSRC1                                          =_PMBANK+$0278
_SPSRC2                                          =_PMBANK+$0290
_SPSRC3                                          =_PMBANK+$02A8
_SPSRC4                                          =_PMBANK+$02C0
_SPRITEUSE                                       =_PMBANK+$02D8
                                            
_MIBANK                                          =_PMBANK+$0300
_PMBNK0                                          =_PMBANK+$0400
_PMBNK1                             	           =_PMBANK+$0500
_PMBNK2                                          =_PMBANK+$0600
_PMBNK3                             	           =_PMBANK+$0700
            
_character_px                                    =_VARBANK + $020
_character_py                                    =_VARBANK + $021
_character_status                                =_VARBANK + $022
_prior_py                                        =_VARBANK + $024
_stick_read                                      =_VARBANK + $026 
_character_frame                                 =_VARBANK + $027
_prior_rt_clock                                  =_VARBANK + $02C
_menu_selection                                  =_VARBANK + $02D
_find_option                                     =_VARBANK + $02E
_bombs_on_option                                 =_VARBANK + $02F
_walls_on_option                                 =_VARBANK + $030
_shooters_option                                 =_VARBANK + $032
_mind_color                                      =_VARBANK + $034
_show_countdown                                  =_VARBANK + $036
_minds_found                                     =_VARBANK + $038
_minds_under                                     =_VARBANK + $03A
_titlephase                                      =_VARBANK + $03C
_score                                           =_VARBANK + $03E
_lives                                           =_VARBANK + $040
_level                                           =_VARBANK + $041
_topMem                                          =_VARBANK + $042;
_chbase1                                         =_VARBANK + $044;
_row_addr                                        =_VARBANK + $046; 
_exit_cx  	                                	   =_VARBANK + $048;
_exit_cy  	                                		 =_VARBANK + $049; 
_exit_p0  	                                		 =_VARBANK + $04A;
_exit_p1  	                                		 =_VARBANK + $04B; 
_SOUND_COMMANDER_VARIABLE_AREA                   =_VARBANK + $060;



      .export _PMBANK
      .export _VARBANK                                        
      .export _SCREEN_ADDR                                         
      .export _GAME_SCREEN_ADDR
      .export _PMBANK_HI

      .export _M0									  
      .export _M1									  
      .export _M2								  
      .export _M3									  
      .export _M4									  
      .export _M5								  
      .export _M6									  
      .export _M7									  
      .export _M8									  
      .export _M9									  
      
      .export _NDX0									  
      .export _NDX1									  
      .export _NDX2									  
      .export _NDX3									  
      .export _HOLDX									  
      .export _HOLDY									                  
      ;.export _PLAY_SOUNDS           
      ;.export _START_SOUND           
      ;.export _GET_NEXT_MUSIC_NOTE   
      ;.export _STOP_SOUND            
      ;.export _SILENCE               
      .export _SPRITENUM	            
      .export _SETSP0COLOR           
      .export _SETSP1COLOR           
      .export _SETSPWIDTH            
      .export _SPRITENHOZ            
      .export _SPRITENVRT            
      .export _SPHOZNEXT             
      .export _SPRHZ0	              
      .export _SPRHZ1	              
      .export _SPRHZ2	              
      .export _SPRHZ3	              
      .export _SPZONT                
      .export _SPZONB                
      .export _SPSRC0                
      .export _SPSRC1                
      .export _SPSRC2                
      .export _SPSRC3                
      .export _SPSRC4                
      .export _SPRITEUSE                                    
      .export _MIBANK                
      .export _PMBNK0                          
      .export _PMBNK1                    
      .export _PMBNK2                    
      .export _PMBNK3                

      .export _character_px     
      .export _character_py     
      .export _character_status 
      .export _prior_py         
      .export _stick_read       
      .export _character_frame
      .export _prior_rt_clock   
      .export _menu_selection   
      .export _find_option      
      .export _bombs_on_option  
      .export _walls_on_option  
      .export _shooters_option  
      .export _mind_color       
      .export _show_countdown   
      .export _minds_found      
      .export _minds_under      
      .export _titlephase       
      .export _score            
      .export _lives                  
      .export _level                  
      .export _topMem                 
      .export _chbase1                
      .export _row_addr               
      .export _exit_cx  	             
      .export _exit_cy  	             
      .export _exit_p0  	             
      .export _exit_p1

      
      .segment "DATA0"
       
      .include "Atari 8-bit Equates.asm"
      .include "zeropage.inc"      
      .include "mindfield_data.asm"
      .include "Mind_Field_Interupts.asm"
      .include "atari_sound_commander.asm"
            



; ------------------------------------------------------------------------
; Actual code
; *** end of main startup code
  
          .segment "DATA0"

_RANDOM_PLACE_MINDS:
    .export _RANDOM_PLACE_MINDS
			LDA #193
      LDY RANDOM      
      STA _GAME_SCREEN_ADDR+0,Y
      LDY RANDOM
      STA _GAME_SCREEN_ADDR+256,Y 
      LDY RANDOM
      STA _GAME_SCREEN_ADDR+512,Y 
      LDY RANDOM
      STA _GAME_SCREEN_ADDR+768,Y        
      RTS


_SCAN_FOR_MINDS:
            .export _SCAN_FOR_MINDS            
;     
; Scan For Minds
;
                            
              LDA _character_px
              SEC
              SBC #55
              CMP #248
              BCC SM_L0 
              LDA #0
SM_L0:
              CMP #148
              BCC SM_L1
              LDA #148
SM_L1:                                                         
              LSR
              LSR 
              STA _M2
              
              LDA _character_py
              SEC
              SBC #32
              BCS SM_L2
              LDA #0
SM_L2:              
              LSR
              LSR 
              LSR
              STA _M1

              LDA #0
              STA _M6
              STA _minds_found 
              LDY _M1
              CPY #26
              BCS Scan_For_restore_Beyond_Screen
              DEY
              DEY                

              STY _M5
              BPL No_0_First_restore_Row
              LDY #0
No_0_First_restore_Row:
              LDA _M2
              CLC
              ADC _SCRREN_ROW_LOW,Y
              STA _NDX0
              LDA _SCRREN_ROW_HIGH,Y
              ADC #0
              STA _NDX1
Scan_restore_Row_Start:
              LDA _M5
              BEQ Skip_restore_Scan_Row
              CMP #26
              BCS Skip_restore_Scan_Row                           
              LDY #5
Scan_For_restore_Loop:                          
              LDA (_NDX0),Y
              CMP _M3 
              BNE No_restore_Found
              LDA _M4
              STA (_NDX0),Y
              INC _minds_found
No_restore_Found:
              DEY
              BPL Scan_For_restore_Loop

              LDA _NDX0
              CLC
              ADC #40 ; or 48 if widescren
              STA _NDX0
              BCC SM_L5
              INC _NDX1
SM_L5:       

Skip_restore_Scan_Row:
              LDY _M6
              INY
              CPY #5
              STY _M6
              BCS Scan_For_restore_Beyond_Screen
              INC _M5 
              JMP Scan_restore_Row_Start                                             
Scan_For_restore_Beyond_Screen:
              RTS


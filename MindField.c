#include <atari.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <joystick.h>
#include <peekpoke.h>
#include <atari_equates.h>

extern const          TITLE_VBI;
extern const          GAME_VBI;       
extern const          PAUSE_VBI;
extern const          TITLE00_DLI; 
extern const          TITLE01_DLI;
extern const          TITLE02_DLI;
extern const          TITLE03_DLI;
extern const          GAME00_DLI;
extern const          GAME01_DLI;
extern const          GAME02_DLI;
extern const          GAME03_DLI; 

extern const          RANDOM_PLACE_MINDS;
extern const          SCAN_FOR_MINDS;

extern unsigned char  CHARSET_GAME;
extern unsigned char  SPRITEADDR_PLY0LO;    
extern unsigned char  SPRITEADDR_PLY0HI;    
extern unsigned char  CHARSET_TITLE;
extern unsigned int   TITLE_DATA;           
extern const          display_list_title;   
extern const          display_list_game;    
extern const          PMBANK;         
extern const          VARBANK;         
extern unsigned char  SCREEN_ADDR;         
extern unsigned char  GAME_SCREEN_ADDR;         
extern const          CHARSET_GAME_HI; 
extern const          CHARSET_TITLE_HI;
extern const          PMBANK_HI;
extern unsigned char  PLAY_SOUNDS;             
extern unsigned char  START_SOUND;             
extern unsigned char  GET_NEXT_MUSIC_NOTE;     
extern unsigned char  STOP_SOUND;              
extern unsigned char  SILENCE;                 
extern unsigned char  SPRITENUM;	              
extern unsigned char  SETSP0COLOR;             
extern unsigned char  SETSP1COLOR;             
extern unsigned char  SETSPWIDTH;              
extern unsigned char  SPRITENHOZ;              
extern unsigned char  SPRITENVRT;              
extern unsigned char  SPHOZNEXT;               
extern unsigned char  SCREEN_LINE_ADDR_LOW;    
extern unsigned char  SCREEN_LINE_ADDR_HIGH;   
extern unsigned char  SPRHZ0;	                
extern unsigned char  SPRHZ1;	                
extern unsigned char  SPRHZ2;	                
extern unsigned char  SPRHZ3;	                
extern unsigned char  SPZONT;                  
extern unsigned char  SPZONB;                  
extern unsigned char  SPSRC0;                  
extern unsigned char  SPSRC1;                  
extern unsigned char  SPSRC2;                  
extern unsigned char  SPSRC3;                  
extern unsigned char  SPSRC4;                  
extern unsigned char  SPRITEUSE;               
extern unsigned char  MIBANK;                  
extern unsigned char  PMBNK0;                 
extern unsigned char  PMBNK1;                  
extern unsigned char  PMBNK2;                  
extern unsigned char  PMBNK3;   

extern unsigned char  M0;									  
extern unsigned char  M1;									  
extern unsigned char  M2;								  
extern unsigned char  M3;									  
extern unsigned char  M4;									  
extern unsigned char  M5;								  
extern unsigned char  M6;									  
extern unsigned char  M7;									  
extern unsigned char  M8;									  
extern unsigned char  M9;									        
extern unsigned char  NDX0;									  
extern unsigned char  NDX1;									  
extern unsigned char  NDX2;									  
extern unsigned char  NDX3;									  
extern unsigned char  HOLDX;									  
extern unsigned char  HOLDY;									                  

extern unsigned char  character_px;              
extern unsigned char	character_py;       
extern unsigned char	character_status;
extern unsigned char	prior_py;               
extern unsigned char	stick_read;             
extern unsigned char	character_frame;
extern unsigned char	prior_rt_clock;         
extern unsigned char	menu_selection;         
extern unsigned char	find_option;            
extern unsigned char	bombs_on_option;        
extern unsigned char	walls_on_option;        
extern unsigned char	shooters_option;        
extern unsigned char	mind_color;             
extern unsigned char	show_countdown;         
extern unsigned char	minds_found;            
extern unsigned char	minds_under;            
extern unsigned char	titlephase;
extern unsigned int   score;
extern unsigned char	lives;
extern unsigned char	level;
extern unsigned int   topMem;
extern unsigned char  chbase1;
extern unsigned int   row_addr;
extern unsigned char  exit_cx;
extern unsigned char  exit_cy; 
extern unsigned char  exit_p0;
extern unsigned char  exit_p1; 
extern unsigned char  SPRITEADDR_PLY0LO; 
extern unsigned char  SPRITEADDR_PLY0HI; 
extern const          SPRITEADDR_PLY0W[];

extern const          SF_EXPLOSION; 
extern const          SF_BELL_01; 
extern const          SF_BELL_02; 
extern const          SF_EXTRA_LIFE;
extern const          SF_GET_ITEM; 
extern const          SF_ALERT; 
extern const          SF_GAME_OVER; 

#pragma codeseg("BANK0")
#pragma rodataseg("BANK0")

#pragma regvaraddr(on)  // Allow taking the address of register variables.
                                      
unsigned char	TEMP0;
unsigned char	TEMP1;
unsigned char	TEMP2;
unsigned char	TEMP3;
unsigned char	TEMP4;
unsigned char	TEMP5;
unsigned char	TEMP6;
unsigned char	TEMP7;
unsigned char	TEMP8;
unsigned char	TEMP9;

unsigned char a; 
unsigned char b; 
unsigned char c; 
unsigned char d;
unsigned char e; 
unsigned char f; 
unsigned char g; 
unsigned char h;
unsigned char i; 
unsigned char j; 
unsigned char k; 
unsigned char l;

unsigned int  p;
unsigned int  q;
unsigned int  r;
unsigned int  s;

unsigned char difficulty = 0;

unsigned short int hiscore [11] = {0,0,0,0,0,0,0,0,0,0,0}; //Set High Scores to 0







unsigned int  screen_rows[] = {  // Address of each line of the screen, 40 bytes per line
    (&GAME_SCREEN_ADDR +   0),(&GAME_SCREEN_ADDR +   40), (&GAME_SCREEN_ADDR +  80), (&GAME_SCREEN_ADDR + 120), (&GAME_SCREEN_ADDR + 160),
    (&GAME_SCREEN_ADDR + 200), (&GAME_SCREEN_ADDR + 240), (&GAME_SCREEN_ADDR + 280), (&GAME_SCREEN_ADDR + 320), (&GAME_SCREEN_ADDR + 360),  
  	(&GAME_SCREEN_ADDR + 400), (&GAME_SCREEN_ADDR + 440), (&GAME_SCREEN_ADDR + 480), (&GAME_SCREEN_ADDR + 520), (&GAME_SCREEN_ADDR + 560),
  	(&GAME_SCREEN_ADDR + 600), (&GAME_SCREEN_ADDR + 640), (&GAME_SCREEN_ADDR + 680), (&GAME_SCREEN_ADDR + 720), (&GAME_SCREEN_ADDR + 760),
    (&GAME_SCREEN_ADDR + 800), (&GAME_SCREEN_ADDR + 840), (&GAME_SCREEN_ADDR + 880), (&GAME_SCREEN_ADDR + 920), (&GAME_SCREEN_ADDR + 960),
    (&GAME_SCREEN_ADDR + 1000) 
};    


#pragma codeseg("CODE")
  
void Display_Information_Line(void)
// Displays Current Score, Lives, and Level
	{
	gotoxy(0, 0);
  printf("SCORE:%d \n", score);
  gotoxy(12, 0);
  if(lives >= 0 && lives <=252)
      {    	
    	printf("LIVES:%d \n",lives);
      }
  else if (lives >=253)
      {
      printf("GAME OVER   \n");
      }
	gotoxy(26, 0);
	printf("LEVEL:%d \n", level);
  }

void  Show_Hi_Scores(void)
  {
		gotoxy(10,6); 
		printf("SCORE : %d \n",score);
		gotoxy(8,8);
		printf ("TODAYS HIGH SCORES.\n");
   	for( i = 1; i < 6; i++ )
        {
        if (k == i)
            {  
  	          gotoxy(12,(8+i));
  	          printf("*\n");
  	      }
  	      gotoxy(14,(8+i));  
  	      printf("%d : %d \n", i , hiscore[i] );
     		} 
	 }


void ShowTitleScreen(void)
{
      POKE(NMIEN,0);
      POKE(DMACTL,0);

      POKEW (VDSLST,&TITLE00_DLI);
      POKEW (VVBLKD,&TITLE_VBI);
      POKEW (DLISTW,&display_list_title); 	 
      POKEW (SDLSTW,&display_list_title); 
      POKEW (SAVMSC,&GAME_SCREEN_ADDR); 	   
      POKE  (CHBAS,&CHARSET_TITLE_HI);     
      
      POKE (&SCREEN_ADDR,5);
      
      POKE(82,0);
      POKE(710,0);
      POKE(709,12);
      POKE(PRIOR,0);
      POKE(HITCLR,0);
      
      i=6;
      k=6;
          
      while (i > 0)
      {
        if(score > hiscore[i])
        {
          k=i;                
        }
      i = i - 1;
      }

      POKE (COLPF2,68);
      POKE (COLBAK,142);
    

     if (k < 5)
     {
        i = 6;  
        while (i > k)
        {
          hiscore[i] = hiscore[i - 1];
          i = i - 1;    
        }      
        hiscore[k] = score;
     }



//  asm ("JSR SILENCE");
      memset(&MIBANK, 0, 1279);
      memset(&SCREEN_ADDR, 0, 1024);                        
      
      titlephase = 0;  
      i = 6;
      k = 6;

    clrscr();
    gotoxy(0, 0); 
    
    printf("          ATARI 8-BIT C VERSION        \n");
    printf(" PROGRAMMING            PETER J. MEYER \n");
    printf("                                       \n");
    printf(" GRAPHICS                              \n");
    printf(" SOUND AND MUSIC                       \n");
            
    TEMP5 = 0; 
    POKE (PRIOR,1);
    
    k = 6;
    i = 5;
    POKE (COLOR0,0xD8);	
    POKE (COLOR1,06);
    POKE (COLOR2,0xAA);
    POKE (COLOR3,54);
    POKE (COLOR4,34);
    
    POKE (GRACTL,0);
    Show_Hi_Scores();
    while (PEEK(VCOUNT) >> 2)  {}        
    POKE (NMIEN,192);
    POKE (DMACTL,34);
    POKE (SDMCTL,34);


    TEMP5 = 0;

    // Wait until Start Key is Pressed
    while (TEMP5 == 0)
    {
        if ((PEEK(CONSOL) & 0x01) == 0)
          {
            TEMP5 = 255;
          }
    }
        POKE (NMIEN,0);
        clrscr();
}


void Initialize_Level(void)
{  // Initialize Level. Reandoly Place Minds using ML Call
	memset(&GAME_SCREEN_ADDR, 0, 1024);
	mind_color=0x46;
  POKE (NMIEN,192);
  for( i = 0; i < 16; i = i + 1 )
    {
       asm ("JSR _RANDOM_PLACE_MINDS");  
    }

    // Randomly place 64 minds on the screen using some assembly language.
	
        character_px =124;
        character_py =216;
        character_status =0;
      POKE (&M3,193);
      POKE (&M4,0);
      asm("JSR _SCAN_FOR_MINDS");
      
			exit_cx = 4 + PEEK(RANDOM)&30;
			exit_cy = 0;
			exit_p0 = exit_cx * 4 + 46;
			exit_p1 = exit_p0 + 8;




      p = &GAME_SCREEN_ADDR+exit_cx;           
      POKEW(p,19274);
}



void Main_Game_Loop(void)
    {
    while (character_status <= 96)    //causing infinate loop before going to first IF
      {			
      if (prior_rt_clock != PEEK(RTCLOK1))
         {				              
    			prior_rt_clock = PEEK(RTCLOK1);																							
          a = (character_px - 47) / 4;          
          if (a<=2)
            { a = 2; }
          else if (a >=37)
            { a = 37; }                             
          b = (character_py - 16) / 8;
          if (b > 2)
            { b = b - 2 ; }              
          else
            { b = 0; }
          row_addr = screen_rows[b] + a;
          POKE (&M3,65);
          POKE (&M4,193);
          asm("JSR _SCAN_FOR_MINDS");


              if (character_status == 0)
                { 
                  stick_read = PEEK(PORTA) & 15; 				
  						    g = (PEEK(RTCLOK1) & 4); 
  								character_frame=0;
     
  			          if ((stick_read & 1)==0)
                    {                                      
  		          	  character_py = character_py - 1;                  			          	
                    if (character_py<16)
                        {                     
                          character_py = 16;
                        }
                        character_frame=1+g;
                    }                  
        	        if ((stick_read & 2)==0)
                    {
  		          		character_py = character_py + 1;
  		          		if (character_py>232)
                        {
                        character_py = 232;                      
                        }
  			          	    character_frame=3+g;
                    }                                                                                        
  								if ((stick_read & 4) == 0)
  								  {
  										character_px = character_px - 1;
  										if (character_px < 48)
  										{
  											character_px = 48;
  										}
  										character_frame = 2 + g;
  								  }
  								if ((stick_read & 8) == 0)
  									{
  										character_px = character_px + 1;
  										if (character_px > 200)
  										  {
  											  character_px = 200;
  										  }
  										  character_frame = 4 + g;
  									}
  								POKE (PCOLR0,202);
                  POKE (&M3,193);
                  POKE (&M4,65);
                  asm("JSR _SCAN_FOR_MINDS");
                  a = (character_px - 47) / 4;
                  b = (character_py - 30) / 8;
                  for (f = b; f <= b + 1; f = f + 1) 
                    {
                    row_addr = screen_rows[f] + a;                                                  
              			  for (p = row_addr; p <= row_addr + 1; p = p + 1)
              			  {
                        e = PEEK(p);
              				  if (e == 65)
              				  {
                          POKE (PCOLR0,15);  
                          character_status = 1;
                          asm ("LDA #1");
                          asm ("LDX #0");
                          asm ("JSR _START_SOUND");       
               				  }
                			}
                    }
                  }
									if (character_py < 38)
									{
										character_py = 38;
										if ((character_px > exit_p0) && (character_px < exit_p1))
										{
											 if (character_status == 0)
											 {
												 character_status = 32;
												// Start_Sound_Effect(1,1);                        
                       asm ("LDA #1");
                       asm ("LDX #1");
                       asm ("JSR _START_SOUND");                                                                      
											}
										}
									}
  								if ((character_status > 0) && (character_status < 30))
  								{
  									character_status = character_status + 1;
  									if (character_status == 30)
  									{
  										character_status = 128;
  									}
  									if (character_status < 16)
  									 {
  					           character_frame = 16 + (character_status/4);
  				           }
  									if (character_status > 15)
  									{
  										character_frame = 19;
  										character_px = 0;
  									}
  								}
  								if ((character_status > 31) && (character_status < 64))
  								{
  									character_status = character_status + 1;
  									if (character_status == 64)
  									{
  										character_status = 144;
  									}
  									if (character_status && 1 == 1)
  									{
  										POKEW(&GAME_SCREEN_ADDR + exit_cx,19274);
     								}
  									else
  									{
  										POKEW(&GAME_SCREEN_ADDR + exit_cx,0);
  								  }
  							  }           
          		  if (PEEK(53279U) != 7) 
                  {
                  character_status = 132;
                  }
        }
      }   
    }


void pmtest(void)
  {
      POKEW (DLISTW,&display_list_game);
      POKEW (SDLSTW,&display_list_game); 	  
      POKEW (SAVMSC,&SCREEN_ADDR); 
	    POKE  (CHBAS,&CHARSET_GAME_HI);
      POKE  (PMBASE,&PMBANK_HI);
      POKE (DMACTL,62);
      POKE (SDMCTL,62);
      POKE (GRACTL,3);
      POKE (PRIOR,1);
      POKE (PCOLR0,202);
      POKE (PCOLR1,138);
      POKE (PCOLR2,68);
      POKE (PCOLR3,24);      
      POKE (HPOSP0,60);
      POKE (HPOSP1,80);
      POKE (HPOSP2,100);
      POKE (HPOSP3,120);
      POKE (HPOSM0,146);
      POKE (HPOSM1,144);
      POKE (HPOSM2,142);
      POKE (HPOSM3,140);
      POKE (SIZEP0,0);
      POKE (SIZEP1,0);
      POKE (SIZEP2,0);
      POKE (SIZEP3,0);
      POKE (SIZEM,0);    
      POKE (NMIEN,192);
      
       

TESTHOLD:
  for (i = 0; i<20;i++)
   {
     for (j = 0; j<240;j=j+14)
      {
        memcpy (&PMBNK0+j,SPRITEADDR_PLY0W[i],14);
        memcpy (&PMBNK1+j,SPRITEADDR_PLY0W[i],14);
        memcpy (&PMBNK2+j,SPRITEADDR_PLY0W[i],14);
        memcpy (&PMBNK3+j,SPRITEADDR_PLY0W[i],14);
        memcpy (&MIBANK+j,SPRITEADDR_PLY0W[i],14);
      }

   }
  goto TESTHOLD;
  }

//{***************************************************************************************}
//{************************************** MAIN *******************************************}
//{***************************************************************************************}

void main(void)
{ 
  topMem = chbase1 * 256;
//  TopLogicLoop:
	while (1)		
    {
      POKE (NMIEN,0);
      POKE (DMACTL,0);
      ShowTitleScreen();
		  score = 0;
	    lives = 5;
	    level = 1;
	    character_status  =  0;
	    memset(&MIBANK, 0, 1279);	          
      POKEW (DLISTW,&display_list_game);
      POKEW (SDLSTW,&display_list_game); 	  
      POKEW (SAVMSC,&SCREEN_ADDR); 
      POKEW (VDSLST,&GAME00_DLI);
	    POKE  (CHBAS,&CHARSET_GAME_HI);
      POKE  (PMBASE,&PMBANK_HI);
      POKE (DMACTL,62);
      POKE (SDMCTL,62);
      POKE (GRACTL,3);
      POKE (PRIOR,1);
      while (character_status != 159)
        {
        Initialize_Level();    
  	    POKE (COLOR0,142);	
  	    POKE (COLOR1,212);
  	    POKE (COLOR3,150);
  	    POKE (COLOR4,34);
  	    POKE (PCOLR0,202);
  	    POKE (PCOLR1,250);
  	    POKE (PCOLR2,136);
  	    POKE (PCOLR3,36);				
        POKE (SIZEP0,0);
        POKE (SIZEP1,0);
        POKE (SIZEP2,0);
        POKE (SIZEP3,0);
        POKE (SIZEM,0);
        POKE (NMIEN,192);
        POKE (DMACTL,62);
        Display_Information_Line();
        POKEW (VVBLKD,&GAME_VBI);
  			show_countdown = 180;
  			mind_color = 0x3F;				
        character_frame  = 0; 				
        prior_rt_clock  =  PEEK(RTCLOK1);
                   
        while (show_countdown > 0 || mind_color >= 0x32)     
          { 
          if (prior_rt_clock != PEEK(RTCLOK1))
              {				              
			        prior_rt_clock = PEEK(RTCLOK1);																							
      		    if (show_countdown >= 1)
                  {
      			      show_countdown = show_countdown - 1;
                  }			  					
      		    else if (mind_color > 0x31)
                  {
                  mind_color = mind_color - 1;			  						
    	  	        }
              }			
          }            
        mind_color = 0x22;
       
       
        Main_Game_Loop();
	  		if (character_status == 128) 
            { 
              lives  =  lives - 1; 
              if (lives == 255) 
                {
                character_status  =  159;
                character_px  = 0;
                Display_Information_Line();
                }              
            }  
		    if (character_status == 144)
          {
		    	   score  = score + 10;
		    	   level  = level + 1;
          }
        }
  	    if (character_status == 159)
          {
  			    while (character_status >= 80)
            { 				
  				   if (prior_rt_clock != PEEK(RTCLOK1))
              {
  					   character_status  =  character_status - 1;
  					   prior_rt_clock  =  PEEK(RTCLOK1);
              }
  				  }
  		    } 						              
    }
}


// End of Program



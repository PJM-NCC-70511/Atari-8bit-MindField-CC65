set cc65=..\bin\cc65
set PATH=..\bin;..\;..\include;..\asminc;..\lib
rem  Compile and assemble main program

rem cc65 -O2 -t atari --all-cdecl -o mindField.s MindField.c
rem cc65 -O2 -t atari --all -o mindField.s MindField.c
cc65 -t atari -o mindField.s mindfield.c
ca65 -t atari -o mindField.o mindField.s -l mindfield_listing_c.txt

rem  Assemble native routines in assembler
ca65 -t atari -o mindfield_ml.o mindfield_ml_cart.asm -l mindfield_listing_ml.txt

rem  Link binary file
ld65 -C linker_cartridge.cfg -o  mindfield.rom MindField.o mindfield_ml.o atari.lib 


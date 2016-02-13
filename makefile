# AVR programming makefile
# By Nico Vijlbrief - codeasm.com
#
# Defaults are definded here:
CC=avr-gcc
SOURCES=blink.c
TARGET=atmega328p
#LFUSE=0xE1
#HFUSE=0xD9

#suported and tested sofar
#atmega328p atmega88 atmega8

all: main prog

main: main.out
	avr-objcopy -j .text -j .data -O ihex main.out main.hex

main.out: main.c
	$(CC) -mmcu=$(TARGET) main.c -o main.out

clean:
	rm *out

cleanall: clean
	rm main.hex

prog:
	avrdude -p $(TARGET) -c usbasp -v -e -U flash:w:main.hex 

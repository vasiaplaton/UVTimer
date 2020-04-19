MCU=attiny2313
F_CPU=8000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
	avr-size -C --format=avr ${TARGET}.bin
flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -B32 -P usb

clean:
	rm -f *.bin *.hex


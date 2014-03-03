
build/flash:     file format elf32-avr


Disassembly of section .text:

00000000 <__vectors>:
   0:	0c 94 34 00 	jmp	0x68	; 0x68 <__ctors_end>
   4:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
   8:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
   c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  10:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  14:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  18:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  1c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  20:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  24:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  28:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  2c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  30:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  34:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  38:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  3c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  40:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  44:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  48:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  4c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  50:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  54:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  58:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  5c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  60:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  64:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>

00000068 <__ctors_end>:
  68:	11 24       	eor	r1, r1
  6a:	1f be       	out	0x3f, r1	; 63
  6c:	cf ef       	ldi	r28, 0xFF	; 255
  6e:	d8 e0       	ldi	r29, 0x08	; 8
  70:	de bf       	out	0x3e, r29	; 62
  72:	cd bf       	out	0x3d, r28	; 61

00000074 <__do_copy_data>:
  74:	11 e0       	ldi	r17, 0x01	; 1
  76:	a0 e0       	ldi	r26, 0x00	; 0
  78:	b1 e0       	ldi	r27, 0x01	; 1
  7a:	e4 e9       	ldi	r30, 0x94	; 148
  7c:	f1 e0       	ldi	r31, 0x01	; 1
  7e:	02 c0       	rjmp	.+4      	; 0x84 <__do_copy_data+0x10>
  80:	05 90       	lpm	r0, Z+
  82:	0d 92       	st	X+, r0
  84:	a8 30       	cpi	r26, 0x08	; 8
  86:	b1 07       	cpc	r27, r17
  88:	d9 f7       	brne	.-10     	; 0x80 <__do_copy_data+0xc>
  8a:	0e 94 4b 00 	call	0x96	; 0x96 <main>
  8e:	0c 94 c8 00 	jmp	0x190	; 0x190 <_exit>

00000092 <__bad_interrupt>:
  92:	0c 94 00 00 	jmp	0	; 0x0 <__vectors>

00000096 <main>:
  96:	cf 93       	push	r28
  98:	df 93       	push	r29
  9a:	88 e1       	ldi	r24, 0x18	; 24
  9c:	0f b6       	in	r0, 0x3f	; 63
  9e:	f8 94       	cli
  a0:	80 93 60 00 	sts	0x0060, r24
  a4:	10 92 60 00 	sts	0x0060, r1
  a8:	0f be       	out	0x3f, r0	; 63
  aa:	f8 94       	cli
  ac:	0e 94 74 00 	call	0xe8	; 0xe8 <setupLeds>
  b0:	78 94       	sei
  b2:	c0 e0       	ldi	r28, 0x00	; 0
  b4:	d0 e0       	ldi	r29, 0x00	; 0
  b6:	02 c0       	rjmp	.+4      	; 0xbc <main+0x26>
  b8:	c0 e0       	ldi	r28, 0x00	; 0
  ba:	d0 e0       	ldi	r29, 0x00	; 0
  bc:	0e 94 a2 00 	call	0x144	; 0x144 <nbLeds>
  c0:	c8 17       	cp	r28, r24
  c2:	d9 07       	cpc	r29, r25
  c4:	cc f7       	brge	.-14     	; 0xb8 <main+0x22>
  c6:	ce 01       	movw	r24, r28
  c8:	0e 94 a5 00 	call	0x14a	; 0x14a <ledOn>
  cc:	8f ef       	ldi	r24, 0xFF	; 255
  ce:	93 ed       	ldi	r25, 0xD3	; 211
  d0:	a0 e3       	ldi	r26, 0x30	; 48
  d2:	81 50       	subi	r24, 0x01	; 1
  d4:	90 40       	sbci	r25, 0x00	; 0
  d6:	a0 40       	sbci	r26, 0x00	; 0
  d8:	e1 f7       	brne	.-8      	; 0xd2 <main+0x3c>
  da:	00 c0       	rjmp	.+0      	; 0xdc <main+0x46>
  dc:	00 00       	nop
  de:	ce 01       	movw	r24, r28
  e0:	0e 94 b6 00 	call	0x16c	; 0x16c <ledOff>
  e4:	21 96       	adiw	r28, 0x01	; 1
  e6:	ea cf       	rjmp	.-44     	; 0xbc <main+0x26>

000000e8 <setupLeds>:
  e8:	44 b1       	in	r20, 0x04	; 4
  ea:	81 e0       	ldi	r24, 0x01	; 1
  ec:	90 e0       	ldi	r25, 0x00	; 0
  ee:	9c 01       	movw	r18, r24
  f0:	00 90 00 01 	lds	r0, 0x0100
  f4:	02 c0       	rjmp	.+4      	; 0xfa <setupLeds+0x12>
  f6:	22 0f       	add	r18, r18
  f8:	33 1f       	adc	r19, r19
  fa:	0a 94       	dec	r0
  fc:	e2 f7       	brpl	.-8      	; 0xf6 <setupLeds+0xe>
  fe:	42 2b       	or	r20, r18
 100:	44 b9       	out	0x04, r20	; 4
 102:	44 b1       	in	r20, 0x04	; 4
 104:	9c 01       	movw	r18, r24
 106:	00 90 02 01 	lds	r0, 0x0102
 10a:	02 c0       	rjmp	.+4      	; 0x110 <setupLeds+0x28>
 10c:	22 0f       	add	r18, r18
 10e:	33 1f       	adc	r19, r19
 110:	0a 94       	dec	r0
 112:	e2 f7       	brpl	.-8      	; 0x10c <setupLeds+0x24>
 114:	42 2b       	or	r20, r18
 116:	44 b9       	out	0x04, r20	; 4
 118:	44 b1       	in	r20, 0x04	; 4
 11a:	9c 01       	movw	r18, r24
 11c:	00 90 04 01 	lds	r0, 0x0104
 120:	02 c0       	rjmp	.+4      	; 0x126 <setupLeds+0x3e>
 122:	22 0f       	add	r18, r18
 124:	33 1f       	adc	r19, r19
 126:	0a 94       	dec	r0
 128:	e2 f7       	brpl	.-8      	; 0x122 <setupLeds+0x3a>
 12a:	42 2b       	or	r20, r18
 12c:	44 b9       	out	0x04, r20	; 4
 12e:	24 b1       	in	r18, 0x04	; 4
 130:	00 90 06 01 	lds	r0, 0x0106
 134:	02 c0       	rjmp	.+4      	; 0x13a <setupLeds+0x52>
 136:	88 0f       	add	r24, r24
 138:	99 1f       	adc	r25, r25
 13a:	0a 94       	dec	r0
 13c:	e2 f7       	brpl	.-8      	; 0x136 <setupLeds+0x4e>
 13e:	28 2b       	or	r18, r24
 140:	24 b9       	out	0x04, r18	; 4
 142:	08 95       	ret

00000144 <nbLeds>:
 144:	84 e0       	ldi	r24, 0x04	; 4
 146:	90 e0       	ldi	r25, 0x00	; 0
 148:	08 95       	ret

0000014a <ledOn>:
 14a:	25 b1       	in	r18, 0x05	; 5
 14c:	fc 01       	movw	r30, r24
 14e:	ee 0f       	add	r30, r30
 150:	ff 1f       	adc	r31, r31
 152:	e0 50       	subi	r30, 0x00	; 0
 154:	ff 4f       	sbci	r31, 0xFF	; 255
 156:	81 e0       	ldi	r24, 0x01	; 1
 158:	90 e0       	ldi	r25, 0x00	; 0
 15a:	00 80       	ld	r0, Z
 15c:	02 c0       	rjmp	.+4      	; 0x162 <ledOn+0x18>
 15e:	88 0f       	add	r24, r24
 160:	99 1f       	adc	r25, r25
 162:	0a 94       	dec	r0
 164:	e2 f7       	brpl	.-8      	; 0x15e <ledOn+0x14>
 166:	28 2b       	or	r18, r24
 168:	25 b9       	out	0x05, r18	; 5
 16a:	08 95       	ret

0000016c <ledOff>:
 16c:	25 b1       	in	r18, 0x05	; 5
 16e:	fc 01       	movw	r30, r24
 170:	ee 0f       	add	r30, r30
 172:	ff 1f       	adc	r31, r31
 174:	e0 50       	subi	r30, 0x00	; 0
 176:	ff 4f       	sbci	r31, 0xFF	; 255
 178:	81 e0       	ldi	r24, 0x01	; 1
 17a:	90 e0       	ldi	r25, 0x00	; 0
 17c:	00 80       	ld	r0, Z
 17e:	02 c0       	rjmp	.+4      	; 0x184 <ledOff+0x18>
 180:	88 0f       	add	r24, r24
 182:	99 1f       	adc	r25, r25
 184:	0a 94       	dec	r0
 186:	e2 f7       	brpl	.-8      	; 0x180 <ledOff+0x14>
 188:	80 95       	com	r24
 18a:	82 23       	and	r24, r18
 18c:	85 b9       	out	0x05, r24	; 5
 18e:	08 95       	ret

00000190 <_exit>:
 190:	f8 94       	cli

00000192 <__stop_program>:
 192:	ff cf       	rjmp	.-2      	; 0x192 <__stop_program>

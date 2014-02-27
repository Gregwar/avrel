; Exemple d'assembleur AVR pour le blink-led

; Vecteurs d'initialisation
00000000 <__vectors>:
; Vecteur de reset, appelé au moment du démarrage du processeur:
   0:	0c 94 34 00 	jmp	0x68	; 0x68 <__ctors_end>
   4:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
   8:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
   c:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  10:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  14:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  18:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  1c:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  20:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  24:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  28:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  2c:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  30:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  34:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  38:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  3c:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  40:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  44:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  48:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  4c:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  50:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  54:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  58:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  5c:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  60:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>
  64:	0c 94 3e 00 	jmp	0x7c	; 0x7c <__bad_interrupt>

; Initialisation
00000068 <__ctors_end>:
  ; On met SREG à 0
  68:	11 24       	eor	r1, r1
  6a:	1f be       	out	0x3f, r1	; 63 (SREG)

  ; On initialise la pile a 2303
  6c:	cf ef       	ldi	r28, 0xFF	; 255
  6e:	d8 e0       	ldi	r29, 0x08	; 8
  70:	de bf       	out	0x3e, r29	; 62
  72:	cd bf       	out	0x3d, r28	; 61

  ; Appel de main
  74:	0e 94 40 00 	call	0x80	; 0x80 <main>

  ; Saut dans exit
  78:	0c 94 60 00 	jmp	0xc0	; 0xc0 <_exit>

  ; Lors d'une interruption non traité, on reset la puce en sautant à
  ; l'adresse 0 (reset)
0000007c <__bad_interrupt>:
  7c:	0c 94 00 00 	jmp	0	; 0x0 <__vectors>

  ; Code du main
00000080 <main>:
  80:	88 e1       	ldi	r24, 0x18	; 24
  82:	0f b6       	in	r0, 0x3f	; 63
  84:	f8 94       	cli
  86:	80 93 60 00 	sts	0x0060, r24
  8a:	10 92 60 00 	sts	0x0060, r1
  8e:	0f be       	out	0x3f, r0	; 63
  90:	f8 94       	cli
  92:	25 9a       	sbi	0x04, 5	; 4
  94:	78 94       	sei

  ; Début de la boucle principale
  
  ; Allume la LED (sbi = set bit) en définissant le bit 5 du registre
  ; 5, c'est à dire PORTB
  96:	2d 9a       	sbi	0x05, 5	; 5

  ; Code qui fera "perdre" 1 seconde au processeur
  98:	8f ef       	ldi	r24, 0xFF	; 255
  9a:	93 ed       	ldi	r25, 0xD3	; 211
  9c:	a0 e3       	ldi	r26, 0x30	; 48
  9e:	81 50       	subi	r24, 0x01	; 1
  a0:	90 40       	sbci	r25, 0x00	; 0
  a2:	a0 40       	sbci	r26, 0x00	; 0
  a4:	e1 f7       	brne	.-8      	; 0x9e <main+0x1e>
  a6:	00 c0       	rjmp	.+0      	; 0xa8 <main+0x28>
  a8:	00 00       	nop

  ; Eteint la LED, en clearant le bit 5 du registre 5, c'est à 
  ; dire de PORTB
  aa:	2d 98       	cbi	0x05, 5	; 5

  ; Code qui fera "perdre" 1 seconde au processeur
  ac:	8f ef       	ldi	r24, 0xFF	; 255
  ae:	93 ed       	ldi	r25, 0xD3	; 211
  b0:	a0 e3       	ldi	r26, 0x30	; 48
  b2:	81 50       	subi	r24, 0x01	; 1
  b4:	90 40       	sbci	r25, 0x00	; 0
  b6:	a0 40       	sbci	r26, 0x00	; 0
  b8:	e1 f7       	brne	.-8      	; 0xb2 <main+0x32>
  ba:	00 c0       	rjmp	.+0      	; 0xbc <main+0x3c>
  bc:	00 00       	nop

  ; Retour au début de la boucle
  be:	eb cf       	rjmp	.-42     	; 0x96 <main+0x16>

 ; Exit désactive les interruptions et boucle à l'infini
000000c0 <_exit>:
  c0:	f8 94       	cli

000000c2 <__stop_program>:
  c2:	ff cf       	rjmp	.-2      	; 0xc2 <__stop_program>

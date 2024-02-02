#include <iostream>
using namespace std;

void mul_20()
{
	unsigned char a = 5;
	unsigned short y;

	_asm {
		mov al, a
		shl al, 4
		mov bl, al
		shr bl, 2
		add al, bl
		mov ah, 0
		mov y, ax
	}

	printf("%d", y);
}

void if_else_not_equals()
{
	unsigned char y, a;
	a = 0x32;

	__asm {
		mov al, a;
		sub al, 0x32;
		jnz isfalse;
		mov y, 1;
		jmp close;
	isfalse:
		mov y, 0;
	close:
	}
	printf("%d", y);
}

void if_else_not_equals_bool_true()
{
	unsigned char a = 0x12;
	bool y;

	__asm {
		mov al, a
		sub al, 0x32
		mov y, al
	}
	printf("%s", y ? "true" : "false");
}

void for_loop()
{
	unsigned int y = 0;

	_asm {
		mov eax, 0;
	_loop:
		sub eax, 5;
		jz _break;
		add eax, 5;
		add y, eax;
		add eax, 1;
		jmp _loop;
	_break:
	}
	printf("%d", y);
}

void while_loop()
{
	unsigned int y = 0;

	_asm {
		mov eax, y
		_loop :
		sub eax, 5
			jz _break
			add eax, 6
			jmp _loop
			_break :
		add eax, 5
			mov y, eax
	}
	printf("%d", y);
}

void byte_count_zeros()
{
	unsigned char y;
	y = 0;

	__asm
	{
		mov bl, 0;
		mov al, 0x00;
	_loop:
		mov cl, al;
		and cl, 1;
		add bl, cl;
		shr al, 1;
		jnz _loop;

		mov dl, 8;
		sub dl, bl;
		mov y, dl;
	}

	printf("%d", y);
}

void test()
{
	char a = 5;
	int b;

	__asm
		{
		mov eax, 0
		mov al, a
		mov b, eax
		}
	printf("%d", b);
}

void mul_by_float()
{
	short a, y;
	a = 1000;

	_asm {
		mov ax, a
		mov bx, ax

		shr bx, 3
		add ax, bx

		mov y, ax
	}
	printf("%d", y);
}

void zad1()
{
	typedef union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char a : 3;
			unsigned char b : 2;
			unsigned char c : 3;
		} bits;
	} un_X;
	un_X x;
	// 000.1 0.101
	//| c | b | a |
	x.bits.a = 0x05;
	x.bits.b = 0x02;
	x.bits.c = 0x00;
	printf("byte: %x\n", x.BYTE); // 0001 0101 (0x15)

	while (x.bits.b > 1)
	{
		printf("c: %d\tb: %d\n", x.bits.c, x.bits.b);
		x.bits.c = 3 * x.bits.b++;
		printf("c: %d\tb: %d\n\n", x.bits.c, x.bits.b);
	}
	printf("byte: %x\n", x.BYTE); // 0001 0101 (0x15)

	x.bits.a = 0x05;
	x.bits.b = 0x02;
	x.bits.c = 0x00;
	printf("byte: %x\n", x.BYTE); // 0001 0101 (0x15)

	// 0x01 = 0000 0001 -> 1111 1110

	_asm {
		mov al, x.BYTE // 0001 0101
		mov bl, al
		and bl, 0x18 // 0001 0000
		shr bl, 3 // 0000 0010

		_loop:
		mov dl, bl
			add dl, 0xFE // 0000 0010 + 1111 1110 = 1 0000 0000 - first iteration (add left comp number to the right reversed(neg) comp number -> (x.bits.b > 0x01) -> x.bits.b + ~0x01 = x.bits.b + 0xFE)
			jnc _end // if bl <= 1 jump

			mov cl, bl
			shl cl, 1
			add cl, bl // y = 2^1 + 2^0 = 2 + 1 = 3 = (b << 1) + b ---> cl = 0x06 (0000 0110)

			and cl, 0x07 // 0000 0110
			shl cl, 5 // 1100 0000
			and al, 0x1F // 0001 0101

			add al, cl // 1101 0101

			add bl, 1 // ++

			and bl, 0x03
			mov dl, bl
			shl dl, 3

			and al, 0xE7 // 1110 0111
			add al, dl

			jmp _loop

			_end :
		mov x.BYTE, al
	}
	printf("c: %d\tb: %d\n\n", x.bits.c, x.bits.b);
	printf("byte: %x\n", x.BYTE);

	// c: 0    b: 2
	// c: 6    b: 3

	// c: 6    b: 3
	// c: 1    b: 0 - wynik
}

void zad14()
{
	typedef union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char a : 1;
			unsigned char b : 3;
			unsigned char c : 4;
		} bits;
	} un_X;

	un_X x;
	// 1.101 1001
	x.bits.a = 0x01;
	x.bits.b = 0x05;
	x.bits.c = 0x09;
	unsigned char bpom;

	printf("0x%x\n", x.BYTE);

	x.BYTE &= 0x0F;
	if (x.BYTE & 0x01)
	{
		bpom = x.BYTE & 0x0E;
		bpom <<= 3;
		x.BYTE |= bpom;
	}

	_asm {
		mov al, x.BYTE
		and al, 0x0F
		mov bl, al

		and bl, 0x01
		jz _end

		mov cl, al
		and cl, 0x0E
		shl cl, 3

		or al, cl

		mov x.BYTE, al

		_end :
	}

	printf("0x%x", x.BYTE);
}

void lower_bigger()
{

	char a, b;
	a = 0x04;

	//__asm {
	//	mov al, a
	//
	//	add al, 0xFB // 0x04 + 0xFB = 0000 0100 + 1111 1011 = 1111 1111 = 255
	//	jc _then
	//	mov b, 0
	//	jmp _end
	//
	//_then:
	//	mov b, 1
	//_end:
	//}
	// printf("%d", b);

	// 0x05 = 0000 0101
	// 0xFA = 1111 1010

	__asm {
		mov al, a // 0000 0100

		add al, 0xFB // 0x04 + 0xFA = 0xFE (0000 0100 + 1111 1010 = 1111 1110) = 254
		jnc _then
		mov b, 0
		jmp _end

		_then :
		mov b, 1
			_end :
	}
	printf("%d", b);
}

void for_with_minus()
{
	short a;
	a = 0;

	_asm {

		mov ax, a
		mov cx, 5

	_loop:
		mov dx, 0
		cmp dx, cx
		jz _end

		mov dx, cx // 0000 0000 0000 0101
		xor dx, 0xffff // 1111 1111 1111 1010
		add dx, 1 // 1111 1111 1111 1011
		add ax, dx // 1111 1111 1111 1011

		add cx, 0xffff
		jmp _loop

	_end:
		mov a, ax
	}
	printf("%d", a);
}

void lower_for()
{
	// for (int i = 0; i < 5; i++) += y;

	unsigned int a, y;
	a = 0;

	_asm {
		mov eax, 0 // y
		mov ecx, 0 // i

	_loop:
		mov edx, ecx
		add edx, 0xFFFFFFFB // 0xFFFB = 1111 1111 1111 1111 1111 1111 1111 1011
		jc _end

		add eax, ecx
		
		add ecx, 1
		jmp _loop

	_end:
		mov y, eax
	}
	printf("%d", y);
}

void bigger_equals_for()
{
	// for (int i = 5; i >= 5; i--) -= y;

	int a, y;
	a = 0;

	_asm {
		mov eax, a
		mov ecx, 5 // i

	_loop:
		mov edx, ecx
		add edx, 0xFFFFFFFF // 0xFFFFFFFF = ...1111 1111
		jnc _end


		mov edx, ecx // ...0000 0101
		xor edx, 0xFFFFFFFF // ...1111 1010 = 250
		add edx, 1 // ...1111 1011 = 251
		add eax, edx // 0 + 251 = 251

		add ecx, 0xFFFFFFFF // 5 + 255 = 4
		jmp _loop

	_end:
		mov y, eax
	}
	printf("%d", y);
}

void zad13()
{
	typedef union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char a : 2;
			unsigned char b : 3;
			unsigned char c : 3;
		} bits;
	} un_X;

	un_X x;
	// 001 010 00
	//	c	b   a
	x.bits.a = 0;
	x.bits.b = 2;
	x.bits.c = 1;
	printf("BYTE: %d\na: %d\tb: %d\tc: %d\n\n", x.BYTE, x.bits.a, x.bits.b, x.bits.c);

	_asm {
		mov al, x.bits
		mov cl, al

		and cl, 0x20
		shr cl, 5
		sub cl, 1
		jnz _else

		mov cl, al
		and cl, 0x0C
		shr cl, 2

		and al, 0xFC
		add al, cl

		mov x.bits, al

	_else:
	}
	printf("BYTE: %d\na: %d\tb: %d\tc: %d", x.BYTE, x.bits.a, x.bits.b, x.bits.c);
}

void kolok()
{
	typedef union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char a : 3;
			unsigned char b : 5;
		} bits;
	} un_X;

	un_X x;

	x.bits.a = x.bits.b * 0.75;

	_asm {
		mov al, x.BYTE
		mov bl, al
		

		; Shift right by 2 to divide by 4 (x.bits.b / 4)
    	shr al, 2

    	; Add x.bits.b / 4 to itself (2 * x.bits.b / 4)
    	add al, al
	}
}

int main()
{
	zad13();
	return 0;
}
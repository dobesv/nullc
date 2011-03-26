#pragma once

#ifdef NULLC_BUILD_X86_JIT
// Implementations of some functions, called from user binary code

#ifdef __linux
int intPow(int power, int number)
{
	// http://en.wikipedia.org/wiki/Exponentiation_by_squaring
	int result = 1;
	while(power)
	{
		if(power & 1)
		{
			result *= number;
			power--;
		}
		number *= number;
		power /= 2;
	}
	return result;
}

void doublePow() 
{
	// x**y
	// st0 == x
	// st1 == y
	asm("push %eax ; \
	movw $0x1f7f, 2(%esp); \
\
	fstcw (%esp); \
	fldcw 2(%esp);\
\
	fldz ;\
	fcomip %st(1),%st(0) ; \
	je Zero ; \
\
	fyl2x ;\
	fld %st(0) ;\
	frndint ; \
	fsubr %st(1), %st(0) ; \
	f2xm1 ; \
	fld1 ; \
	faddp %st(0), %st(1); \
	fscale ; \
\
	Zero:\
	fxch %st(1) ;\
	fstp %st(0) ;\
	\
	fldcw (%esp) ; \
	pop %eax ;");
}


#else

__declspec(naked) void intPow()
{
	// http://en.wikipedia.org/wiki/Exponentiation_by_squaring
	//eax is the power
	//ebx is the number
	__asm
	{
		push ebx ;
		mov eax, [esp+8] ;
		mov ebx, [esp+12] ;
		mov edx, 1 ; //edx is the result
		whileStart: ; 
		cmp eax, 0 ; //while(power)
		jz whileEnd ;
		  test eax, 1 ; // if(power & 1)
		  je skipIf ;
			imul edx, ebx ; // result *= number
			sub eax, 1 ; //power--;
		  skipIf: ;
			imul ebx, ebx ; // number *= number
			shr eax, 1 ; //power /= 2
		  jmp whileStart ;
		whileEnd: ;
		pop ebx ;
		ret ;
	}
}

__declspec(naked) void doublePow()
{
	// x**y
	// st0 == x
	// st1 == y
	__asm
	{
		push eax ; // ���� ������� ���� �������� fpu
		mov word ptr [esp+2], 1F7Fh ; //�������� ���� � ����������� � 0

		fstcw word ptr [esp] ; //�������� ���� ��������
		fldcw word ptr [esp+2] ; //��������� ���

		fldz ;
		fcomip st,st(1) ; // ������� x � 0.0
		je Zero ; // ���� ���, ������ 0.0

		fyl2x ; //st0 = y*log2(x)
		fld st(0) ; //���������
		frndint ; //�������� ����
		fsubr st, st(1) ; //st1=y*log2(x), st0=fract(y*log2(x))
		f2xm1 ; //st0=2**(fract(y*log2(x)))-1
		fld1 ; //�������� ����
		faddp st(1), st; //���������, st0=2**(fract(y*log2(x)))
		fscale ; //������� st0=2**(y*log2(x))

		Zero:
		fxch st(1) ; //�������� st0 � st1
		fstp st(0) ; //����� st0
		
		fldcw word ptr [esp] ; //���������� ���� ��������
		pop eax ;
		ret
	}
}
#endif

double doubleMod(double a, double b)
{
	return fmod(b, a);
}

long long longMul(long long a, long long b)
{
	return b * a;
}

long long longDiv(long long a, long long b)
{
	return b / a;
}

long long longMod(long long a, long long b)
{
	return b % a;
}

long long longShl(long long a, long long b)
{
	return b << a;
}

long long longShr(long long a, long long b)
{
	return b >> a;
}

#ifdef __linux

long long longPow(long long power, long long number)
{
	if(power < 0)
		return 0;
	long long result = 1;
	while(power)
	{
		if(power & 1)
		{
			result *= number;
			power--;
		}
		number *= number;
		power >>= 1;
	}
	return result;
}

#else

__declspec(naked) void longPow()
{
	// ���, ����� ��������� � 8 ������ � [esp+12]
	// ������� ��������� � 8 ������ � [esp+4] (������� �������� eip)
	__asm
	{
		// ��������� �� �����, ���� ��� ����� 1 ��� 0, ������ ��� �������
		cmp dword ptr [esp+16], 0 ;
		jne greaterThanOne ;
		cmp dword ptr [esp+12], 1 ;
		jg greaterThanOne ;
		mov eax, dword ptr [esp+12] ;
		xor edx, edx ;
		ret ;

		greaterThanOne:
		// ��������� �� �������, ��� ������ ���� �� ������ 63, ����� ������ 0
		cmp dword ptr [esp+8], 0 ;
		jne returnZero ;
		cmp dword ptr [esp+4], 63 ;
		jle fullPower ;

		returnZero:
		xor eax, eax ;
		xor edx, edx ;
		ret ;

		fullPower:
		push edi ;
		push esi ; // �������� ��� ��� ��������, ������ ��� ��� ����� ������� ����� �������� �����
		// ����: numHigh, numLow, expHigh, expLow, EIP,  EDI,  ESI
		//       esp+24   esp+20  esp+16   esp+12  esp+8 esp+4 esp

		// ����� ������� � edi:esi
		mov edi, dword ptr [esp+24] ;
		mov esi, dword ptr [esp+20] ;
		// ��������� ���� ����� ������������ �� �������� �����, ��� ���� �������
		push 0 ;
		push 1 ; // ��������� ���� ����� 1
		whileStart: ;
		mov eax, dword ptr [esp+12+8] ;
		or eax, eax ;//dword ptr [esp+16+8] ; //while(power)
		jz whileEnd ;
		  mov eax, dword ptr [esp+12+8]
		  test eax, 1 ;
		  jz skipIf ;
			push edi ;
			push esi ; // ������ � ����� ������� ��������� � �����
			call longMul ;
			mov dword ptr [esp+8], eax ;
			mov dword ptr [esp+12], edx ; // �������� ���������
			add esp, 8 ; // �������� ������� ������ ���������
			sub dword ptr [esp+12+8], 1 ;
			//sbb dword ptr [esp+16+8], 0 ; //power--;
		  skipIf: ;
			push edi ;
			push esi ; // �������� ����� � ����
			xchg edi, dword ptr [esp+12] ;
			xchg esi, dword ptr [esp+8] ; // �������� ����� � ���������, ������ ����� � ����� ������
			call longMul ; // number *= number
			mov dword ptr [esp+8], eax ;
			mov dword ptr [esp+12], edx ; // �������� ���������
			add esp, 8 ; // �������� ������� ������ ������� �����
			xchg edi, dword ptr [esp+4] ;
			xchg esi, dword ptr [esp] ; // �������� ����� � ���������, ��������� ����� � �����
			shr dword ptr [esp+12+8], 1 ; //power /= 2
			//mov eax, dword ptr [esp+16+8]
			//shrd dword ptr [esp+12+8], eax, 1 ; //power /= 2
		  jmp whileStart ;
		whileEnd: ;
		mov edx, dword ptr [esp+4] ;
		mov eax, dword ptr [esp] ;
		add esp, 8 ;
		pop esi ;
		pop edi ;
		ret ;
	}
}

#endif

#endif

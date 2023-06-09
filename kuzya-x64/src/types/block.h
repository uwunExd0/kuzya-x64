#pragma once
#include <iostream>

class byte;
class block// класс описывающий блок данных для шифрования (16 байт/128 бит)
{
public:
	byte* value;
	block();
	block(const void* buffer);
	block(const block& buffer);
	block(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h, uint8_t i, uint8_t j, uint8_t k, uint8_t l, uint8_t m, uint8_t n, uint8_t o, uint8_t p);

	~block();

	block& operator=(const block& buffer);
	block& operator=(const void* buffer);

	byte& operator[](int indx);
	const byte& operator[](int indx) const;

	block operator+(const block& a);// сложение блоков / преобразование X (xor байт одного блока с байтами другого блока)
	void operator+=(const block& a);

	void operator<<=(const int pos);// сдвиг на 1 влева (больше алгоритму не требуется, поэтому реализовывать не стал)

	void Clear();
	std::string ToString();

	static block S(block& a);
	static void R(block& state);
	static block L(block& in);

	static block InverseS(block& a);
	static void InverseR(block& state);
	static block InverseL(block& in);

	inline static size_t GetSize() {
		return 16; // 128 бит
	}
};

std::ostream& operator<<(std::ostream& stream, const block& block);
extern byte PI[256];
extern byte invPI[256];
extern byte vecL[256];

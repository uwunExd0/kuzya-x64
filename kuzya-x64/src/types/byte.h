#pragma once
using uint8_t = unsigned char;

class byte//класс описывающий 1 байт данных а также операции сложения и умножения
{
public:
	uint8_t value;
	byte();
	byte(const uint8_t& _value);
	byte(const byte& _value);

	byte operator+(const byte& a);//сложение / xor
	byte operator+(const uint8_t& a);

	void operator+=(const byte& a);
	void operator+=(const uint8_t& a);

	byte operator*(const byte& a);// умножение в поле GF(2^8), порождающий полином = x^8 + x^7 + x^6 + x + 1
	byte operator*(const uint8_t& a);

	byte& operator=(const byte& a);
	byte& operator=(const uint8_t& a);

	operator uint8_t() const;
	operator uint8_t();
};
extern uint8_t gf256[];// результаты умножения в поле GF(2^8): a*b = gf256[256*a+b]


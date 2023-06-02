#pragma once
using uint8_t = unsigned char;

class byte
{
public:
	uint8_t value;
	byte();
	byte(const uint8_t& _value);
	byte(const byte& _value);

	byte operator+(const byte& a);
	byte operator+(const uint8_t& a);

	void operator+=(const byte& a);
	void operator+=(const uint8_t& a);

	byte operator*(const byte& a);
	byte operator*(const uint8_t& a);

	byte& operator=(const byte& a);
	byte& operator=(const uint8_t& a);

	operator uint8_t() const;
	operator uint8_t();
};
extern uint8_t gf256[];


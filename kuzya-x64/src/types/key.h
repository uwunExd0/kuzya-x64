#pragma once
#include <iostream>

class block;
class key
{
private:
	static key F(key& k, block& c);
public:
	block left, right;
	block* roundKeys;

	key();
	key(block& left, block& right);
	key(const void* buffer);
	key(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h, uint8_t i, uint8_t j, uint8_t k, uint8_t l, uint8_t m, uint8_t n, uint8_t o, uint8_t p, uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t h1, uint8_t i1, uint8_t j1, uint8_t k1, uint8_t l1, uint8_t m1, uint8_t n1, uint8_t o1, uint8_t p1);
	key(const key& _key);

	key& operator=(const key& buffer);

	void Expand();
	void SetRandom();
};

std::ostream& operator<<(std::ostream& stream, const key& key);

extern block iterC[32];
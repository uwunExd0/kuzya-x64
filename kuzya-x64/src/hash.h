#pragma once
#include "types/block.h"
#include "types/byte.h"
#include "types/key.h"

class Gost
{
private:
	key _key;
public:
	Gost();
	Gost(key& key);
	
	block Encrypt(block& buffer);
	block Decrypt(block& buffer);

	block Hash(const void* message, size_t size);
};
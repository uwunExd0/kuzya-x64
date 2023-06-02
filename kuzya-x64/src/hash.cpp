#include "hash.h"

Gost::Gost()
{
	_key.SetRandom();
	_key.Expand();
}

Gost::Gost(key& key)
{
	_key = key;
	_key.Expand();
}

block Gost::Encrypt(block& buffer)
{
    block result = buffer;

    for (int i = 0; i < 9; ++i)
    {
        result += _key.roundKeys[i];
        result = block::S(result);
        result = block::L(result);
    }

    result += _key.roundKeys[9];

    return result;
}

block Gost::Decrypt(block& buffer)
{
    block result = buffer;

    for (int i = 9; i > 0; --i)
    {
        result += _key.roundKeys[i];
        result = block::InverseL(result);
        result = block::InverseS(result);
    }

    result += _key.roundKeys[0];

    return result;
}

block Gost::Hash(const void* message, size_t size)
{
    size_t mod = size % block::GetSize();
    size_t intCountBlocks = size / block::GetSize();
    size_t countBlocks = mod ? intCountBlocks + 1 : intCountBlocks;
    
    block* buffer = new block[countBlocks];

    uint8_t* temp_arr = new uint8_t[countBlocks*block::GetSize()];
    memset(temp_arr, 0, countBlocks * block::GetSize());
    memcpy(temp_arr, message, size);

    if (mod)
    {
        temp_arr[size] = 0x80;
    }

    for (int i = 0; i < countBlocks; i++)
    {
        buffer[i] = temp_arr + i * block::GetSize();
    }

    block helpKeys[2];
    block tmp;

    block Bn;
    Bn[0] = 0x87;
    tmp = Encrypt(tmp);
    tmp <<= 1;
    helpKeys[0] = tmp[15] & 1 ? tmp + Bn : tmp;
    tmp = helpKeys[0];
    tmp <<= 1;
    helpKeys[1] = tmp[15] & 1 ? tmp + Bn : tmp;

    block* C = new block[countBlocks];
    for (int i = 0; i < countBlocks-1; ++i)
    {
        block t = buffer[i] + C[i];
        C[i + 1] = Encrypt(t);
    }

    block keyStar = mod ? helpKeys[1] : helpKeys[0];
    block result = buffer[countBlocks - 1] + C[countBlocks - 1] + keyStar;

    delete[] buffer;
    delete[] temp_arr;
    delete[] C;

    return Encrypt(result);
}

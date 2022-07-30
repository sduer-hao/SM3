#ifndef SM3_SM3_H
#define SM3_SM3_H

#include <cstdint>
#include <vector>

class SM3 {
private:
    static void CF(uint32_t* V, uint8_t* B);
    static uint32_t P0(uint32_t X);
    static uint32_t P1(uint32_t X);
    static uint32_t FF(int j, uint32_t X, uint32_t Y, uint32_t Z);
    static uint32_t GG(int j, uint32_t X, uint32_t Y, uint32_t Z);
    static uint32_t T(int j);
public:
    static uint32_t* hash(uint8_t* input, uint32_t inputLen);
};

int birthday();
uint32_t* Rho(uint32_t* hash);

#endif //SM3_SM3_H
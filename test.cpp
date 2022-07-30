#include <iostream>
#include "SM3.h"

int main() {
    //uint8_t input[] = { 0x61, 0x62, 0x63};
    uint8_t input[] = { 0xab, 0xcd, 0xef };
    uint32_t* hash = SM3::hash(input, 3);
    for (int i = 0; i < 8; i++) {
        printf("%x ", hash[i]);
    }
    printf("\n");
    
    //birthday();
    Rho(hash);
}
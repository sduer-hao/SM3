#include "SM3.h"

#define ROTATELEFT(X, n)  (((X)<<(n)) | ((X)>>(32-(n))))

uint32_t* SM3::hash(uint8_t* input, uint32_t inputLen) { 
    uint32_t VI[] = { 0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e };
    uint32_t* state = new uint32_t[8];

    for (int i = 0; i < 8; i++) {
        state[i] = VI[i];
    }

    uint8_t buf[64];
    int inputPtr = 0;
    int bufPtr = 0;

    while (inputPtr < inputLen) {
        buf[bufPtr] = input[inputPtr];
        inputPtr++;
        bufPtr++;

        if (bufPtr == 64) {
            CF(state, buf);
            bufPtr = 0;
        }
    }

    buf[bufPtr++] = 0x80;
    if (64 - bufPtr < 8) {
        while (bufPtr < 64) buf[bufPtr++] = 0;
        bufPtr = 0;
        CF(state, buf);
    }
    while (bufPtr < 56) buf[bufPtr++] = 0;

    inputLen *= 8;
    buf[63] = static_cast<uint8_t>(inputLen & 0x00000000000000ff);
    buf[62] = static_cast<uint8_t>((inputLen & 0x000000000000ff00) >> 8);
    buf[61] = static_cast<uint8_t>((inputLen & 0x0000000000ff0000) >> 16);
    buf[60] = static_cast<uint8_t>((inputLen & 0x00000000ff000000) >> 24);
    buf[59] = static_cast<uint8_t>((inputLen & 0x000000ff00000000) >> 32);
    buf[58] = static_cast<uint8_t>((inputLen & 0x0000ff0000000000) >> 40);
    buf[57] = static_cast<uint8_t>((inputLen & 0x00ff000000000000) >> 48);
    buf[56] = static_cast<uint8_t>((inputLen & 0xff00000000000000) >> 56);

    CF(state, buf);
    return state;
}

void SM3::CF(uint32_t* V, uint8_t* Bi) {
    auto W = std::vector<uint32_t>(68, 0); // W
    auto WW = std::vector<uint32_t>(64, 0); // W'
    for (int i = 0; i < 16; ++i) {
        W[i] = 0;
        W[i] |= ((uint32_t)Bi[i * 4] << 24);
        W[i] |= ((uint32_t)Bi[i * 4 + 1] << 16);
        W[i] |= ((uint32_t)Bi[i * 4 + 2] << 8);
        W[i] |= ((uint32_t)Bi[i * 4 + 3]);
    }
    for (int i = 16; i <= 67; ++i) {
        W[i] = P1(W[i - 16] ^ W[i - 9] ^ ROTATELEFT(W[i - 3], 15)) ^ ROTATELEFT(W[i - 13], 7) ^ (W[i - 6]);
    }
    for (int i = 0; i <= 63; ++i) {
        WW[i] = W[i] ^ W[i + 4];
    }
    constexpr int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7;
    uint32_t reg[8];

    for (int j = 0; j < 8; ++j) {
        reg[j] = V[j];
    }

    for (int j = 0; j <= 63; ++j) {
        uint32_t SS1, SS2, TT1, TT2;
        SS1 = ROTATELEFT(ROTATELEFT(reg[A], 12) + reg[E] + ROTATELEFT(T(j), j), 7);
        SS2 = SS1 ^ ROTATELEFT(reg[A], 12);
        TT1 = FF(j, reg[A], reg[B], reg[C]) + reg[D] + SS2 + WW[j];
        TT2 = GG(j, reg[E], reg[F], reg[G]) + reg[H] + SS1 + W[j];
        reg[D] = reg[C];
        reg[C] = ROTATELEFT(reg[B], 9);
        reg[B] = reg[A];
        reg[A] = TT1;
        reg[H] = reg[G];
        reg[G] = ROTATELEFT(reg[F], 19);
        reg[F] = reg[E];
        reg[E] = P0(TT2);

    }
    for (int i = 0; i < 8; ++i) {
        V[i] ^= reg[i];
    }
}

uint32_t SM3::P0(uint32_t X) {
    return X ^ ROTATELEFT(X, 9) ^ ROTATELEFT(X, 17);
}

uint32_t SM3::P1(uint32_t X) {
    return X ^ ROTATELEFT(X, 15) ^ ROTATELEFT(X, 23);
}

uint32_t SM3::T(int j) {
    if (j <= 15) {
        return 0x79cc4519;
    }
    else {
        return 0x7a879d8a;
    }
}

uint32_t SM3::FF(int j, uint32_t X, uint32_t Y, uint32_t Z) {
    if (j <= 15) {
        return X ^ Y ^ Z;
    }
    else {
        return (X & Y) | (X & Z) | (Y & Z);
    }
}

uint32_t SM3::GG(int j, uint32_t X, uint32_t Y, uint32_t Z) {
    if (j <= 15) {
        return X ^ Y ^ Z;
    }
    else {
        return (X & Y) | ((~X) & Z);
    }
}
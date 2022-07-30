#include"sm3.h"

uint32_t* Rho(uint32_t* hash)
{
    uint8_t tmp_hash[32];
    for (int i = 0; i < 32; i++) 
    {
        tmp_hash[i] = *((uint8_t*)hash + i);
    }
    for (int i = 0; i < 8; i++)
    {
        uint8_t tmp1 = tmp_hash[i * 4 + 3];
        uint8_t tmp2 = tmp_hash[i * 4 + 2];
        tmp_hash[i * 4 + 3] = tmp_hash[i * 4];
        tmp_hash[i * 4 + 2] = tmp_hash[i * 4 + 1];
        tmp_hash[i * 4 + 1] = tmp2;
        tmp_hash[i * 4] = tmp1;
    }

    hash = SM3::hash(tmp_hash, 32);

    uint8_t hash2[32];
	while (true)
	{
        for (int i = 0; i < 32; i++) {
            hash2[i] = *((uint8_t*)hash + i);
        }
        for (int i = 0; i < 8; i++)
        {
            uint8_t tmp1 = hash2[i * 4 + 3];
            uint8_t tmp2 = hash2[i * 4 + 2];
            hash2[i * 4 + 3] = hash2[i * 4];
            hash2[i * 4 + 2] = hash2[i * 4 + 1];
            hash2[i * 4 + 1] = tmp2;
            hash2[i * 4] = tmp1;
        }

        /*for (int i = 0; i < 32; i++) {
            printf("%x ", hash2[i]);
        }
        printf("\n");*/

        int y = 0;
        for (int i = 0; i < 32; i++)
        {
            if (tmp_hash[i] == hash2[i])y++;
            else break;
        }
        if (y > 2) {
            for (int i = 0; i < 8; i++) {
                printf("%x ", hash[i]);
            }
            printf("\n");
            break;
        }

		hash = SM3::hash(hash2, 32);
        /*for (int i = 0; i < 8; i++) {
            printf("%x ", hash[i]);
        }
        printf("\n");*/
        
	}
    return hash;
}
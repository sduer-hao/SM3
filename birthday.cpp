#include"sm3.h"
#include<random>
#include<time.h>

int birthday()
{
	srand((unsigned)time(0));
	while (true)
	{
		
		uint32_t rand_len1 = 64;
		uint32_t rand_len2 = 64;
		uint8_t* input1 = new uint8_t[rand_len1];
		uint8_t* input2 = new uint8_t[rand_len2];
		for (int i = 0; i < rand_len1; i++)
		{
			input1[i] = (rand() % 497) + 16;
			//printf("%x ", input1[i]);
		}
		//printf("\n");
		for (int i = 0; i < rand_len2; i++)
		{
			input2[i] = (rand() % 497) + 16;
			//printf("%x ", input2[i]);
		}
		//printf("\n");

		uint32_t* hash1 = SM3::hash(input1, rand_len1);
		uint32_t* hash2 = SM3::hash(input2, rand_len2);
		/*for (int i = 0; i < 8; i++) {
			printf("%x ", hash1[i]);
		}
		printf("\n");*/


		uint8_t hash11[32], hash22[32];
		for (int i = 0; i < 32; i++) {
			hash11[i] = *((uint8_t*)hash1 + i);
			hash22[i] = *((uint8_t*)hash2 + i);
		}

		for (int i = 0; i < 8; i++)
		{
			uint8_t tmp1 = hash11[i * 4 + 3];
			uint8_t tmp2 = hash11[i * 4 + 2];
			hash11[i * 4 + 3] = hash11[i * 4];
			hash11[i * 4 + 2] = hash11[i * 4 + 1];
			hash11[i * 4 + 1] = tmp2;
			hash11[i * 4] = tmp1;
		}

		for (int i = 0; i < 8; i++)
		{
			uint8_t tmp1 = hash22[i * 4 + 3];
			uint8_t tmp2 = hash22[i * 4 + 2];
			hash22[i * 4 + 3] = hash22[i * 4];
			hash22[i * 4 + 2] = hash22[i * 4 + 1];
			hash22[i * 4 + 1] = tmp2;
			hash22[i * 4] = tmp1;
		}

		int y = 0;
		for (int i = 0; i < 32; i++)
		{
			if (hash11[i] == hash22[i])y++;
			else break;
		}
		if (y > 2) {
			for (int i = 0; i < 8; i++) {
				printf("%x ", hash1[i]);
			}
			printf("\n");
			for (int i = 0; i < 8; i++) {
				printf("%x ", hash2[i]);
			}
			printf("\n");
			for (int i = 0; i < 64; i++) {
				printf("%x ", input1[i]);
			}
			printf("\n");
			for (int i = 0; i < 64; i++) {
				printf("%x ", input2[i]);
			}
			printf("\n");
			break;
		}
	}
	return 1;
}
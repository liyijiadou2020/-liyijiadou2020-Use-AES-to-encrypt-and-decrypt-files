#ifndef DECRYPT_H
#define DECRYPT_H
#include"encryption.h"


using namespace std;

// 1 逆行变换
void InvShiftRow(byte sta_matr[4 * 4]);

// 2 逆S盒变换
void InvSubBytes(byte sta_matr[4 * 4]);

// 3 逆列变换
void InvMixColumns(byte sta_matr[4 * 4]);

// 4 解密函数
void decrypt(byte in[4 * 4], word w[4 * (Nr + 1)]);

#endif
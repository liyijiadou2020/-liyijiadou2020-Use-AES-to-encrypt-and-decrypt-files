#ifndef DECRYPT_H
#define DECRYPT_H
#include"encryption.h"


using namespace std;

// 1 ���б任
void InvShiftRow(byte sta_matr[4 * 4]);

// 2 ��S�б任
void InvSubBytes(byte sta_matr[4 * 4]);

// 3 ���б任
void InvMixColumns(byte sta_matr[4 * 4]);

// 4 ���ܺ���
void decrypt(byte in[4 * 4], word w[4 * (Nr + 1)]);

#endif
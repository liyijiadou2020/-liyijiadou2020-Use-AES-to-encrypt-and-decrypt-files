#pragma once
#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include "keyExtend.h"

using namespace std;

/*
* Ԥ������	: ����������ϵĳ˷����� 
*/
byte GFMul(byte a, byte b);

// ---------------------------------------------
// 1 ����Կ��
void RKey_Add(byte sta_matr[4 * 4], word w[4]);
// 2 �ֽڴ���
void SubBytes(byte sta_matr[4 * 4]);
// 3 ����λ--���н����ֽ���λ
void ShiftRow(byte sta_matr[4 * 4]);
// 4 �л�� 
void MixColumns(byte sta_matr[4 * 4], byte s[4 * 4]);
// ---------------------------------------------
// 5 ���ܺ���
void encrypt(byte in[4 * 4], word w[4 * (Nr + 1)]);

#endif
#include<iostream>
#include<string>
#include"decrypt.h"


using namespace std;

// 1 ���б任  ѭ������     �Ѳ���û������ 
void InvShiftRow(byte sta_matr[4 * 4]) {

	for (int i = 0; i < 4; i++) {		
		byte* temp = new byte[i]; //#�ĳ�new��û������

		//���� ��ֹ������
		for (int j = 0; j < i; j++) {
			temp[j] = sta_matr[i * 4 + 3 - j];
		}

		// �����ᷢ���±�����Ľ��и�ֵ 
		for (int j = 0; j < 4 - i; j++) {
			sta_matr[i * 4 + 3 - j] = sta_matr[i * 4 + 3 - j - i];
		}
		
		// ���ݴ�����Ż�״̬���� ���� 
		for (int m = 0; m < i; m++) {
			sta_matr[i * 4 + m] = temp[i - m - 1];
		}
	}

}
// 2 ��S�б任    û�仯û���� 
void InvSubBytes(byte sta_matr[4 * 4]) {
	// ��16���ֽ����ν��д���
	for (int i = 0; i < 16; i++) {
		//bitset��ַ����ǵ�λ��ǰ,��λ�ں�,�볣���෴,������Ҫ���� 
		int row = sta_matr[i][7] * 8 + sta_matr[i][6] * 4 + sta_matr[i][5] * 2 + sta_matr[i][4];
		int col = sta_matr[i][3] * 8 + sta_matr[i][2] * 4 + sta_matr[i][1] * 2 + sta_matr[i][0];
		sta_matr[i] = inv_S[row * 16 + col];
	}
}

// 3 ���б任   û�仯û���� 
void InvMixColumns(byte sta_matr[4 * 4], byte s[4 * 4]) {
	byte matr[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			matr[j] = sta_matr[i + j * 4];

		sta_matr[i] = GFMul(s[0], matr[0]) ^ GFMul(s[1], matr[1]) ^ GFMul(s[2], matr[2]) ^ GFMul(s[3], matr[3]);
		sta_matr[i + 4] = GFMul(s[4], matr[0]) ^ GFMul(s[5], matr[1]) ^ GFMul(s[6], matr[2]) ^ GFMul(s[7], matr[3]);
		sta_matr[i + 8] = GFMul(s[8], matr[0]) ^ GFMul(s[9], matr[1]) ^ GFMul(s[10], matr[2]) ^ GFMul(s[11], matr[3]);
		sta_matr[i + 12] = GFMul(s[12], matr[0]) ^ GFMul(s[13], matr[1]) ^ GFMul(s[14], matr[2]) ^ GFMul(s[15], matr[3]);
	}
}

// 4 ���ܺ��� 
void decrypt(byte sta_matr[4 * 4], word w[4 * (Nr + 1)]) {
	word key[4];
	for (int i = 0; i < 4; i++)
		key[i] = w[4 * Nr + i];
	//�Ƚ���һ������Կ�� 
	RKey_Add(sta_matr, key);
	//���ֲ���  ������λ   ��S�� ����Կ��  ���л�� 
	for (int r = Nr - 1; r > 0; r--)
	{
		InvShiftRow(sta_matr);
		InvSubBytes(sta_matr);
		for (int i = 0; i < 4; i++)
			key[i] = w[4 * r + i];
		RKey_Add(sta_matr, key);
		InvMixColumns(sta_matr, decry_s);
	}
	//��ʮ��   ������λ   ��S�� ����Կ�� 
	InvShiftRow(sta_matr);
	InvSubBytes(sta_matr);
	for (int i = 0; i < 4; i++)
		key[i] = w[i];
	RKey_Add(sta_matr, key);
}

#include<iostream>
#include<string>
#include"encryption.h"
using namespace std;


//�������ϵĳ˷� GF(2^8)  ��ʾ����2��N�η���Ԫ�ص�������  �����Ѳ�û���� 
// ע�������дһ�¶����Ƴ˷���֪��ԭ���� 
byte GFMul(byte a, byte b) {
	byte p = 0;
	for (int i = 0; i < 8; i++) {
		//���ж�b�ĵͽ�λ		
		if (b[0] == 1)
			p ^= a;
		//�õ�a�ĸ߽�λ 
		int temp = a[7];
		a <<= 1;
		//���Ƶ�������� �����ü���û�ж�ʧ���ݵ����ƺ�a mod m(x)  �ȼ��ڶ�ʧ���ݺ�a ^ 0x1b 
		if (temp == 1)
			a ^= 0x1b;
		b >>= 1;
	}
	return p;
}


/*
* RKey_Add(AddRoundKey) ���֧�ק� �ڧ� ��ѧ��ڧ�ѧߧڧ� �ܧݧ��֧� `w` ��էߧ� �ާѧ��ڧ�� ��ѧ٧ާ֧�� 4��Nb 
* �� ����ݧ֧ާ֧ߧ�ߧ� �է�ҧѧӧݧ�֧�(XOR) �֧� �� �ާѧ��ڧ�� �������ߧڧ� .
* ����ݧ� �էӧ� ��ѧ٧� ���ڧާ֧ߧڧ�� AddRoundKey, ��� �ߧڧ�֧ԧ� �ߧ� �ڧ٧ާ֧ߧڧ���,
* ������ާ� ���֧�ҧ�ѧ٧�ӧѧߧڧ� ��ҧ�ѧ�ߧ�� �� AddRoundKey ���� ��ߧ� ��ѧާ�.
*/
// 1 ����Կ�� ��״̬�����һ�е��ĸ��ֽں�����Կ�Ķ�Ӧ�ֽڽ������ 
void RKey_Add(byte status[4 * 4], word w[4]) {
	for (int i = 0; i < 4; i++) {
		//ÿһ�����һ�� �ĸ��ֽڵ���� 
		word k0 = w[i] >> 24;
		word k1 = (w[i] << 8) >> 24;
		word k2 = (w[i] << 16) >> 24;
		word k3 = (w[i] << 24) >> 24;

		status[i] = status[i] ^ byte(k0.to_ulong());
		status[i + 4] = status[i + 4] ^ byte(k1.to_ulong());
		status[i + 8] = status[i + 8] ^ byte(k2.to_ulong());
		status[i + 12] = status[i + 12] ^ byte(k3.to_ulong());
	}

}

/*
* SubBytes �٧ѧާ֧ߧ�֧� �ܧѧاէ�� ��ݧ֧ާ֧ߧ� �ާѧ��ڧ�� �������ߧڧ� �����ӧ֧�ӧ���ڧ� ��ݧ֧ާ֧ߧ��� 
* ��ѧҧݧڧ�� SBox: sij = SBox[sij]. ����֧�ҧ�ѧ٧�ӧѧߧڧ� SubBytes ��ҧ�ѧ�ڧާ�. ���ҧ�ѧ�ߧ�� 
* �� �ߧ֧ާ� �ߧѧ��էڧ��� �� ���ާ���� ��ѧҧݧڧ�� InvSBox.
*/
// 2 �ֽڴ���  ������û������ 
void SubBytes(byte status[4 * 4]) {
	// ��16���ֽ����ν��д���
	for (int i = 0; i < 16; i++) {
		//bitset��ַ����ǵ�λ��ǰ,��λ�ں�,�볣���෴,������Ҫ���� 
		int row = status[i][7] * 8 + status[i][6] * 4 + status[i][5] * 2 + status[i][4] * 1;
		int col = status[i][3] * 8 + status[i][2] * 4 + status[i][1] * 2 + status[i][0] * 1;
		status[i] = S[row * 16 + col];
	}
}

/*
* ShiftRows ��էӧڧԧѧ֧� i-��� �����ܧ� �ާѧ��ڧ�� s �ߧ� i ���٧ڧ�ڧ� �ӧݧ֧ӧ�, 
* ���ڧ�ѧ� i �� �ߧ�ݧ�. ���ҧ�ѧ�ߧ�� ���֧�ҧ�ѧ٧�ӧѧߧڧ� InvShiftRows ��էӧڧԧѧ֧� �����ܧ� �ӧ��ѧӧ�.
*/
 //3 ����λ--���н����ֽ���λ   �����Ѳ�û���� 
void ShiftRow(byte status[4 * 4]) {
	//�ڶ���ѭ������һ���ֽ�
	//������ѭ�����ƶ����ֽ� 
	//������ѭ�����������ֽ�

	for (int i = 0; i < 4; i++) {
		//byte temp[i];
		byte* temp = new byte[i];

		//���� ��ֹ������
		for (int j = 0; j < i; j++) {
			temp[j] = status[i * 4 + j];
		}
		// �����ᷢ���±�����Ľ��и�ֵ 
		for (int j = 0; j < 4 - i; j++) {
			status[i * 4 + j] = status[i * 4 + j + i];
		}
		// ���ݴ�����Ż�״̬���� ���� 
		for (int m = 4 - i; m < 4; m++) {
			status[i * 4 + m] = temp[m + i - 4];
		}
	}
}

/*
* MixColumns ��ާߧ�اѧ֧� �ܧѧاէ�� ����ݧҧ֧� �ާѧ��ڧ�� s ��ݧ֧ӧ� �ߧ� ����ҧ�� �ާѧ��ڧ�� ��ѧ٧ާ֧�� 4��4:
*/
// 4 �л��   ������û���� 
void MixColumns(byte status[4 * 4], byte s[4 * 4]) {
	byte matr[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			matr[j] = status[i + j * 4];

		status[i] = GFMul(s[0], matr[0]) ^ GFMul(s[1], matr[1]) ^ GFMul(s[2], matr[2]) ^ GFMul(s[3], matr[3]);
		status[i + 4] = GFMul(s[4], matr[0]) ^ GFMul(s[5], matr[1]) ^ GFMul(s[6], matr[2]) ^ GFMul(s[7], matr[3]);
		status[i + 8] = GFMul(s[8], matr[0]) ^ GFMul(s[9], matr[1]) ^ GFMul(s[10], matr[2]) ^ GFMul(s[11], matr[3]);
		status[i + 12] = GFMul(s[12], matr[0]) ^ GFMul(s[13], matr[1]) ^ GFMul(s[14], matr[2]) ^ GFMul(s[15], matr[3]);
	}

}

// 5 ���ܺ���
void encrypt(byte status[4 * 4], word w[4 * (Nr + 1)]) {
	
	word key[4];

	for (int i = 0; i < 4; i++) // ����ȡ�õ�0�ֵ���Կ
		key[i] = w[i];
	
	//�Ƚ���һ������Կ�� 
	RKey_Add(status, key);
	
	cout<<"> Round 0 Encrypting Result (Only With RoundKeyAdd)��"<<endl;
	for(int i=0;i<16;i++){
			cout<<hex<<status[i].to_ulong()<<"  ";
			if((i+1)%4==0)cout<<endl;
	}

		
	//���ֲ���   S��  ����λ  �л��  ����Կ�� 
	for (int r = 1; r < Nr; r++)
	{
		SubBytes(status); //�ֽڴ���
		ShiftRow(status); // ����λ
		MixColumns(status, encry_s); //�л��
		for (int i = 0; i < 4; i++) //����һ����Կ
			key[i] = w[4 * r + i]; 
		RKey_Add(status, key); // ����Կ��
		
		cout<<endl;
		cout<<"> Round "<<r<<" Encrypting Result: "<<endl;

		for(int i=0;i<16;i++){
		cout<<hex<<status[i].to_ulong()<<"  ";
		if((i+1)%4==0)cout<<endl;
		}  
	}
	 
	//��ʮ��   S��  ����λ  ����Կ�� 
	SubBytes(status);
	ShiftRow(status);
	for (int i = 0; i < 4; ++i)
		key[i] = w[4 * Nr + i];
	RKey_Add(status, key);
	cout << endl;

	cout<<"> Round 10 (SubBytes, ShiftRow, RoundKeyAdd) Result: "<<endl;
	for(int i=0;i<16;i++){
		cout<<hex<<status[i].to_ulong()<<"  ";
		if((i+1)%4==0)cout<<endl;
	}  

}
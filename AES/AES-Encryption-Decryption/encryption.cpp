#include<iostream>
#include<string>
#include"encryption.h"
using namespace std;


//有限域上的乘法 GF(2^8)  表示含有2的N次方个元素的有限域  代码已测没问题 
// 注意可以手写一下二进制乘法就知道原理了 
byte GFMul(byte a, byte b) {
	byte p = 0;
	for (int i = 0; i < 8; i++) {
		//先判断b的低阶位		
		if (b[0] == 1)
			p ^= a;
		//拿到a的高阶位 
		int temp = a[7];
		a <<= 1;
		//左移导致溢出了 所以用假如没有丢失数据的左移后a mod m(x)  等价于丢失数据后a ^ 0x1b 
		if (temp == 1)
			a ^= 0x1b;
		b >>= 1;
	}
	return p;
}


// 1 轮密钥加 将状态矩阵的一列的四个字节和轮密钥的对应字节进行异或   
void RKey_Add(byte sta_matr[4 * 4], word w[4]) {
	for (int i = 0; i < 4; i++) {
		//每一轮完成一列 四个字节的异或 
		word k0 = w[i] >> 24;
		word k1 = (w[i] << 8) >> 24;
		word k2 = (w[i] << 16) >> 24;
		word k3 = (w[i] << 24) >> 24;

		sta_matr[i] = sta_matr[i] ^ byte(k0.to_ulong());
		sta_matr[i + 4] = sta_matr[i + 4] ^ byte(k1.to_ulong());
		sta_matr[i + 8] = sta_matr[i + 8] ^ byte(k2.to_ulong());
		sta_matr[i + 12] = sta_matr[i + 12] ^ byte(k3.to_ulong());
	}

}

// 2 字节代换  经测试没有问题 
void SubBytes(byte sta_matr[4 * 4]) {
	// 将16个字节依次进行代换
	for (int i = 0; i < 16; i++) {
		//bitset地址存放是低位在前,高位在后,与常规相反,计算需要谨慎 
		int row = sta_matr[i][7] * 8 + sta_matr[i][6] * 4 + sta_matr[i][5] * 2 + sta_matr[i][4] * 1;
		int col = sta_matr[i][3] * 8 + sta_matr[i][2] * 4 + sta_matr[i][1] * 2 + sta_matr[i][0] * 1;
		sta_matr[i] = S[row * 16 + col];
	}


}

 //3 行移位--按行进行字节移位   代码已测没问题 
void ShiftRow(byte sta_matr[4 * 4]) {
	//第二行循环左移一个字节
	//第三行循环左移二个字节 
	//第三行循环左移三个字节

	for (int i = 0; i < 4; i++) {
		//byte temp[i];
		byte* temp = new byte[i];

		//存数 防止被覆盖
		for (int j = 0; j < i; j++) {
			temp[j] = sta_matr[i * 4 + j];
		}
		// 将不会发生下标溢出的进行赋值 
		for (int j = 0; j < 4 - i; j++) {
			sta_matr[i * 4 + j] = sta_matr[i * 4 + j + i];
		}
		// 将暂存的数放回状态数组 行中 
		for (int m = 4 - i; m < 4; m++) {
			sta_matr[i * 4 + m] = temp[m + i - 4];
		}
	}
}

// 4 列混合   经测试没问题 
void MixColumns(byte sta_matr[4 * 4], byte s[4 * 4]) {
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

// 5 加密函数
void encrypt(byte sta_matr[4 * 4], word w[4 * (Nr + 1)]) {
	
	word key[4];

	for (int i = 0; i < 4; i++) // 首先取得第0轮的密钥
		key[i] = w[i];
	
	//先进行一次轮密钥加 
	RKey_Add(sta_matr, key);
	
	cout<<"> Round 0 Encrypting Result (Only With RoundKeyAdd)："<<endl;
	for(int i=0;i<16;i++){
			cout<<hex<<sta_matr[i].to_ulong()<<"  ";
			if((i+1)%4==0)cout<<endl;
	}

		
	//九轮操作   S盒  行移位  列混合  轮密钥加 
	for (int r = 1; r < Nr; r++)
	{
		SubBytes(sta_matr); //字节代换
		ShiftRow(sta_matr); // 行移位
		MixColumns(sta_matr, encry_s); //列混合
		for (int i = 0; i < 4; i++) //换下一个密钥
			key[i] = w[4 * r + i]; 
		RKey_Add(sta_matr, key); // 轮密钥加
		
		cout<<endl;
		cout<<"> Round "<<r<<" Encrypting Result: "<<endl;

		for(int i=0;i<16;i++){
		cout<<hex<<sta_matr[i].to_ulong()<<"  ";
		if((i+1)%4==0)cout<<endl;
		}  
	}
	 
	//第十轮   S盒  行移位  轮密钥加 
	SubBytes(sta_matr);
	ShiftRow(sta_matr);
	for (int i = 0; i < 4; ++i)
		key[i] = w[4 * Nr + i];
	RKey_Add(sta_matr, key);
	cout << endl;

	cout<<"> Round 10 (SubBytes, ShiftRow, RoundKeyAdd) Result: "<<endl;
	for(int i=0;i<16;i++){
		cout<<hex<<sta_matr[i].to_ulong()<<"  ";
		if((i+1)%4==0)cout<<endl;
	}  

}
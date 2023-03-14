#include"encryption.h"
#include"decrypt.h"
#include<iostream>
#include<bitset>

// date��2023��3��14�� ���ڶ�
// ����ͨ��
int main() {
	//������Կ 
	byte key[16] = { 0x2b, 0x7e, 0x15, 0x16,
					0x28, 0xae, 0xd2, 0xa6,
					0xab, 0xf7, 0x15, 0x88,
					0x09, 0xcf, 0x4f, 0x3c };

		//��������� 
	byte sta_matr[16] = { 0x32,0x88,0x31,0xe0,
						0x43,0x5a,0x31,0x37,
						0xf6,0x30,0x98,0x07,
						0xa8,0x8d,0xa2,0x34 };

		//������Կ��չ
	word expanded_key_array[4 * (Nr + 1)]; //Nr=10
	KeyExpansion(key, expanded_key_array);

		//�����Կ��ok
	cout << "��Կ��:" << endl;
	for (int i = 0; i < 16; i++) {
		cout << hex << key[i].to_ulong() << "  ";
		if ((i + 1) % 4 == 0) cout << endl;
	}

	//��Կ��չ���飬ok
	cout << "��չ����Կ����:" << endl;
	for (int i = 0; i < 44; i++) {
		cout << hex << expanded_key_array[i].to_ulong() << "  ";
		if ((i + 1) % 4 == 0) cout << endl;
	}
	
	//������ģ�ok
	cout << endl;
	cout << "������:" << endl;
	for (int i = 0; i < 16; i++) {
		cout << hex << sta_matr[i].to_ulong() << "  ";
		if ((i + 1) % 4 == 0) cout << endl;
	}

 
	//�������
	cout << endl;
	encrypt(sta_matr, expanded_key_array);
	
	cout << "-----------------------------\n" << "������..." << endl;

	cout << endl << "������:" << endl;
	for (int i = 0; i < 16; i++) {
		cout << hex << sta_matr[i].to_ulong() << "  ";
		if ((i + 1) % 4 == 0)cout << endl;
	}

	//�ٴν��н���
	byte* encryped_text = new byte[16];
	encryped_text = sta_matr;
	
	
	cout << "\n���Ľ��ܵõ�:" << endl;
	decrypt(encryped_text, expanded_key_array);

	for (int i = 0; i < 16; i++) {
		cout << hex << encryped_text[i].to_ulong() << "  ";
		if ((i + 1) % 4 == 0)cout << endl;
	}



	return 0;

	
}






























// -------------------------------------------------------------
// ԭmain��2023��3��14��ǰ��
//int main() {
//	//������Կ 
//	byte key[16] = { 0x2b, 0x7e, 0x15, 0x16,
//					0x28, 0xae, 0xd2, 0xa6,
//					0xab, 0xf7, 0x15, 0x88,
//					0x09, 0xcf, 0x4f, 0x3c };
//	//	byte key[16] = {0x00, 0x01, 0x02, 0x03, 
//	//					0x04, 0x05, 0x06, 0x07, 
//	//					0x08, 0x09, 0x01, 0x02, 
//	//					0x03, 0x04, 0x05, 0x06};
//	//	byte key[16] = {0x00, 0x01, 0x02, 0x03, 
//	//						0x04, 0x05, 0x06, 0x07, 
//	//						0x08, 0x09, 0x0a, 0x0b, 
//	//						0x0c, 0x0d, 0x0e, 0x0f};
//
//
//		//��������� 
//	byte sta_matr[16] = { 0x32,0x88,0x31,0xe0,
//						0x43,0x5a,0x31,0x37,
//						0xf6,0x30,0x98,0x07,
//						0xa8,0x8d,0xa2,0x34 };
//	//    byte sta_matr[16]={0x61,0x62,0x63,0x64,
//	//    					0x65,0x66,0x67,0x68,
//	//    					0x69,0x6A,0x6B,0x6C,
//	//    					0x6D,0x6E,0x6F,0x70					
//	//	}; 
//	//	byte sta_matr[16] = {0x00, 0x11, 0x22, 0x33, 
//	//							0x44, 0x55, 0x66, 0x77, 
//	//							0x88, 0x99, 0xaa, 0xbb, 
//	//							0xcc, 0xdd, 0xee, 0xff};
//
//
//		//������Կ��չ
//	word w[4 * (Nr + 1)];
//	KeyExpansion(key, w);
//
//	//�����Կ
//	cout << "��Կ��:" << endl;
//	for (int i = 0; i < 16; i++) {
//		cout << hex << key[i].to_ulong() << "  ";
//		if ((i + 1) % 4 == 0)cout << endl;
//	}
//	cout << endl;
//	//�������
//	cout << "������:" << endl;
//	for (int i = 0; i < 16; i++) {
//		cout << hex << sta_matr[i].to_ulong() << "  ";
//		if ((i + 1) % 4 == 0)cout << endl;
//	}
//	//�������
//	cout << endl;
//	encrypt(sta_matr, w);
//	cout << "������:" << endl;
//	for (int i = 0; i < 16; i++) {
//		cout << hex << sta_matr[i].to_ulong() << "  ";
//		if ((i + 1) % 4 == 0)cout << endl;
//	}
//
//	//�ٴν��н���
//	cout << endl;
//	cout << "���Ľ�����:" << endl;
//	decrypt(sta_matr, w);
//	for (int i = 0; i < 16; i++) {
//		cout << hex << sta_matr[i].to_ulong() << "  ";
//		if ((i + 1) % 4 == 0)cout << endl;
//	}
//
//	return 0;
//
//
//
//
//	/*
//		�����Ǻ�����ȷ����֤����
//			1 ��Կ��չ��֤
//				for(int i=0;i<4*(Nr+1);i++){
//				cout<<"w["<<dec<<i<<"]="<<hex<<w[i].to_ulong()<<endl;
//				}
//
//			2 ��֤������˷�
//				byte temp=GFMul(0x57,0x83);
//				for(int i=0;i<8;i++){
//					cout<<temp[i]<<" ";}
//					cout<<endl;
//				cout<<"0x57*0x83:"<<hex<<temp.to_ulong();
//
//			3 �����ֽڴ�����������
//				SubBytes(sta_matr);
//				cout<<"�ֽڴ�������:"<<endl;
//				for(int i=0;i<16;i++){
//					cout<<hex<<sta_matr[i].to_ulong()<<"  ";
//					if((i+1)%4==0)cout<<endl;
//				}
//
//			4 �����л�Ϻ����Ƿ���ȷ
//				byte s[16] = {0xc9,0xe5,0xfd,0x2b,
//						0x7a,0xf2,0x78,0x6e,
//						0x63,0x9c,0x26,0x67,
//						0xb0,0xa7,0x82,0xe5};
//				MixColumns(s,encry_s);
//				for(int i=0;i<16;i++){
//					cout<<hex<<s[i].to_ulong()<<"  ";
//					if((i+1)%4==0)cout<<endl;
//				}
//
//
//
//	*/
//
//	/*
//		����ά��֤bitset�������ݵĴ洢�Լ����㷽ʽ
//			1 С��ģʽ��������˼ά��0011 0011�ڼ�����洢���1100 1100
//			2 ���������byte(bitset<8>)���ݽ������Ҳ�ǰ�������С����ʽ�����ݽ�����򣬴洢��������С�˸�ʽ
//			3 �����λ��� С�˸�ʽ  ���ֽ���� ��˸�ʽ
//			4 ����ʹ��a������˳��(���) ������λ��ʱ�����С��
//			5 a^b ���ֽ�������������˳��
//				byte temp0=0x57;
//				cout<<temp<<endl;
//				cout<<(temp>>1)<<endl;
//				cout<<temp[5];
//				byte temp2=0x83;
//				cout<<(temp^temp2);
//				cout<<"temp1:";
//				for(int i=0;i<8;i++){
//					cout<<temp[i]<<" ";
//				}
//				cout<<endl;
//				cout<<"temp2:";
//				for(int i=0;i<8;i++){
//					cout<<temp2[i]<<" ";
//				}
//				cout<<endl;
//				cout<<"temp1^temp2:";
//				byte temp3=temp^temp2;
//				for(int i=0;i<8;i++){
//					cout<<temp3[i]<<" ";
//				}
//				cout<<dec<<temp3.to_ulong();
//	*/
//}
// -------------------------------------------------------------
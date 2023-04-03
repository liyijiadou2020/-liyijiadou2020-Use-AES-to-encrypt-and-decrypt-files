#ifndef KEYEXTEND_H
#define KEYEXTEND_H

#include<bitset>
using namespace std;

typedef bitset<8> byte;
typedef bitset<32> word;

extern byte S[256]; //S-��
extern byte inv_S[256];
extern word rcon[10]; //��ϵ��Rcon��������S�еļ������������
extern byte encry_s[4 * 4];
extern byte decry_s[4 * 4];

//����������Կ�����Լ���չ����
const int Nr = 10;// ���� (Nr ��ѧ� ���ڧާ֧ߧ�֧� �� ����� �ާѧ��ڧ�� 4 ���֧�ҧ�ѧ٧�ӧѧߧڧ�)
const int Nk = 4; //������Կ���ĸ��� 

// ��Կ��չ ��غ���
// 1) 4 byte to 1 word.
word Word(byte b0, byte b1, byte b2, byte b3);
// 2) byte shift, ����λ 
word CycWord(word rw);
// 3) S-��ѧҧݧڧ�� �٧ѧާ֧ߧ�, S���滻 
word SubWord(word sw);
// 4  ����ݧ��ڧ�� ��ѧ��ڧ�ѧߧڧ� �ܧݧ��֧� w, ��Կ��չ 
void KeyExpansion(byte key[4 * Nk], word w[4 * (Nr + 1)]);



#endif
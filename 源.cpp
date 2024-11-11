#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include<algorithm>
#include<numeric>
#include<vector>
#include"std.h"
#include <sstream>  // �ַ��������������� std::stringstream �����ͷ�ļ�
#include <fstream>   // ���ļ��������
//���� ��λ ת���ģʽ ɢ�� ���
#define H_NUM 8    //һ����32biteҲ����8��ʮ��������(4bite)
#define BINARY 16   //16����
#define GROUP_BIT 512 //��Ϣ��֤��һ��512bite
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
//�ļ��е�����
string s;
//5���Ĵ����ĳ�ʼֵ
string A0 = "67452301";
string B0 = "EFCDAB89";
string C0 = "98BADCFE";
string D0 = "10325476";
string E0 = "C3D2E1F0";
//���ļ��ж����������,�������д���ļ�
void readfile();
//4λ������ת1λ16����
char bny_to_hex(int a, int b, int c, int d);
//16����ת�����ƴ�
string hex_to_bny(char a);
//������aת��Ϊ����Ϊlength��K���Ƶ�������
vector<int> KConvert(const unsigned long long& a, int K, int length);
//16���Ʒ��Ŵ�ת16����������
vector<int> strH_to_intH(const string& word);
//16����������ת16���Ʒ��Ŵ�
string intH_to_strH(const vector<int>& a);
//һ���ַ�ת��λ�����ƴ�
string char_to_bny(const char a);
//�ֵ������
string w_AND(const string& a, const string& b);
//�ֵĻ����
string w_OR(const string& a, const string& b);
//�ֵ����
string w_XOR(const string& a, const string& b);
//�ֵķ���
string w_CPL(const string& a);
//�ֹ���ģ2^32������
string w_ADD(const string& a, const string& b);
//ѭ������sλ
string Recycle_Left(const string& a, int s);
//��ϣ����(t,A,B,C)
string Ft(int t, const string& B, const string& C, const string& D);
//������K
string K(int t);
//��亯��,�����õõ�����Ϣ�Ķ������ַ���
vector<vector<int> > SHA_1_FILL(const string& b_msg);
//���������Ϣ��160bite��Ҳ����8��16��������Ϊһ�飬�ָ��������
vector<vector<string> > SHA_1_DIVIDE(const vector<vector<int> >& result);
//�㷨ִ�к���
string SHA_1_RESULT(const string& msg);
//���ļ�data.in�ж����������,д���ļ�result.out
void readfile() {
	char c;
	//    freopen("databig.in","r",stdin);
	//    freopen("datasmall.in","r",stdin);
	freopen("H://datamix.in.txt", "r", stdin);
	freopen("H://result.out.txt", "w", stdout);
	while (cin >> c) {
		if (c == '\n')
			break;
		s += c;
	}
}
//4λ������ת1λ16����
char bny_to_hex(int a, int b, int c, int d) {
	if (a == 0 && b == 0 && c == 0 && d == 0)
		return '0';
	else if (a == 0 && b == 0 && c == 0 && d == 1)
		return '1';
	else if (a == 0 && b == 0 && c == 1 && d == 0)
		return '2';
	else if (a == 0 && b == 0 && c == 1 && d == 1)
		return '3';
	else if (a == 0 && b == 1 && c == 0 && d == 0)
		return '4';
	else if (a == 0 && b == 1 && c == 0 && d == 1)
		return '5';
	else if (a == 0 && b == 1 && c == 1 && d == 0)
		return '6';
	else if (a == 0 && b == 1 && c == 1 && d == 1)
		return '7';
	else if (a == 1 && b == 0 && c == 0 && d == 0)
		return '8';
	else if (a == 1 && b == 0 && c == 0 && d == 1)
		return '9';
	else if (a == 1 && b == 0 && c == 1 && d == 0)
		return 'A';
	else if (a == 1 && b == 0 && c == 1 && d == 1)
		return 'B';
	else if (a == 1 && b == 1 && c == 0 && d == 0)
		return 'C';
	else if (a == 1 && b == 1 && c == 0 && d == 1)
		return 'D';
	else if (a == 1 && b == 1 && c == 1 && d == 0)
		return 'E';
	else if (a == 1 && b == 1 && c == 1 && d == 1)
		return 'F';
}
//16����ת�����ƴ�
string hex_to_bny(char a) {
	if (a == '0')
		return "0000";
	else if (a == '1')
		return "0001";
	else if (a == '2')
		return "0010";
	else if (a == '3')
		return "0011";
	else if (a == '4')
		return "0100";
	else if (a == '5')
		return "0101";
	else if (a == '6')
		return "0110";
	else if (a == '7')
		return "0111";
	else if (a == '8')
		return "1000";
	else if (a == '9')
		return "1001";
	else if (a == 'A')
		return "1010";
	else if (a == 'B')
		return "1011";
	else if (a == 'C')
		return "1100";
	else if (a == 'D')
		return "1101";
	else if (a == 'E')
		return "1110";
	else if (a == 'F')
		return "1111";
}
//������aת��Ϊ����Ϊlength��K���Ƶ�������
vector<int> KConvert(const unsigned long long& a, int K, int length) {
	vector<int> result;
	stack<int> tmp;
	unsigned long long a1 = a;
	do {
		int temp = a1 % K;
		tmp.push(temp);
		a1 /= K;
	} while (a1 != 0);
	for (int i = 0; i < length - tmp.size(); i++)//���0��ȷ������ָ�����ȵ�K���ƴ�
		result.push_back(0);
	while (!tmp.empty()) {
		result.push_back(tmp.top());
		tmp.pop();
	}
	return result;
}
//16���Ʒ��Ŵ�ת16����������
vector<int> strH_to_intH(const string& word) {
	vector<int> result(H_NUM, 0);
	for (int i = 0; i < H_NUM; i++) {
		if (word[i] >= '0' && word[i] <= '9')
			result[i] = word[i] - '0';
		else if (word[i] >= 'A' && word[i] <= 'Z')
			result[i] = 10 + word[i] - 'A';
	}
	return result;
}
//16����������ת16���Ʒ��Ŵ�
string intH_to_strH(const vector<int>& a) {
	string result;
	for (int i = 0; i < H_NUM; i++) {
		if (a[i] >= 0 && a[i] <= 9)
			result += a[i] + '0';
		else if (a[i] >= 10 && a[i] <= 15)
			result += a[i] - 10 + 'A';
	}
	return result;
}
//һ���ַ�ת��λ�����ƴ�
string char_to_bny(const char a) {
	int a_int;
	//���ASCII��
	if (a >= '0' && a <= '9')
		a_int = a - '0' + 48;
	else if (a >= 'A' && a <= 'Z')
		a_int = a - 'A' + 65;
	else if (a >= 'a' && a <= 'z')
		a_int = a - 'a' + 97;
	//��ASCII��ת��Ϊ8λ�����Ƶ�������
	vector<int> temp = KConvert(a_int, 2, 8);
	string result;
	//8λ������������ת��Ϊ�ַ���
	for (int i = 0; i < temp.size(); i++)
		result += temp[i] + '0';
	return result;
}
//�ֵ������(a��b����8λ16���Ƶ��ַ�������������ķ��Ŵ�)
string w_AND(const string& a, const string& b) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> b_int = strH_to_intH(b);
	vector<int> r_int(H_NUM, 0);
	//a��b��λ����
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = a_int[i] & b_int[i];
	return intH_to_strH(r_int);
}
//�ֵĻ����(a��b����8λ16���Ƶ��ַ������������ķ��Ŵ�)
string w_OR(const string& a, const string& b) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> b_int = strH_to_intH(b);
	vector<int> r_int(H_NUM, 0);
	//a��b��λ���
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = a_int[i] | b_int[i];
	return intH_to_strH(r_int);
}
//�ֵ����(a��b����8λ16���Ƶ��ַ��������������ķ��Ŵ�)
string w_XOR(const string& a, const string& b) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> b_int = strH_to_intH(b);
	vector<int> r_int(H_NUM, 0);
	//a��b��λ�����
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = a_int[i] ^ b_int[i];
	return intH_to_strH(r_int);
}
//�ֵķ���(a��8λ16���Ƶ��ַ���)
string w_CPL(const string& a) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> r_int(H_NUM, 0);
	//a��λȡ��
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = BINARY - 1 - a_int[i];
	return intH_to_strH(r_int);
}
//�ֹ���ģ2^32�µ�������
string w_ADD(const string& a, const string& b) {
	vector<int> A = strH_to_intH(a);
	vector<int> B = strH_to_intH(b);
	vector<int> Result(H_NUM, 0);
	//��λ��־
	int sign = 0;
	for (int i = H_NUM - 1; i >= 0; i--) {
		Result[i] = A[i] + B[i] + sign;
		sign = Result[i] / BINARY;
		Result[i] %= BINARY;
	}
	return intH_to_strH(Result);
}
//ѭ������sλ
string Recycle_Left(const string& a, int s) {
	vector<int> A = strH_to_intH(a);
	//�ֵ�����ֵ
	unsigned long a_int = 0;
	for (int i = 0; i < H_NUM; i++)
		a_int += A[H_NUM - 1 - i] * pow(BINARY, i);
	//sizeof(a_int)*8��ʾ������������ռ��λ��,(a_int>>(sizeof(a_int)*8-s))�õ�����sλ����ĸ�sλ
	a_int = (a_int >> (sizeof(a_int) * 8 - s)) | (a_int << s);
	//������a_intת��Ϊ8λ16���ƴ�(ѭ�����ƺ��)
	vector<int> A1 = KConvert(a_int, BINARY, H_NUM);
	return intH_to_strH(A1);
}
//��ϣ����(t,A,B,C)�漰�롢��������
string Ft(int t, const string& B, const string& C, const string& D) {
	if (t >= 0 && t <= 19)
		return w_OR(w_AND(B, C), w_AND(w_CPL(B), D));
	else if (t >= 20 && t <= 39)
		return w_XOR(w_XOR(B, C), D);
	else if (t >= 40 && t <= 59)
		return w_OR(w_OR(w_AND(B, C), w_AND(B, D)), w_AND(C, D));
	else if (t >= 60 && t <= 79)
		return w_XOR(w_XOR(B, C), D);
}
//������K
string K(int t) {
	if (t >= 0 && t <= 19)
		return "5A827999";
	else if (t >= 20 && t <= 39)
		return "6ED9EBA1";
	else if (t >= 40 && t <= 59)
		return "8F1BBCDC";
	else if (t >= 60 && t <= 79)
		return "CA62C1D6";
}
//��亯��,�����õõ�����Ϣ�Ķ������ַ���
vector<vector<int> > SHA_1_FILL(const string& b_msg) {
	unsigned long long length = b_msg.size();
	//d����Ҫ����1�����0�ĸ���
	int d = (448 - 1 - length) % GROUP_BIT;
	//��Ϣ����(64bite)�Ķ����Ʊ�ʾ
	vector<int> l = KConvert(length, 2, 64);
	vector<vector<int> > result;
	string str_result;
	str_result += b_msg;
	str_result += '1';
	for (int i = 0; i < d; i++)
		str_result += '0';
	//������64bite����Ϣ����
	for (int i = 0; i < l.size(); i++)
		str_result += '0' + l[i];
	//�������Ϣ�ɷֳ�n��
	int n = str_result.size() / GROUP_BIT;
	//�����ݴ洢λn��521�еľ���
	result.resize(n, vector<int>(GROUP_BIT, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < GROUP_BIT; j++)
			result[i][j] = str_result[i * GROUP_BIT + j] - '0';
	return result;
}
//���������Ϣ��160bite��Ҳ����8��8λ16��������Ϊһ�飬�ָ��������
vector<vector<string> > SHA_1_DIVIDE(const vector<vector<int> >& result) {
	vector<vector<string> > w_result(result.size(), vector<string>(BINARY, ""));
	//��ÿ��string����result�е�32λ2�������ó�һ����λ16���Ʒ��Ŵ�
	for (int i = 0; i < result.size(); i++)
		for (int j = 0; j < BINARY; j++) {
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 0], result[i][j * 32 + 1], result[i][j * 32 + 2], result[i][j * 32 + 3]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 4], result[i][j * 32 + 5], result[i][j * 32 + 6], result[i][j * 32 + 7]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 8], result[i][j * 32 + 9], result[i][j * 32 + 10], result[i][j * 32 + 11]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 12], result[i][j * 32 + 13], result[i][j * 32 + 14], result[i][j * 32 + 15]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 16], result[i][j * 32 + 17], result[i][j * 32 + 18], result[i][j * 32 + 19]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 20], result[i][j * 32 + 21], result[i][j * 32 + 22], result[i][j * 32 + 23]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 24], result[i][j * 32 + 25], result[i][j * 32 + 26], result[i][j * 32 + 27]);
			w_result[i][j] += bny_to_hex(result[i][j * 32 + 28], result[i][j * 32 + 29], result[i][j * 32 + 30], result[i][j * 32 + 31]);
		}
	return w_result;
}
//�㷨ִ�к���
string SHA_1_RESULT(const string& msg) {
	string b_msg;
	//����Ϣ�е�ÿ���ַ�ת��Ϊ8λ�����ƴ�
	for (int i = 0; i < msg.size(); i++)
		b_msg += char_to_bny(msg[i]);
	//�����Ϣ
	vector<vector<int> > y = SHA_1_FILL(b_msg);
	//�ָ��������Ϣ
	vector<vector<string> > w_y = SHA_1_DIVIDE(y);
	//W����
	vector<string> W(80, "");
	for (int i = 0; i < y.size(); i++) {
		for (int t = 0; t <= 15; t++)
			W[t] = w_y[i][t];
		for (int t = 16; t <= 79; t++) {
			string tmp = w_XOR(w_XOR(w_XOR(W[t - 3], W[t - 8]), W[t - 14]), W[t - 16]);
			W[t] = Recycle_Left(tmp, 1);
		}
		string A = A0;
		string B = B0;
		string C = C0;
		string D = D0;
		string E = E0;
		//�ܹ�4�֣�ÿ��20�����Ĵ���ÿ�����ڱ䣬F��W��ÿ�ֱ仯
		for (int t = 0; t <= 79; t++) {
			string temp;
			temp = w_ADD(w_ADD(w_ADD(w_ADD(E, Ft(t, B, C, D)), Recycle_Left(A, 5)), W[t]), K(t));
			E = D;
			D = C;
			C = Recycle_Left(B, 30);
			B = A;
			A = temp;
		}
		A0 = w_ADD(A0, A);
		B0 = w_ADD(B0, B);
		C0 = w_ADD(C0, C);
		D0 = w_ADD(D0, D);
		E0 = w_ADD(E0, E);
	}
	string result = A0 + B0 + C0 + D0 + E0;
	//���õ��ļ��ܴ���д��Сд
	for (int i = 0; i < result.size(); i++) {
		if (result[i] >= 'A' && result[i] <= 'Z')
			result[i] = result[i] - 'A' + 'a';
	}
	return result;
}

int main()
{
	readfile();
	cout << "����Ϊ��" << SHA_1_RESULT(s) << endl;
	return 0;
}
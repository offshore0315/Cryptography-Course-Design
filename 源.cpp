#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include<algorithm>
#include<numeric>
#include<vector>
#include"std.h"
#include <sstream>  // 字符串流，在这里是 std::stringstream 所需的头文件
#include <fstream>   // 对文件输入输出
//分组 补位 转大端模式 散列 输出
#define H_NUM 8    //一个字32bite也就是8个十六进制数(4bite)
#define BINARY 16   //16进制
#define GROUP_BIT 512 //消息认证码一组512bite
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
//文件中的数据
string s;
//5个寄存器的初始值
string A0 = "67452301";
string B0 = "EFCDAB89";
string C0 = "98BADCFE";
string D0 = "10325476";
string E0 = "C3D2E1F0";
//从文件中读入测试数据,并将结果写入文件
void readfile();
//4位二进制转1位16进制
char bny_to_hex(int a, int b, int c, int d);
//16进制转二进制串
string hex_to_bny(char a);
//把整数a转换为长度为length的K进制的整数串
vector<int> KConvert(const unsigned long long& a, int K, int length);
//16进制符号串转16进制整数串
vector<int> strH_to_intH(const string& word);
//16进制整数串转16进制符号串
string intH_to_strH(const vector<int>& a);
//一个字符转八位二进制串
string char_to_bny(const char a);
//字的与操作
string w_AND(const string& a, const string& b);
//字的或操作
string w_OR(const string& a, const string& b);
//字的异或
string w_XOR(const string& a, const string& b);
//字的反码
string w_CPL(const string& a);
//字关于模2^32整数加
string w_ADD(const string& a, const string& b);
//循环左移s位
string Recycle_Left(const string& a, int s);
//哈希函数(t,A,B,C)
string Ft(int t, const string& B, const string& C, const string& D);
//常数字K
string K(int t);
//填充函数,这里用得到的消息的二进制字符串
vector<vector<int> > SHA_1_FILL(const string& b_msg);
//将填充后的消息以160bite（也就是8个16进制数）为一组，分割成若干组
vector<vector<string> > SHA_1_DIVIDE(const vector<vector<int> >& result);
//算法执行函数
string SHA_1_RESULT(const string& msg);
//从文件data.in中读入测试数据,写入文件result.out
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
//4位二进制转1位16进制
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
//16进制转二进制串
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
//把整数a转换为长度为length的K进制的整数串
vector<int> KConvert(const unsigned long long& a, int K, int length) {
	vector<int> result;
	stack<int> tmp;
	unsigned long long a1 = a;
	do {
		int temp = a1 % K;
		tmp.push(temp);
		a1 /= K;
	} while (a1 != 0);
	for (int i = 0; i < length - tmp.size(); i++)//填充0，确保返回指定长度的K进制串
		result.push_back(0);
	while (!tmp.empty()) {
		result.push_back(tmp.top());
		tmp.pop();
	}
	return result;
}
//16进制符号串转16进制整数串
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
//16进制整数串转16进制符号串
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
//一个字符转八位二进制串
string char_to_bny(const char a) {
	int a_int;
	//获得ASCII码
	if (a >= '0' && a <= '9')
		a_int = a - '0' + 48;
	else if (a >= 'A' && a <= 'Z')
		a_int = a - 'A' + 65;
	else if (a >= 'a' && a <= 'z')
		a_int = a - 'a' + 97;
	//将ASCII码转换为8位二进制的整数串
	vector<int> temp = KConvert(a_int, 2, 8);
	string result;
	//8位二进制整数串转化为字符串
	for (int i = 0; i < temp.size(); i++)
		result += temp[i] + '0';
	return result;
}
//字的与操作(a和b都是8位16进制的字符串，返回相与的符号串)
string w_AND(const string& a, const string& b) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> b_int = strH_to_intH(b);
	vector<int> r_int(H_NUM, 0);
	//a和b按位相与
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = a_int[i] & b_int[i];
	return intH_to_strH(r_int);
}
//字的或操作(a和b都是8位16进制的字符串，返回相或的符号串)
string w_OR(const string& a, const string& b) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> b_int = strH_to_intH(b);
	vector<int> r_int(H_NUM, 0);
	//a和b按位相或
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = a_int[i] | b_int[i];
	return intH_to_strH(r_int);
}
//字的异或(a和b都是8位16进制的字符串，返回相异或的符号串)
string w_XOR(const string& a, const string& b) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> b_int = strH_to_intH(b);
	vector<int> r_int(H_NUM, 0);
	//a和b按位相异或
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = a_int[i] ^ b_int[i];
	return intH_to_strH(r_int);
}
//字的反码(a是8位16进制的字符串)
string w_CPL(const string& a) {
	vector<int> a_int = strH_to_intH(a);
	vector<int> r_int(H_NUM, 0);
	//a按位取反
	for (int i = 0; i < H_NUM; i++)
		r_int[i] = BINARY - 1 - a_int[i];
	return intH_to_strH(r_int);
}
//字关于模2^32下的整数加
string w_ADD(const string& a, const string& b) {
	vector<int> A = strH_to_intH(a);
	vector<int> B = strH_to_intH(b);
	vector<int> Result(H_NUM, 0);
	//进位标志
	int sign = 0;
	for (int i = H_NUM - 1; i >= 0; i--) {
		Result[i] = A[i] + B[i] + sign;
		sign = Result[i] / BINARY;
		Result[i] %= BINARY;
	}
	return intH_to_strH(Result);
}
//循环左移s位
string Recycle_Left(const string& a, int s) {
	vector<int> A = strH_to_intH(a);
	//字的整数值
	unsigned long a_int = 0;
	for (int i = 0; i < H_NUM; i++)
		a_int += A[H_NUM - 1 - i] * pow(BINARY, i);
	//sizeof(a_int)*8表示该数二进制所占的位数,(a_int>>(sizeof(a_int)*8-s))得到左移s位溢出的高s位
	a_int = (a_int >> (sizeof(a_int) * 8 - s)) | (a_int << s);
	//将整数a_int转化为8位16进制串(循环左移后的)
	vector<int> A1 = KConvert(a_int, BINARY, H_NUM);
	return intH_to_strH(A1);
}
//哈希函数(t,A,B,C)涉及与、或、异或操作
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
//常数字K
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
//填充函数,这里用得到的消息的二进制字符串
vector<vector<int> > SHA_1_FILL(const string& b_msg) {
	unsigned long long length = b_msg.size();
	//d是需要填充的1后面的0的个数
	int d = (448 - 1 - length) % GROUP_BIT;
	//消息长度(64bite)的二进制表示
	vector<int> l = KConvert(length, 2, 64);
	vector<vector<int> > result;
	string str_result;
	str_result += b_msg;
	str_result += '1';
	for (int i = 0; i < d; i++)
		str_result += '0';
	//连接上64bite的消息长度
	for (int i = 0; i < l.size(); i++)
		str_result += '0' + l[i];
	//填充后的消息可分成n组
	int n = str_result.size() / GROUP_BIT;
	//将数据存储位n行521列的矩阵
	result.resize(n, vector<int>(GROUP_BIT, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < GROUP_BIT; j++)
			result[i][j] = str_result[i * GROUP_BIT + j] - '0';
	return result;
}
//将填充后的消息以160bite（也就是8个8位16进制数）为一组，分割成若干组
vector<vector<string> > SHA_1_DIVIDE(const vector<vector<int> >& result) {
	vector<vector<string> > w_result(result.size(), vector<string>(BINARY, ""));
	//对每个string，由result中的32位2进制数得出一个八位16进制符号串
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
//算法执行函数
string SHA_1_RESULT(const string& msg) {
	string b_msg;
	//将消息中的每个字符转化为8位二进制串
	for (int i = 0; i < msg.size(); i++)
		b_msg += char_to_bny(msg[i]);
	//填充消息
	vector<vector<int> > y = SHA_1_FILL(b_msg);
	//分割填充后的消息
	vector<vector<string> > w_y = SHA_1_DIVIDE(y);
	//W参数
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
		//总共4轮，每轮20步，寄存器每步都在变，F和W是每轮变化
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
	//将得到的加密串大写变小写
	for (int i = 0; i < result.size(); i++) {
		if (result[i] >= 'A' && result[i] <= 'Z')
			result[i] = result[i] - 'A' + 'a';
	}
	return result;
}

int main()
{
	readfile();
	cout << "密文为：" << SHA_1_RESULT(s) << endl;
	return 0;
}
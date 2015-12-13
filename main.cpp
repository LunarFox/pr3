
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <windows.h>
#include <cmath>

using namespace std;

char ru_alfabit [36] = {'а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я','.',' ',',','-'};
int ru_p = 36;
int ru_n = 6;

char eng_alfabit [36] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', '.', ' ', ',', '-', ':', ';', '?', '(', ')', '!'};
int eng_p = 36;
int eng_n = 6;
int mod(int a, int m)
{
    while(a<0)
        a = a+m;
    if(a >= m)
        a = a%m;
    return a;
}

int filling(int start, int n, char *mass, char *sourse)
{
	int y = start;
	for(int i = 0; i<n; i++)
	{
		int flag = 0;
		for(int j = 0; (j<y)&&(flag == 0); j++)
		{
			if(mass[j] == sourse[i])
				flag = 1;
		}
		if(flag == 0)
		{
			mass[y] = sourse[i];
			y++;
		}
	}
	return y;
}

void get_code_matrix(int p, int n, char *code_matrix[], char *alfabit, char *key_word, int key_length)
{
	int i, j;
	char *check_letter;
	check_letter = new char[p];
	filling(filling(0, key_length, check_letter, key_word), p, check_letter, alfabit);
	int y = 0;
	for(i = 0; i<n; i++)
	{
		for(j = 0; j<n; j++)
		{
			code_matrix[i][j] = check_letter[y];
			y++;
		}
	}
}


int coding(char *message, int message_length, char *code_matrix[], int p, int n, char *code_message)
{
	char bigrama[2];
	int i, j, k;
	int code_length = 0;
	for(i = 0; i<message_length;i = i+2)
	{
		bigrama[0] = message[i];
		bigrama[1] = message[i+1];
		if((bigrama[0] == bigrama[1])||(i+1 == message_length))
		{
			bigrama[1] = '.';
			i--;
		}
		int i1, i2, j1, j2;
		for(j = 0; j<n; j++)
		{
			for(k = 0; k<n; k++)
			{
				if(code_matrix[j][k] == bigrama[0])
				{
					i1 = j; j1 = k;
				}
				else if(code_matrix[j][k] == bigrama[1])
				{
					i2 = j; j2 = k;
				}
			}
		}
		int num;
		if(i1 == i2)
		{
			num = mod(j1+1, n);
			code_message[code_length] = code_matrix[i1][num];
			code_length++;
			num = mod(j2+1, n);
			code_message[code_length] = code_matrix[i2][num];
			code_length++;
		}
		else if(j1 == j2)
		{
			num = mod(i1+1, n);
			code_message[code_length] = code_matrix[num][j1];
			code_length++;
			num = mod(i2+1, n);
			code_message[code_length] = code_matrix[num][j2];
			code_length++;
		}
		else
		{
			code_message[code_length] = code_matrix[i1][j2];
			code_length++;
			code_message[code_length] = code_matrix[i2][j1];
			code_length++;

		}

	}
	code_message[code_length] = '\0';
	return code_length;
}

int decoding(char *code_message, int code_length, char *code_matrix[], int p, int n, char *message)
{
	char bigrama[2];
	int i, j, k;
	int mes_length = 0;
	for(i = 0; i<code_length;i = i+2)
	{
		bigrama[0] = code_message[i];
		bigrama[1] = code_message[i+1];
		int i1, i2, j1, j2;
		for(j = 0; j<n; j++)
		{
			for(k = 0; k<n; k++)
			{
				if(code_matrix[j][k] == bigrama[0])
				{
					i1 = j; j1 = k;
				}
				else if(code_matrix[j][k] == bigrama[1])
				{
					i2 = j; j2 = k;
				}
			}
		}
		int num;
		if(i1 == i2)
		{
			num = mod(j1-1, n);
			message[mes_length] = code_matrix[i1][num];
			mes_length++;
			num = mod(j2-1, n);
			message[mes_length] = code_matrix[i2][num];
			mes_length++;
		}
		else if(j1 == j2)
		{
			num = mod(i1-1, n);
			message[mes_length] = code_matrix[num][j1];
			mes_length++;
			num = mod(i2-1, n);
			message[mes_length] = code_matrix[num][j2];
			mes_length++;
		}
		else
		{
			message[mes_length] = code_matrix[i1][j2];
			mes_length++;
			message[mes_length] = code_matrix[i2][j1];
			mes_length++;

		}

	}
	message[mes_length] = '\0';
	return mes_length;
}



int main()
{
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	cout<<"Использовать русский язык или английский?(1 для русского, 0 для английского)\n";
	int ru_en;
	cin>>ru_en;
	int n;
	if(ru_en == 1)
		n = ru_n;
	else
		n = eng_n;
	char **code_matrix;
	code_matrix = new char*[n];
	int i;
	for(i = 0; i<n; i++)
	{
		code_matrix[i] = new char [n];
	}
	std::cout<<"Введите ключевое слово\n";
	string s;
	std::cin>>s;
	char* key_word = new char[s.length()];
	for(i = 0; i<s.length();i++)
		key_word[i] = s[i];
	if(ru_en == 1)
		get_code_matrix(ru_p, ru_n, code_matrix, ru_alfabit, key_word, i);
	else
		get_code_matrix(eng_p, eng_n, code_matrix, eng_alfabit, key_word, i);

	FILE *g = freopen("message.txt","r", stdin);
	char *message = new char[10000];
	i = 0;
	while(!feof(g))
	{
		message[i] = getchar();
		i++;
	}
	message[i-1] = '\0';
	fclose(g);
	freopen("CON", "r", stdin);

	char *code_message = new char[10000];
	int code_length;
	if(ru_en == 1)
		code_length = coding(message, i-1, code_matrix, ru_p, ru_n, code_message);
	else
		code_length = coding(message, i-1, code_matrix, eng_p, eng_n, code_message);
	cout<<"Зашифованное сообщение:\n\n";
	cout<<code_message<<"\n\n";

	char *decoded_message = new char[10000];
	if(ru_en == 1)
		decoding(code_message, code_length, code_matrix, ru_p, ru_n, decoded_message);
	else
		decoding(code_message, code_length, code_matrix, eng_p, eng_n, decoded_message);
	cout<<"Расшифованное сообщение:\n\n";
	cout<<decoded_message<<"\n";
	getch();
}





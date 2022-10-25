#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <Windows.h>
#include <bitset>

using namespace std;

void MyEncryption(char Ins[64], unsigned short OutCoding[64]);

enum  ConsoleColor : unsigned int
{							//0000 IRGB  
	Black = 0x00,			//0000 0000
	Blue = 0x01,			//0000 0001
	Green = 0x02,			//0000 0010
	Cyan = 0x03,			//0000 0011
	Red = 0x04,				//0000 0100
	Magenta = 0x05,			//0000 0101
	Brown = 0x06,			//0000 0110
	LightGray = 0x07,		//0000 0111 
	DarkGray = 0x08,		//0000 1000
	LightBlue = 0x09,		//0000 1001
	LightGreen = 0x0a,		//0000 1010
	LightCyan = 0x0b,		//0000 1011
	LightRed = 0x0c,		//0000 1100
	LightMagenta = 0x0d,	//0000 1101
	Yellow = 0x0e,			//0000 1110
	White = 0x0f,			//0000 1111
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, (WORD)((background << 4) | text));
}

void InputColor()
{
	int kText, kBackground;
	do {
		cout << "Select the text and background color:\n";
		cout << "0.	Black		\n"
			<< "1.	Blue		\n"
			<< "2.	Green		\n"
			<< "3.	Cyan		\n"
			<< "4.	Red			\n"
			<< "5.	Magenta		\n"
			<< "6.	Brown		\n"
			<< "7.	LightGray	\n"
			<< "8.	DarkGray	\n"
			<< "9.	LightBlue	\n"
			<< "10.LightGreen	\n"
			<< "11.LightCyan	\n"
			<< "12.LightRed	\n"
			<< "13.LightMagen	\n"
			<< "14.Yellow		\n"
			<< "15.White		\n";

		cin >> kText >> kBackground;
		if (kText <= 15 || kBackground <= 15)
			SetColor(ConsoleColor(kText), ConsoleColor(kBackground));
		else
			cout << "Uncorrect value(es)";
	} while (kText > 15 || kBackground > 15);
	cin.get();

}

void MenuExamples() {

	cout << "    Examples   \n";
	cout << "    1.  Expression calculation using bitwise operations \n";
	cout << "    2.  Encryption\n";
	cout << "    3.	 Encryption structure \n";
	cout << "    4.  Change starshiBITS and molodshiyBITS\n";
	cout << "    5.  Change the text and background color\n";
	cout << "    6.  Exit \n";

}

void Example1()
{
	int a, b, c, d, x, y;
	cout << "An example of calculating an expression using only bitwise operations.\n";
	cout << " Input a  b  c  d: ";

	cin >> a >> b >> c >> d;
	auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); return; }
	x = ((a + (a << 4) + ((((c << 8) + (c << 6))) - (c << 3))) >> 5) - ((b << 7) - (b << 3)) + ((d << 7) - d);
	y = ((17 * a + 312 * c) / 32) - b * 120 + d * 127;
	cout << "  x=" << x << "  y=" << y << " a=" << a << "  b=" << b << " c=" << c << " d=" << d << endl;
	cin.get();
}


/*
5. Задано текст до 128 символів. Доповнити пробілами до 128 символів. Шифрувати тексти
таким чином, щоб кожний символ тексту записувався у два байта. Два байта мають таку
структуру:
у бітах 0-6 позиція символу в рядку (7 біти),
у бітах 7-14 ASCII - код букви (8 біт),
15 біт – біт парності перших двох полів (1 біт)
*/

void MyEncryption(char InS[128], unsigned short OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i, b;
	short j;
		for (i = 0; i < 128; i++)            //
		{
			r = 0;							// 0000 0000 0000 0000
			c = InS[i];                     // s - 0x73 = 0111 0011
			t = c;
			r |= i;							// 0000 0000 0000 0101  if i=5 -> 0000 0000 0000 0101
			r |= t << 7;					// 0011 1001 1000 0101  if i=5 -> 0000 0000 0000 0101
		 
			t = 1;
			b = 0;
			for (j = 0; j < 15; j++)         // обчислення біта парності
			{
				if (r & t) {
					if (b == 0) b = 1; else b = 0;
				}
				t <<= 1;
			}
			r |= b << 15;                    // 0011 0000 0101 0111 if i=5 0000 0000 0000 0101
			OutCoding[i] = r;


			cout << "coded symbol '" << InS[i] << "' in pos [" << i << "]" << endl;
			cout << bitset<16>(OutCoding[i]) << endl;
		}
}

void Example2()
{
	unsigned short OutCoding[128];
	string string_text;

	cout << "Enter text: ";
	getline(cin, string_text);

	char char_text[128];
	//	strcpy(char_text, text.c_str());
	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";
	if (string_text.length() != 128)
	{
		for (int i = string_text.length(); i < 128; i++)
		{
			char_text[i] = ' ';
		}
	}

	MyEncryption(char_text, OutCoding);
}

struct TextCode {
	unsigned short posrow : 7;
	unsigned short kb : 8;
	unsigned short bitp : 1;

};

unsigned char pbit(unsigned char c)
{
	unsigned char t = 1, b = 0;
	for (int j = 0; j < 16; j++)         // обчислення біта парності
	{
		if (c & t) {
			if (b == 0) b = 1; else b = 0;
		}
		t <<= 1;
	}
	return b;
}

void MyEncryptionS(char InS[128], TextCode OutCoding[128])
{
	unsigned char c;
	unsigned short r, t, i;
	short j;
	for (i = 0; i < 128; i++)            //
	{
		c = InS[i];                     // s - 0x73 = 0111 0011
		OutCoding[i].posrow = i;
		OutCoding[i].kb = c;
		
		r = pbit(c << 7);
		t = pbit(static_cast<unsigned char>(i));
		OutCoding[i].bitp = r ^ t;

		cout << "coded symbol '" << InS[i] << "' in pos [" << i << "]" << endl;
		cout << "the position of the character in the string : " << bitset<7>(OutCoding[i].posrow) << endl;
		cout << "code symbol : " << bitset<8>(OutCoding[i].kb) << endl;
		cout << "even bit : " << bitset<1>(OutCoding[i].bitp) << endl;
	}
}


void Example3() {
	TextCode OutCoding[128];
	string string_text;

	cout << "Enter text: ";

	getline(cin, string_text);

	char char_text[128];
	//	strcpy(char_text, text.c_str());
	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";
	if (string_text.length() != 128)
	{
		for (int i = string_text.length(); i < 128; i++)
		{
			char_text[i] = ' ';
		}
	}

	MyEncryptionS(char_text, OutCoding);
}


void MyEncryption2(char InS[128], unsigned short OutCoding[128], int size)
{
	unsigned char c;
	unsigned short r, t, i, b;
	short j;
	for (i = 0; i < size; i++)            //
	{
		r = 0;                        // 0000 0000 0000 0000
		c = InS[i];                     // s - 0x73 = 0111 0011
		t = c;						//0011 0111
		r |= t >> 4;      
		r |= t << 4;					
		r = r << 8;
		r = r >> 8;
		OutCoding[i] = r;

	}
}
/*
* Зашифрувати текст, помінявши у бітовому представленні кожного символу старші та
	молодші 4 біти.
*/
void Example4() {
	unsigned short OutCoding[128];
	string string_text;

	cout << "Enter text: ";

	getline(cin, string_text);

	char char_text[128];
	//	strcpy(char_text, text.c_str());
	for (int i = 0; i < string_text.length(); i++)
	{
		char_text[i] = string_text[i];
		cout << char_text[i];
	}
	cout << "\n";

	MyEncryption2(char_text, OutCoding, string_text.length());
}

void Examples() {
	char ch = '5';
	do {
		MenuExamples();


		ch = cin.get();
		cin.get();

		switch (ch) {
		case '1':
			Example1();
			break;
		case '2':
		{
			Example2();
			cin.get();
			break;
		}
		case '3':
			Example3();
			cin.get();
			break;
		case '4':
			Example4();
			cin.get();
			break;
		case '5':
			InputColor();
			break;

		case '6': cout << "It's end...";
		}

		/*if (ch != '6')
		{
		cout << " Press any key and enter\n";
		ch = cin.get();
		}*/
	} while (ch != '6');
}




int main() {

	Examples();

}
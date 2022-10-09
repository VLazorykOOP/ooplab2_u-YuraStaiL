#include <iostream>
#include <fstream>
#include <string.h>
#include <Windows.h>

using namespace std;

MyEncryption(char Ins[64], unsigned short OutCoding[64]);

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
	cout <<	"Select the text and background color:\n";
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
	cout << "    2. \n";
	cout << "    3.   \n";
	cout << "    4.  \n";
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
				

		case '5':
			InputColor();
			break;

		case '6': cout << "goodbye";
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
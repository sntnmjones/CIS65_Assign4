#include "FileIn.h"

////////////////
FileIn::FileIn()
{
	inFileBufferLength = 0;
	bookCount = 0;
}

//////////////////////////
void FileIn::fileInStuff()
{
	fileOpen();
	inFileBufferLength = getBufferLength(inFile);
	fillBuffer(inFile);
	getBookCount(buffer, inFileBufferLength);
	inFile.close();
}

///////////////////////
void FileIn::fileOpen()
{
	try
	{
		inFile.open("books.txt");
		if (!inFile.is_open())
		{
			throw 1;
		}
	}
	catch (int)
	{
		std::cout << "File could not be retrieved.\nfileOpen() error" << std::endl;
	}
}

///////////////////////////////////////////////
int FileIn::getBufferLength(std::ifstream& inf)
{
	unsigned int len = 0;
	inf.seekg(0, inf.end);
	len = (int)inf.tellg();
	inf.seekg(0, inf.beg);
	return len;
}

//////////////////////////////////////////
void FileIn::fillBuffer(std::ifstream& in)
{
	using namespace std;

	do
	{
		if (in.is_open())
		{
			buffer = new char[inFileBufferLength];
			in.read(buffer, inFileBufferLength);
		}
		else
		{
			cout << "Input file is not open..." << endl;
			cout << "Attempting to open \"inventory.txt\"..." << endl;
			in.open("inventory.txt");
		}
	} while (!in.is_open());
}

void FileIn::getBookCount(const char* buff, const int a)
{
	int lineCount = 0;
	int i = a;
	int b = 0;
	do
	{
		if (buff[b] == 10)
		{
			lineCount++;
			b++;
		}
		else
		{
			b++;
		}
	} while (buff[b] != -51 && buff[b] != -3);
	bookCount = lineCount / 3;
}

//
FileIn::~FileIn()
{
	inFile.close();
	delete[] buffer;
}
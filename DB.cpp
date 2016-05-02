#include "DB.h"

//////////////////////////////////////////////////
DB::DB()
{
	try
	{
		bookDB.open("books.txt");
		if (!bookDB.is_open())
		{
			throw 1;
		}
	}
	catch (int)
	{
		std::cout << "File \"books.txt\" not found.\nfileOpen() error \n" << std::endl;
	}

	unsortedArrayLength = -1;
	logIter = 0;
	mid = 0;
}

/////////////////////////////////////////////
void DB::loadDBs()
{
	fileInStuff();
	createNodes(buffer, inFileBufferLength);
}

///////////////////////////////////
void DB::printToLog(Book *tBook)
{
	log[logIter].action = tBook->action;
	log[logIter].author = tBook->author;
	log[logIter].subject = tBook->subject;
	log[logIter].time = tBook->time;
	log[logIter].title = tBook->title;
	logIter++;
}


///////////////////////////////////////////////
void DB::createNodes(const char* buff, int len)
{
	using namespace std;

	int a = 0;
	
	unsortedList = new Book[100];
	do
	{
		string title = "";
		string author = "";
		string subject = "";	
		Book* newBook = new Book;
		unsortedArrayLength++;

		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
				while (buff[a] != 10) //while buff[a] != \n
				{
					newBook->title += buff[a];
					a++;
				}
				break;
			case 1:
				while (buff[a] != 10) //while buff[a] != \n
				{
					newBook->author += buff[a];
					a++;
				}
				break;
			case 2:
				while (buff[a] != 10 && buff[a] != -51 && buff[a] != -3) //while buff[a] != \n or other weird stuff
				{
					newBook->subject += buff[a];
					a++;
				}
				break;
			}
			
			a++;
		}

		//inserts info into array.
		unsortedList[unsortedArrayLength].title = newBook->title;
		unsortedList[unsortedArrayLength].author = newBook->author;
		unsortedList[unsortedArrayLength].subject = newBook->subject;
		unsortedList[unsortedArrayLength].time = 0;
		unsortedList[unsortedArrayLength].action = "from DB";
		
		delete newBook;
	} while (a < len && buff[a] != -51 && buff[a] != -3);

	log = new Book[100]; // prepares log array for input
	sortedByTitle = new Book[100]; //prepares sortedByTitle array for input
	sortedByAuthor = new Book[100]; //prepares sortedByAuthor array for input
	sortedBySubject = new Book[100]; //prepares sortedBySubject array for input
}


//////////////////////////////////////////////////
bool DB::isMemFull()
{
	DB* location;
	try
	{
		location = new DB;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

/////////////////////////////////////////////
void DB::insertBook(Book* tempBook)
{
	using namespace std;
	string tit = tempBook->title;
	string act = tempBook->action;
	string aut = tempBook->author;
	string sub = tempBook->subject;
	char* tm = tempBook->time;
	
	unsortedList[bookCount].title = tit;
	unsortedList[bookCount].action = act;
	unsortedList[bookCount].author = aut;
	unsortedList[bookCount].subject = sub;
	unsortedList[bookCount].time = tm;

	system("cls");

	cout << "You have " << unsortedList[bookCount].action <<":\n" << endl <<
		unsortedList[bookCount].title << endl <<
		unsortedList[bookCount].author << endl <<
		unsortedList[bookCount].subject << endl <<
		"on " << unsortedList[bookCount].time << endl << endl;
	
	bookCount++;
	printToLog(tempBook);
}

//////////////////////////////////////////////////
DB::~DB()
{

	bookDB.close();
	delete[] unsortedList;
	delete[] sortedByAuthor;
	delete[] sortedBySubject;
	delete[] sortedByTitle;
}

void DB::deleteBook(Book* tBook, std::string tit, int location)
{	
	printToLog(tBook);

	for (int index = location + 1; index < bookCount; index++)
		unsortedList[index - 1] = unsortedList[index];

	bookCount--;
}
#include "UI.h"
#include "DB.h"
//////////////////////////////////////////////////
UI::UI()
{
	midPoint = 0;
	inInventory = true;
	bookAdded = false;
}

//////////////////////////////////////////////////
bool UI::BinarySearch(Book* info, std::string item, int fromLocation, int toLocation)
{
	if (midPoint == -1) // Base case 1
	{
		midPoint = 0;
		return false;
	}
	else
	{
		midPoint = (fromLocation + toLocation) / 2;
		if (item != info[midPoint].title)
			return BinarySearch(info, item, fromLocation, midPoint -= 1);
		else if (item == info[midPoint].title)
		{
			midPoint = 0;
			return true;
		}
		else
			return BinarySearch(info, item, midPoint += 1, toLocation);
	}
}

//////////////////////////////////////////////////
int UI::userCommands()
{
	using namespace std;
	string strInput = "";
	int tempInput = -1;
	cout << "Please make a selection from the options below...\n" << endl;
	cout << "Press \"1\" to insert a book into the database." << endl;
	cout << "Press \"2\" to delete a book from the database." << endl;
	cout << "Press \"3\" to list books in database." << endl;
	cout << "Press \"4\" to quit program." << endl;

	getline(std::cin, strInput);
	if (strInput.length() > 1)
	{
		cout << "You have made an ivalid selection. Please try again.\n" << endl;
	}
	tempInput = stoi(strInput);
	return tempInput;
}

//////////////////////////////////////////////////
void UI::insertMagic(const std::string title, const std::string author, const std::string subject)
{
	//tests for full memory
	memoryFull = isMemFull();
	if (memoryFull == true)
	{
		std::cout << "Memory is full. Please contact administrator for further assistance.\n" << std::endl;
	}
	//if memory valid
	else
	{
		Book* tempBook = new Book;

		// insertion time stamp
		time_t now = time(0);
		char* dt = ctime(&now);

		// assign values to tempBook
		tempBook->time = dt;
		tempBook->title = title;
		tempBook->subject = subject;
		tempBook->author = author;
		tempBook->action = "inserted";

		// search inventory for duplicates
		inInventory = BinarySearch(unsortedList, title, 0, bookCount);
		if (inInventory != true)
		{
			insertBook(tempBook);
			std::cout << "Book inserted...\n" << std::endl;
		}
		else
		{
			std::cout << "Title is already in inventory." << std::endl;
		}
		delete tempBook;
	}
}

void UI::saveDB()
{
	printToFile("books.txt", bookCount);
	printToLog("log.txt", log, logIter);
}

void UI::printToLog(std::string DBname, Book* arr, int arrLen)
{
	outFile.open(DBname);
	for (int i = 0; i < (arrLen); i++)
	{
		outFile << arr[i].title << std::endl;
		outFile << arr[i].author << std::endl;
		outFile << arr[i].subject << std::endl;
		outFile << arr[i].action << std::endl;
		outFile << arr[i].time << std::endl;
	}
	outFile.close();
}

void UI::printToFile(std::string DBname, int arrLen)
{
	outFile.open(DBname);
	for (int i = 0; i < (arrLen); i++)
	{
		outFile << unsortedList[i].title << std::endl;
		outFile << unsortedList[i].author << std::endl;
		outFile << unsortedList[i].subject << std::endl;
	}
	outFile.close();
}

void UI::deleteMagic(const std::string tit, const std::string aut, const std::string sub)
{
	Book* tempBook = new Book;

	// insertion time stamp
	time_t now = time(0);
	char* dt = ctime(&now);
	// assign values to tempBook
	tempBook->time = dt;
	tempBook->title = tit;
	tempBook->subject = sub;
	tempBook->author = aut;
	tempBook->action = "deleted";
	// search inventory for duplicates
	
	int location = findStuff(tit);
	
	//inInventory = BinarySearch(unsortedList, tit, 0, unsortedArrayLength);
	if (inInventory == true)
	{
		deleteBook(tempBook, tit, location);
		std::cout << "Book deleted...\n" << std::endl;
	}
	else
	{
		std::cout << "Title is not in inventory." << std::endl;
	}
	delete tempBook;
}

void UI::sortMagic(const std::string userOp)
{
	using namespace std;
	if (userOp.length() > 1)
	{
		cout << "You have entered an invalid option, please try again." << endl;
	}
	else
	{
		int boo = stoi(userOp);
		int a = 0; //case2 iterator
		Book* tempBook = new Book;
		
		switch (boo)
		{
		case 1: //unsorted List
			for (int i = 0; i < bookCount; i++)
			{
				cout << unsortedList[i].title << endl;
				cout << unsortedList[i].author << endl;
				cout << unsortedList[i].subject << endl << endl;
			}
			break;
		case 2: //sorted by title
			for (int i = 0; i < bookCount; i++)
			{
				sortedByTitle[i] = unsortedList[i];
			}
			for (int j = 0; j < (bookCount*bookCount); j++)
			{
				for (int i = 0; i < (bookCount); i++)
				{
					while ((sortedByTitle[a].title > sortedByTitle[a + 1].title) && (a + 1 != bookCount))
					{
						if (sortedByTitle[a].title > sortedByTitle[a + 1].title)
						{
							tempBook->title = sortedByTitle[a].title;
							tempBook->author = sortedByTitle[a].author;
							tempBook->subject = sortedByTitle[a].subject;

							sortedByTitle[a] = sortedByTitle[a + 1];
							sortedByTitle[a + 1].title = tempBook->title;
							sortedByTitle[a + 1].author = tempBook->author;
							sortedByTitle[a + 1].subject = tempBook->subject;
							a++;
						}
						else
						{
							a++;
						}
					}
					a++;
				}
				a = 0;
			}
			for (int i = 0; i < bookCount; i++)
			{
				cout << sortedByTitle[i].title << endl;
				cout << sortedByTitle[i].author << endl;
				cout << sortedByTitle[i].subject << endl;
				cout << endl;
			}
			break;
		case 3: //sort by author

			for (int i = 0; i < bookCount; i++)
			{
				sortedByAuthor[i] = unsortedList[i];
			}
			for (int j = 0; j < (bookCount*bookCount); j++)
			{
				for (int i = 0; i < (bookCount); i++)
				{
					while ((sortedByAuthor[a].author > sortedByAuthor[a + 1].author) && (a + 1 != bookCount))
					{
						if (sortedByAuthor[a].author > sortedByAuthor[a + 1].author)
						{
							tempBook->title = sortedByAuthor[a].title;
							tempBook->author = sortedByAuthor[a].author;
							tempBook->subject = sortedByAuthor[a].subject;

							sortedByAuthor[a] = sortedByAuthor[a + 1];
							sortedByAuthor[a + 1].title = tempBook->title;
							sortedByAuthor[a + 1].author = tempBook->author;
							sortedByAuthor[a + 1].subject = tempBook->subject;
							a++;
						}
						else
						{
							a++;
						}
					}
					a++;
				}
				a = 0;
			}
			for (int i = 0; i < bookCount; i++)
			{
				cout << sortedByAuthor[i].author << endl;
				cout << sortedByAuthor[i].title << endl;
				cout << sortedByAuthor[i].subject << endl;
				cout << endl;
			}
			break;
		case 4: //sort by subject
			for (int i = 0; i < bookCount; i++)
			{
				sortedBySubject[i] = unsortedList[i];
			}
			for (int j = 0; j < (bookCount*bookCount); j++)
			{
				for (int i = 0; i < (bookCount); i++)
				{
					while ((sortedBySubject[a].subject > sortedBySubject[a + 1].subject) && (a + 1 != bookCount))
					{
						if (sortedBySubject[a].subject > sortedBySubject[a + 1].subject)
						{
							tempBook->title = sortedBySubject[a].title;
							tempBook->author = sortedBySubject[a].author;
							tempBook->subject = sortedBySubject[a].subject;

							sortedBySubject[a] = sortedBySubject[a + 1];
							sortedBySubject[a + 1].title = tempBook->title;
							sortedBySubject[a + 1].author = tempBook->author;
							sortedBySubject[a + 1].subject = tempBook->subject;
							a++;
						}
						else
						{
							a++;
						}
					}
					a++;
				}
				a = 0;
			}
			for (int i = 0; i < bookCount; i++)
			{
				cout << sortedBySubject[i].subject << endl;
				cout << sortedBySubject[i].title << endl;
				cout << sortedBySubject[i].author << endl;
				cout << endl;
			}
			break;
		default:
			cout << "You have entered an invalid option, please try again." << endl;
			break;
		}
	}

}

int UI::findStuff(std::string tit)
{
	for (int i = 0; i < bookCount; i++)
	{
		if (unsortedList[i].title == tit)
		{
			inInventory = true;
			return i;
			break;
		}
	}
}

#include "UI.h"

/*******************************************************************************
* Program Name: Library Inventory Database
* Created Date: 4/24/16
* Created By: Troy Jones
* Purpose: To make a database for library books
* Acknowledgements: n/a
*******************************************************************************/
int main()
{
	using namespace std;
	UI doo;
	doo.loadDBs();
	int userSelection = -1;
	std::string title = "";
	std::string author = "";
	std::string subject = "";
	string sortOption = "";
	bool userSelectionOkay = false;

	cout << "Welcome to the Library Inventory Database." << endl;

	do
	{
		userSelection = doo.userCommands();

		switch (userSelection)
		{
		case 1: //Result if user chooses to insert a book into database
			cout << "Please enter title of the book you wish to add." << endl;
			getline(cin, title);
			cout << "Please enter author of the book you wish to add. (last name, first name)" << endl;
			getline(cin, author);
			cout << "Lastly, please enter the subject of the book you wish to add" << endl;
			getline(cin, subject);
			doo.insertMagic(title, author, subject);
			userSelectionOkay = false;
			break;
		case 2: //Result if user chooses to delete a book from database
			cout << "Please enter title of the book you wish to delete." << endl;
			getline(cin, title);
			subject = "";
			author = "";
			doo.deleteMagic(title, author, subject);
			userSelectionOkay = false;
			break;
		case 3: //Result if user chooses to view database
			cout << "How would you like inventory displayed?" << endl;
			cout << "Unsorted, press '1'" << endl;
			cout << "Sorted by title, press '2'" << endl;
			cout << "Sorted by author, press '3'" << endl;
			cout << "Sorted by subject, press '4'" << endl;
			getline(cin, sortOption);
			doo.sortMagic(sortOption);
			userSelectionOkay = false;
			break;
		case 4: //Result if user chooses to quit program.
			cout << "Thank you for using Library Inventory Database." << endl;
			doo.saveDB();
			userSelectionOkay = true;
			break;
		default: //Result for invalid selection.
			cout << "You have entered an invalid choice. Please try again..." << endl << endl;
			userSelectionOkay = false;
			break;
		}

		title = "";
		author = "";
		subject = "";
	} while (userSelectionOkay == false);

	system("pause");
	return 0;
}
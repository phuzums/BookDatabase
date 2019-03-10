#include <iostream>
#include <iomanip>
#include <string>
#include "BookDB.h"

using namespace std;

void exit();
void complete(string type, string name);
void welcome();
void loopReset(bool loop[]);
void printDebug(BookDB *myDB);

#define SIZE 100
#define DEBUG false

int main(int argc, char** argv)
{
	BookDB *myDB = new BookDB("books.txt");
	int choice[SIZE];
	string schoice[SIZE];
	bool loop[SIZE];
	string type;
	do
	{

		if (DEBUG)
		{
			cout << "\nChecking DB...\n";
			printDebug(myDB);
			cin.sync();
		}

		loopReset(loop);
		welcome();
		cout << "=====================================" << endl;
		cout << "De Anza Book Shop. " << endl;
		cout << "=====================================" << endl;
		cout << "Modules: " << endl;
		cout << "	1. Cashier" << endl;
		cout << "	2. Inventory" << endl;
		cout << "	3. Report" << endl;
		cout << "	4. Exit" << endl;
		cout << "=====================================" << endl;
		cin >> choice[0];


		if (choice[0] == 1) // CASHIER MODULE
		{
			system("CLS");
			do
			{
				loopReset(loop);
				cout << "=====================================" << endl;
				cout << "Cashier Module " << endl;
				cout << "=====================================" << endl;
				cout << "1. Enter a book's name that you want to buy" << endl;
				cout << "2. Enter a book's ISBN that you want to buy" << endl;
				cout << "3. Go back" << endl;
				cout << "=====================================" << endl;
				cin >> choice[1];
				if (choice[1] == 1)
				{
					cin.ignore();
					system("CLS");
					do
					{
						loopReset(loop);
						cout << "=====================================" << endl;
						cout << "Cashier Module            " << endl;
						cout << "=====================================" << endl;
						cout << "Please enter the name of your book" << endl;
						cout << "1. Go back" << endl;
						cout << "=====================================" << endl;
						getline(cin, schoice[0]); // reads book name
						if (schoice[0] == "1")
						{
							loop[2] = 0;
							system("CLS");
						}
						else // schoice[0] = book...
						{
							type = "book";
							//complete(type, schoice[0]); // for testing purposes
							int idx = myDB->findBook(schoice[0]);
							if (idx < 0)
								cout << "\nBook could not be found... Please try again.\n";
							else
								if (myDB->getBook(idx).quantity <= 0)
									cout << "\nBook is currently sold out... Please try another book.\n";
								else
								{
									double price = myDB->sellBook(idx);
									cout << "\n" << '\"' << myDB->getBook(idx).title << '\"' << " was sold for: " << setprecision(2) << fixed << price;
								}
							cout << "\nPress any key...";
							system("pause >nul");
							system("cls");
						}
					} while (loop[2]);

				}
				else if (choice[1] == 2)
				{
					cin.ignore();
					system("CLS");

					// Prep a books list for a checkout
					BookList cart;

					do
					{
						// TODO : Cart requires error-checking against duplicate books. 
						//   Books we do not have cannot be added to the cart, but if we have
						//   at least 1, you can add 50000 of that book to the cart >_<
						loopReset(loop);
						cout << "=====================================" << endl;
						cout << "Cashier Module            " << endl;
						cout << "=====================================" << endl;
						cout << "Please enter the ISBN of your book" << endl;
						cout << "1. Go back" << endl;
						cout << "2. View Cart" << endl;
						cout << "3. Checkout" << endl;
						cout << "=====================================" << endl;
						getline(cin, schoice[1]); // reads ISBN name
						std::cin.sync();
						if (schoice[1] == "1" || schoice[1] == "2" || schoice[1] == "3")
						{
							if (schoice[1] == "1")
							{
								loop[3] = 0;
								system("CLS");
							}
							if (schoice[1] == "2")
							{
								system("CLS");
								loop[3] = 1; // <--- kinda hack but it works :)
								std::setfill('.');

								cout << "=====================================" << endl;
								cout << "Current Cart Contents..." << endl;
								cout << "=====================================" << endl;
								cout << std::left << std::setfill('.');
								for (int idx = 0; idx < cart.getNumBooks(); idx++)
									cout << std::setw(31) << cart.getBook(idx).title << "$" << setprecision(2) << fixed << cart.getBook(idx).retailCost << endl;
								cout << "=====================================" << endl;
								cout << std::setw(31) << "Total cost" << "$" << setprecision(2) << fixed << cart.getTotalCost() << endl;
								cout << endl << endl << "Press any key to continue...";
								system("pause >nul");
								system("cls");
								cin.sync();
							}
							if (schoice[1] == "3")
							{
								// Sell all the books based off each of the cart's item's ISBNs
								// Note that an ISBN that has associated quantity <= 0 cannot be
								// added to a cart, so no error checking here.
								for (int idx = 0; idx < cart.getNumBooks(); idx++)
									myDB->sellBook(cart.getBook(idx).ISBN);
								// Also note that profit tracking is inherant to the BookDB class
								// ...so no profit tracking here either...
							}
						}
						else // schoice[1] = book...
						{
							type = "ISBN";
							//complete(type, schoice[1]); // for testing purposes
							int idx = myDB->findBook(stol(schoice[1]));
							if (idx < 0)
								cout << "\nBook could not be found... Please try again.\n";
							else
								if (myDB->getBook(idx).quantity <= 0)
									cout << "\nBook is currently sold out... Please try another book.\n";
								else
								{
									// Add a book to the cart
									cart.addBook(myDB->getBook(idx));
									cout << "\n" << '\"' << myDB->getBook(idx).title << '\"' << " was added to the cart!" << endl;
									// Repeating the cart value is verbose ... we can turn that on tho here by uncommenting if you want
									//cout << "Current Cart Value : " << setprecision(2) << fixed << cart.getTotalCost();
								}
							cout << "\nPress any key...";
							system("pause >nul");
							system("cls");
						}


					} while (loop[3]);
				}
				else if (choice[1] == 3) // go back
				{
					loop[1] = 0;
					system("CLS");
				}
				else
				{
					system("CLS");
					cout << endl << "Please try again by entering a number 1-3. " << endl << endl;
				}
			} while (loop[1]);
		}
		else if (choice[0] == 2) // INVENTORY MODULE
		{
			system("CLS");
			do
			{
				loopReset(loop);
				cout << "=====================================" << endl;
				cout << "Welcome to the Inventory Module " << endl;
				cout << "=====================================" << endl;
				cout << "1. Search for a book" << endl;
				cout << "2. Add a book" << endl;
				cout << "3. Delete a book" << endl;
				cout << "4. Edit a book" << endl;
				cout << "5. Go back" << endl;
				cout << "=====================================" << endl;
				cin >> choice[2];
				if (choice[2] == 1)
				{
					cout << "=====================================" << endl;
					cout << "Inventory Module            " << endl;
					cout << "=====================================" << endl;
					cout << "Please enter the ISBN of your book" << endl;
					cout << "1. Go back" << endl;
					cout << "=====================================" << endl;
				}
				else if (choice[2] == 2)
				{
					// lots of cin work here, gotta get all the details to fill a book class 
					/* Book Members:
						unsigned long ISBN;
						double wholesaleCost, retailCost;
						std::string title, author, publisher;
						Date addedOn;
						int quantity = 1;
					*/
				}
				else if (choice[2] == 3)
				{
					loop[4] = 0;
				}
				else
				{
					cout << endl << "You have typed in an invalid bookname/ISBN, please try again. " << endl << endl;
				}
			} while (loop[4]);

		}
		else if (choice[0] == 3)
		{

		}
		else if (choice[0] == 4)
		{
		delete myDB;
		cout << "\nPress any key...";
		system("pause >nul");
			exit();
		}
		else
		{
			system("CLS");
			cout << endl << "Please try again by entering a number 1-4. " << endl << endl;
		}

	} while (loop[0]);





	exit();



	return 0;

}

void exit()
{
	system("CLS");
	cout << " _ _ _ " << endl;
	cout << "| | | | | | " << endl;
	cout << "| || |__ __ _ _ __ | | ___ _ ___ _ _ " << endl;
	cout << "| _| ' \ / ` | ' \| |/ / | | |/ _ \| | | | " << endl;
	cout << "| || | | | (| | | | | <| || | () | || | " << endl;
	cout << " \|| ||\,|| |||\\\, |\/ \__,| " << endl;
	cout << " / | " << endl;
	cout << " |/ " << endl << endl;
	cout << "For using our app. Safe Travels. U w U. ";

	cout << endl << "Press enter to exit the program. " << endl;
	cin.get();
	cin.ignore();
	exit(0);
}

void complete(string type, string name)
{
	system("CLS");
	cout << "Your " << type << ", " << """ <<name << """ << " has been added to the store. " << endl << endl;
}

void welcome()
{
	cout << " _ _ _ _ _ _ " << endl;
	cout << "| | | | | | | | | | | | " << endl;
	cout << "| | | | | | ___ ___ _ __ ___ ___ | | ___ | || |_ ___ " << endl;
	cout << "| |/\| |/ _ \ |/ / _ \| ' _ \\ / _ \\ | __/ _ \\ | __| '_ \\ / _ \\ " << endl; cout << "\\ /\\ / __/ | (_| (_) | | | | | | __/ | || (_) | | |_| | | | __/ " << endl; cout << " \\/ \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| \\__\\___/ \\__|_| |_|\\___| " << endl; cout << "	______ ___ " << endl; cout << "	| _ \\ / _ \\ " << endl; cout << "	| | | |___/ /_\\ \\_ __ ______ _" << endl; cout << "	| | | / _ \\ _ | '_ \\|_ / _ | " << endl;
	cout << "	| |/ / / | | | | | |/ / (| | " << endl;
	cout << "	|/ \\| |/| |/\,| " << endl;
	cout << "	______ _ _____ _ " << endl;
	cout << "	| ___ \ | | / | | " << endl;
	cout << "	| |/ / ___ ___ | | __ \ --.| |__ ___ _ __ " << endl; cout << "	| ___ \\/ _ \\ / _ \\| |/ / --. \ ' \ / _ \| ' \ " << endl;
	cout << "	| |/ / () | () | < /\__/ / | | | () | |) | " << endl;
	cout << "	\/ \/ \/||\\ \/|| ||\/| ./ " << endl;
	cout << "	| | " << endl;
	cout << "	|_| " << endl;
	cout << endl << "Press enter to start the program. " << endl;
	cin.get();
	system("CLS");
}

void loopReset(bool loop[])
{
	for (int i = 0; i <= SIZE; i++) // sets all values of loop into true
	{
		loop[i] = 1;
	}
}


void printDebug(BookDB *myDB)
{
	std::cout << "\nPrint all books? (y/n) : ";
	char meow;
	std::cin >> meow;
	if(meow == 'y')
		for (int idx = 0; idx < myDB->getNumBooks(); idx++)
			std::cout << "\nBook " << idx << ':' << myDB->getBook(idx);

	std::cout << "\nTotal Wholesale Worth: " << myDB->getWholesaleValue();
	std::cout << "\nTotal Retail Worth: " << myDB->getRetailValue();
	std::cout << "\nBooks in DB: " << myDB->getNumBooks();
	std::cout << "\n====================================";

	if (meow == 'y')
	{
		std::cout << "\n\n  ~ Original Book List ~";
		for (int idx = 0; idx < myDB->getNumBooks(); idx++)
			std::cout << "\nBook " << idx << ':' << myDB->getBook(idx).title;
		std::cout << "\n====================================";
	}

	std::cout << "\n\n";
	system("pause >nul");
	std::cin.sync();
}

#include <iostream>
#include <iomanip>
#include <string>
#include "BookDB.h"
#include "BookList.h"

using namespace std;

void exit();
void complete(string type, string name);
void welcome();
void loopReset(bool loop[]);
void printDebug(BookDB *myDB);
void printDebugList(BookDB *myDB);

#define SIZE 100
#define DEBUG false

int main(int argc, char** argv)
{
	BookDB *myDB = new BookDB("books.txt");
	int choice[SIZE];
	string schoice[SIZE];
	string IchoiceString[SIZE];
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

		if (choice[0] == 88)
		{
			system("cls");
			int verb = 0;
			std::cout << "  Input Verbosity... (0-3)" << std::endl;
			std::cin >> verb;
			printDebug(myDB);
			std::cout << "  Press any key to continue...";
			system("pause >nul");

			system("cls");
			std::cout << "  Press any key to output sorted databases..." << std::endl << std::endl;

			std::cout << "\n  Sorting by quantity : " << std::endl << std::left << std::setfill('.');
			myDB->sortBooks(SORT_METHOD::QUANTITY);
			myDB->printByMethod(verb, SORT_METHOD::QUANTITY);
			std::cout << "\n\n  Press any key...\n";
			system("pause >nul");

			std::cout << "\n  Sorting by cost : " << std::endl;
			myDB->sortBooks(SORT_METHOD::COST);
			myDB->printByMethod(verb, SORT_METHOD::COST);
			std::cout << "\n\n  Press any key...\n";
			system("pause >nul");

			std::cout << "\n  Sorting by age : " << std::endl;
			myDB->sortBooks(SORT_METHOD::AGE);
			myDB->printByMethod(verb, SORT_METHOD::AGE);
			std::cout << "\n\n  Press any key...\n";
			system("pause >nul");
		}
		if (choice[0] == 1) // CASHIER MODULE
		{
			system("CLS");
			do
			{
				loopReset(loop);
				cout << "=====================================" << endl;
				cout << "Cashier Module " << endl;
				cout << "=====================================" << endl;
				cout << "   1. Enter a book's name that you want to buy" << endl;
				cout << "   2. Enter a book's ISBN that you want to buy" << endl;
				cout << "   3. Go back" << endl;
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
						cout << "   1. Go back" << endl;
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
						cout << "   1. Go back" << endl;
						cout << "   2. View Cart" << endl;
						cout << "   3. Checkout" << endl;
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
	cout << "Inventory Module " << endl;
	cout << "=====================================" << endl;
	cout << "   1. Search for a book" << endl;
	cout << "   2. Add a book" << endl;
	cout << "   3. Delete a book" << endl;
	cout << "   4. Edit a book" << endl;
	cout << "   5. Go back" << endl;
	cout << "=====================================" << endl;
	cin >> choice[2];
	if (choice[2] == 1) // Search for a book
	{
		cin.ignore();
		system("CLS");
		do
		{
			loopReset(loop);
			cout << "=====================================" << endl;
			cout << "Inventory Module " << endl;
			cout << "=====================================" << endl;
			cout << "   Search for a book by: " << endl;
			cout << "   1. ISBN" << endl;
			cout << "   2. Title" << endl;
			cout << "   3. Author" << endl;
			cout << "   4. Publisher" << endl;
			cout << "   5. Date Added" << endl;
			cout << "   6. Quantity on Hand" << endl;
			cout << "   7. Wholesale Cost" << endl;
			cout << "   8. Retail Price" << endl;
			cout << "   9. Go back" << endl;
			cout << "=====================================" << endl;
			cin >> choice[3];
			if (choice[3] == 1) // ISBN
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the ISBN: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[0]);
					if (IchoiceString[0] == "Back" || IchoiceString[0] == "back")
					{
						loop[5] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");
						if (myDB->findBook(atoi(IchoiceString[0].c_str())))
							cout << "\nBook Found: " << myDB->getBook(myDB->findBook(atoi(IchoiceString[0].c_str())));
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[5] = 0;
						system("CLS");
					}
				} while (loop[5]);
			}
			else if (choice[3] == 2) // Title
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the Title: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[1]);
					if (IchoiceString[1] == "Back" || IchoiceString[1] == "back")
					{
						loop[6] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");
						int idx = myDB->findBook(IchoiceString[1]);
						if (idx > 0)
							cout << "\nBook Found: " << myDB->getBook(idx);
						else
							cout << "\nBook not found...";
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[5] = 0;
						system("CLS");
					}
				} while (loop[6]);
			}
			else if (choice[3] == 3) // Author
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the Author: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[2]);
					if (IchoiceString[2] == "Back" || IchoiceString[2] == "back")
					{
						loop[7] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");
						BookList *searchResult = myDB->findBookByAuthor(IchoiceString[2]);
						
						if (searchResult->getNumBooks() > 0)
						{
							cout << searchResult->getNumBooks() << " books found with author " << IchoiceString[2] << "...\n";
							for (int idx = 0; idx < searchResult->getNumBooks(); idx++)
								cout << searchResult->getBook(idx) << std::endl;
						}
						else
							cout << "No books found for Author " << IchoiceString[2];
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[7] = 0;
						system("CLS");
					}
				} while (loop[7]);
			}
			else if (choice[3] == 4) // Publisher
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the Publisher: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[3]);
					if (IchoiceString[3] == "Back" || IchoiceString[3] == "back")
					{
						loop[8] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");
						BookList *searchResult = myDB->findBookByPublisher(IchoiceString[3]);

						if (searchResult->getNumBooks() > 0)
						{
							cout << searchResult->getNumBooks() << " books found with publisher " << IchoiceString[3] << "...\n";
							for (int idx = 0; idx < searchResult->getNumBooks(); idx++)
								cout << searchResult->getBook(idx) << std::endl;
						}
						else
							cout << "No books found for Publisher " << IchoiceString[3];
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[8] = 0;
						system("CLS");
					}
				} while (loop[8]);
			}
			else if (choice[3] == 5) // Date Added
			{
				cin.ignore();
				system("CLS");
				do
				{
					// Note : had to break this out of the menu loop to access cin more easily
					loopReset(loop);
						system("CLS");
						Date myDate = { 0,0,0 };
						// WARNING : assumes we don't have any books written before 0/0/0000 ... hey, it could happen! ... :D
						cout << "=====================================" << endl;
						cout << "Inventory Module " << endl;
						cout << "=====================================" << endl;
						cout << "Please enter the year to search : "; //Year cannot be 0, as that would output all da books lol
						cin >> myDate.year;
						cout << "Please enter the month to search (or 0 to search all): ";
						cin >> myDate.month;
						if (myDate.month > 0)
						{
							cout << "Please enter the day to search (or 0 to search all): ";
							cin >> myDate.day;
						}
						
						BookList *searchResult = myDB->findBookByDate(myDate);
						system("cls");
						if (searchResult->getNumBooks() > 0)
						{
							// Don't really have to, but format the date output based on search conditions...
							if(myDate.day == 0)
								if(myDate.month == 0)
									cout << searchResult->getNumBooks() << " books found with date " << '*' << '/' << '*' << '/' << myDate.year << "...\n";
								else
									cout << searchResult->getNumBooks() << " books found with date " << myDate.month << ' / ' << '*' << ' / ' << myDate.year << "...\n";
							else
								cout << searchResult->getNumBooks() << " books found with date " << myDate.month << '/' << myDate.day << '/' << myDate.year << "...\n";

							// Then output the book list
							for (int idx = 0; idx < searchResult->getNumBooks(); idx++)
								cout << searchResult->getBook(idx) << std::endl;
						}

						cout << endl << "Press enter to continue. " << endl;
						system("pause >nul");

						loop[9] = 0;
						system("CLS");
				} while (loop[9]);
			}
			else if (choice[3] == 6) // Quantity on hand
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the Quantity on Hand: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[5]);
					if (IchoiceString[5] == "Back" || IchoiceString[5] == "back")
					{
						loop[10] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");

						BookList *searchResult = myDB->findBookByQuantity(atof(IchoiceString[5].c_str()));

						if (searchResult->getNumBooks() > 0)
						{
							cout << searchResult->getNumBooks() << " books found with quantity " << IchoiceString[5] << "...\n";
							for (int idx = 0; idx < searchResult->getNumBooks(); idx++)
								cout << searchResult->getBook(idx) << std::endl;
						}
						else
							cout << "No books found for quantity " << IchoiceString[2];
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[10] = 0;
						system("CLS");
					}
				} while (loop[10]);
			}
			else if (choice[3] == 7) // Wholesale Cost
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the Wholesale Cost: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[6]);
					if (IchoiceString[6] == "Back" || IchoiceString[6] == "back")
					{
						loop[11] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");						
						BookList *searchResult = myDB->findBookByWholesalePrice(atof(IchoiceString[6].c_str()));

						if (searchResult->getNumBooks() > 0)
						{
							cout << searchResult->getNumBooks() << " books found with price " << IchoiceString[6] << "...\n";
							for (int idx = 0; idx < searchResult->getNumBooks(); idx++)
								cout << searchResult->getBook(idx) << std::endl;
						}
						else
							cout << "No books found for price " << IchoiceString[6];
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[11] = 0;
						system("CLS");
					}
				} while (loop[11]);
			}
			else if (choice[3] == 8) // Retail Price
			{
				cin.ignore();
				system("CLS");
				do
				{
					loopReset(loop);
					cout << "=====================================" << endl;
					cout << "Inventory Module " << endl;
					cout << "=====================================" << endl;
					cout << "Enter the Retail Price: " << endl;
					cout << " Or type Back to go back" << endl;
					cout << "=====================================" << endl;
					getline(cin, IchoiceString[7]);
					if (IchoiceString[7] == "Back" || IchoiceString[7] == "back")
					{
						loop[12] = 0;
						system("CLS");
					}
					else
					{
						system("CLS");						
						BookList *searchResult = myDB->findBookByRetailPrice(atof(IchoiceString[7].c_str()));

						if (searchResult->getNumBooks() > 0)
						{
							cout << searchResult->getNumBooks() << " books found with price " << IchoiceString[7] << "...\n";
							for (int idx = 0; idx < searchResult->getNumBooks(); idx++)
								cout << searchResult->getBook(idx) << std::endl;
						}
						else
							cout << "No books found for price " << IchoiceString[7];
						cout << endl << "Press enter to continue. " << endl;
						cin.get();
						loop[12] = 0;
						system("CLS");
					}
				} while (loop[12]);
			}
			else if (choice[3] == 9) // go back
			{
				loop[13] = 0;
				system("CLS");
			}
			else
			{
				system("CLS");
				cout << endl << "Please try again by entering a number 1-9. " << endl << endl;
			}
		} while (loop[13]);
	}
	else if (choice[2] == 2) // Add a book
	{
		/* Book Members:
		unsigned long ISBN;
		double wholesaleCost, retailCost;
		string title, author, publisher;
		Date addedOn;
		int quantity = 1;
		*/

		// Make a temp Book class to hold values...
		Date t_date;
		Book t_bk;
		// hack to clear the hanging '\n' off the buffer
		cin.get();
		loopReset(loop);
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the ISBN: ";
		getline(cin, IchoiceString[8]);
		t_bk.ISBN = atol(IchoiceString[8].c_str());
		cout << "=====================================" << endl;
		// = IchoiceString[8];
		system("CLS");
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Wholesale Cost: ";
		getline(cin, IchoiceString[9]);
		t_bk.wholesaleCost = atof(IchoiceString[9].c_str());
		cout << "=====================================" << endl;
		// = IchoiceString[9];
		system("CLS");
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Retail Cost: ";
		getline(cin, IchoiceString[10]);
		t_bk.retailCost = atof(IchoiceString[10].c_str());
		cout << "=====================================" << endl;
		// = IchoiceString[10];
		system("CLS");
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Title: ";
		getline(cin, IchoiceString[11]);
		t_bk.title = IchoiceString[11];
		cout << "=====================================" << endl;
		// = IchoiceString[11];
		system("CLS");
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Author: ";
		getline(cin, IchoiceString[12]);
		t_bk.author = IchoiceString[12];
		cout << "=====================================" << endl;
		// = IchoiceString[12];
		system("CLS");
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Publisher: ";
		getline(cin, IchoiceString[13]);
		t_bk.publisher = IchoiceString[13];
		cout << "=====================================" << endl;
		// = IchoiceString[13];
		system("CLS");
		// This could be avoided but I don't think we can use other libaries (i.e. chrono or ctime)
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Year it was Added: ";
		getline(cin, IchoiceString[14]);
		t_date.year = atoi(IchoiceString[14].c_str());
		cout << "Enter the Month it was Added: ";
		getline(cin, IchoiceString[14]);
		t_date.month = atoi(IchoiceString[14].c_str());
		cout << "Enter the day it was Added: ";
		getline(cin, IchoiceString[14]);
		t_date.day = atoi(IchoiceString[14].c_str());
		t_bk.addedOn = t_date;
		// = IchoiceString[14];
		system("CLS");
		cout << "=====================================" << endl;
		cout << "Inventory Module " << endl;
		cout << "=====================================" << endl;
		cout << "Enter the Quantity: ";
		getline(cin, IchoiceString[15]);
		t_bk.quantity = atoi(IchoiceString[15].c_str());
		cout << "=====================================" << endl;
		
		// Then add the book to the Database...
		myDB->addBook(t_bk);
		cout << "Successfully added \"" << t_bk.title << "\" to the database!" << endl << "Press Any Key to Continue...";
		system("pause >nul");
	
		system("CLS");
	} // Add a Book
	else if (choice[2] == 3) // Delete a Book 
	{
		system("CLS");
		cin.ignore();
		do
		{
			loopReset(loop);
			cout << "=====================================" << endl;
			cout << "Inventory Module " << endl;
			cout << "=====================================" << endl;
			cout << "Type the ISBN of the book you want to delete: " << endl;
			cout << " Or type Back to go back" << endl;
			cout << "=====================================" << endl;
			getline(cin, IchoiceString[12]);
			if (IchoiceString[12] == "Back" || IchoiceString[12] == "back")
			{
				system("CLS");
				loop[14] = 0;
			}
			else
			{
				system("CLS");
				// read the ISBN (IchoiceString[12]) and find the book name 
				// ok :D added another if/else tho incase book not fundeded
				do
				{
					if (!myDB->findBook(atol(IchoiceString[12].c_str())))
					{
						cout << "Book not found...";
						break;
					}
					else
					{
						int idx = myDB->findBook(atol(IchoiceString[12].c_str()));
						loopReset(loop);
						cout << "=====================================" << endl;
						cout << "Inventory Module " << endl;
						cout << "=====================================" << endl;
						cout << "ARE YOU SURE YOU WANT TO DELETE YOUR BOOK " << endl;
						cout << myDB->getBook(idx).title << " FROM THE BOOKSTORE?" << endl;
						cout << "=====================================" << endl;
						getline(cin, IchoiceString[13]);
						if (IchoiceString[13] == "Yes" || IchoiceString[13] == "yes")
						{
							// delete the book here uwu
							// uuuuuuuuUwUuuuuuuuu
							myDB->removeBook(atol(IchoiceString[12].c_str()), myDB->getBook(idx).quantity);
							system("CLS");
							cout << "Your book \"" << myDB->getBook(idx).title << "\" has been deleted from the store. " << endl;
							loop[15] = 0;
						}
						else if (IchoiceString[13] == "No" || IchoiceString[13] == "no")
						{
							system("CLS");
							loop[15] = 0;
						}
						else
						{
							system("CLS");
							cout << "Invalid Input. Please enter Yes or No. " << endl << endl;
						}
					}
				} while (loop[15]);
			}


		} while (loop[14]);
	}
	else if (choice[2] == 4) // Edit a Book
	{
		system("CLS");
		cin.ignore();
		do
		{
			loopReset(loop);
			cout << "=====================================" << endl;
			cout << "Inventory Module " << endl;
			cout << "=====================================" << endl;
			cout << "Type the ISBN of the book you want to edit: " << endl;
			cout << " Or type Back to go back" << endl;
			cout << "=====================================" << endl;
			getline(cin, IchoiceString[14]);

			if (IchoiceString[14] == "Back" || IchoiceString[14] == "back")
			{
				system("CLS");
				loop[16] = 0;
			}
			else
			{
				system("CLS");
				int idx = myDB->findBook(atol(IchoiceString[14].c_str()));
				if (idx <= 0)
					cout << "Book not found.";
				else
					do
					{
						Book t_bk = myDB->getBook(idx);
						loopReset(loop);
						cout << "=====================================" << endl;
						cout << "Inventory Module " << endl;
						cout << "=====================================" << endl;
						cout << "What part of your book, " << t_bk.title << " do you want edited? " << endl;
						cout << "   1. ISBN" << endl;
						cout << "   2. Title" << endl;
						cout << "   3. Author" << endl;
						cout << "   4. Publisher" << endl;
						cout << "   5. Date Added" << endl;
						cout << "   6. Quantity on Hand" << endl;
						cout << "   7. Wholesale Cost" << endl;
						cout << "   8. Retail Price" << endl;
						cout << "   9. Go back" << endl;
						cout << "=====================================" << endl;
						cin >> choice[4];
						if (choice[4] == 1)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new ISBN " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[15]);
								if (IchoiceString[15] == "Back" || IchoiceString[15] == "back")
								{
									system("CLS");
									loop[18] = 0;
								}
								else
								{
									t_bk.ISBN = atoi(IchoiceString[15].c_str());
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's ISBN has been changed. " << endl << endl;
									loop[18] = 0;
								}

							} while (loop[18]);
						}
						else if (choice[4] == 2)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new Title " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[16]);
								if (IchoiceString[16] == "Back" || IchoiceString[16] == "back")
								{
									system("CLS");
									loop[19] = 0;
								}
								else
								{
									t_bk.title = IchoiceString[16];
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Title has been changed. " << endl << endl;
									loop[19] = 0;
								}

							} while (loop[19]);
						}
						else if (choice[4] == 3)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new Author " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[17]);
								if (IchoiceString[17] == "Back" || IchoiceString[17] == "back")
								{
									system("CLS");
									loop[20] = 0;
								}
								else
								{
									t_bk.author = IchoiceString[17];
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Author has been changed. " << endl << endl;
									loop[20] = 0;
								}

							} while (loop[20]);
						}
						else if (choice[4] == 4)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new Publisher " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[18]);
								if (IchoiceString[18] == "Back" || IchoiceString[18] == "back")
								{
									system("CLS");
									loop[21] = 0;
								}
								else
								{
									t_bk.publisher = IchoiceString[18];
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Publisher has been changed. " << endl << endl;
									loop[21] = 0;
								}

							} while (loop[21]);
						}
						else if (choice[4] == 5)
						{
							cin.ignore();
							system("CLS");
							do
							{
								Date myDate = { 0,0,0 };
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in the year " << endl;
								getline(cin, IchoiceString[19]);
								myDate.year = atoi(IchoiceString[19].c_str());

								cout << "Type in the month " << endl;
								getline(cin, IchoiceString[19]);
								myDate.month = atoi(IchoiceString[19].c_str());

								cout << "Type in the day " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[19]);
								myDate.day = atoi(IchoiceString[19].c_str());

								if (IchoiceString[19] == "Back" || IchoiceString[19] == "back")
								{
									system("CLS");
									loop[22] = 0;
								}
								else
								{
									t_bk.addedOn = myDate;
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Date it was Added has been changed. " << endl << endl;
									loop[22] = 0;
								}

							} while (loop[22]);
						}
						else if (choice[4] == 6)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new quantity on hand " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[20]);
								if (IchoiceString[20] == "Back" || IchoiceString[20] == "back")
								{
									system("CLS");
									loop[23] = 0;
								}
								else
								{
									t_bk.quantity = atoi(IchoiceString[20].c_str());
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Quantity on hand has been changed. " << endl << endl;
									loop[23] = 0;
								}

							} while (loop[23]);
						}
						else if (choice[4] == 7)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new Wholesale Cost " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[21]);
								if (IchoiceString[21] == "Back" || IchoiceString[21] == "back")
								{
									system("CLS");
									loop[24] = 0;
								}
								else
								{
									t_bk.wholesaleCost = atof(IchoiceString[20].c_str());
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Wholesale Cost has been changed. " << endl << endl;
									loop[24] = 0;
								}

							} while (loop[24]);
						}
						else if (choice[4] == 8)
						{
							cin.ignore();
							system("CLS");
							do
							{
								loopReset(loop);
								cout << "=====================================" << endl;
								cout << "Inventory Module " << endl;
								cout << "=====================================" << endl;
								cout << "Type in your new Retail Price " << endl;
								cout << " Or type Back to go back" << endl;
								cout << "=====================================" << endl;
								getline(cin, IchoiceString[22]);
								if (IchoiceString[22] == "Back" || IchoiceString[22] == "back")
								{
									system("CLS");
									loop[25] = 0;
								}
								else
								{
									t_bk.retailCost = atof(IchoiceString[20].c_str());
									myDB->modifyBook(idx, t_bk);
									system("CLS");
									cout << "The Book's Retail Price has been changed. " << endl << endl;
									loop[25] = 0;
								}

							} while (loop[25]);
						}

						else if (choice[4] == 9)
						{
							cin.ignore();
							system("CLS");
							loop[17] = 0;
						}
						else
						{
							system("CLS");
							cout << "Invalid Input. Please enter a number 1-9. " << endl << endl;
						}
					} while (loop[17]);
			}

		} while (loop[16]);
	}
	else if (choice[2] == 5) // Go back
	{
		loop[4] = 0;
	}
	else
	{
		cout << endl << "Invalid input. Please try again by entering a number 1-5. " << endl << endl;
	}
} while (loop[4]);

	}
else if (choice[0] == 3) // REPORT MODULE
	{
	system("CLS");
	do
	{
		loopReset(loop);
		cout << "======================================================" << endl;
		cout << "Report Module. " << endl;
		cout << "======================================================" << endl;
		cout << "   1. Inventory List" << endl;
		cout << "   2. Display WholeSale Value" << endl;
		cout << "   3. Display Retail Value" << endl;
		cout << "   4. Display Amounts" << endl;
		cout << "   5. Display Dates Added" << endl;
		cout << "   6. Sort List" << endl;
		cout << "   7. Sales Data" << endl;
		cout << "   8. Go Back " << endl;
		cout << "======================================================" << endl;
		cin >> choice[5];

		if (choice[5] == 1) // Info on all books
		{
			cin.ignore();
			system("CLS");
			BookList* bl = myDB;
			bl->printByMethod(0, SORT_METHOD::SIMPLE);
			cout << endl << endl << "Press enter to continue. " << endl;
			cin.get();
			system("CLS");

		}
		else if (choice[5] == 2) // Info on wholesale
		{
			cin.ignore();
			system("CLS");
			myDB->printByMethod(0, SORT_METHOD::WHOLESALE);
			cout << endl << endl << "Press enter to continue. " << endl;
			cin.get();
			system("CLS");
		}
		else if (choice[5] == 3) // Info on retail
		{
			cin.ignore();
			system("CLS");
			myDB->printByMethod(0, SORT_METHOD::COST);
			cout << endl << endl << "Press enter to continue. " << endl;
			cin.get();
			system("CLS");
		}
		else if (choice[5] == 4) // Info on quantity
		{
			cin.ignore();
			system("CLS");
			myDB->printByMethod(0, SORT_METHOD::QUANTITY);
			cout << endl << endl << "Press enter to continue. " << endl;
			cin.get();
			system("CLS");
		}
		else if (choice[5] == 5) // Info on age
		{
			cin.ignore();
			system("CLS");
			myDB->printByMethod(0, SORT_METHOD::AGE);
			cout << endl << endl << "Press enter to continue. " << endl;
			cin.get();
			system("CLS");
		}
		else if (choice[5] == 6) // Info on age
		{
			do
			{
				cin.ignore();
				system("CLS");
				cout << "======================================================" << endl;
				cout << "Report Module. " << endl;
				cout << "======================================================" << endl;
				cout << "   1. Sort by Quantity" << endl;
				cout << "   2. Sort by Retail Cost" << endl;
				cout << "   3. Sort by Age in Inventory" << endl;
				cout << "   4. Go Back " << endl;
				cout << "======================================================" << endl;
				cin >> choice[5];

				if (choice[5] == 1)
				{
					myDB->sortBooks(SORT_METHOD::QUANTITY);
					cout << "Database now sorted by Quantity." << endl;
					choice[5] = 4;
				}
				else if (choice[5] == 2)
				{
					myDB->sortBooks(SORT_METHOD::COST);
					cout << "Database now sorted by Retail Cost." << endl;
					choice[5] = 4;
				}
				else if (choice[5] == 3)
				{
					myDB->sortBooks(SORT_METHOD::AGE);
					cout << "Database now sorted by Age." << endl;
					choice[5] = 4;
				}
				else if (choice[5] != 4)
				{
					cout << "Invalid selection... Please try again." << endl;
				}

				cout << "Press any key to continue..." << endl;
				system("pause >nul");
				system("CLS");
			} while (choice[5] != 4);
		}
		else if (choice[5] == 7) // Sales Data
		{
			cin.ignore();
			system("CLS");
			cout << "Current Worth Of Database..." << endl << endl;
			cout << "Wholesale Value : $" << std::fixed << std::setprecision(2) << myDB->getWholesaleValue() << endl;
			cout << "Retail Value    : $" << std::fixed << std::setprecision(2) << myDB->getRetailValue() << endl;
			cout << "Net Profit      : $" << std::fixed << std::setprecision(2) << myDB->getNetProfit();
			cout << endl << endl << "Press enter to continue. " << endl;
			cin.get();
			system("CLS");
		}
		else if (choice[5] == 8) // go back
		{
			loop[26] = 0;
		}
		else
		{
			system("CLS");
			cout << endl << "Please try again by entering a number 1-7. " << endl << endl;
		}
	} while (loop[26]);
	}
		else if (choice[0] == 4)
		{
		myDB->writeOutput();
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
	cout << " _    _      _                            _          _   _ " << endl;
	cout << "| |  | |    | |                          | |        | | | | " << endl;
	cout << "| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   | |_| |__   ___ " << endl;
	cout << "| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | __| '_ \\ / _ \\ " << endl;
	cout << "\\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |_| | | |  __/ " << endl;
	cout << " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \\__|_| |_|\\___| " << endl;
	cout << "		______      ___ " << endl;
	cout << "		|  _  \\    / _ \\ " << endl;
	cout << "		| | | |___/ /_\\ \\_ __  ______ _" << endl;
	cout << "		| | | / _ \\  _  | '_ \\|_  / _` | " << endl;
	cout << "		| |/ /  __/ | | | | | |/ / (_| | " << endl;
	cout << "		|___/ \\___\\_| |_/_| |_/___\\__,_| " << endl;
	cout << "		______             _      _____ _ " << endl;
	cout << "		| ___ \\           | |    /  ___| | " << endl;
	cout << "		| |_/ / ___   ___ | | __ \\ `--.| |__   ___  _ __ " << endl;
	cout << "		| ___ \\/ _ \\ / _ \\| |/ /  `--. \\ '_ \\ / _ \\| '_ \\ " << endl;
	cout << "		| |_/ / (_) | (_) |   <  /\\__/ / | | | (_) | |_) | " << endl;
	cout << "		\\____/ \\___/ \\___/|_|\\_\\ \\____/|_| |_|\\___/| .__/ " << endl;
	cout << "						 	   | | " << endl;
	cout << "						 	   |_| " << endl;
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

void printDebugList(BookDB *myDB)
{
	for (int idx = 0; idx < myDB->getNumBooks(); idx++)
		std::cout << "\nBook " << idx << ':' << myDB->getBook(idx).title;
}

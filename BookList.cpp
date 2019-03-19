#include <iomanip>
#include "BookList.h"

BookList::BookList()
{
	numBooks = 0;
	books = new Book[MAX_BOOKS];
}

BookList::~BookList()
{
	if (books)
		delete[] books;
}
double BookList::getTotalCost()
{
	double cost = 0.0f;
	for (int idx = 0; idx < numBooks; idx++)
		cost += books[idx].retailCost;
	return cost;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been filled with at least 1 book?
//Post: pointer to books array is returned
Book* BookList::getBooks()
{
	return books;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  
//Post: 
Book BookList::getBook(int index)
{
	if (index >= 0)
		return books[index];
	else
	{
		Book bk;
		return bk; // bk will auto-initialize to an 'error' book
	}
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: books array is traversed to find how many book entries there are
//          number of books is returned as an int
int BookList::getNumBooks()
{
	// figure out how many books via iteratting
	return numBooks;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: returns the wholesale value of all the books combined
int BookList::findBook(unsigned long ISBN)
{
	if (numBooks > 0)
		for (int idx = 0; idx < numBooks; idx++)
			if (books[idx].ISBN == ISBN)
				return idx;
	return -1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: 
int BookList::findBook(std::string title)
{
	if (numBooks > 0)
		for (int idx = 0; idx < numBooks; idx++)
			if (books[idx].title == title)
				return idx;
	return -1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: A Booklist pointer is returned which is a sublist of the calling
//		booklist. User must also check the booklist to make sure it includes 
//		any books at all, as an empty booklist might be the result of this search.
BookList* BookList::findBookByAuthor(std::string author)
{
	BookList *t_list = new BookList();
	for (int idx = 0; idx < numBooks; idx++)
		if (books[idx].author == author)
			t_list->addBook(books[idx]);
	return t_list;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: A Booklist pointer is returned which is a sublist of the calling
//		booklist including members of the calling booklist which have the publisher
//		searched for. User must also check the booklist to make sure it includes 
//		any books at all, as an empty booklist might be the result of this search.
BookList* BookList::findBookByPublisher(std::string publisher)
{
	BookList *t_list = new BookList();
	for (int idx = 0; idx < numBooks; idx++)
		if (books[idx].publisher == publisher)
			t_list->addBook(books[idx]);
	return t_list;
}


/////////////////////////////////////////////////////////////////////////
//Pre:  books has been initialized
//Post: 
BookList* BookList::findBookByDate(Date myDate)
{
	BookList *t_list = new BookList();
	//Search by year
	for (int idx = 0; idx < numBooks; idx++)
		if (books[idx].addedOn.year == myDate.year) // find hits for that year
			if (books[idx].addedOn.month == myDate.month || myDate.month == 0) //See if that hit matches the month (or if month is 0)
				if (books[idx].addedOn.day == myDate.day || myDate.day == 0) // See if the day matches or if it's zero
					t_list->addBook(books[idx]); // Add the book to the sublist, as it's a hit :D
	return t_list;
}


BookList* BookList::findBookByQuantity(int amt)
{
	BookList *t_list = new BookList();
	for (int idx = 0; idx < numBooks; idx++)
		if (books[idx].quantity == amt)
			t_list->addBook(books[idx]);
	return t_list;
}



/////////////////////////////////////////////////////////////////////////
//Pre: bk is a valid book
//Post: bk is added to the end of the array IF the numBooks is less than
//      or equal to the max amt of books. Wholesale and Retail value is updated
//      by adding to the class's member variables. Returns 1 if success, 0 if
//      error such as not enough space or bk not initialized. Also checks the
//      values of bk to make sure they're there (not missing ISBN, etc...)
bool BookList::addBook(const Book &bk)
{
	if (numBooks >= MAX_BOOKS)
		return false;

	// ISBN checking
	if (findBook(bk.ISBN))
		// If the book already exists, just add the quantity to ours. Price gets assimulated to our prices
		books[findBook(bk.ISBN)].quantity += bk.quantity;
	else
		// If not, add it to the end of our book list while increasing neccessary values...
		books[numBooks++] = bk; // <--invokes our awesome assignment oppeartor

	books[numBooks++] = bk;
	return true;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  stuff
//Post: Pretty much the same as sellBook, except it can remove multiple books at
//		one and returns true if successful and false if there was an error
bool BookList::removeBook(unsigned long ISBN, int quantity)
{
	int idx = findBook(ISBN);
	if (idx < 0)
		return false;
	if (books[idx].quantity < quantity)
		return false;

	books[idx].quantity -= quantity;
	return 1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  stuff
//Post: Pretty much the same as sellBook, except it can remove multiple books at
//		one and returns true if successful and false if there was an error
void BookList::modifyBook(int idx, Book replacement)
{
	books[idx] = replacement;
}

void BookList::printByMethod(int verbosity, SORT_METHOD sm)
{
	for (int idx = 0; idx < numBooks; idx++)
	{
		std::cout << "\nBook " << (idx > 9 ? "" : " ") << idx << " : ";
		if (sm == SORT_METHOD::AGE)
		{
			std::cout << std::left << std::setfill('.');
			std::cout << std::setw(50) << books[idx].title << "Age : " << (books[idx].addedOn.month < 10 ? " " : "") << books[idx].addedOn.month
				<< '/' << (books[idx].addedOn.day < 10 ? " " : "") << books[idx].addedOn.day << '/' << books[idx].addedOn.year;
		}
		if (sm == SORT_METHOD::QUANTITY)
		{
			std::cout << std::left << std::setfill('.');
			std::cout << std::setw(50) << books[idx].title << "Quantity : "
				<< books[idx].quantity;
		}
		if (sm == SORT_METHOD::SIMPLE)
		{
			std::cout << std::left << std::setfill('.');
			std::cout << std::setw(45) << books[idx].title << "by " << books[idx].author << '.';
		}
		if (verbosity > 1)
			std::cout << std::endl << "Author : " << books[idx].author << "... Publisher : " << books[idx].publisher;
		if (verbosity > 0)
			std::cout << std::endl << "ISBN : " << books[idx].ISBN << std::endl;
	}
}

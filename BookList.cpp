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
		Book bk = { 0, 0, 0, "err", "err", "err", {0,0,0},0 };
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
	books[numBooks++] = bk;
	return 1;
}

/////////////////////////////////////////////////////////////////////////
//Pre:  stuff
//Post: Pretty much the same as sellBook, except it can remove multiple books at
//		one and returns true if successful and false if there was an error
bool    BookList::removeBook(unsigned long ISBN, int quantity)
{
	int idx = findBook(ISBN);
	if (idx < 0)
		return false;
	if (books[idx].quantity < 1 + quantity)
		return false;

	books[idx].quantity -= quantity;
	return 1;
}

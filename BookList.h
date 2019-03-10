#pragma once
#include <fstream>
#include <string>
#include "Book.h"

#define MAX_BOOKS 2048

class BookList
{
public:
	BookList();
	~BookList();
public:
	Book*			getBooks();
	Book			getBook(int index);
	int				getNumBooks();

	// Some lists will need to update dif vals upon removal, so use their version
	virtual bool    removeBook(unsigned long ISBN, int quantity);
	bool			addBook(const Book &bk);

	int				findBook(unsigned long ISBN);						// Returns the index in our array of the found entry or -1 if not found
	int				findBook(std::string title);

	double			getTotalCost();
	void			modifyBook(unsigned long ISBN, Book replacement);	// un-needed?

protected:
	Book*			books;
	int				numBooks;				// number of book objects (entries in DB)

};

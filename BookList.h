#pragma once
#include <fstream>
#include <string>
#include "Book.h"

#define MAX_BOOKS 2048

class BookList
{
public:
	BookList();
	virtual ~BookList();
public:
	Book*			getBooks();
	Book			getBook(int index);
	int				getNumBooks();

	// Some lists will need to update dif vals upon removal, so use their version
	virtual bool    removeBook(unsigned long ISBN, int quantity);
	bool			addBook(const Book &bk);

	int				findBook(unsigned long ISBN);						// Returns the index in our array of the found entry or -1 if not found
	int				findBook(std::string title);		// Note there can only be one book per title (other editions etc. have varying titles)
	BookList*		findBookByAuthor(std::string author);
	BookList*		findBookByPublisher(std::string publisher);
	BookList*		findBookByDate(Date myDate);
	BookList*		findBookByQuantity(int amt); // Not sure when anyone would ever need this (maybe to find low stocks) but hey...
	
	template<typename T>
	BookList*		findBookByRetailPrice(T price);

	template<typename T>
	BookList*		findBookByWholesalePrice(T price);

	double			getTotalCost();
	void			modifyBook(int idx, Book replacement);
	virtual void	printByMethod(int verbosity, SORT_METHOD sm);

protected:
	Book*			books;
	int				numBooks;				// number of book objects (entries in DB)

};

template<typename T>
BookList* BookList::findBookByRetailPrice(T price)
{
	BookList *t_list = new BookList();
	for (int idx = 0; idx < numBooks; idx++)
		if (books[idx].retailCost == price)
			t_list->addBook(books[idx]);
	return t_list;
}

template<typename T>
BookList* BookList::findBookByWholesalePrice(T price)
{
	BookList *t_list = new BookList();
	for (int idx = 0; idx < numBooks; idx++)
		if (books[idx].wholesaleCost == price)
			t_list->addBook(books[idx]);
	return t_list;
}

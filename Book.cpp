#include "Book.h"

Book::Book()
{
	title = "err";
	ISBN = 0;
	author = "err";
	wholesaleCost = 0.00;
	retailCost = 0.00;
	publisher = "err";
	addedOn.day = 0;
	addedOn.month = 0;
	addedOn.year = 0;
	quantity = 0;
}

std::ostream& operator <<(std::ostream &out, const Book &bk)
{
	std::cout << "\n  Title: " << bk.title << "\n  Author: " << bk.author << "\n  Cost: " << bk.retailCost
		<< "\n  Wholesale: " << bk.wholesaleCost << "\n  Publisher: " << bk.publisher
		<< "\n  ISBN: " << bk.ISBN << "\n  Quantity: " << bk.quantity;
	return out;
}


void Book::operator=(const Book &right) {
	this->title = right.title;
	this->ISBN = right.ISBN;
	this->author = right.author;
	this->wholesaleCost = right.wholesaleCost;
	this->retailCost = right.retailCost;
	this->publisher = right.publisher;
	this->addedOn.day = right.addedOn.day;
	this->addedOn.month = right.addedOn.month;
	this->addedOn.year = right.addedOn.year;
	this->quantity = right.quantity;
};

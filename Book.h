#pragma once
#include <iostream>
#include <string>

struct Date
{
	int day, month, year;
};

class Book
{
public:
	
public:
	void operator=(const Book &right);
	unsigned long ISBN;
	double wholesaleCost, retailCost;
	std::string title, author, publisher;
	Date addedOn;
	int quantity = 1;
	friend std::ostream& operator<<(std::ostream &out, const Book &bk);
};

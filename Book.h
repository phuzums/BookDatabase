#pragma once
#include <iostream>
#include <string>

struct Date
{
	int day, month, year;
};

enum SORT_METHOD
{
	QUANTITY = 0, COST, AGE, WHOLESALE
};

class Book
{
public:
	Book();
public:
	void operator=(const Book &right);
	unsigned long ISBN;
	double wholesaleCost, retailCost;
	std::string title, author, publisher;
	Date addedOn;
	int quantity;
	friend std::ostream& operator<<(std::ostream &out, const Book &bk);
};

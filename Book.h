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
	//implement later
	//Book();
	//Book(unsigned long isbn, std::string title, std::string author, std::string publisher);

public:
	unsigned long ISBN;
	double wholesaleCost, retailCost;
	std::string title, author, publisher;
	Date addedOn;
	int quantity = 1;
	friend std::ostream& operator<<(std::ostream &out, const Book &bk);
};

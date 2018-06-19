#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

using namespace std;

class Customer
{
private:
	string surname;
	string phoneNum;
public:
	Customer();
	Customer(string name, string phone);
	string getName() const;
	void setName(string newName);
	string getPhoneNum() const;
	void setPhoneNum(string newNumber);
	void displayCustomerDetails() const;
};
#endif
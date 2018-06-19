#include "Customer.h"

// Constructors
Customer::Customer() :
	surname("No Name"),
	phoneNum("No Number")
{}

Customer::Customer(string name, string phone) :
	surname(name),
	phoneNum(phone)
{}


// Gets and sets
string Customer::getName() const
{
	return surname;
}


void Customer::setName(string newName)
{
	surname = newName;
}


string Customer::getPhoneNum() const
{
	return phoneNum;
}


void Customer::setPhoneNum(string newNumber)
{
	phoneNum = newNumber;
}


// Display
void Customer::displayCustomerDetails() const
{
	cout << "Name: " << surname << endl;
	cout << "Phone Number: " << phoneNum << endl;
}
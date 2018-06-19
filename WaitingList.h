#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "Customer.h"

const int MAXQUEUESIZE = 10;

class WaitingList
{
private:
	Customer *queue;
	int queueSize;
	int front;
	int back;
	string eventName;
	int numOnList;
public:
	// Custructors and destructors
	WaitingList(int size = 10);
	WaitingList(string name, int size = MAXQUEUESIZE);
	~WaitingList();
	WaitingList(const WaitingList& original);
	WaitingList& operator= (const WaitingList& original);

	// Queue management functions
	bool isEmpty() const;
	bool isFull() const;
	bool remove(Customer& frontCustomer);
	bool add(const Customer& newCustomer);
	int getPosition(string customerName) const;

	// Gets, sets and display functions
	string getEventName() const;
	void setEventName(string newName);
	int getNumOnList() const;
	void setNumOnList(int newNumOnList);
	void displayWaitingList() const;	
};
#endif
#include "WaitingList.h"


// Constructors
WaitingList::WaitingList(string name, int size) :
	eventName(name),
	numOnList(0),
	queueSize(size),
	queue(new Customer[(size + 1)]),
	front(0),
	back(0)
{}


WaitingList::WaitingList(int size) :
	eventName("Empty Event Slot"),
	numOnList(0),
	queueSize(size),
	queue(new Customer[(size + 1)]),
	front(0),
	back(0)
{}


// Destructor
WaitingList::~WaitingList()
{
	delete[] queue;
}


// Copy constructors for assignment and intialisation
WaitingList::WaitingList(const WaitingList& original)
{
	if (this != &original)
	{
		eventName = original.eventName;
		numOnList = original.numOnList;
		front = original.front;
		back = original.back;
		queueSize = original.queueSize;
		queue = new Customer[(queueSize + 1)];
	}
}


WaitingList& WaitingList::operator=(const WaitingList& original)
{
	if (this != &original)
	{
		delete[] queue;
		eventName = original.eventName;
		numOnList = original.numOnList;
		front = original.front;
		back = original.back;
		queueSize = original.queueSize;
		queue = new Customer[(queueSize + 1)];
	}

	return (*this);
}


// Queue management functions
bool WaitingList::isEmpty() const
{
	return (front == back)
		? true : false;
}


bool WaitingList::isFull() const
{
	return ((back + 1) % (queueSize + 1) == front)
		? true : false;
}


bool WaitingList::remove(Customer& frontCustomer)
{
	if (isEmpty())
		return false;
	else
	{
		frontCustomer = queue[front];
		front = (front + 1) % (queueSize + 1);
		numOnList--;
		return true;
	}
}


bool WaitingList::add(const Customer& newCustomer)
{
	if (isFull())
		return false;
	else
	{
		queue[back] = newCustomer;
		back = (back + 1) % (queueSize + 1);
		numOnList++;
		return true;
	}
}


// Gets and sets
string WaitingList::getEventName() const
{
	return eventName;
}


void WaitingList::setEventName(string newName)
{
	eventName = newName;
}


int WaitingList::getNumOnList() const
{
	return numOnList;
}


void WaitingList::setNumOnList(int newNumOnList)
{
	numOnList = newNumOnList;
}


// Display function
void WaitingList::displayWaitingList() const
{
	int current = front;
	int position = 1;

	cout << endl << "Event: " << eventName << endl << endl; 
	
	while (current != back)
	{
		cout << "Position " << position << endl;
		queue[current].displayCustomerDetails(); 
		current = (current + 1) % (queueSize + 1);
		position++;
	}
}


int WaitingList::getPosition(string name) const
{
	int position = 1;
	int current = front;

	while (queue[current].getName() != name && current != back)
	{
		current = (current + 1) % (queueSize + 1);
		position++;
	}

	// Need to include check we're not at "back" as this is one step out of bounds and shouldn't be "counted" as a valid position
	return (queue[current].getName() == name && current != back)
		? position : -1;
}
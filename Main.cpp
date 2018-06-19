#include "WaitingList.h"


// Function declarations
const int NUMOFEVENTS = 10;
void displayWelcome();
void displayListMenu();
void displayEventsMenu(WaitingList events[NUMOFEVENTS]);
Customer getCustomerDetails();
string getName();
void addCustomer(int eventChoice, WaitingList events[NUMOFEVENTS]);
void removeCustomer(int eventChoice, WaitingList events[NUMOFEVENTS]);
void checkPosition(int eventChoice, WaitingList events[NUMOFEVENTS]);
void resetQueue(int eventChoice, WaitingList(&events)[NUMOFEVENTS]);
void setExampleData(WaitingList events[NUMOFEVENTS]);


int main()
{
	int eventChoice, menuChoice = 1;
	WaitingList events[NUMOFEVENTS] = { WaitingList() };

	// Populate some events waiting lists with some example data for ease of testing
	setExampleData(events);
	displayWelcome();


	// Display the events list and get the user's (validated) choice of list
	displayEventsMenu(events);
	cin >> eventChoice;
	while (cin.fail() || eventChoice < 0 || eventChoice > NUMOFEVENTS)  
	{
		cout << endl << "That's not a valid choice, please enter the number of a waiting list listed, or 0 to exit: " << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> eventChoice;
	}

	if (eventChoice != 0)
	{// Waiting list menu loop
		while (menuChoice != 0 || eventChoice != 0)
		{
			// Display the waiting list menu and get the user's (validated) choice
			displayListMenu();
			cin >> menuChoice;
			while (cin.fail() || menuChoice < 0 || menuChoice > 4)
			{
				cout << endl << "That's not a valid choice, please enter 1-4, or 0 to exit: " << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> menuChoice;
			}

			switch (menuChoice)
			{
			case 1:
				// Add a customer to the end of the queue
				addCustomer(eventChoice - 1, events);
				break;

			case 2:
				// Delete the lucky customer that got tickets from the front of the queue
				removeCustomer(eventChoice - 1, events);
				break;

			case 3:
				// Check the position of a customer in the queue
				checkPosition(eventChoice - 1, events);
				break;

			case 4:
				// Clear a waiting list and change the details
				resetQueue(eventChoice - 1, events);
				events[eventChoice - 1].displayWaitingList();
				break;

			case 0:
				// If the user wants to go back, display the event menu and get their new waiting list selection.
				displayEventsMenu(events);
				cin >> eventChoice;
				while (cin.fail() || eventChoice < 0 || eventChoice > NUMOFEVENTS)
				{
					cout << endl << "That's not a valid choice, please enter the number of a waiting list listed, or 0 to exit: " << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> eventChoice;
				}
				break;

			default:
				// If not an expected entry, get a new choice number
				cout << "That's not a valid choice, please enter 1-4, or 0 to exit: " << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> menuChoice;
				break;
			} //endswitch

		} // End waiting list menu
	}

	return 0;
}


// Main, menu option functions

// Try to add a customer to the back of a queue and display a message to the user depending on the result
void addCustomer(int eventChoice, WaitingList events[NUMOFEVENTS])
{
	if (events[eventChoice].isFull())
		cout << endl << "Sorry, there are no spaces left on this waiting list. Please try again later." << endl;
	else if (events[eventChoice].add(getCustomerDetails()))
		cout << endl << "Customer successfully added to the back of the queue." << endl;
	else
		cout << "Sorry, the customer could not be added to the queue." << endl;
}



// Try to remove a customer from the front of a queue and display a suitable message to the user depending on the result.
void removeCustomer(int eventChoice, WaitingList events[NUMOFEVENTS])
{
	Customer customer;
	
	if (events[eventChoice].isEmpty())
		cout << endl << "Sorry, it looks like the list was already empty and no one is waiting on tickets." << endl;
	else if (events[eventChoice].remove(customer))
	{
		cout << endl << "Customer successfully removed to receive tickets: " << endl;
		customer.displayCustomerDetails();
	}
	else
		cout << "Sorry, the customer could not be removed from the queue." << endl;
}



// Check the position of a user based on their name in the queue; -1 is indication that no name matching the customer's was found in the queue
void checkPosition(int eventChoice, WaitingList events[NUMOFEVENTS])
{
	int position = events[eventChoice].getPosition(getName());

	if (position == -1)
		cout << endl << "No customer with that name was found on the waiting list. Select 3 from the menu to try again." << endl;
	else
		cout << endl << "The customer is currently at position  " << position << "  in the list." << endl;
}



// Get the new event name from the user, delete the old waiting list, and replace it with a new list with the new event name
void resetQueue(int eventChoice, WaitingList (&events)[NUMOFEVENTS])
{
	string name;	
	cout << endl << "Please enter the name of the new event: " << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, name);

	events[eventChoice] = WaitingList(name);

	cout << "The list was successfully reset and replaced by a new waiting list for the " << name << " event." << endl;
}


// User Input functions

// Get the user to input the customer's details to add to a waiting list
Customer getCustomerDetails()
{
	string surname;
	string phoneNo;

	cout << "Please enter the customer's details to add them to the waiting list:" << endl;
	cout << "Surname: ";
	cin >> surname;

	cout << "Phone Number: ";
	cin >> phoneNo;

	Customer customerDetails = Customer(surname, phoneNo);
	return customerDetails;
}



// Get the name of the customer from the user to search in their queue for their position
string getName()
{
	string name;
	cout << endl << "Please enter the customer's surname: ";
	cin >> name;

	return name;
}


// Display functions

// Display the program welcome message
void displayWelcome()
{
	cout << "***************************************************************************************" << endl;
	cout << "***                                    Welcome!                                     ***" << endl;
	cout << "***     This program will help manage customer waiting lists for tickets to up      ***" << endl;
	cout << "***                                  to 10 events.                                  ***" << endl;
	cout << "***                                                                                 ***" << endl;
	cout << "***************************************************************************************" << endl << endl;
}



// Display the main menu
void displayListMenu()
{
	cout << endl << endl << "---------------------------------- MAIN MENU ----------------------------------" << endl;
	cout << "  1. Add a customer to the waiting list" << endl;
	cout << "  2. Remove a customer from the front of the queue" << endl;
	cout << "  3. Check customer's position in the list" << endl;
	cout << "  4. Reset and begin a new event waiting list" << endl << endl;
	cout << "  Please enter the number of your choice or 0 to go back: ";
}



// Display the list of events and the number of people on the waiting list for each
void displayEventsMenu(WaitingList events[NUMOFEVENTS])
{
	for (int count = 0; count < NUMOFEVENTS; count++)
	{
		cout << count + 1 << ". " << events[count].getEventName() << endl;
		cout << "Waiting List: " << events[count].getNumOnList() << " people" << endl;
	}
	cout << endl << "Enter the number of your choice or 0 to exit: ";
}


// Test Data Function

// Assign some example data to the waiting lists to save time populating it for testing.
void setExampleData(WaitingList events[NUMOFEVENTS])
{
	events[0].setEventName("Super Junior K.R.Y. - Phonograph Tour");
	events[1].setEventName("Harry Potter and the Cursed Child");
	events[2].setEventName("Ed Sheeran in Concert");
	events[8].setEventName("The Godess Is Watching - Musical");

	events[0].add(Customer("Alton", "11111111111"));
	events[0].add(Customer("Brown", "22222222222"));
	events[0].add(Customer("Calendar", "33333333333"));
	events[0].add(Customer("Doe", "44444444444"));
	events[0].add(Customer("Ewens", "55555555555"));
	events[0].add(Customer("Ferguson", "66666666666"));
	events[0].add(Customer("Grey", "77777777777"));
	events[0].add(Customer("Heron", "88888888888"));
	events[0].add(Customer("Innes", "99999999999"));
	events[0].add(Customer("Jung", "00000000000"));

	events[8].add(Customer("Morris", "123456789098"));
	events[8].add(Customer("Stewart", "123454353538"));
	events[8].add(Customer("Zerteuche", "123432229098"));
}
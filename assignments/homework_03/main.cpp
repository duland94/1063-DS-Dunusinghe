// Name - Dulan Dunusnghe
// Author - Dr.Terry Griffin
// Date - 10/15/2019 
// Description - Overloading and stacks.
//This is my homework three and i have Edited
//the ListStack.h file, and have added an overloaded constructor for 
//the file so that it accepts the animal name, weight, and it's scary score.

#include "ListStack.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name;
	double weight;
	double scary;
	ifstream fin("animals.txt");
	Animal *a;
	ListStack LS;

	// While still animals in the file
	while (!fin.eof())
	{
		fin >> name >> weight >> scary;
		a = new Animal(name, weight, scary);
		LS.Push(a);
	}

	cout << "Original Stack \n";
	LS.Print();  // Print the stack

	cout << endl;

	LS.Pop();

	LS.Pop();

	cout << "\nNew Stack \n";

	LS.Print();

	return 0;
}
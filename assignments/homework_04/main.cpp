//Name - Dulan Dunusinghe
//Author - Terry Griffin
//Date - 10/15/2019
//Description - This is my homework4 of CMPS data Structure class.
//it's overloading and queues.i have edited Edit the ListQueue.hpp file,
//and alter the queue so that it accepts Animals 


#include <iostream>
#include <fstream>
#include <string>
#include "ListQueue.hpp"

using namespace std;


int main() {
	ListQueue LQ;                 // Queue instance 
	ifstream fin;

	// New variable for reading in file
	string name;
	double weight;
	double scary;
	Animal *a;

	fin.open("animals.txt");

	// Read in the animals
	while (!fin.eof())
	{
		fin >> name >> weight >> scary;
		a = new Animal(name, weight, scary);

		LQ.Push(a);
	}

	cout << endl;                     // ummmm 

	LQ.Print();                     // print queue to see where values are


	cout << "\nRemoving Items:" << endl;
	for (int i = 0; i < 3; i++) {           // remove 3 items
		if (!LQ.Empty()) {
			Animal * t = LQ.Pop();
			cout << "Item: " << t->name << " "
				<< t->weight << " " << t->scary
				<< endl;    // print out items
		}
		else {
			cout << "Empty queue!" << endl;
		}

	}

	cout << "\nQueue after removal: " << endl;
	LQ.Print();                     // print again to show front removal
	LQ.PrintPointers();

	Node* f = LQ.GetFront();

	// We added this in class JUST to see what front
	// pointed to.

	cout << "\nFront Item: " << endl;
	cout << f->data->name << " " << f->data->weight <<
		" " << f->data->scary << endl;
}
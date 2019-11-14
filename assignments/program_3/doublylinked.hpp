
// Author:           Dulan Dunusinghe
// Assignment:       Program_03
// Date:             14 November 2019
// Title:            Program 3 - Arbitrary Precision Math
// Semester:         Fall 2019
// Course:           CMPS 1063 
// 
// Files:            apm.cpp
//                   doublylinked.hpp
//                   input_data.txt 
//                   output.num
// Description:    this program will use doubly linked lists
//      to add, subtract and multiply arbitrarily long numbers,
//      then store them in a file.

#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* Next;
	Node* Prev;

	Node(int d) {
		data = d;
		Next = NULL;
		Prev = NULL;
	}
};

class DoubleyLinked {
private:
	Node *Head;
	Node *Middle;
	Node *Tail;

	int MiddleLoc;
	int size;
public:

	DoubleyLinked();
	void FrontSert(int);
	void EndSert(int);
	void Print();
	void Delete();
	int Length();
	void add(DoubleyLinked*, DoubleyLinked*);
	void mul(DoubleyLinked*, DoubleyLinked*);
	void sub(DoubleyLinked*, DoubleyLinked*);
	void PrintResult(ofstream &);
};


DoubleyLinked::DoubleyLinked() {
	Head = Middle = Tail = NULL;
	size = 0;
}

void DoubleyLinked::FrontSert(int value) {
	Node* temp = new Node(value);

	if (Head == NULL)
		Head = Tail = temp;
	else {
		Head->Prev = temp;
		temp->Next = Head;
		Head = temp;
	}
	size++;
}

void DoubleyLinked::EndSert(int value) {
	Node* temp = new Node(value);

	if (Tail == NULL)
		Head = Tail = temp;
	else {
		Tail->Next = temp;
		temp->Prev = Tail;
		Tail = temp;
	}
	size++;
}

void DoubleyLinked::Print() {
	Node* Temp = Head;

	while (Temp) {
		cout << Temp->data;
		if (Temp->Next) {
			cout << "->";
		}
		Temp = Temp->Next;
	}
	cout << endl;
}

int DoubleyLinked::Length() {
	return size;
}


//Add
// Description:
 //     Adds two doubly linked lists together.

void DoubleyLinked::add(DoubleyLinked* a, DoubleyLinked* b) {
	int c = 0, s;
	DoubleyLinked* a1 = new DoubleyLinked(*a);
	DoubleyLinked* b1 = new DoubleyLinked(*b);

	// default copy constructor 
	// Copy Constructor that copies data in Node 
	this->Head = NULL;
	this->Tail = NULL;
	this->size = 0;

	while (a1->Tail != NULL || b1->Tail != NULL) {
		if (a1->Tail != NULL && b1->Tail != NULL) {
			s = ((a1->Tail->data) + (b1->Tail->data) + c) % 10;
			c = ((a1->Tail->data) + (b1->Tail->data) + c) / 10;
			a1->Tail = a1->Tail->Prev;
			b1->Tail = b1->Tail->Prev;
		}
		else if (a1->Tail == NULL && b1->Tail != NULL) {
			s = ((b1->Tail->data) + c) % 10;
			c = ((b1->Tail->data) + c) / 10;
			b1->Tail = b1->Tail->Prev;
		}
		else if (a1->Tail != NULL && b1->Tail == NULL) {
			s = ((a1->Tail->data) + c) % 10;
			c = ((a1->Tail->data) + c) / 10;
			a1->Tail = a1->Tail->Prev;
		}

		// Inserting the sum digit 
		FrontSert(s);
	}

	// Inserting last carry 
	if (c != 0)
		FrontSert(c);
}


// sub
 //
 // Description:
 //      Subtracts one doubly linked list to another.

void DoubleyLinked::sub(DoubleyLinked* a, DoubleyLinked* b) {
	int c = 0, s;
	DoubleyLinked* a1 = new DoubleyLinked(*a);
	DoubleyLinked* b1 = new DoubleyLinked(*b);

	this->Head = NULL;
	this->Tail = NULL;
	this->size = 0;

	while (a1->Tail != NULL || b1->Tail != NULL) {
		if (a1->Tail != NULL && b1->Tail != NULL) {
			if ((a1->Tail->data) + c >= (b1->Tail->data)) {
				s = ((a1->Tail->data) + c - (b1->Tail->data));
				c = 0;
			}
			else {
				s = ((a1->Tail->data) + c + 10 - (b1->Tail->data));
				c = -1;
			}
			a1->Tail = a1->Tail->Prev;
			b1->Tail = b1->Tail->Prev;
		}
		else if (a1->Tail != NULL && b1->Tail == NULL) {
			if (a1->Tail->data >= 1) {
				s = ((a1->Tail->data) + c);
				c = 0;
			}
			else {
				if (c != 0) {
					s = ((a1->Tail->data) + 10 + c);
					c = -1;
				}
				else
					s = a1->Tail->data;
			}
			a1->Tail = a1->Tail->Prev;
		}
		FrontSert(s);
	}
}


// Mul
// Description:
//     Multiplies two doubly linked lists together.


void DoubleyLinked::mul(DoubleyLinked* a, DoubleyLinked* b) {
	int Count = 0, i;
	DoubleyLinked* tpro = new DoubleyLinked();
	while (b->Tail != NULL) {
		int c = 0, s = 0;
		DoubleyLinked* temp = new DoubleyLinked(*a);
		DoubleyLinked* pro = new DoubleyLinked();
		while (temp->Tail != NULL) {
			s = ((temp->Tail->data) * (b->Tail->data) + c) % 10;
			c = ((temp->Tail->data) * (b->Tail->data) + c) / 10;
			pro->FrontSert(s);
			temp->Tail = temp->Tail->Prev;
		}
		if (c != 0)
			pro->FrontSert(c);

		for (i = 0; i < Count; i++)
			pro->EndSert(0);

		add(this, pro);
		Count++;
		b->Tail = b->Tail->Prev;
		pro->Head = pro->Tail = NULL;
		pro->size = 0;
	}
}


// PrintResult

// Description:
 //      Prints out the large number from a list

void DoubleyLinked::PrintResult(ofstream &fout) {
	Node* temp = Head;
	while (temp != NULL) {
		fout << temp->data;
		temp = temp->Next;
	}
	fout << endl << endl;
}
// Author:          Dulan Dunusinghe
// Assignment:      Homework 5
// Date:            11 November 2019
// Title:           Homework 5 - Ordering a list of strings
// Semester:        Spring 2018
// Course:          CMPS 1063 
// 
// Files:           homework5.cpp 

// Description:     I have fixed the ordering function we made in class

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node
{
	string word;
	Node *Next;
	// node constructor    
	Node(string w)
	{
		word = w;
		Next = NULL;
	}
};

class Dictionary
{
private:
	Node *Start;
	//  make all letters for word(input) lowercase 

	string LowerCase(string input)
	{
		for (int i = 0; i < input.length(); i++)
		{
			if ((int)input[i] < 96)
			{
				input[i] += 32;
			}
		}
		return input;
	}

public:
	// basic dictionary constructor
	Dictionary()
	{
		Start = NULL;
	}

	// adds an animal to the list
	void Add(string word)
	{

		word = LowerCase(word);
		// create new memory
		Node *temp = new Node(word);

		// if list is empty hook in new Node
		if (Start == NULL)
		{
			Start = temp;
		}
		else
		{
			// get ready to walk the list
			Node *traverse = Start;
			while (traverse->Next != NULL)
			{
			// walks the list
				traverse = traverse->Next;
			}
			// now at proper place to link in new memory
			traverse->Next = temp;
		}
	}
	// remove a given animal from the list   
	string Remove(string key)
	{
		string temp = "";

		if (!Start)
		{
			return "";
		}
		else
		{
			Node *cptr = Start;
			Node *prev = Start;
			while (cptr && cptr->word != key)
			{
				prev = cptr;
				cptr = cptr->Next;
			}
			// if cptr then we found the word
			if (cptr)
			{
				temp = cptr->word;
				prev->Next = cptr->Next;
				delete cptr;
			}
			else
			{
			// no word, return empty
				temp = "";
			}
			return temp;
		}

		return temp;
	}
	// fix the list to be in ascending order 
	void ReOrder() {
		// pointers for new list
		Node *NewList = NULL;
		Node *Tail = NULL;

		int i = 0;

		while (Start != NULL) {

			// helping pointers to manipulate lists
			Node *Ptr = Start;
			Node *Min = Start;
			Node *Prev = Start;
			Node *MinPrev = Start;

			// find one minimum word in old list
			while (Ptr != NULL)
			{
				if (Ptr->word < Min->word)
				{
					MinPrev = Prev;
					Min = Ptr;
				}
				Prev = Ptr;
				Ptr = Ptr->Next;
			}
			//end finding one word in old list

			// add one word to new list

			if (!NewList)
			{
				NewList = Min;
			}
			else
			{
				Tail->Next = Min;
			}

			Tail = Min;
			if (Min == Start)
			{
				Start = Start->Next;
			}
			else
			{
				MinPrev->Next = Min->Next;
			}

			Min->Next = NULL;

			// adding one word to new list

			Node *Tempt = NewList;

			while (Tempt)
			{
				cout << Tempt->word << " ";
				Tempt = Tempt->Next;
			}
			cout << endl;

		}
		Start = NewList;
	}
	// print the list of animals with arrows    
	void Print()
	{
		Node *temp = Start;
		while (temp)
		{
			cout << temp->word;
			if (temp->Next)
			{
				cout << "->";
			}
			temp = temp->Next;
		}
		cout << endl;
	}
};
/////////////////////////////////////////////////////

int main()
{
	Dictionary W;
	ifstream fin("dictionary.txt");
	string word;

	// while(fin>>word){
	//   W.Add(word);
	// }

	W.Add("Ant");
	W.Add("Dog");
	W.Add("Aaron");
	W.Add("Aardvark");
	W.Add("Cow");
	W.Add("Rabbit");
	W.Add("Zebra");
	W.Add("Hare");
	W.Add("Aardvark");
	W.Add("Yeti");
	W.Add("Crab");
	W.Add("Tapir");

	W.Print();
	cout << endl;

	W.ReOrder();

	W.Print();
}
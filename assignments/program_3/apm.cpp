// Author:           Dulan Dunusinghe
// Assignment:       Program_03
// Date:             14 November 2019
// Title:            Program 3 - Arbitrary Precision Math
// Semester:         Fall 2019
// Course:           CMPS 1063 
// 
// Files:            apm.cpp, 
//                   doublylinked.hpp, 
//                   input_data.txt 
//                   output.num
// Description:    this program will use doubly linked lists
//      to add, subtract and multiply arbitrarily long numbers,
//      then store them in a file.
//

#include <iostream>
#include <fstream>
#include "doublylinked.hpp"

using namespace std;

int main() {
	ifstream fin;
	fin.open("input_data.txt");
	ofstream fmout;
	fmout.open("output.num");
	fmout << "Dulan Dunusinghe\n" << "Program 3\n"
		<< "Arbitrary Precision Math\n" << endl;

	DoubleyLinked* a = new DoubleyLinked();
	DoubleyLinked* s = new DoubleyLinked();
	DoubleyLinked* p = new DoubleyLinked();
	char op;
	string s1, s2;

	while (fin >> op >> s1 >> s2) {
		DoubleyLinked* m = new DoubleyLinked();
		DoubleyLinked* n = new DoubleyLinked();
		for (int i = 0; i < s1.length(); i++) {
			m->FrontSert(s1.at(i) - '0');
		}
		for (int i = 0; i < s2.length(); i++) {
			n->EndSert(s2.at(i) - '0');
		}
		switch (op) {
		case '+': a->add(m, n);
			fmout << "Operation 1: Addition\n Answer: \n";
			a->PrintResult(fmout); break;
		case '-': s->sub(m, n);
			fmout << "Operation 2: Subtraction\n Answer: \n";
			s->PrintResult(fmout); break;
		case '*': p->mul(m, n);
			fmout << "Operation 3: Multiplication\n Answer: \n";
			p->PrintResult(fmout); break;
		}
		delete m;
		delete n;
	}
	fin.close();
	fmout.close();

	return 0;
}

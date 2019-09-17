// Dulan Dunusinghe
// CMPS 1063 - 102
// Prof - Terry Griffin

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Employee {
	string emp_id;
	string first_name;
	string last_name;
	string gender;
	string email;
	double hourly_pay;
	Employee* Next;

	Employee()
	{
		emp_id = "";
		first_name = "";
		last_name = "";
		gender = "";
		email = "";
		hourly_pay = 0.0;
	}

	Employee(string id, string first, string last, string sex, string mail, double pay)
	{
		emp_id = id;
		first_name = first;
		last_name = last;
		gender = sex;
		email = mail;
		hourly_pay = pay;
		Next = nullptr;
	}
};

class LinkedList {
private:
	Employee * Head;

public:
	LinkedList()
	{
		Head = nullptr;
	}

	void push(string id, string first, string last, string sex, string mail, double pay) {
		Employee * Temp = new Employee(id, first, last, sex, mail, pay);

		if (Head == nullptr)
		{
			Head = Temp;
		}
		else
		{
			Temp->Next = Head;
			Head = Temp;
		}

	}

	void pop()
	{
		Employee * Temp;

		if (Head == NULL)
		{
			cout << "Empty List!";
		}
		else
		{
			Temp = Head->Next;
			delete Head;
			Head = Temp;
		}
	}

	void print()
	{
		Employee * Temp = Head;

		while (Temp != nullptr)
		{
			cout << Temp->emp_id << ", " << Temp->first_name << ", "
				<< Temp->last_name << ", " << Temp->email << ", "
				<< Temp->gender << ", " << Temp->hourly_pay;

			if (Temp->Next)
			{
				cout << " -> ";
			}
			Temp = Temp->Next;
		}

		cout << endl;
	}

	// Prints employee ids to an outfile. The number of 
	// employees is specified by user in main
	void printids(int x, ofstream & out)
	{
		Employee *Temp = Head;

		for (int i = 0; i < x; i++)
		{
			out << Temp->emp_id << "\n";
			Temp = Temp->Next;
		}
	}

	bool find(string mail)
	{
		Employee * Temp = Head;
		string email;

		// If linked list is empty
		if (!Head)
			return false;

		// Make sure value is not in first node
		email = Head->email;
		if (substringMatch(email, mail))
		{
			return true;
		}


		while (Temp->Next)
		{
			if (substringMatch(email, mail))
			{
				return true;
			}

			Temp = Temp->Next;
			email = Temp->email;
		}

		// Check last node
		email = Head->email;
		if (substringMatch(email, mail))
		{
			return true;
		}

		return false;
	}


	void Delete(string mail)
	{
		Employee *nodePtr = Head;
		Employee *previous = Head;
		string email = Head->email;

		// If list is empty do nothing
		if (!Head)
		{
			return;
		}

		// If first node should be deleted
		if (substringMatch(email, mail))
		{
			nodePtr = Head;
			Head = Head->Next;
			delete nodePtr;
		}
		else
		{
			nodePtr = Head;
			email = Head->email;

			// Move through list until node is found
			while (nodePtr != nullptr && !substringMatch(email, mail))
			{
				previous = nodePtr;
				nodePtr = nodePtr->Next;
				email = nodePtr->email;
			}

			// If value is in list but not at end
			if (nodePtr->Next)
			{
				previous->Next = nodePtr->Next;
				delete nodePtr;
			}

			// If value is at end of list
			else if (nodePtr->Next == nullptr)
			{
				delete nodePtr;
				previous->Next = nullptr;
			}
		}
	}

	// Checks if what the user input is a substring of
	// the actual email desired
	bool substringMatch(string employeemail, string mail)
	{
		return (employeemail.find(mail) != std::string::npos);
	}

	// Writes to an output file the results of searching for an email
	// will also work for substrings.
	void emailsearchresults(string mail, ofstream &out)
	{
		Employee * Temp = Head;
		string email;

		// If linked list is empty
		if (!Head)
			out << "empty\n";

		email = Head->email;
		while (Temp->Next)
		{
			if (substringMatch(email, mail))
			{
				out << "Found\n";
			}
			
			Temp = Temp->Next;
			email = Temp->email;

		}

		// Get last node evaluated
		email = Temp->email;
		if (substringMatch(email, mail))
		{
			out << "Found\n";
		}
		else
			out << "Not Found\n";
	}
};


int main()
{
	int choice = 0;
	string useremail;
	LinkedList EmpList;

	string empid;
	string first;
	string last;
	string email;
	string gender;
	double pay;

	string line;
	string *tokens;
	ifstream fin;
	ofstream outfile;
	fin.open("employees.dat");
	outfile.open("resultsout.txt");
	



	while (!fin.eof())
	{
		fin >> empid >> first >> last >> email >> gender >> pay;

		EmpList.push(empid, first, last, email, gender, pay);
		cout << empid << " " << first << " " << " " <<last << " " << email << " "<< gender << " " << pay << endl;
	}
	
	EmpList.Delete("petkens");
	EmpList.print();

	outfile << "First 30 Employee Ids:\n";
	EmpList.printids(30, outfile);

	outfile << "\nResults searching for salon:\n";
	EmpList.emailsearchresults("salon", outfile);

	system("pause");
	return 0;
}
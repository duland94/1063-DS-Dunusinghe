///////////////////////////////////////////////////////////////////////////////
//
// Author:           DULAN DUNUSINGHE
// Assignment:       Program_04
// Date:             25 November 2019
// Title:            Program 4 - Caesar Cipher
// Semester:         Fall 2019
// Course:           CMPS 1063 
// 
// Files:                     
//          encrypted.txt
//          decrypted.txt
//          cipher.cpp
//
// Description:
//       uses a class to decrypt/encrypt an encrypted/decrypted message 
//      
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin("encrypted.txt");
ofstream fout("decrypted.txt");

 // CaesarCipher class
 
 // Description:
 //      class that contains functions and variables to
 //      encrypt/decrypt the strings
 
 // variables:
 //    string eline : Encrypted string read from file/calculated
 //    string dline : decrypted string read from file/calculated
 //    int shift : value read from file that is used to encrypt/decrypt
 
 
class CaesarCipher
{
private:

public:
	CaesarCipher();// defalt constructor 
	string eline; //encrypted string
	string dline; //decrypted string

	int shift;
    string Encrypt();   // encrypts a string given a specific shift value
	string Decrypt();   // decrypts a string given a specific shift value
	string UpperCase(); // a method that uppercases a string ( there are built in methods, but we will write our own)
	void SetShift();          // sets the shift amount for your class (default should be 13)
	string ReadCipherText();  // reads an encrypted file into a string
	void WriteCipherText();   // writes an encrypted message to a file
	string ReadPlainText();   // reads a plain text file into a string
	void WritePlainText();    // writes a plain text string to a file
	
};

 // main
 
 // Description:
 //      uses a loop to call methods to read in encrypted text, decrypt it,
 //      and write it to the outfile for the entire file
 
 // Params:
 //      none
 
 // Returns:
 //    0

int main() {
	int count = 0;
	fin >> count;
	fout << "DULAN DUNUSINGHE\n";
	fout << "11/25/19\n";
	fout << "Program 4 Output\n\n";
	for (int i = 0; i < count; i++) {
		CaesarCipher a;
		a.ReadCipherText();
		a.Decrypt();
		a.WritePlainText();
	}
	return 0;
}

 
CaesarCipher::CaesarCipher() {
	eline = ' ';
	dline = ' ';
	shift = 0;
}

 // WritePlainText
 //
 // Description:
 //      writes decrypted text to file "decrypted.txt"
 //
 // Params:
 //          none
 
 // Returns:
 //     None
 
void CaesarCipher::WritePlainText() {
	fout << dline << endl << endl;
}

 // WriteCipherText
 
 // Description:
 //      writes encrypted text to file
 // Params:
 //      none
 
 // Returns:
 //      none
 
void CaesarCipher::WriteCipherText() {
	fout << eline << endl << endl;
}

// UpperCase
 
 // Description:
 //      cycles through plain text variable and subtracts 32
 //      from a character if it is lowercase
 
 // Params:
 //      none
 
 // Returns:
 //     dline, now completely uppercase if it wasn't already
 
string CaesarCipher::UpperCase() {
	for (int i = 0; i < dline.size(); i++) {
		if (dline[i] >= 97 && dline[i] <= 122) {
			dline[i] -= 32;
		}
	}
	return dline;
}

 // SetShift
 
 // Description:
 //      reads shift from file
 
 // Params:
 //      none
 
 //Returns:
 //     none
 
void CaesarCipher::SetShift() {
	fin >> shift;
}

 // ReadCipherText
 
 // Description:
 //      reads an entire line of encrypted text into eline
 
 // Params:
 //    none
 
 // Returns:
 //     eline : encrypted text
 
string CaesarCipher::ReadCipherText() {
	SetShift();
	getline(fin, eline);
	getline(fin, eline);

	return eline;
}

 //ReadPlainText
 
 // Description:
 //     Reads plain text from a hypothetical plain text file
 
 // Params:
 //      none
 
 // Returns:
 //      dline : plain text
 
string CaesarCipher::ReadPlainText() {
	getline(fin, dline);
	getline(fin, dline);

	UpperCase();
	return dline;
}

 // Encrypt
 
 // Description:
 //      Encrypts plain text
 
 // Params:
 //      none
 
 // Returns:
 //      eline : encrypted line
 
string CaesarCipher::Encrypt() {
	int intVal = 0;
	string line = dline;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] >= 65 && line[i] <= 90) {
			intVal = (int)line[i] - 65;  // Turn it into an integer number between 0-25
			intVal += shift;
			intVal = intVal % 26;       // Shift the letter, using mod to wrap back around
			line[i] = intVal + 65;       // Turn integer back into an ascii upper case letter
		}
	}
	eline = line;
	return eline;
}

 // Decrypt
 
 // Description:
 //      decrypts an encrypted string
 
 //Params:
 //     none
 
 // Returns:
 //     dline : decrypted string
 
string CaesarCipher::Decrypt() {
	int intVal = 0;
	string line = eline;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] >= 65 && line[i] <= 90)
		{
			intVal = (int)line[i] - 65; // Turn it into an integer number between 0-25
			intVal -= shift;
			if (intVal < 0) //if negative, add 26 to bring it back up
			{
				intVal += 26;
			}
			intVal = intVal % 26;  // Shift the letter, using mod to wrap back around
			line[i] = intVal + 65; // Turn integer back into an ascii upper case letter
		}
	}
	dline = line;
	return dline;
}
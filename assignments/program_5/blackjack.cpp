///////////////////////////////////////////////////////////////////////////////
//
// Author:           Dulan Dunusinghe
// Assignment:       Program_05
// Date:             11 December 2019
// Description:
//       blackjack.cpp: Main file of blackjack game
//        This program uses TermGame.h to create a visual game of  blackjack with the classes:
//      Card, Deck, Player, Opponent
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include "Termgame.h"

// So we don't have to type Termgame and Termprint every time.
namespace TG = TermGame;
namespace TP = TermPrint;

// For printing to terminal
using namespace std;

/*
This class represents the qualities of a card. Its suit,
face value, and code to print it out are all in this class.
*/

class card {
public:
	card* next;
	int cnum;
	int face;
	int suit;
	//public:

	card() {
		next = NULL;
		cnum = 0;
		face = 0;
		suit = 0;
	}
	card(int num) {
		next = NULL;
		cnum = num;
		face = (num % 13) + 1;
		suit = num / 13.1;
	}

	int getface() {
		return face;
	}
	int getSuit() {
		return suit;
	}

	// Print out the cards onto the screen
	void printCard() {
		string card = "";
		card += "┌────┐\n|";
		card += "    |\n|";
		switch (suit) {
		case 0:
			card += "♥ ";
			break;
		case 1:
			card += "♦ ";
			break;
		case 2:
			card += "♣ ";
			break;
		case 3:
			card += "♠ ";
			break;
		}
		switch (face) {
		case 1:
			card += "A │\n";
			break;
		case 11:
			card += "J │\n";
			break;
		case 12:
			card += "Q │\n";
			break;
		case 13:
			card += "K │\n";
			break;
		case 10:
			card += "10│\n";
			break;
		default:
			card += to_string(face);
			card += " │\n";
			break;
		}
		card += "│    │\n";
		card += "└────┘\n";

		cout << card;
	}
};

// Class for a deck of cards. Holds the position, how many cards are left and other important data.
class deck {
private:
	card* top;
	int decksize;

public:

	deck() {
		top = new card(1);
		card* temp = top;
		for (int i = 2; i < 53; i++) {
			temp->next = new card(i);
			temp = temp->next;
		}
		decksize = 52;
	}

	// This function will shuffle the cards in order to 
	// make the selection of cards random.
	void shuffle() {

		// Create a random number based on the time
		srand(time(NULL));
		int num1;
		int num2;

		card* temp = top;
		card* temp2 = top;


		for (int i = 0; i < 1000; i++) {
			temp = top;
			temp2 = top;
			num1 = rand() % decksize;
			for (int i = 0; i <= num1; i++) {
				temp = temp->next;
			}
			num2 = rand() % decksize;
			for (int i = 1; i <= num2; i++) {
				temp2 = temp2->next;
			}
			swap(temp, temp2);
		}
	}

	// Do a swap
	void swap(card* a, card* b) {
		if (a == b) {
			return;
		}
		card *prevA = NULL;
		card *currA = top;
		while (currA != a)
		{
			prevA = currA;
			currA = currA->next;
		}
		card *prevB = NULL;
		card *currB = top;
		while (currB != b)
		{
			prevB = currB;
			currB = currB->next;
		}

		if (currA == NULL || currB == NULL)
			return;

		if (prevA != NULL)
			prevA->next = currB;
		else
			top = currB;

		if (prevB != NULL)
			prevB->next = currA;
		else
			top = currA;


		card* temp = currB->next;
		currB->next = currA->next;
		currA->next = temp;
	}

	void push(int A) {
		// allocate new memory
		card *newnode = new card(A);
		cout << newnode->suit;

		// check if list is empty
		if (!top) {
			top = newnode;
		}
		else {
			newnode->next = top;

			top = newnode;

		}
		decksize++;
	}

	// Pop a card off the stack. It will always be the one on       top.
	card* pop() {
		if (!top) {
			return NULL;        // Return NULL for empty stack
		}
		else {
			card *Temp = top;   // Point to top with temp pointer

			card *a = top;

			top = top->next;    // Move top of stack 

			delete Temp;        // Delete old top node

			decksize--;
			return a;
		}

	}


};

/*
This class simulates the dealer or opponent. They will
Randomly be given some cards, and generally make the best
decision they can at a given moment.
*/

class opponent {
private:
	card* left;

public:

	opponent() {
		left = NULL;
	}

	void push(card* anode) {

		// check if list is empty
		if (!left) {
			left = anode;  // If empty stack just point to new node
			left->next = NULL;
		}
		else {
			anode->next = left;            // Link new node by point its next to old top
			left = anode;                  // Now update top to point to the new node
		}

	}

	// This function gets the score from the game
	int getScore() {
		card* temp = left;
		int score = 0;
		int ace = 0;

		// If no cards, just return the score
		if (left == NULL)
			return score;

		// The following code is used to determine what value
		// the ace should be (1 or 11).
		while (temp) {
			if (temp->face == 1) {
				score += 11;
				ace += 1;

			}
			else if (temp->face == 11 || temp->face == 12 || temp->face == 13) {
				score += 10;
			}
			else {
				score += temp->face;
			}

			temp = temp->next;
		}

		for (int i = 0; i < ace; i++) {
			if (score > 21) {
				score -= 10;
			}
		}
		score = 21 - score;
		return score;
	}

	void print() {
		card *Temp = left;
		while (Temp != NULL) {
			Temp->printCard();
			Temp = Temp->next;
		}
		cout << "--------------------------------------------\n";
	}

	// Hides the computer's first card from the player to make
	// things more interesting.
	void printHide() {
		left->printCard();
		cout << "┌────┐\n│■■■■│\n│■■■■│\n└────┘\n";
	}

	void startHand(deck* D) {
		push(D->pop());
		push(D->pop());
	}

	int play(deck* D, int pScore) {
		int score = getScore();

		bool risk = true;
		if (pScore < 0) {
			risk = false;
		}

		while (score > pScore && risk) {
			push(D->pop());
			score = getScore();
		}

		return getScore();
	}
};

class player {
private:
	card* left;

public:

	player() {
		left = NULL;
	}

	void push(card* anode) {

		// check if list is empty
		if (!left) {
			left = anode;                  // If empty stack just point to new node
			left->next = NULL;
		}
		else {
			anode->next = left;            // Link new node by point its next to old top
			left = anode;                  // Now update top to point to the new node
		}
	}

	// This code returns the user's score so they can see 
	// how they are doing versus the opponent.
	int getScore() {
		card* temp = left;
		int score = 0;
		int ace = 0;

		if (left == NULL)
			return score;

		while (temp) {
			if (temp->face == 1) {
				score += 11;
				ace += 1;
			}
			else if (temp->face == 11 || temp->face == 12 || temp->face == 13) {
				score += 10;
			}
			else {
				score += temp->face;
			}
			temp = temp->next;
		}

		for (int i = 0; i < ace; i++) {
			if (score > 21) {
				score -= 10;
			}
		}
		score = 21 - score;

		return score;
	}

	// Same as the other print function, just for humans.
	void print() {
		card *Temp = left;

		while (Temp != NULL) {
			Temp->printCard();
			Temp = Temp->next;
		}
		cout << "---------------------------------------------\n";
	}

	// This function will simulate a game of poker. The player
	// is given a choice to fold, hit, or take a peek at what 
	// their opponent has. The game is over once the player folds
	// or someone goes over 21.
	int play(deck* D, opponent* dealer) {
		int score;
		card* selected = left;

		// Used for decision making.
		bool fold = false;
		char move;

		cout << "Dealer's cards: \n";

		dealer->printHide();

		push(D->pop());
		push(D->pop());

		while (!fold && getScore() >= 0) {
			cout << "Your cards: \n";
			print();

			cout << "Please make a choice. (F = fold, H = hit, D = show dealer's hand). Please press enter after entering choice.\n";
			char move;

			cin >> move;

			// This will make the user's input uppercase. 
			// It removes the need for an or statement when
			// checking.
			move = toupper(move);

			// Clears the screen
			TP::clear();
			if (move == 'F')
				fold = true;
			else if (move == 'H') {
				push(D->pop());
			}
			else if (move == 'D') {
				cout << "Dealers hand is shown: \n";
				dealer->printHide();
			}
			else
				cout << "Wrong input.\n";

		}

		if (getScore() == 0) {
			cout << "21!\n";
		}
		cout << "Your Cards: \n";

		// Print out the user's cards
		print();

		return score;
	}

};

int main() {
	deck D;
	player human;
	opponent computer;

	D.shuffle();

	computer.startHand(&D);

	human.play(&D, &computer);

	int playerScore = human.getScore();
	int cmpScore;

	cmpScore = computer.play(&D, playerScore);

	cout << "Dealers hand: \n";
	computer.print();

	cout << "Your score: " << 21 - playerScore << endl;
	cout << "Dealer score: " << 21 - cmpScore << endl;

	// If a player goes over twenty one, their score becomes
	// a negative value. This is used to determine a bust. 
	if (playerScore < 0) {
		cout << "You Busted!\n";
	}
	else if (cmpScore < 0) {
		cout << "DEALER BUSTED!\n";
	}

	// Show player their results.
	else {
		if (cmpScore < playerScore) {
			cout << "The House Wins!\n";
		}
		else if (cmpScore == playerScore) {
			cout << "TIE!\n";
		}
		else {
			cout << "YOU WIN!!\n";
		}
	}

	return 0;
}
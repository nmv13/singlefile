/****************************************************************************
* RiskDice: This program allows the user to select from two different modes.
* The first mode is for a single dice roll, allowing the attacker to go from
* one attack at a time. The second is a blitz so the attacker doesn't need
* to roll for a while before coming to a concluding result.
****************************************************************************/

#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

using namespace std;

int numDie(int x, char c);
void faceOff(int dieA, int dieD, int * numA, int * numD, int mode);
void a1d1(int * numA, int * numD, int mode);
void a2d1(int * numA, int * numD, int mode);
void a1d2(int * numA, int * numD, int mode);
void a2d2(int * numA, int * numD, int mode);
void a3d1(int * numA, int * numD, int mode);
void a3d2(int * numA, int * numD, int mode);
void result(int numA, int numD, int th);

int main()
{
	int mode; // Whether the user wants Normal or Blitz
	int numA; // Number of troops Attacker has
	int numD; // Number of troops Defender has
	int dieA; // Number of dice Attacker has
	int dieD; // Number of dice Defender has
	int th;   // Threshhold variable
	char ans; // The user answer if it's single mode
	int go = false; // For validation

	do
	{
		// Prompt user, which mode they want
		cout << "What mode do you want?\n\n   1: Normal\n   2: Blitz\n\nSelect: ";
		cin  >> mode;

		if (mode == 1 || mode == 2)
				go = true;
			else
			{
				cin.clear(); 
    			cin.ignore(16, '\n');
    			system("clear");
				cout << "\nError: Please enter (1 or 2)\n";
			}
	} while (go == false);

	go = false;
	do
	{
		// Prompt the user for number of troops attacking
		cout << "Number of troops Attacking: ";
		cin  >> numA;

		if (numA > 1)
				go = true;
			else
			{
				cin.clear(); 
    			cin.ignore(16, '\n');
    			system("clear");
				cout << "\nError: Please enter a troop amount greater than 1\n";
			}
	} while (go == false);

	go = false;
	do
	{
		// Prompt the user for number of troops defending
		cout << "Number of troops Defending: ";
		cin  >> numD;

		if (numD > 0)
				go = true;
			else
			{
				cin.clear(); 
    			cin.ignore(16, '\n');
    			system("clear");
				cout << "\nError: Please enter a troop number greater than 0\n\nNumber of troops Attacking: " << numA << endl;
			}
	} while (go == false);

	// Prompt the Attacker for desired threshhold if count is high and close
	if ((numA > 50 && ((numA - numD) <= 20)) && mode == 2)
	{
		go = false;
		do
		{
			cout << "Minimal troop(s) ceasefire threshhold (1 - " << (numA - 50) << "): ";
			cin  >> th;

			if (th > 0 && th < (numA - 50))
					go = true;
				else
				{
					cin.clear(); 
	    			cin.ignore(16, '\n');
	    			system("clear");
					cout << "\nError: Please enter a troop number as specified below\n\nNumber of troops Attacking: " << numA << "\nNumber of troops Defending: " << numD << endl;
				}
		} while (go == false);
	}
	else
		th = 1;

	// Buffer new line
	cout << endl;

	// Single die roll mode
	if (mode == 1)
	{
		for(;;)
		{
			system("clear");
			// Defener has a max of 2 die for 2+ people
			dieD = numDie(numD, 'D');
			
			// Attacker has a max of 3 for 3+ people
			dieA = numDie(numA, 'A');

			// Battle
			faceOff(dieA, dieD, &numA, &numD, mode);

			// Keep going?
			if (numD <= 0 || numA <= 1)
			{
				result(numA, numD, th);
				return 0;
			}
			else
			{
				usleep(600000);
				cout << "\nEnter 'a' to continue attacking, 'c' to ceasefire: ";
				cin  >> ans;
			}

			// Stop if attacker decides to stop
			if (ans == 'c' || ans == 'C')
			{
				result(numA, numD, th);
				return 0;
			}
		}
	}

	// Initiate rolls : https://www.bitdegree.org/learn/random-number-generator-cpp
	srand((unsigned) time(0));
  	do
  	{		
		// Attacker has a max of 3 die for 4+ people
		dieA = numDie(numA, 'A');

		// Defender has a max of 2 die for 2+ people
		dieD = numDie(numD, 'D');

		// Battle
		faceOff(dieA, dieD, &numA, &numD, mode);

		cout << "\n. A = " << numA << " | D = " << numD;
		usleep(600000);

  	} while (numD > 0 && numA > th);

  	result(numA, numD, th);

  	return 0;
}

/**********************************************
* Find how many die each side is able to use
**********************************************/
int numDie(int x, char c)
{
	int die;

	// Defener has a max of 2 die for 2+ people
	if (c == 'D')
	{
		if (x == 1)
			die = 1;
		else if (x >= 2)
			die = 2;
	}
	// Attacker has a max of 3 for 3+ people
	else if (c == 'A')
	{
		if (x == 2)
			die = 1;
		else if (x == 3)
			die = 2;
		else if (x > 3)
			die = 3;
	}

	return die;
}

/**********************************************
* Determine battle function based on die count
**********************************************/
void faceOff(int dieA, int dieD, int * numA, int * numD, int mode)
{
	if (dieA == 1 && dieD == 1)
	{
		a1d1(numA, numD, mode);
	}
	else if (dieA == 2 && dieD == 1)
	{
		a2d1(numA, numD, mode);
	}
	else if (dieA == 1 && dieD == 2)
	{
		a1d2(numA, numD, mode);
	}
	else if (dieA == 3 && dieD == 1)
	{
		a3d1(numA, numD, mode);
	}
	else if (dieA == 2 && dieD == 2)
	{
		a2d2(numA, numD, mode);
	}
	else if (dieA == 3 && dieD == 2)
	{
		a3d2(numA, numD, mode);	
	}
}

/**********************************************
* Attacker has 1 die, defender has 1
**********************************************/
void a1d1(int * numA, int * numD, int mode)
{
	srand((unsigned) time(0));
	int rollD1 = 1 + (rand() % 6);
	int rollA1 = 1 + (rand() % 6);

	if (mode == 1)
		cout << "Attacker = " << rollA1 << "\nDefender = " << rollD1 << endl;

	if (rollD1 >= rollA1)
	{
		*numA = *numA - 1;
		if (mode == 1)
			cout << "\nAttacker - 1\n";
	}
	else
	{
		*numD = *numD - 1;
		if (mode == 1)
			cout << "\nDefender - 1\n";
	}

	if (mode == 1)
		cout << "\n---\nnumA = " << *numA << "\nnumD = " << *numD << "\n---\n";
}

/**********************************************
* Attacker has 2 die, defender has 1
**********************************************/
void a2d1(int * numA, int * numD, int mode)
{
	srand((unsigned) time(0));
	int rollD1 = 1 + (rand() % 6);
	int rollA1 = 1 + (rand() % 6);
	int rollA2 = 1 + (rand() % 6);

	if (mode == 1)
		cout << "Attacker = " << rollA1 << ", " << rollA2 << "\nDefender = " << rollD1 << endl;

	if ((rollD1 >= rollA1) || (rollD1 >= rollA2))
	{
		*numA = *numA - 1;
		if (mode == 1)
			cout << "\nAttacker - 1\n";
	}
	else
	{
		*numD = *numD - 1;
		if (mode == 1)
			cout << "\nDefender - 1\n";
	}

	if (mode == 1)
		cout << "\n---\nnumA = " << *numA << "\nnumD = " << *numD << "\n---\n";
}

/**********************************************
* Attacker has 1 die, defender has 2
**********************************************/
void a1d2(int * numA, int * numD, int mode)
{
	srand((unsigned) time(0));
	int rollD1 = 1 + (rand() % 6);
	int rollD2 = 1 + (rand() % 6);
	int rollA1 = 1 + (rand() % 6);

	if (mode == 1)
		cout << "Attacker = " << rollA1 << "\nDefender = " << rollD1 << ", " << rollD2 << endl;


	if ((rollA1 <= rollD1) || (rollA1 <= rollD2))
	{
		*numA = *numA - 1;
		if (mode == 1)
			cout << "\nAttacker - 1\n";
	}
	else
	{
		*numD = *numD - 1;
		if (mode == 1)
			cout << "\nDefender - 1\n";
	}

	if (mode == 1)
		cout << "\n---\nnumA = " << *numA << "\nnumD = " << *numD << "\n---\n";
}

/**********************************************
* Attacker has 3 die, defender has 1
**********************************************/
void a3d1(int * numA, int * numD, int mode)
{
	srand((unsigned) time(0));
	int rollD1 = 1 + (rand() % 6);
	int rollA1 = 1 + (rand() % 6);
	int rollA2 = 1 + (rand() % 6);
	int rollA3 = 1 + (rand() % 6);

	if (mode == 1)
		cout << "Attacker = " << rollA1 << ", " << rollA2 << ", " << rollA3 << "\nDefender = " << rollD1 << endl;

	if ((rollD1 >= rollA1) && (rollD1 >= rollA2) && (rollD1 >= rollA3))
	{
		*numA = *numA - 1;
		if (mode == 1)
			cout << "\nAttacker - 1\n";
	}
	else
	{
		*numD = *numD - 1;
		if (mode == 1)
			cout << "\nDefender - 1\n";
	}

	if (mode == 1)
		cout << "\n---\nnumA = " << *numA << "\nnumD = " << *numD << "\n---\n";
}

/**********************************************
* Attacker has 2 die, defender has 2
**********************************************/
void a2d2(int * numA, int * numD, int mode)
{
	srand((unsigned) time(0));
	int rollD1 = 1 + (rand() % 6);
	int rollD2 = 1 + (rand() % 6);
	int rollA1 = 1 + (rand() % 6);
	int rollA2 = 1 + (rand() % 6);
	int largeD, smallD, largeA, smallA;

	if (mode == 1)
		cout << "Attacker = " << rollA1 << ", " << rollA2 << "\nDefender = " << rollD1 << ", " << rollD2 << endl;


	// Find Defender die values
	if (rollD1 > rollD2)
	{
		largeD = rollD1;
		smallD = rollD2;
	}
	else
	{
		largeD = rollD2;
		smallD = rollD1;
	}

	// Find attacker die values
	if (rollA1 > rollA2)
	{
		largeA = rollA1;
		smallA = rollA2;
	}
	else
	{
		largeA = rollA2;
		smallA = rollA1;
	}


	if ((largeD >= largeA) && (smallD >= smallA))
	{
		*numA = *numA - 2;
		if (mode == 1)
			cout << "\nAttacker - 2\n";
	}
	else if ((largeD >= largeA) || (smallD >= smallA))
	{
		*numA = *numA - 1;
		*numD = *numD - 1;
		if (mode == 1)
			cout << "\nAttacker - 1\nDefender - 1\n";
	}
	else
	{
		*numD = *numD - 2;
		if (mode == 1)
		cout << "\nDefender - 2\n";
	}

	if (mode == 1)
		cout << "\n---\nnumA = " << *numA << "\nnumD = " << *numD << "\n---\n";
}

/**********************************************
* Attacker has 3 die, defender has 2
**********************************************/
void a3d2(int * numA, int * numD, int mode)
{
	srand((unsigned) time(0));
	int rollD1 = 1 + (rand() % 6);
	int rollD2 = 1 + (rand() % 6);
	int rollA1 = 1 + (rand() % 6);
	int rollA2 = 1 + (rand() % 6);
	int rollA3 = 1 + (rand() % 6);
	int largeD, smallD, largeA, smallA;

	if (mode == 1)
		cout << "Attacker = " << rollA1 << ", " << rollA2 << ", " << rollA3 << "\nDefender = " << rollD1 << ", " << rollD2 << endl;

	// Find Defender die values
	if (rollD1 > rollD2)
	{
		largeD = rollD1;
		smallD = rollD2;
	}
	else
	{
		largeD = rollD2;
		smallD = rollD1;
	}

	// Find attacker die values
	if ((rollA1 > rollA2) && (rollA1 > rollA3))
	{
		largeA = rollA1;
		if (rollA2 >= rollA3)
		{
			smallA = rollA2;
		}
		else
		{
			smallA = rollA3;
		}
	}
	else if ((rollA2 > rollA1) && (rollA2 > rollA3))
	{
		largeA = rollA2;
		if (rollA1 >= rollA3)
		{
			smallA = rollA1;
		}
		else
		{
			smallA = rollA3;
		}
	}
	else
	{
		largeA = rollA3;
		if (rollA1 >= rollA2)
		{
			smallA = rollA1;
		}
		else
		{
			smallA = rollA2;
		}
	}


	if ((largeD >= largeA) && (smallD >= smallA))
	{
		*numA = *numA - 2;
		if (mode == 1)
			cout << "\nAttacker - 2\n";
	}
	else if ((largeD >= largeA) || (smallD >= smallA))
	{
		*numA = *numA - 1;
		*numD = *numD - 1;
		if (mode == 1)
			cout << "\nAttacker - 1\nDefender - 1\n";
	}
	else
	{
		*numD = *numD - 2;
		if (mode == 1)
		cout << "\nDefender - 2\n";
	}

	if (mode == 1)
		cout << "\n---\nnumA = " << *numA << "\nnumD = " << *numD << "\n---\n";
}

/**********************************************
* Display the results of the battle
**********************************************/
void result(int numA, int numD, int th)
{
  	// Adjust
  	if (numD < 0)
  		numD = 0;
  	if (numA < 0)
  		numA = 0;

  	if (numD == 0)
  			cout << "\nAttacker Won!\nAttacker has " << numA << " troop(s) remaining\nDefender has " << numD << " troop(s) remaining\n";
  	else if (numA == 1)
  			cout << "\nAttacker Lost!\nAttacker has " << numA << " troop(s) remaining\nDefender has " << numD << " troop(s) remaining\n";
  	else
  			cout << "\nAttacker Ceasefire!\nAttacker has " << numA << " troop(s) remaining\nDefender has " << numD << " troop(s) remaining\n";
}
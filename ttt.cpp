#include <iomanip>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

using namespace std;

// NOTE: All functionality except for "Impossible->First" are fully defined

/**************************************
* Current Bug: on the computer goes first mode, game is ending pre-maturely
**************************************/

void game(int mode, int key[9], char board[9], int difficulty, int turn);
char find(int a, int b, int c, vector<int> p, char board[9], char xo);
char gameVScpu(char board[9], int turnF, int key[9], int difficulty, int turn);
bool check(char board[9], char p);
template <class T> void display(T arr);

bool GO = true;

int main()
{
	int mode;
	int difficulty;
	int turn;
	bool ans;
	
	do
	{
		// create array for key
		int key[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

		// Create array for playing board
		char board[9] = {32, 32, 32, 32, 32, 32, 32, 32, 32};


		cout << "Welcome!\n\n   1: 2-Person Player\n   2: Computer Player\n\nPlease choose mode: ";
		cin  >> mode;

		if (mode == 2)
		{
			cout << "Please choose a difficulty:\n\n   1: Easy\n   2: Standard\n   3: Impossible\n\nDifficulty: ";
			cin  >> difficulty; 

			cout << "Choose your turn:\n\n   1: First\n   2: Second\n\nPreference: ";
			cin  >> turn;
		}

		display(key);
		display(board);
		game(mode, key, board, difficulty, turn);

		cout << "Enter 0 to quit, 1 to keep playing: ";
		cin  >> ans;

	} while (ans);

	cout << "Thanks for playing!\n";

	return 0;
}

char find(int a, int b, int c, vector<int> p, char board[9], char xo)
{
	// sleep(1);
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i] == a)
		{
			for (int j = (i + 1); j < p.size(); j++)
			{
				if (p[j] == b && board[c] != xo)
				{
					board[c] = 'O';
					GO = false;
					return board[9];
				}
				else if (p[j] == c && board[b] != xo)
				{
					board[b] = 'O';
					GO = false;
					return board[9];
				}
			}
		}
		else if (p[i] == b)
		{
			for (int j = (i + 1); j < p.size(); j++)
			{
				if (p[j] == c && board[a] != xo)
				{
					board[a] = 'O';
					GO = false;
					return board[9];
				}
			}
		}
	}
	return board[9];
}

char gameVScpu(char board[9], int turnF, int key[9], int difficulty, int turn)
{
	int n = 0; // Random number variable for easy level

	if (difficulty == 1) // Easy
	{
		while (n < 10)
		{
			// sleep(1);
			srand (time(NULL));
			n = rand() % 8;
			if (board[n] == ' ')
			{
				board[n] = 'O';
				n = 10;
			}
		}
	}
	else if (difficulty == 2) //Standard
	{
		vector<int> x; // X
		vector<int> o; // O
		vector<int> s; // Space

		bool r1x = false; // {0,1,2}
		bool r2x = false; // {3,4,5}
		bool r3x = false; // {6,7,8}
		bool c1x = false; // {0,3,6}
		bool c2x = false; // {1,4,7}
		bool c3x = false; // {2,5,8}
		bool ddx = false; // {0,4,8}
		bool dux = false; // {2,4,6}

		bool r1o = false; // {0,1,2}
		bool r2o = false; // {3,4,5}
		bool r3o = false; // {6,7,8}
		bool c1o = false; // {0,3,6}
		bool c2o = false; // {1,4,7}
		bool c3o = false; // {2,5,8}
		bool ddo = false; // {0,4,8}
		bool duo = false; // {2,4,6}
		GO = true;

		// find where 'X's, 'O's, and spaces are on the board
		for (int i = 0; i < 9; i++)
		{
			if (board[i] == 'X')
				x.push_back(i);
			else if (board[i] == 'O')
				o.push_back(i);
			else
				s.push_back(i);
		}

		// 'X's
		for (int z = 0; z < x.size(); z++)
		{
			if (x[z] == 0)
			{
				r1x = true; c1x = true; ddx = true;
			}
			if (x[z] == 1)
			{
				r1x = true; c2x = true;
			}
			if (x[z] == 2)
			{
				r1x = true; c3x = true; dux = true;
			}
			if (x[z] == 3)
			{
				r2x = true; c1x = true;
			}
			if (x[z] == 4)
			{
				r2x = true; c2x = true; ddx = true; dux = true; 
			}
			if (x[z] == 5)
			{
				r2x = true; c3x = true;
			}
			if (x[z] == 6)
			{
				r3x = true; c1x = true; dux = true;
			}
			if (x[z] == 7)
			{
				r3x = true; c2x = true;
			}
			if (x[z] == 8)
			{
				r3x = true; c3x = true; ddx = true;
			}
		}

		// 'O's
		for (int z = 0; z < o.size(); z++)
		{
			if (o[z] == 0)
			{
				r1o = true; c1o = true; ddo = true;
			}
			if (o[z] == 1)
			{
				r1o = true; c2o = true;
			}
			if (o[z] == 2)
			{
				r1o = true; c3o = true; duo = true;
			}
			if (o[z] == 3)
			{
				r2o = true; c1o = true;
			}
			if (o[z] == 4)
			{
				r2o = true; c2o = true; ddo = true; duo = true; 
			}
			if (o[z] == 5)
			{
				r2o = true; c3o = true;
			}
			if (o[z] == 6)
			{
				r3o = true; c1o = true; duo = true;
			}
			if (o[z] == 7)
			{
				r3o = true; c2o = true;
			}
			if (o[z] == 8)
			{
				r3o = true; c3o = true; ddo = true;
			}
		}

		// Check for 'O's
		if (r1o)
			board[9] = find(0, 1, 2, o, board, 'X');
		if (r2o && GO)
			board[9] = find(3, 4, 5, o, board, 'X');
		if (r3o && GO)
			board[9] = find(6, 7, 8, o, board, 'X');
		if (c1o && GO)
			board[9] = find(0, 3, 6, o, board, 'X');
		if (c2o && GO)
			board[9] = find(1, 4, 7, o, board, 'X');
		if (c3o && GO)
			board[9] = find(2, 5, 8, o, board, 'X');
		if (ddo && GO)
			board[9] = find(0, 4, 8, o, board, 'X');
		if (duo && GO)
			board[9] = find(2, 4, 6, o, board, 'X');

		// Check for 'X's
		if (r1x && GO)
			board[9] = find(0, 1, 2, x, board, 'O');
		if (r2x && GO)
			board[9] = find(3, 4, 5, x, board, 'O');
		if (r3x && GO)
			board[9] = find(6, 7, 8, x, board, 'O');
		if (c1x && GO)
			board[9] = find(0, 3, 6, x, board, 'O');
		if (c2x && GO)
			board[9] = find(1, 4, 7, x, board, 'O');
		if (c3x && GO)
			board[9] = find(2, 5, 8, x, board, 'O');
		if (ddx && GO)
			board[9] = find(0, 4, 8, x, board, 'O');
		if (dux && GO)
			board[9] = find(2, 4, 6, x, board, 'O');
		if (GO)
		{
			while (n < 10)
			{
				cout << ".";
				sleep(1);
				srand (time(NULL));
				n = rand() % 8;
				if (board[n] == ' ')
				{
					board[n] = 'O';
					n = 10;
				}
			}
		}
	}
	else if (difficulty == 3) // Impossible
	{
		sleep(1); // Pause computer for 1 second for realistic response
		if (turn == 2) // User goes second
		{
			if (turnF == 2)
				board[6] = 'O';
			else if (turnF == 3)
			{
				if (board[0] == 'X')
					board[8] = 'O';
				else if (board[1] == 'X')
					board[0] = 'O';
				else if (board[2] == 'X')
					board[0] = 'O';
				else if (board[3] == 'X')
					board[8] = 'O';
				else if (board[4] == 'X')
					board[2] = 'O';
				else if (board[5] == 'X')
					board[8] = 'O';
				else if (board[7] == 'X')
					board[0] = 'O';
				else
					board[0] = 'O';
			}
			else if (turnF == 4)
			{
				if (board[8] == 'O')
				{
					if (board[3] == 'X')
					{
						if (board[7] == 32)
							board[7] = 'O';
						else
							board[2] = 'O';
					}
					else if (board[0] == 'X')
					{
						if (board[7] == 32)
							board[7] = 'O';
						else
							board[2] = 'O';
					}
					else if (board[2] == 'X')
					{
						if (board[7] == 32)
							board[7] = 'O';
						else
							board[0] = 'O';
					}
					else if (board[5] == 'X')
					{
						if (board[7] == 32)
							board[7] = 'O';
						else
							board[0] = 'O';
					}
				}
				else if (board[0] == 'O')
				{
					if (board[1] == 'X')
					{
						if (board[3] == 32)
							board[3] = 'O';
						else
							board[8] = 'O';
					}
					else if (board[8] == 'X')
					{
						if (board[3] == 32)
							board[3] = 'O';
						else
							board[2] = 'O';
					}
					else if (board[7] == 'X')
					{
						if (board[3] == 32)
							board[3] = 'O';
						else
							board[2] = 'O';
					}
				}
				else if (board[2] == 'O')
				{
					if (board[0] == 'X')
						board[8] = 'O';
					else if (board[8] == 'X')
						board[0] = 'O';
					else if (board[1] == 'X')
						board[7] = 'O';
					else if (board[7] == 'X')
						board[1] = 'O';
					else if (board[3] == 'X')
						board[5] = 'O';
					else
						board[3] = 'O';
				}
			}
			else if (turnF == 5)
			{
				if (board[2] == 'O' && board[6] == 'O' && board[8] == 'O')
				{
					if (board[4] == 32)
						board[4] = 'O';
					else
						board[5] = 'O';
				}
				else if (board[0] == 'O' && board[6] == 'O' && board[8] == 'O')
				{
					if (board[4] == 32)
						board[4] = 'O';
					else if (board[3] == 32)
						board[3] = 'O';
					else
						board[7] = 'O';
				}
				else if (board[0] == 'O' && board[6] == 'O' && board[8] == 'O')
				{
					if (board[4] == 32)
						board[4] = 'O';
					else
						board[1] = 'O';
				}
				else
				{
					if (board[2] == 'O' && board[6] == 'O' && board[8] == 'O')
					{
						if (board[5] == 32)
							board[5] = 'O';
						else
							board[7] = 'O';
					}
					else if (board[0] == 'O' && board[2] == 'O' && board[6] == 'O')
					{
						if (board[1] == 32)
							board[1] = 'O';
						else
							board[3] = 'O';
					}
					else if (board[2] == 'O' && board[6] == 'O' && board[7] == 'O')
					{
						if (board[8] == 32)
							board[8] = 'O';
						else
							board[0] = 'O';
					}
					else if (board[1] == 'O' && board[2] == 'O' && board[6] == 'O')
					{
						if (board[0] == 32)
							board[0] = 'O';
						else
							board[8] = 'O';
					}
					else if (board[2] == 'O' && board[5] == 'O' && board[6] == 'O')
					{
						if (board[8] == 32)
							board[8] = 'O';
						else
							board[0] = 'O';
					}
					else if (board[2] == 'O' && board[3] == 'O' && board[6] == 'O')
					{
						if (board[0] == 32)
							board[0] = 'O';
						else
							board[8] = 'O';
					}
				}
			}
			else if (turnF == 6)
			{
				if (board[0] == 'O' && board[2] == 'O' && board[6] == 'O' && board[7] == 'O')
				{
					if (board[3] == 32)
						board[3] = 'O';
					else
						board[5] = 'O';
				}
				else if (board[0] == 'O' && board[2] == 'O' && board[5] == 'O' && board[6] == 'O')
				{
					if (board[1] == 32)
						board[1] = 'O';
					else
						board[7] = 'O';
				}
				else if (board[2] == 'O' && board[3] == 'O' && board[6] == 'O' && board[8] == 'O')
				{
					if (board[7] == 32)
						board[7] = 'O';
					else
						board[1] = 'O';
				}
				else if (board[1] == 'O' && board[2] == 'O' && board[6] == 'O' && board[8] == 'O')
				{
					if (board[5] == 32)
						board[5] = 'O';
					else
						board[3] = 'O';
				}
			}
		}
		else if (turn == 1) // User goes first
		{
			if (turnF == 2)
			{
				if (board[4] == 32)
					board[4] = 'O';
				else
					board[6] = 'O';
			}
			else if (turnF == 3)
			{
				// In progress
			}
			else if (turnF == 4)
			{
				// In progress
			}
			else if (turnF == 5)
			{
				// In progress
			}
		}
	}

	display(key);
	display(board);

	return board[9];
}

void game(int mode, int key[9], char board[9], int difficulty, int turn)
{
	// Initialize move variables
	int p1, p2;
	bool end = false;
	bool good = false;
	bool go = true;
	int turnF = 1;
	int turnCounter = turn;

	do
	{
		if (turnCounter == 1)
		{
			do
			{
				// Ask for move from player 1
				cout << "Player X, make your move: ";
				cin  >> p1;

				// Check for move validity
				if (p1 > 0 && p1 < 10 && board[p1 - 1] == 32)
				{
					board[p1 - 1] = 'X';
					good = true;
				}
				else
					cout << "error: The number you entered is invalid or the square is already filled.\n";
			} while (!good);

			if (turnF >= 3 && check(board, 'X'))
			{
				// system("clear");
				cout << "Player X Wins!";
				end = true;
				go = false;
				display(board);
			}
			else if (turnF >= 6)
			{
				// system("clear");
				cout << "It's A Tie!\n";
				end = true;
				go = false;
				display(board);
			}
			else
			{
				good = false;
				display(key);
				display(board);
				turnF++;
			}
		}
		else
		{
			turnCounter = 1;
			turnF++;
		}

		if (mode == 1)
		{
			while (!good)
			{
				// Ask for move from player 2
				cout << turnF << endl;
				cout << "Player O, make your move: ";
				cin  >> p2;

				// Check for move validity
				if (p2 > 0 && p2 < 10 && board[p2 - 1] == 32)
				{
					board[p2 - 1] = 'O';
					good = true;
				}
				else
						cout << "error: The number you entered is invalid or the square is already filled.\n";
			}

			if (turnF >= 3 && check(board, 'O') && go)
			{
				// system("clear");
				cout << turnF << endl;
				cout << "Player O Wins!";
				end = true;
				display(board);
			}
			else if (turnF >= 6)
			{
				// system("clear");
				cout << "It's A Tie!\n";
				end = true;
				go = false;
				display(board);
			}
			else if (go)
			{
				good = false;
				display(key);
				display(board);
			}
		}
		else if (go)
		{
			board[9] = gameVScpu(board, turnF, key, difficulty, turn);

			if (turnF >= 3 && check(board, 'O') && go)
			{
				// system("clear");
				cout << "Computer Wins!";
				end = true;
				display(board);
			}
		}
	} while (!end);
}

bool check(char board[9], char p)
{
	// Check for all possible win positions for X
	if (board[0] == p && board[1] == p && board[2] == p) 
		return true;
	else if (board[3] == p && board[4] == p && board[5] == p)
		return true;
	else if (board[6] == p && board[7] == p && board[8] == p)
		return true;
	else if (board[0] == p && board[3] == p && board[6] == p)
		return true;
	else if (board[1] == p && board[4] == p && board[7] == p)
		return true;
	else if (board[2] == p && board[5] == p && board[8] == p)
		return true;
	else if (board[0] == p && board[4] == p && board[8] == p)
		return true;
	else if (board[6] == p && board[4] == p && board[2] == p)
		return true;
	else
		return false;
}

template <class T>
void display(T arr)
{
	if (arr[0] == 1)
	{
		// system("clear");
		cout << "\n\n\n                               KEY\n";
	}
	else
		cout << "\n\n\n                               PLAY\n";

	cout << "\n                     |                     |                  \n"
	     << "          " << arr[0] << "          |          " << arr[1] << "          |          " << arr[2] << endl
	     << "                     |                     |                  \n"
	     << "------------------------------------------------------------------\n"
	     << "                     |                     |                  \n"
	     << "          " << arr[3] << "          |          " << arr[4] << "          |          " << arr[5] << endl
	     << "                     |                     |                  \n"
	     << "------------------------------------------------------------------\n"
	     << "                     |                     |                  \n"
	     << "          " << arr[6] << "          |          " << arr[7] << "          |          " << arr[8] << endl
	     << "                     |                     |                  \n\n\n\n";
}
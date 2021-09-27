#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include "fns.hpp"

using namespace std;

#define COMPUTER 1 
#define PLAYER 2 

#define SIDE 3 // Length of the board 

// Computer will move with 'O' 
// and human with 'X' 
#define COMPUTERMOVE 'O' 
#define HUMANMOVE 'X' 

char current_marker;



void drawBoard(char board[][SIDE]) 
{ 
	
	cout << "\t\t\t" << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n"; 
	cout << "\t\t\t-----------\n"; 
	cout << "\t\t\t" << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n"; 
	cout << "\t\t\t-----------\n";
	cout << "\t\t\t" << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n"; 
} 

// A function to show the instructions 
void intro() 
{ 
	cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n"; 
	
	cout << "\t\t\t 1 | 2 | 3 \n";
	cout << "\t\t\t-----------\n";
	cout << "\t\t\t 4 | 5 | 6 \n"; 
	cout << "\t\t\t-----------\n";
	cout << "\t\t\t 7 | 8 | 9 \n\n"; 
} 


// A function to initialiseBoard the game 
void initialiseBoard(char board[][SIDE]) 
{	
	// Initially the board is empty 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			board[i][j] = ' '; 
	} 
} 

// A function to declare the winner of the game 
void Winner(int whoseTurn) 
{ 
	if (whoseTurn == COMPUTER) 
		cout << "COMPUTER has won\n"; 
	else
		cout << "HUMAN has won\n"; 
} 

// A function that returns true if any of the row 
// is crossed with the same player's move 
bool checkWin(char board[][SIDE]) {
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') return true;
        if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') return true;
    }
    if(board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') return true;
    if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return true; 
    return false;
}

char swap_player_marker(char current) {
	if(current_marker == 'X') return COMPUTERMOVE;
	else if(current_marker == 'O') return HUMANMOVE;
}

// ham tra ve max neu luot di cua player, min neu luot di cua computer
int minimax(char board[][SIDE], int depth, char currentMove, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (checkWin(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				
				bestScore = -999;
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, swap_player_marker(board[i][j]), false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, swap_player_marker(board[i][j]), true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

// tinh ra vi tri to nhat
int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;

				score = minimax(board, moveIndex+1, swap_player_marker(board[i][j]), false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

// A function to play Tic-Tac-Toe 
void gamePlay(int whoseTurn) 
{ 
	char board[SIDE][SIDE]; 
	int moveIndex = 0, x = 0, y = 0;

	initialiseBoard(board);
	intro(); 
	
	// Keep playing till the game is over or it is a draw 
	while (checkWin(board) == false && moveIndex != SIDE*SIDE) 
	{ 
		int n;
		if (whoseTurn == COMPUTER) 
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = swap_player_marker(current_marker); 
			cout << "COMPUTER da danh " << swap_player_marker(current_marker) << " tai " << n+1 << endl;
			drawBoard(board);
			moveIndex ++; 
			whoseTurn = PLAYER;
		} 
		
		else if (whoseTurn == PLAYER) 
		{
			cout <<"Ban co the danh vao nhung vi tri: ";
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
						cout << (i * 3 + j) + 1 << " ";
			cout <<"\n\nVi tri ban muon danh: ";
			cin >> n;
			n--;
			x = n / SIDE;
			y = n % SIDE; 
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = current_marker; 
				cout <<"\nBan da danh " << current_marker << " tai " << n+1 << endl;
				drawBoard(board); 
				moveIndex ++; 
				whoseTurn = COMPUTER;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				cout <<"\nPosition is occupied, select any one place from the available places\n\n";
			}
			else if(n<0 || n>8)
			{
				cout <<"Invalid position\n";
			}
		} 
	} 
    	// If the game has drawn 
	if (checkWin(board) == false && moveIndex == SIDE * SIDE) 
		cout <<"It's a draw\n"; 
	else
	{ 
		// Toggling the user to declare the actual winner 
		if (whoseTurn == COMPUTER) 
			whoseTurn = PLAYER; 
		else if (whoseTurn == PLAYER) 
			whoseTurn = COMPUTER; 
		
		Winner(whoseTurn); 
	} 
} 

void play() {
    char choice, conti = 'n';
    cout << "\t\t\t\t-----------------WELCOME TO THE GAME----------------------\n\n";
    while (conti == 'n')
    {
        cout << "Ban co muon bat dau truoc?(y/n)";
        cin >> choice;
        
        if(choice == 'y') {
 	       cout << "\n\nBan muon bat dau voi X hay O? ";
 	       cin >> current_marker;
            gamePlay(PLAYER);
        }
        else if (choice == 'n'){
			current_marker = 'X';
            gamePlay(COMPUTER);
        }
        cout << "\n\nBan muon thoat tro choi?(y/n)";
        cin >> conti;
    }
}

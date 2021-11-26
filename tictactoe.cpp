#include <iostream>
#include <limits>
#include <vector>

#include <algorithm>
#include <iostream>
#include <cmath>


#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

char sqr[9] = {'0','1','2','3','4','5','6','7','8'};
vector<char> square(sqr, sqr + 9);

vector<int> get_empty(vector<char>);
vector<vector<char>> nextStates(int, vector<char>);
float eval(int, vector<char>);


int checkwin(vector<char> sq = square) // checks if given board has a winner
{
	if (sq[0] == sq[1]  && sq[1] == sq[2] ){
		if ( sq[0] == 'X' )			
			return 1;
		else
			return 2; 
	}		
	else if (sq[3] == sq[4]  && sq[4] == sq[5] ){
		if ( sq[3] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (sq[6] == sq[7]  && sq[7] == sq[8] ){
		if ( sq[6] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (sq[0] == sq[3]  && sq[3] == sq[6] ){
		if ( sq[0] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (sq[1] == sq[4]  && sq[4] == sq[7] ){
		if ( sq[1] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (sq[2] == sq[5]  && sq[5] == sq[8])
	{	
		if ( sq[2] == 'X' )			
			return 1;
		else
			return 2; 
		}
	else if (sq[0] == sq[4]  && sq[4] == sq[8] )
	{
		if ( sq[0] == 'X' )			
			return 1;
		else
			return 2; 
		}
	else if (sq[2] == sq [4]  && sq[4] == sq[6] )
	{
		if ( sq[2] == 'X' )			
			return 1;
		else
			return 2; 
		}
	else if (sq[0] == sq[3]  && sq[3] == sq[6] )
	{
		if ( sq[0] == 'X' )			
			return 1;
			else
			return 2; 
		}
	else 
		return 0;
}


void mark(int player, int box) // marks current board state at given box for player
{
	if (player == 1)
		square[box] = 'X';
	else
		square[box] = 'O';
}


void display(vector<char> sq = square) // displays the current board in command line
{
	cout << endl;
	for(int i=0; i<9; i++){
		cout << sq[i] << "\t";
		if (i == 2 || i== 5 || i==8)
			cout<<"\n"; 
	}
}


float eval(int winner) // returns an integer value based on the eval function
{
	switch (winner)
	{
	case 0:
		return 0;	
	case 1:
		return 1;
	case 2:
		return -1;
	default:
		return 0;
	}

}

vector<int> get_empty(vector<char> sq = square) // returns given board's empty squares as indices
{
	vector<int> eboxes;
	for (int i=0; i < 9; i++)
	{
		if (sq[i] != 'X' && sq[i] != 'O')
			eboxes.push_back(sq[i] - '0'); // converts ascii int value to numeric.
	}
	return eboxes;
}

 // reference: https://github.com/CodingTrain/website/blob/main/CodingChallenges/CC_154_Tic_Tac_Toe_Minimax/P5/minimax.js
float minimax(bool ismax, int d, vector<char> state = square) // returns index of highest scored move
{
	int win = checkwin(state);
	//cout << endl << get_empty(state).size() << endl;
	if (d == 4 || get_empty(state).size() == 0)
		return (float) eval(win)/d;
	
	vector<int> esq = get_empty(state); //gives possible moves at actual current board state
	int states = esq.size();
	
	
	if (ismax)
	{
		float bestScore = -INFINITY;
		for (int i=0; i < states; i++){

			state[esq[i]] = 'X';
			float score = minimax(false, d+1, state); // returns the optimal score from minimax
			state[esq[i]] = '0' + esq[i];

			bestScore = max(score, bestScore);
		}
		return bestScore;
	} else
	{
		float bestScore = INFINITY;
		for (int i=0; i < states; i++){

			state[esq[i]] = 'O';
			float score = minimax(true, d+1, state); // returns the optimal score from minimax
			state[esq[i]] = '0' + esq[i];
			bestScore = min(score, bestScore);
		}
		return bestScore;
	}
}


int intakeMove(int p) // takes user input move or generates minimax move
{
	int box;

	if (p == 2)
	{
		cin >> box;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	else if (p == 1)
	{
		vector<int> esq = get_empty(); //gives possible moves at actual current board state
		int states = esq.size();
		vector<char> board = square;

		float bestScore = -INFINITY;
		int bestMove;
		for (int i=0; i < states; i++){

			board[esq[i]] = 'X';
			float score = minimax(false, 0, board); // returns the optimal score from minimax
			board[esq[i]] = '0' + esq[i];
			if (score > bestScore)
			{
				bestScore = score;
				bestMove = i;
			}
		}

		cout << endl << "move from minimax: " << bestMove << " score: " << bestScore << endl;
		box = esq[bestMove];
	}

	return box;
}


int validateMove(int p) // validates the given move (user input/minimax), checks if within range 0-9 and if tile is open
{
	int box;

	box = intakeMove(p);
	while (true)
	{
		if ((box < 0 || box > 8) ||  (square[box] == 'X' || square[box] == 'Y'))
		{
			if (p == 1)
				cout << "please enter a valid tile [0, 8]" << '\n';

			cout << "intake error" << endl;
			box = intakeMove(p);
			continue; // continues loop and checks new input
		}	
		break;
	}
	cout << endl << "move validated" << endl; // reaches here when move is valid
	return box;
}


int main()
{
	int player1 = 1, player2 = 2;
	
	int box = -1, result = 0, flag = 0;
	
	for(int i=1;i<5;i++)
	{
		cout << "\n Player " << player1 << "Enter the Box";

		box = validateMove(player1);

		mark(player1, box);
		display();

		result = checkwin();	
		if (result == 1 )
		{	
			cout<<"\n Congratualtions! player " << player1 << " has Won ";
			flag = 1;			
			break;
		}
		else if (result == 2 )
		{	cout<<"\n Congratualtions! player " << player2 << " has Won ";
			flag = 1;			
			break;
		}

		cout << "\n AI Player " << player2 << " Enters the Box";
		
		box = validateMove(player2);

		mark (player2, box);
		display();
		
		result = checkwin();	
		if (result == 1 )
		{	
			cout<<"\n Congratualtions! player " << player1 << " has Won ";
			flag = 1;
			break;
		}
		else if (result == 2 )
		{	
			cout<<"\n Congratualtions! player " << player2 << " has Won ";
			flag = 1;
			break;
		}		
	}
	if (flag == 0 )
		cout <<" \n Sorry, The game is a draw ";
	
	return 0;
}
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
int eval(int, vector<char>);
int maxim(int, vector<char>);
int minim(int, vector<char>);



int checkwin(vector<char> sq = square)
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

void mark(int player, int box)
{
	if (player == 1)
		square[box] = 'X';
	else
		square[box] = 'Y';
}

void display(vector<char> sq = square)
{
	cout << endl;
	for(int i=0; i<9; i++){
		cout << sq[i] << "\t";
		if (i == 2 || i== 5 || i==8)
			cout<<"\n"; 
	}
}


int min(int a, int b)
{
	if (a < b)
		return a;
	else 
		return b;
}


int minim(int p, vector<char> state)
{
	if (checkwin(state) != 0)
		return eval(p, state);

	vector<vector<char>> sArr = nextStates(p, state);
	int states = int(sArr.size());

	int v;

	for (int i=1; i < states; i++)
	{
		v = eval(p, sArr[i]);
		v = min(v, maxim(p, sArr[i]));

	}

	return v;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else 
		return b;
}


int maxim(int p, vector<char> state)
{
	if (checkwin(state) != 0)
		return eval(p, state);

	vector<vector<char>> sArr = nextStates(p, state);
	int states = int(sArr.size());

	int v;

	for (int i=1; i < states; i++)
	{
		v = eval(p, sArr[i]);
		v = max(v, minim(p, sArr[i]));

	}

	return v;
}

int eval(int p, vector<char> sq = square)
{
	/*evaluates utility function of given board*/
	int score = 0;

	int winner = checkwin(sq);
	if (winner != 0){
		cout << endl << "winner: " << winner << "Player: " << p << endl;
		display(sq);
		if (winner != 2)
			return -100;
		else
			return 100;
	}
		

	vector<int> unoccupiedSq = get_empty(sq);

	for (int i=0; i < int(unoccupiedSq.size()); i++){
		if (p == winner)
			score += 100;
		if (winner != 0 && p != winner)
			score -= 100;
		if (unoccupiedSq[i] == 4)
			score += 5;
		if (unoccupiedSq[i] == 0 || unoccupiedSq[i] == 2 || unoccupiedSq[i] == 6 || unoccupiedSq[i] == 8 )
			score += 3;
		else
			score += 1;
	}

	return score;

}

vector<int> get_empty(vector<char> sq = square)
{
	vector<int> eboxes;
	for (int i=0; i < 9; i++)
	{
		if (sq[i] != 'X' && sq[i] != 'Y')
			eboxes.push_back(sq[i] - '0'); // converts ascii int value to numeric.
	}
	return eboxes;
}


int minimax(int p = 2, int d = 2, vector<char> state = square, int minimaxidx=-1, int minimaxScore=-1)
{
	int plyr;

	vector<int> esq = get_empty(state);
	int states = int(esq.size());

	cout << endl << "player:" << p << endl;
	display(state);

	// attempt at acquiring all next board states
	// gather vector of board states, display them all at each move
	vector<vector<char>> stateArr = nextStates(p, state);

	if (states % 2 == 1)
		plyr = 2;
	else if (states %2 == 0)
		plyr = 1;


	vector<int> scores(states);
	vector<int>::iterator result;
	for (int i=0; i < states; i++)
	{
		int boardScore = minim(plyr, stateArr[i]);
		scores[i] = boardScore;
	}


	result = max_element(scores.begin(), scores.end());
	minimaxidx = distance(scores.begin(), result);
	minimaxScore = scores[minimaxidx];

	cout << endl << "score " << minimaxScore << " at index : " << minimaxidx << endl;


	return minimaxidx;
	
}


vector<vector<char>> nextStates(int p, vector<char> state = square)
{

	vector<int> esq = get_empty(state);
	int states = int(esq.size());

	vector<vector<char>> statesArr(states);

	for (int i=0; i < states; i++)
	{
		vector<char> altBoard(sqr, sqr+9); 
		
		for (int j = 0; j < 9; j++)
			altBoard[j] = state[j];
		
		// cout << endl << "empty spot:" << esq[i] << "player:" << p << endl;

		// mark square with the appropriate player's piece
		if (p == 2)
			altBoard[esq[i]] = 'Y';
		else if (p == 1)
			altBoard[esq[i]] = 'X';

		// cout << endl << "filled spot:" << altBoard[esq[i]] << endl;

		for (int j = 0; j < 9; j ++)
			statesArr[i].push_back(altBoard[j]);
	}
	return statesArr;
}


int intakeMove(int p)
{
	int box;

	if (p == 1)
	{
		cin >> box;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	else if (p == 2)
	{
		srand(time(NULL));

		vector<int> esq = get_empty();

		/* displays each potential board state
		for (int i=0; i < states; i++)
		{
			cout << endl << "Game state:" << i << endl;
			display(stateArr[i]);
		}

		// evaluates utility of each board state
		// allocate a score for each state
		int maxidx = 0;
		int maxScore = eval(p, stateArr[0]);
		for (int i=1; i < states; i++)
		{
			int score = eval(p, stateArr[i]);
			if (score < maxScore)
			{
				maxidx = i;
				maxScore = score;
			}
		}


		cout << endl << "max score:" << maxScore << endl;
		// keep for now, eventually replace with minimax steps
		*/

		int move = minimax();
		cout << endl << "move from minimax: " << esq[move] << endl;
		box = esq[move];//maxidx];
	}

	return box;

}

int validateMove(int p){

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
			continue;
		}
		if (p == 2)
			cout << box << endl;
	
		break;
	}
	cout << endl << "move validated" << endl;// reaches here
	return box;
}

int main()
{
	int player1 = 1, player2 = 2 ;
	
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

		cout << endl;
		
		vector<int> esq = get_empty();
		for (int j = 0; j < int(esq.size()); j++)
			cout << esq[j];
			
		cout << endl;
		
}
		if (flag == 0 )
			cout <<" \n Sorry, The game is a draw ";
	
	return 0;
}
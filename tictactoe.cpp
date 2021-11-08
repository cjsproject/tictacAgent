#include <iostream>
#include <limits>
#include <vector>

#include <stdlib.h>
#include <time.h>

using namespace std;
char sqr[9] = {'0','1','2','3','4','5','6','7','8'};
vector<char> square(sqr, sqr + 9);


int checkwin()
{
	if (square[0] == square [1]  && square[1] == square[2] ){
		if ( square [0] == 'X' )			
			return 1;
		else
			return 2; 
	}		
	else if (square[3] == square [4]  && square[4] == square[5] ){
		if ( square [3] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (square[6] == square [7]  && square[7] == square[8] ){
		if ( square [6] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (square[0] == square [3]  && square[3] == square[6] ){
		if ( square [0] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (square[1] == square [4]  && square[4] == square[7] ){
		if ( square [1] == 'X' )			
			return 1;
		else
			return 2; 
	}
	else if (square[2] == square [5]  && square[5] == square[8])
	{	
		if ( square [2] == 'X' )			
			return 1;
		else
			return 2; 
		}
	else if (square[0] == square [4]  && square[4] == square[8] )
	{
		if ( square [0] == 'X' )			
			return 1;
		else
			return 2; 
		}
	else if (square[2] == square [4]  && square[4] == square[6] )
	{
		if ( square [2] == 'X' )			
			return 1;
		else
			return 2; 
		}
	else if (square[0] == square [3]  && square[3] == square[6] )
	{
		if ( square [0] == 'X' )			
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
	for(int i=0; i<9; i++){
		cout << sq[i] << "\t";
		if (i == 2 || i== 5 || i==8)
			cout<<"\n"; 
	}
}

void minim(){return;}

void maxim(){return;}

int eval(int p)
{
	/*evaluates end state of certain tree. ie win/lose/draw state*/


	return 0;

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

int minimax(){return 0;}

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
		int states = int(esq.size());
		// attempt at acquiring all next board states
		// gather array of board states, display them all at each move

		vector<vector<char>> stateArr(states);
		
		cout << endl << "State array allocated" << endl;
		for (int i=0; i < states; i++){
			vector<char> altBoard(sqr, sqr+9); 
			
			for (int j = 0; j < 9; j++)
			{
				altBoard[j] = square[j];
				cout << endl << altBoard[j] << endl;
			}
			
			cout << endl << "empty spot:" << esq[i] << endl;

			altBoard[esq[i]] = 'Y';

			cout << endl << "filled spot:" << altBoard[esq[i]] << endl;

			for (int j = 0; j < 9; j ++)
				stateArr[i].push_back(altBoard[j]);

			cout << endl << "added state:" << stateArr[i][esq[i]] << endl;

		}

		// displays altered board states
		for (int i=0; i < states; i++){
			cout << endl << "Game state:" << i << endl;
			display(stateArr[i]);
		}

		// keep for now, eventually replace with minimax steps

		box = esq[rand() % states];
	}

	return box;

}

int validateMove(int p){

	int box;

	cout << endl << "intake 1" << endl;// reaches here
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
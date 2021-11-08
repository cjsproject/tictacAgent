#include <iostream>
#include <limits>
#include <vector>

#include <stdlib.h>
#include <time.h>

using namespace std;
char square[9] = {'0','1','2','3','4','5','6','7','8'};


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

void display()
{
	for(int i=0; i<9; i++){
		cout << square[i] << "\t";
		if (i == 2 || i== 5 || i==8)
			cout<<"\n"; 
	}
}

void minim(){return;}

void maxim(){return;}

int eval()
{
	/*evaluates current board score*/
	return 0;

}

vector<int> get_empty()
{

	vector<int> eboxes;
	for (int i=0; i < 9; i++){
		if (square[i] != 'X' && square[i] != 'Y')
			eboxes.push_back(square[i] - '0'); // converts ascii int value to numeric.
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
		box = rand() % 9;
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
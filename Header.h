#include <map>
#include<iostream>
#include<vector>
#include <time.h>
#include <limits.h>
using namespace std;



class game{

public:
	map <int, vector<char>> gameTable;
	int count;
	int  DIMENSION; // Dimension of table
	int  WIN;		// Number of rings to win

private:
	map <int, vector<char>> a2;
	int column; // Column input
	int traceHC;//Column input human
	int traceHR;//row input human
	int traceCC;//Column input computer
	int traceCR;//row input computer
	int Minput;//Mouse input
public:

	void insertA(int j, char player){
		for (int i = DIMENSION - 1; i >= 0; i--){
			if (gameTable[i][j] == '-'){
				gameTable[i][j] = player;
				break;
			}
		}
	}
	// Takes the ring/chracter out of the table
	void takeout(int j){

		for (int i = 0; i <= DIMENSION - 1; i++){
			if (gameTable[i][j] != '-')
			{
				gameTable[i][j] = '-';
				break;
			}
		}
	}
	// Checks if column full
	int iffull(int j){
		if (gameTable[0][j] != '-')
			return 1;
		else
			return 0;

	}
	//Minimax recursive algorithm
	int minMAX(int depth)
	{
		int t1 = traceCC;;
		int t2 = traceCR;
		int t3 = traceHC;
		int t4 = traceHR;
		if (depth == 0)
		{
			return 1; // Base case
		}
		int criteria = INT_MIN;
		int index = 0;

		for (int j = 0; j < DIMENSION; j++){
			if (!iffull(j)){
				insertA(j, '2');
				int retVal = Max(depth - 1, criteria);
				if (retVal > criteria)
				{
					criteria = retVal;
					index = j;
				}

				takeout(j);
			}
		}
		traceCC = t1;
		traceCR = t2;
		traceHC = t3;
		traceHR = t4;
		return index + 1;
	}
	int Max(int depth, int parentMin)
	{
		if (depth == 0)
		{
			return evalFunc(1);

		}
		int criteria = INT_MIN;

		for (int j = 0; j < DIMENSION; j++)
		{
			if (!iffull(j))
			{
				insertA(j, '1');
				int retVal = Min(depth - 1, criteria);
				if (retVal > parentMin) // If cutoff possible without looking at other nodes in current step
				{
					takeout(j);
					return retVal;
				}
				if (retVal > criteria)
				{
					criteria = retVal;
				}

				takeout(j);
			}
		}
		return criteria;
	}

	int Min(int depth, int parentMax)
	{
		if (depth == 0)
		{
			return evalFunc(2);
		}

		int criteria = INT_MAX;

		for (int j = 0; j < DIMENSION; j++)
		{
			if (!iffull(j))
			{
				insertA(j, '2');
				int retVal = Max(depth - 1, criteria);
				if (retVal < parentMax)
				{
					takeout(j);
					return retVal;
				}
				if (retVal < criteria)
				{
					criteria = retVal;
				}
				takeout(j);
			}
		}
		return criteria;
	}
	//Evaluates gameTable current state.
	int evalFunc(int playe2r){
		int final = 0;
		int ringsC = 0;
		int Dcheck = 0;
		int Hcheck = 0;
		int Vcheck = 0;
		for (int player = 1; player < 3; player++){
			int r = 0;
			int r2 = 0;
			for (int i = 1; i < 8; i++){
				if (player == 1){
					traceCR = r;
				}
				if (player == 2)
					traceHR = r;
				ringsC = checkHorizontal(WIN, player, DIMENSION, player);
				r++;
				if (ringsC == WIN){
					if (player == 1)
						final = final - 100000;
					else
						final = final + 100000;
				}
				if (ringsC == WIN-1){
					if (player == 1)
						Hcheck = Hcheck - 1000;
					else
						Hcheck = Hcheck + 1000;
				}
				if (ringsC == WIN - 2){
					if (player == 1)
						Hcheck = Hcheck - 200;
					else
						Hcheck = Hcheck + 200;
				}
				ringsC = 0;
				for (int k = 0; k < DIMENSION; k++){
					if (player == 1){
						traceCC = i - 1;
						traceCR = k;
					}
					if (player == 2){
						traceHC = i - 1;
						traceHR = k;
					}
					ringsC = checkDiagonal(WIN, player, DIMENSION, i - 1, player);
					if (ringsC == WIN){
						if (player == 1)
							final = final - 100000;
						else
							final = final + 100000;
					}
					ringsC--;
					if (ringsC == WIN - 1){
						if (player == 1){
							Dcheck = Dcheck - 1000;
						}
						else{
							Dcheck = Dcheck + 1000;
						}
					}
					if (ringsC == WIN - 2){
						if (player == 1){
							Dcheck = Dcheck - 200;
						}
						else{
							Dcheck = Dcheck + 200;
						}
					}
					ringsC = 0;
				}
				ringsC = 0;
				if (player == 1){
					traceCC = i - 1;
				}
				if (player == 2){
					traceHC = i - 1;
				}
				ringsC = checkVertical(WIN, player, DIMENSION, i - 1, player);
				if (ringsC == WIN){
					if (player == 1){
						final = final - 100000;
					}
					else{
						final = final + 100000;
					}
				}
				if (ringsC == WIN - 1){
					if (player == 1){
						Vcheck = Vcheck - 1000;
					}
					else{
						Vcheck = Vcheck + 1000;
					}
				}
				if (ringsC == WIN - 2){
					if (player == 1){
						Vcheck = Vcheck - 200;
					}
					else{
						Vcheck = Vcheck + 200;
					}
				}
			}
		}
		final = final + Hcheck + Dcheck + Vcheck;
		return final;
	}

	//Returns mouse input
	int input(){
		return Minput;
	}
	//Takes input from mouse
	void inputMouse(int a1){
		while (1){
			if (a1 != 0){
				Minput = a1;
				break;
			}
		}
	}
	//Initializes the map
	void iniTable(int dimension){
		vector<char> b;
		for (int i = 0; i < dimension; i++){
			for (int j = 0; j < dimension; j++){
				b.push_back('-');
			}
			gameTable[i] = b;
			b.clear();
		}

	}// Inserts in the map
	void insert(int player, int dimension, int pc){
		char k;
		int times = 0;
		int done = 0;
		map <int, vector<char>> temp = gameTable;

		if (pc == 4){
			column = minMAX(3);
		}
		if (pc != 4){
			column = input();
		}
		if (player == 1)
			k = '1';
		else
			k = '2';

		int i = dimension - 1;
		for (i = dimension - 1; i >= -1; i--){
			if (i != -1){
				if (gameTable[i][column - 1] == '-'){
					gameTable[i][column - 1] = k;

					if (pc == 0)
						column = Minput;

					if (pc == 4){//Keeping AI input in track.
						traceCC = column - 1;
						traceCR = i;
					}
					done++;
					if (pc!=4){// Keeping User input in track.
						traceHC = column - 1;
						traceHR = i;
					}
					
					return;

				}
			}
		}
	}
	// Checks if either player has won
	bool ifcomplete(int win, int player, int column, int dimension, int chk){
		if (chk == 1){ // Checks if AI has won
			if (checkHorizontal(win, player, dimension, 1) == WIN){
				cout << "HORIZONTAL";
				return true;
			}
			if (checkDiagonal(win, player, dimension, column - 1, 1) == WIN){
				cout << "DIAGONAL";

				return true;
			}
			if (WIN == checkVertical(win, player, dimension, column - 1, 1)){
				cout << "VERTICAL";
				return true;
			}

		}
		if (chk == 2){ // Checks if User has Won.
			if (checkHorizontal(win, player, dimension, 2) == WIN){
				cout << "HORIZONTAL";
				return true;
			}


			if (WIN == checkVertical(win, player, dimension, column - 1, 2)){
				cout << "VERTICAL";
				return true;
			}
			if (checkDiagonal(win, player, dimension, column - 1, 2) == WIN){
				cout << "DIAGONAL";

				return true;
			}



		}
		return false;
	}
	//Checks both diagonals, returns #of rings
	int checkDiagonal(int win, int player, int dimension, int column, int pc){
		int rings = 0;
		int row = 0;
		int rings1 = 0;
		int row2 = 0;
		int temp = 0;
		int tempR2 = 0;
		int TempR = 0;
		int TempR2 = 0;
		int column2 = 0;
		int col1 = 0;
		int ro1 = 0;
		char fChar, sChar;
		row = traceHR;
		if (pc == 1){
			row = traceCR;
			column = traceCC;
		}
		if (pc == 2){
			column = traceHC;
			row = traceHR;
		}

		col1 = column;
		ro1 = row;
		row2 = row;
		column2 = column;
		while (1)
		{
			if (ro1 == DIMENSION - 1 || col1 == 0)
				break;

			if (ro1 != DIMENSION - 1 || col1 != 0){
				ro1++;
				col1--;
			}
		}
		while (1)
		{
			if (row2 == DIMENSION - 1 || column2 == DIMENSION - 1)
				break;
			if (row2 != DIMENSION - 1 || column2 != DIMENSION - 1)
			{
				row2++;
				column2++;
			}
		}
		if (player == 1){
			fChar = '1';
			sChar = '2';
		}
		else{
			fChar = '2';
			sChar = '1';
		}
		for (int i = 0; i < dimension; i++){//Checking top left, bottom right diagonal
			if (ro1 >= 0 && col1 < dimension){//Bottom left
				if (gameTable[ro1][col1] == fChar){
					rings1++;
				}
				if (rings1 == 3){
					temp = 3;
				}
				if (rings1 == 2){
					tempR2 = 2;
				}
				if (rings1 == WIN){
					return rings1;
				}
				if (gameTable[ro1][col1] == sChar){
					rings1 = 0;
				}
				if (gameTable[ro1][col1] == '-'){
					rings1 = 0;
				}
				ro1--;
				col1++;
			}
			if (row2 >= 0 && column2 >= 0){//Bottom right
				if (gameTable[row2][column2] == fChar){
					rings++;
				}
				if (rings == 3){
					TempR = 3;
				}
				if (rings == 2){
					TempR2 = 2;
				}
				if (rings == WIN){
					return rings;
				}
				if (gameTable[row2][column2] == sChar){
					rings = 0;
				}
				if (gameTable[row2][column2] == '-'){
					rings = 0;
				}
				row2--;
				column2--;
			}
		}
		if (rings == WIN){
			cout << "rings row: " << row2 << " " << column2;

			return rings;
		}
		if (TempR == 3 || temp == 3)
		{
			if (TempR > temp)
				return TempR;
			else return temp;
		}
		if (TempR2 == 2 || tempR2 == 2)
		{
			if (TempR > temp){
				return TempR2;
			}
			else return tempR2;
		}
		if (rings > rings1)
			return rings;
		else
			return rings1;
	}
	//Checks a row, returns #of rings
	int checkHorizontal(int win, int player, int dimension, int pc){
		int rings = 0;
		int row = 0;
		int iter = 0;
		char fChar, sChar;
		int tempR = 0;
		int temp = row;
		int tempR2 = 0;
		int tempp = 0;
		if (pc == 1)
			row = traceCR;
		if (pc == 2){
			row = traceHR;
		}
		if (player == 1){
			fChar = '1';
			sChar = '2';
		}
		else{
			fChar = '2';
			sChar = '1';
		}


		for (std::map<int, vector<char>>::iterator it = gameTable.begin(); it != gameTable.end(); ++it){
			if (gameTable[row][iter] == fChar){
				rings++;

			}
			if (rings == WIN){
				return rings;
			}
			if (rings == 3){
				tempR = 3;
			}
			if (rings == 2){
				tempR2 = 2;
			}
			if (gameTable[row][iter] == sChar){
				rings = 0;
			}
			if (gameTable[row][iter] == '-'){
				rings = 0;
			}
			iter++;
		}

		row = temp;
		if (tempR == 3){
			return tempR;
		}

		if (tempR2 == 2){
			return tempR2;
		}
		return rings;
	}
	//Checks a column, returns #of rings
	int checkVertical(int win, int player, int dimension, int column, int pc){
		int rings = 0;
		int iter = 0;
		int tempp = 0;
		char fChar, sChar;
		int temp = column;

		if (pc == 1){
			column = traceCC;
		}
		if (pc == 2){
			column = traceHC;
		}
		if (player == 1){
			fChar = '1';
			sChar = '2';
		}
		else{
			fChar = '2';
			sChar = '1';
		}

		for (int i = 0; i < DIMENSION; i++){
			if (gameTable[iter][column] == fChar){
				rings++;
			}
			if (rings == WIN){
				return rings;
			}
			if (rings == 3){
				tempp = rings;
			}
			if (gameTable[iter][column] == sChar){
				rings = 0;
			}
			iter++;
		}
		column = temp;
		if (tempp == 3)
			return 3;

		return rings;
	}

	//AI Function, to take input from the AI.
	int aiFunc(){
		map <int, vector<char>>table;
		int column = 0;
			insert(1, DIMENSION, 4);
			column = traceCC + 1;

			if (ifcomplete(WIN, 1, column, DIMENSION, 1)){

				cout << " WIN " << "Player " << "1" << endl;
				count++;
				return 2;
			}
		

	}
	int userFunc(){
		int column = 0;
		if (count == 0){

			insert(2, DIMENSION, 0);
			column = input();
			if (ifcomplete(WIN, 2, column, DIMENSION, 2)){
				cout << " WIN" << endl;
				count++;
				return 1;

			}
		}
	}
};

#include <conio.h>
#include <iostream>
#include <Windows.h>

using std::cout;
using std::endl;
using std::string;
using std::cin;


const int width = 80;
const int height = 20; // board boundary

int x, y; // head coords paried as x, y 

int foodX, foodY; // food coords

int PlayerScore; // score variable

int snakeTailX[100], snakeTailY[100]; // array for tail coords as x, y variables

int snakeTailLen; // stores length of tail variable 

enum snakesDirection { STOP = 0, LEFT, RIGHT, DOWN, UP }; // stores moving snakesDirection

snakesDirection sDir; // snakesDirection variable 

bool isGameOver;

void GameInit()
{
	isGameOver = false;
	sDir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	PlayerScore = 0;
}

// below is a function for creating the gameboard & rendering //

void GameRender(string playerName)
{
	system("cls"); // clears board may need to impliment own refresh rate

	// will create the top of the board
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {
			// makes sides with '|'
			if (j == 0 || j == width)
				cout << "|";
			//makes snakes head as 'O'
			if (i == y && j == x)
				cout << "O";
			// snakes food as '*'
			else if (i == foodY && j == foodX)
				cout << "*";
			//snakes tail with 'o'
			else {
				bool prTail = false;
				for (int k = 0; k < snakeTailLen; k++)
				{
					if (snakeTailX[k] == j
						&& snakeTailY[k] == i) {
						cout << "o";
						prTail = true;
					}
				}
				if (!prTail)
					cout << " ";
			}
		}
		cout << endl;
	}

	//for creating bottom walls with '-'
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;
}

// next is a function that updates the game state// 
void UpdateGame()
{
	int prevX = snakeTailX[0];
	int prevY = snakeTailY[0];
	int prev2X, prev2Y;
	snakeTailX[0] = x;
	snakeTailY[y] = y;

	for (int i = 1; i < snakeTailLen; i++) {
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		snakeTailX[i] = prevX;
		snakeTailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (sDir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//collison check with wall with (|)
	if (x >= width || x < 0 || y >= height || y < 0)
		isGameOver = true;

	//collision check with tail (o)
	for (int i = 0; i < snakeTailLen; i++) {
		if (snakeTailX[i] == x && snakeTailY[i] == y)
			isGameOver = true;
	}

	//collision check for snake eating food
	if (x == foodX && y == foodY) {
		PlayerScore += 10;
		foodX = rand() % width;
		foodY = rand() % height;
		snakeTailLen++;
	}
}


// function for game difficulty lvl
int SetDifficulty()
{
	int dfc, choice;
	cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard"
		"\nNote: if not chosen difficulty will be set to Medium\nChoose difficulty level:  ";
	cin >> choice;
	switch (choice){
	case '1':
		dfc = 50;
		break;
	case '2':
		dfc = 100;
		break;
	case '3':
		dfc = 150;
		break;
	default: dfc = 100;
		}
	return dfc;
}

//function for user input
void UserInput()
{
	//key press check
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			sDir = LEFT;
			break;
		case 'd':
			sDir = RIGHT;
			break;
		case 'w':
			sDir = UP;
			break;
		case 's':
			sDir = DOWN;
			break;
		case 'x':
			isGameOver = true;
			break;
		}
	}
}


//Main function & game looping function//
int main()
{
	string playerName;
	cout << "enter your name: ";
	cin >> playerName;
	int dfc = SetDifficulty();

	GameInit();
	while (!isGameOver) {
		GameRender(playerName);
		UserInput();
		UpdateGame();
		//creating a delay for the difficulty
		Sleep(dfc);
	}

	return 0;
}
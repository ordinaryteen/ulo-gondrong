#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 50;
const int height = width/2;
int xPrime, yPrime;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLength;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
	gameOver = false;
	dir = STOP;
	x = xPrime;
	y = yPrime;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Map(){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
	for (int i = 0; i < width+3; i++){
		cout << "#";
	} cout << endl;
	
	for (int i = 0; i < height+1; i++){
		for (int j = 0; j < width+2; j++){
			if (j == 0){
				cout << "#";
			}
			
			if (i == y && j == x){
				cout << "o";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < tailLength; k++){
					if (tailX[k] == j && tailY[k] == i){
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
				
		
			if (j == width){
				cout << "#";
			}
		} cout << endl;
	}	
	
	for (int i = 0; i < width+3; i++){
		cout << "#";
	} 
	cout << endl;	
	cout << "Score: " << score << endl;
}


void ConsoleASWD(){
	if (_kbhit()){
		switch (_getch())
		{
			case 'a':
			dir = LEFT;
			break;
			
			case 's':
			dir = DOWN;
			break;
			
			case 'w':
			dir = UP;
			break;
			
			case 'd':
			dir = RIGHT;
			break;
			
			case 'x':
			gameOver = true;
			break;
		}
	}	
}

bool Restart() {
	char choice;
	bool validchoice = false;
	bool playAgain = false;
	
	system ("cls");
	cout << "GAME OVER!";
	Sleep(2000);
	system ("cls");
	
	do {
		cout << "Wanna play again? (Y/T) ";
		cin >> choice;
		
		if (choice == 'Y' || choice == 'T') {
			validchoice = true;
		}
		else {
			system ("cls");
			cout << "Invalid choice! Please choose Y or T." << endl;
		}
	}
	while (!validchoice);
	
	
	if (choice == 'Y'){
		system ("cls");
		cout << "Restarting in:\n";
    	for (int i = 3; i >= 1; i--) {
        cout << i << endl;
        Sleep(1000); 
   	 	}
    	system ("cls");
    	cout << "Restarting now...\n";
    	
    	playAgain = true;
        
	}
	else if (choice == 'T'){
		system ("cls");
		cout << "Hef A Gud Day!! :DD";
	}
	
	return playAgain;
}

void Logic(){	
	for (int i = tailLength; i >= 0; i--)
	 {
	  tailX[i] = tailX[i - 1];
	  tailY[i] = tailY[i - 1];
	 }
	tailX[0] = x;
	tailY[0] = y;
	
	switch (dir)
	{
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
		default:
			break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < tailLength; i++){
		if (tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY){
		score++;
		tailLength++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
	
	if (gameOver && Restart()){
		tailX[0] = xPrime;
		tailY[0] = yPrime;
	}
}

void Play() {
	Setup();
	while (!gameOver)
	{
		Map();
		ConsoleASWD();
		Logic();
		Sleep(10);	
	}
}





int main () {
	do {
		Play();
	}
	while (Restart());
	

}

/*
	A program that generates a dynamically sized maze and displays a path from the begining of the maze to the end.
	If there is no avaivable path, the code generates one.
	The effect is achieved by creating a "dynamic" 2d Array, based on the user inputs for width and height of the maze.

	Problem text:
    Write a program that takes a width and a height and 
    dynamically generates a maze with the given width and 
    height. The maze must always have a valid path through 
    it (how can you ensure this?). Print the maze to the 
    screen once it’s been generated.
*/

#include "stdafx.h"

using namespace std;

void createDynamicArray();
char isEven(int number);
char checkIfPath(char **p_p_maze, int h, int w, int indexH, int indexW);
void customizeMaze();
int checkSymbols(char sym1, char sym2, char sym3, char sym4);
int checkColor(char **p_p_maze, int posH, int posW);
void drawMaze(char **p_p_maze, int h, int w, int& countSteps);
void drawMaze(char **p_p_maze, int h, int w);
void draw(char **p_p_maze, int posH, int posW, char &curChar, char newChar, int color);
void draw(char **p_p_maze, int posH, int posW, char newChar, int color);
void moveInMaze(char **p_p_maze, int h, int w);


char PATH = '_';
char NOTPATH = '@';
char TRAVERSED = '.';
char EXIT = 'E';
char PLAYER = '0';

int main()
{		
	srand( time( NULL ) );
	int input;
	while(true)
	{
		system("cls");
		cout << "Choose : \n1.Create a new maze \n2.Customize maze style \n3.Exit\n::::";
		cin >>input;
		switch(input)
		{
			case(1):
				createDynamicArray();
				break;
			case(2):
				customizeMaze();
				break;
			case(3):
				return 0;
				break;
			default:
				cout <<"Input error!Reseting program...\n";
				system("Pause");
				break;
		}
	}
	return 0;
}

void createDynamicArray()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int h, w, pathNumber, countSteps = 0;
	char **p_p_maze;
	int counter, counterNum;

	do
	{
		system("cls");
		cout << "Input maze height: \n";
		cin >> h;
		cout << "Input maze width: \n";
		cin >> w;
	}while(h<=0 || w<=0);
	cout << "Maze height: " << h << "\nMaze width: " << w <<"\n";
	

	p_p_maze = new char*[h];
	for(int i = 0; i < h; i++)
	{
		p_p_maze[i] = new char[w];
	}
	for(int i = 0; i < h; i++)
	{	
		for(int j = 0; j < w; j++)
		{
			pathNumber = rand() % (100 - 0 + 1);
			p_p_maze[i][j] = isEven(pathNumber);
		}
	}

	p_p_maze[0][0] = TRAVERSED;
	p_p_maze[h-1][w-1] = EXIT;

	char checkMaze = checkIfPath(p_p_maze, h-1, w-1, 0, 0);
	if(checkMaze == 'y')
	{
		cout << "Maze Created! \n\n";
	}else
	{
		cout << "No maze avaivable! \n\n";
	}

	drawMaze(p_p_maze, h, w, countSteps);

	cout <<"\n\n" <<"Legend:\n";
	cout <<"\tAvaivable path: ";
	cout << "|" << PATH <<"|" << "\n";
	cout <<"\tWall: ";
	SetConsoleTextAttribute(hConsole, 12 + 0*16);
	cout << "|" << NOTPATH <<"|" << "\n";
	SetConsoleTextAttribute(hConsole, 15 + 0*16);
	cout <<"\tTraversed path: ";
	SetConsoleTextAttribute(hConsole, 14 + 0*16);
	cout << "|" << TRAVERSED <<"|" << "\n";
	SetConsoleTextAttribute(hConsole, 15 + 0*16);
	cout <<"\tExit: ";
	SetConsoleTextAttribute(hConsole, 14 + 0*16);
	cout << "|" << EXIT <<"|" << "\n";
	SetConsoleTextAttribute(hConsole, 15 + 0*16);
	cout <<"It took "<< countSteps <<" steps to exit this maze " <<h*w<< " tiled maze! \n\n";

	int opt;
		cout <<"\n Would you like to roam the maze? \n1. Yes \n2. No \n::::";
		cin >> opt;
		switch(opt)
		{
			case 1:
				moveInMaze(p_p_maze, h, w);
			case 2:
				break;
			default:
				cout <<"Input error!Reseting program...\n";
		}
		
	for(int i = 0; i < h; i++)
	{
		delete []p_p_maze[i];
	}
	delete []p_p_maze;
}

void drawMaze(char **p_p_maze, int h, int w, int& countSteps){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int color;
	for(int i = 0;i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			color = checkColor(p_p_maze, i, j);
			SetConsoleTextAttribute(hConsole, color + 0*16);
			if(p_p_maze[i][j] == TRAVERSED)
			{
				countSteps++;
			}
			cout <<"|" << p_p_maze[i][j] << "|";
		}
		cout << "\n";
	}
		SetConsoleTextAttribute(hConsole, 15 + 0*16);
}

void drawMaze(char **p_p_maze, int h, int w){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int color;
	for(int i = 0;i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			color = checkColor(p_p_maze, i, j);
			SetConsoleTextAttribute(hConsole, color + 0*16);
			cout <<"|" << p_p_maze[i][j] << "|";
		}
		cout << "\n";
	}
		SetConsoleTextAttribute(hConsole, 15 + 0*16);
}

void moveInMaze(char **p_p_maze, int h, int w){
	int color = 15, fl = 0;
	char opt, curChar = p_p_maze[0][0];
	p_p_maze[0][0] = PLAYER;
	int posH = 0, posW = 0;
	while(fl == 0)
	{
		color = checkColor(p_p_maze,posH,posW);
		system("cls");
		cout << "-------------------------------\n\n";
		drawMaze(p_p_maze, h, w);
		cout << "\n  'w' moves you upwards, 's' downwards, 'a' to the left and 'd' to the right\n Input 'E' to exit\n::::";
		cin >> opt;
		switch(opt)
		{
			case 'w':
				if(posH!=0 && p_p_maze[posH-1][posW]!=NOTPATH)
				{
					draw(p_p_maze, posH, posW, curChar, color);
					posH--;
					draw(p_p_maze,posH,posW, curChar, PLAYER, 3);	
				}
				break;
			case 's':
				if(posH+1!=h && p_p_maze[posH+1][posW]!=NOTPATH)
				{
					draw(p_p_maze, posH, posW, curChar, color);
					posH++;
					draw(p_p_maze,posH,posW, curChar, PLAYER, 3);
				}
				break;
			case 'a':
				if(posW!=0 && p_p_maze[posH][posW-1]!=NOTPATH)
				{
					draw(p_p_maze, posH, posW, curChar, color);
					posW--;
					draw(p_p_maze,posH,posW, curChar, PLAYER, 3);	
					break;
				}
				break;
			case 'd':
				if(posW+1!=w && p_p_maze[posH][posW+1]!=NOTPATH)
				{
					draw(p_p_maze, posH, posW, curChar, color);
					posW++;
					draw(p_p_maze,posH,posW, curChar, PLAYER, 3);	
					break;
				}
				break;
			case 'E':
				fl = 1;
				break;
			default:
				break;
		}
	}
}

int checkColor(char **p_p_maze, int posH, int posW){
	if(p_p_maze[posH][posW] == NOTPATH)
	{
		return 12;
	}
	else if(p_p_maze[posH][posW] == TRAVERSED || p_p_maze[posH][posW] == EXIT)
	{
		return 14;
	}else if(p_p_maze[posH][posW] == PLAYER)
	{
		return 2;
	}else
	{
		return 15;
	}
}

void draw(char **p_p_maze, int posH, int posW, char &curChar, char newChar, int color){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color + 0*16);
	curChar = p_p_maze[posH][posW];
	p_p_maze[posH][posW] = newChar;
	SetConsoleTextAttribute(hConsole, 15 + 0*16);
}

void draw(char **p_p_maze, int posH, int posW, char newChar, int color){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color + 0*16);
	p_p_maze[posH][posW] = newChar;
	SetConsoleTextAttribute(hConsole, 15 + 0*16);
}

char checkIfPath(char **p_p_maze, int h, int w, int indexH, int indexW)
{
	if(indexH > h || indexW > w)
		return NULL;
	char check = NULL;

	if(p_p_maze[indexH][indexW] == EXIT)
	{
		return 'y';
	}

	if(indexH == 0 && indexW == 0)
	{
		if(p_p_maze[indexH][indexW+1]==PATH)
		{
			check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
		}else if(p_p_maze[indexH+1][indexW]==PATH)
		{
			check = checkIfPath(p_p_maze, h, w, indexH+1, indexW);
		}else{
			p_p_maze[indexH][indexW+1]= PATH;
			check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
		}
	}else
	{
		if(p_p_maze[indexH][indexW]==TRAVERSED)
		{
			check = PATH;
			return check;
		}
		//failsafe exists to make sure that the recursive function doesn't stop after it returns
		FAILSAFE:
		 //creating a path, if non is avaivable
			if(indexW!=w && indexH!=h && p_p_maze[indexH][indexW+1] == NOTPATH && p_p_maze[indexH+1][indexW] == NOTPATH)
			{
				if(indexW!=0)
				{
					if(p_p_maze[indexH][indexW-1] == PATH || p_p_maze[indexH][indexW-1] == TRAVERSED)
					{
						p_p_maze[indexH][indexW] = TRAVERSED;
						return NULL;
					}else
					{
						p_p_maze[indexH][indexW] = TRAVERSED;
						p_p_maze[indexH][indexW+1] = PATH;
						check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
					}
				}else
				{
					p_p_maze[indexH][indexW] = TRAVERSED;
					p_p_maze[indexH][indexW+1] = PATH;
					check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
				}
			
			}else if(indexW!=w && indexH!=h && p_p_maze[indexH][indexW+1] == NOTPATH && p_p_maze[indexH+1][indexW] == NOTPATH && p_p_maze[indexH][indexW-1] == NOTPATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				p_p_maze[indexH][indexW+1] = PATH;
				check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
			}else if(indexW!=w && indexH!=h && p_p_maze[indexH+1][indexW] == NOTPATH)
			{
				if(p_p_maze[indexH][indexW+1] == PATH)
				{
					p_p_maze[indexH][indexW] = TRAVERSED;
					check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
				}else if(p_p_maze[indexH][indexW+1] == TRAVERSED)
				{
					p_p_maze[indexH][indexW] = TRAVERSED;
					p_p_maze[indexH+1][indexW] = PATH;
					check = checkIfPath(p_p_maze, h, w, indexH+1, indexW);
				}
			}else if(indexW==w && p_p_maze[indexH+1][indexW] == NOTPATH && p_p_maze[indexH][indexW-1] == NOTPATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				p_p_maze[indexH+1][indexW] = PATH;
				check = checkIfPath(p_p_maze, h, w, indexH+1, indexW);
			}else if(indexW==w && p_p_maze[indexH+1][indexW] == EXIT)
				 // checking for exit  
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				check = checkIfPath(p_p_maze, h, w, indexH+1, indexW); 
			}else if(indexH==h && p_p_maze[indexH][indexW+1] == EXIT)
				//checking for avaivable path    
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
			}else if(indexW!=w && p_p_maze[indexH][indexW+1] == PATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
			}else if(indexH!=h && p_p_maze[indexH+1][indexW] == PATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				check = checkIfPath(p_p_maze, h, w, indexH+1, indexW);
			}else if(indexH!=0 && p_p_maze[indexH-1][indexW] == PATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				check = checkIfPath(p_p_maze, h, w, indexH-1, indexW);
			}else if(indexH==h && p_p_maze[indexH][indexW+1] == NOTPATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				p_p_maze[indexH][indexW+1] = PATH;
				check = checkIfPath(p_p_maze, h, w, indexH, indexW+1);
			}else if(indexW!=0 && p_p_maze[indexH][indexW-1] == PATH)
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				check = checkIfPath(p_p_maze, h, w, indexH, indexW-1);
			}else
			{
				p_p_maze[indexH][indexW] = TRAVERSED;
				return NULL;
			}

		
	}
	if(check == 'y')
	{
		return check;
	}else if(check!='y')
		goto FAILSAFE;
	return check;
}

void customizeMaze()
{
	char path = PATH, notPath = NOTPATH, traversed = TRAVERSED, exit = EXIT;
	int fl = 0;
	do
	{	
		system("cls");
		cout << "Input your symbols: \n[SYMBOLS MUST NOT MATCH AND CAN'T BE " <<PLAYER <<" SYMBOL! ]\n";
		cout << "Input the symbol for avaivable path in the maze: (currently: '" <<PATH<< "')\n::::";
		cin >> path;
		cout << "Input the symbol for traversed path in the maze: (currently: '" <<TRAVERSED<< "')\n::::";
		cin >> traversed;
		cout << "Input the symbol for the walls in the maze: (currently: '" <<NOTPATH<< "')\n::::";
		cin >> notPath;
		cout << "Input the symbol for the exit in the maze: (currently: '" <<EXIT<< "')\n::::";
		cin >> exit;

		fl = checkSymbols(path,notPath,traversed,exit);
		if(fl == 0)
		{
			cout <<"Symbols must not match.\nResetting... \n";
			system("pause");
		}
	}while(fl!=1);
	PATH = path;
	NOTPATH = notPath;
	TRAVERSED = traversed;
	EXIT = exit;
}

int checkSymbols(char sym1, char sym2, char sym3, char sym4)
{
	if(sym1 == sym2)
	{
		return 0;
	}else if(sym1 == sym3)
	{
		return 0;
	}else if(sym1 == sym4)
	{
		return 0;
	}else if(sym1 == PLAYER)
	{
		return 0;
	}else if(sym2 == sym3)
	{
		return 0;
	}else if(sym2 == sym4)
	{
		return 0;
	}else if(sym2 == PLAYER)
	{
		return 0;
	}else if(sym3 == sym4)
	{
		return 0;
	}else if(sym3 == PLAYER)
	{
		return 0;
	}else if(sym4 == PLAYER)
	{
		return 0;
	}else
	{
		return 1;
	}
}

char isEven(int number)
{
	number = number%2;
	if(number == 0){
		return PATH;
	}else
	{
		return NOTPATH;
	}
}

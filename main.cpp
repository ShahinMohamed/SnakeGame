#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<time.h>
#include<Windows.h>

using namespace std;

bool gameOver;
const int width = 50;
const int height = 20;
int x,y,fruitX,fruitY;
int tailX[100],tailY[100];
int tailSize = 0;
int score;
int score2;
int choice;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int speed = 60;

void setup()
{
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	srand(time(0));
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0; 
}
void draw()
{
	int i,j,k;
	system("cls");
	for(i=0;i<width;i++)
		cout<<"-";
	cout<<endl;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(j==0 || j==width-1)
				cout<<"|";
			else if(j==x && i==y)
				cout<<"O";
			else if(j==fruitX && i==fruitY)
					cout<<"#";
			else
			{	
				bool print=false;
				for(k=0;k<tailSize;k++)
				{	
					if(tailX[k]==j && tailY[k]==i)
					{
						print=true;
						cout<<"o";
					}
				}
				if(!print)
					cout<<" ";
			}
		}
		cout<<endl;
		
	}
	for(i=0;i<width;i++)
		cout<<"-";
	cout<<endl;
	cout<<"Score : "<< score<< endl;
}
void input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
		}
		if(score==score2)
		{
			speed -= 10;
			score2 += 20;
		}
	}
}
void logic()
{

	int prevTailX = tailX[0];
	int prevTailY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int tempX,tempY;
	for(int i=1;i<tailSize;i++)
	{
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevTailX;
		tailY[i] = prevTailY;
		prevTailX = tempX;
		prevTailY = tempY;
	}
	if (choice == 1)
	{
		if(x<0)
			x = width -1;
		if(y<0)
			y = height;
		x %= width;
		y %= height + 1;
	}
	else if(choice == 2)
		if(x==0 || x== width || y==0 || y==height)
			gameOver=true;
	for(int i=0;i<tailSize;i++)
	{
		if(x==tailX[i+1] && y==tailY[i+1])
			gameOver = true;
	}
	if(x==fruitX && y==fruitY)
	{
		tailSize++;
		score+=10;
		fruitX = rand() % width;
		fruitY = rand() % height;	
	}
	switch(dir)
	{
		case UP:
			y--;
			Sleep(20);
			break;
		case DOWN:
			y++;
			Sleep(20);
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		default:
			break;
	}
}

int main()
{
	system("cls");
	printf("\n\n\n**********Welcome to Snake game**********\n\n");
	printf("\t1.Normal Mode\n\t2.Hardcore Mode\n");
	cin>>choice;
	score=0;
	if(choice == 1 || choice ==2)
	{
		setup();
		while(!gameOver)
		{
			draw();
			input();
			logic();
			Sleep(speed);
		}
		system("cls");
		printf("\n\nFinal Score= %d",score);
		Sleep(3000);
	}
}			

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
using namespace std;
//dimension of the box of snake game
const int height=20, width=20;
int x,y,fx,fy,score;
// array to store the location of tail array and total nlength of snake
int tailx[100],taily[100],ntail;
bool gameover;
//enum for direction control
enum direct {STOP=0,LEFT,RIGHT,UP,DOWN};
direct  dir;
void draw();
void input();
void logic();
//this function setup the screen when the game starts
//the snake's initial position will be at the centre of the box
//And fruit will be at some random coordinates within the box
//score is initialized with 0
void setup()
{
	system("cls");
	gameover=0;
	dir=STOP;
	x=width/2;
	y=height/2;
	fx=rand()%x;
	fy=rand()%y;
	score=0;
	
}
//function to draw the screen and its objets
void draw()
{
	system("cls");
	int i,j;
//	tailx[0]=i;
//	taily[0]=j;
    //drawing line like structure for game box upper boundary
	for(i=0;i<=width+1;i++)
	   cout<<"-";
	cout<<endl;
	//printing vertical lines for the left and right boundary of the box
	for(i=0;i<height;i++)
	{
		for(j=0;j<=width;j++)
		{
			if(j==0 || j==width)
			   cout<<"|";
			//draw snake's head at (x,y) location
			if(i==y && j==x)
			   cout<<"O";
			//draw fruit F at (fx,fy)
			else if(i==fy && j==fx)
			   cout<<"F";
			else{
				bool print=false;
				//draw the tail part of the snake
				for(int k=0;k<ntail;k++)
				{
					if(tailx[k]==j && taily[k]==i)
					{
						cout<<"o";
						print=true;
					}
				}
				if(!print) cout<<" ";
			} 
			
		}
		cout<<endl;
	}
	//printing the lower horizontal boundary
	for(i=0;i<=width+1;i++)
	   cout<<"-";
    // printing the score
	cout<<"\nScore : "<<score;
}
//function to input the direction from keyborad
void input()
{
	//while keyboard key is pressed
	while(_kbhit())
	{
		//get the ascii value of entered char
		switch(_getch())
		{
			//assigning the directions according to the keys
			case 'a': dir=LEFT; break;
			case 'd': dir=RIGHT; break;
			case 's': dir=DOWN; break;
			case 'w': dir=UP; break;
			case 'x': gameover=1; break;
			
		}
	}
	//	gameover=1;
}
//main logic of the game play
void logic()
{
	//the tail part of the snake follows the head's location
	int prevx=tailx[0];
	int prevy=taily[0];
	int prev2x,prev2y;
	//the next segment of head will be updated with the head's location
	// i.e. the 2nd segment will be updated with the first segment of snake
	tailx[0]=x;
	taily[0]=y;
	for(int i=1;i<ntail;i++)
	{
		// for all the tail parts, update the ith segment with (i-1)th segment
		prev2x=tailx[i];
		tailx[i]=prevx;
		prevx=prev2x;
		prev2y=taily[i];
		taily[i]=prevy;
		prevy=prev2y;
	}
	//change the coordinates according to entered direction
	switch(dir)
	{
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++; break;
	default: break;
   }
   //on getting out of the wall boundary, change the coordinates to strat the snake with next side of the wall
    if(x>=width) x=0; else if(x<0) x=width-1;
     if(y>=height) y=0; else if(y<0) y=height-1;
	 //if the snake touches its own body, end the game
     for(int i=0;i<ntail;i++)
     {
     	if(tailx[i]==x && taily[i]==y)
     	  gameover=true;
	 }
	 //if the snake's head is at fruits coordinates, 
	 //update the score and assign another random location to fruit
	 //increment the tail length of the snake
    if((x==fx && y==fy) || (x==fy && y==fy))
     {
	   score+=10;
	   fx=rand()%width;
	   fy=rand()%height; 
	   ntail++;  
     }
    
}
int main()
{
	system("color 0B");
	setup();
	while(gameover==0)
	{
		draw();
		input();
		logic();
		Sleep(10);
	}
	
		draw();
		cout<<"\n\nGAME OVER\n";
		if(getch()=='\n')
	
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

struct COORD
{
    int X, Y;
};
struct user
{
	char username[30];
	int score;
};
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirecton dir;
struct COORD snake, fruit;
struct COORD tail[100];
bool gameOver;
int score;
int bonus;
int nTail;
int menu(int speed);
int easy();
int medium();
int hard();
int help();
int Quit();
void Setup();
void Draw(int delaytime);
void Input();
void Logic(int delaytime);
const int width = 20;
const int height = 20;
int main()
{
    int speed=0;
    int spd;
    help();
    spd=menu(speed);
	while (gameOver!=true)
	{
		Draw(spd);
		Input();
		Logic(spd);
}
    HigscoreRead();
    Highscore();
   return 0;
}
int menu(int speed){
char choice;
int cursor_y=170;
printf("Menu\n");
printf("1.Easy\n");
printf("2.Medium\n");
printf("3.Hard\n");
printf("4.Quit\n");
printf("High Score: \n");
printf("Please Enter your choice: ");
scanf("%d",&choice);
    system("cls");
        if(choice==1){
            speed=100;
            easy();

        }
        else if(choice==2){
            speed=50;
            medium();
        }
        else if(choice==3){
            speed=0;
            hard();
        }
        else if(choice==4){
            Quit();
        }
return speed;
}
int easy(){
Setup();
}
int medium(){
    Setup();
}
int hard(){
    Setup();
}
int Quit(){
exit(-1);
return 0;
}
int help(){
printf("                                            Help!!!!!!!!!!!!\n");
printf("Welcome to Snake Game!!!Move the snake using the w,a,s,d.Press 'ESC' to PAUSE AND RESUME OR EXIT GAME\n");
return 0;
}
void Setup()
{
    FILE * fptr;
	fptr = fopen("highscore1.txt", "a");
	if (fptr == NULL)
		printf("ERROR!");
    system("cls");
	time_t t;
	gameOver = false;
	dir = STOP;
	snake.X = width / 2;
	snake.Y = height / 2;
	srand((unsigned)time(&t));
	fruit.X = rand() % width;
	fruit.Y = rand() % height;
	score = 0;
	bonus=0;
 return 0;
}
void Draw(int delaytime)
{
    if(delaytime==100) usleep(100000);
    else if(delaytime==50) usleep(1000);
    else usleep(10);

system("cls");
	for (int i = 0; i < width+2; i++)
		printf("-");
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
 				printf("|");
			if (i == snake.Y && j == snake.X)
				printf("O");
			else if (i == fruit.Y && j == fruit.X)
				printf("Y");
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tail[k].X == j && tail[k].Y == i)
					{
						printf("o");
						print = true;
					}
				}
				if (!print)
					printf(" ");
			}

			if (j == width - 1)
				printf("|");
		}
		printf("\n");
	}

	for (int i = 0; i < width+2; i++)
		printf("-");
	printf("\n");
	printf("Score: %i" , score);
	printf("\tBonus Score:%d \n",bonus);
	printf("Total Score: %d ",score+bonus);
	printf("\nPress X to quit game\n");
	return 0;
}

void Input()
{
    char choice2;
	if (_kbhit())
	{
		switch (_getch())
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
			break;
        case '\e':
            printf("U PAUSE GAME\nRESUME GAME OR EXIT? (R/E and press ENTER)\n");
            char c;
            c=_getch();
            if(c=='r' || c=='R') system("cls");
            else exit(-1);
            break;

		}
	}
}

void Logic(int delaytime)
{
	int prevX = tail[0].X;
	int prevY = tail[0].Y;
	int prev2X, prev2Y;
	tail[0].X = snake.X;
	tail[0].Y = snake.Y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tail[i].X;
		prev2Y = tail[i].Y;
		tail[i].X = prevX;
		tail[i].Y = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		snake.X--;
		break;
	case RIGHT:
		snake.X++;
		break;
	case UP:
		snake.Y--;
		break;
	case DOWN:
		snake.Y++;
		break;
	default:
		break;
	}
	if (snake.X >= width) snake.X = 0; else if (snake.X < 0) snake.X = width - 1;
	if (snake.Y >= height) snake.Y = 0; else if (snake.Y < 0) snake.Y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tail[i].X == snake.X && tail[i].Y == snake.Y)
			gameOver = true;

	if (snake.X == fruit.X && snake.Y == fruit.Y)
	{
		score += 10;
		if(score%30==0) bonus+=10;
		fruit.X = rand() % width;
		fruit.Y = rand() % height;
		nTail++;
	}

}
void HigscoreRead()
{
	struct user temp1;
	struct user U;
	FILE * read, * write;
	read = fopen("higscore1.txt", "rb");
    write = fopen("temp.txt", "wb");
	bool addflag = false;

	if (read == NULL)
		printf("ERROR!");


		printf("\n\nEnter username: ");
		scanf("%s", U.username);
		U.score = score+bonus;

		while(fread(&temp1,sizeof(struct user), 1, read))
		{
			if (temp1.score < U.score && addflag == false)
			{
                fwrite(&U, sizeof(struct user), 1, write);
                fwrite(&temp1, sizeof(struct user), 1, write);
                addflag = true;
			}
            else
            {
                fwrite(&temp1, sizeof(struct user), 1, write);
            }
		}

		if (addflag == false)
		{
			fwrite(&U, sizeof(struct user), 1, write);
		}

	fclose(read);
	fclose(write);

    remove("higscore1.txt");
    rename("temp.txt", "higscore1.txt");
}
void Highscore()
{
    struct user temp2;
    FILE * disp;
    disp = fopen("higscore1.txt", "rb");
	system("cls");
	printf("\n\t\t\t\t  HighScore Table\n");
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\tNAME\t\t\t\tSCORE\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	while(fread(&temp2, sizeof(struct user), 1, disp))
	{
		printf("\t\t\t%s\t\t\t\t%i\n", temp2.username, temp2.score);
	}

	fclose(disp);
}

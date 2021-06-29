#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

int menu();
void check();
void dead();
int easy();
int medium();
int hard();
int help();
int Quit();
void check_level();
void high();
int snake_x[500],snake_y[500],snake_size = 5,score,highscore,spd = 100,l;
bool checkdied = false,BONUS = false;

int main()
{
   int gd = DETECT, gm;
   initgraph(&gd, &gm, "C:\\TC\\BGI");
    menu();
   getch();
   closegraph();
   return 0;
}
int menu(){
char ch;
int cursor_y=170;
while(1){
outtextxy(250,150,"Menu");
outtextxy(250,170,"Easy");
outtextxy(250,190,"Medium");
outtextxy(250,210,"Hard");
outtextxy(250,230,"Help");
outtextxy(250,250,"Quit");
outtextxy(250,300,"High Score:");
high();
outtextxy(240,cursor_y,">");
if(kbhit){
ch=getch();
outtextxy(240,cursor_y,">");
if(ch==83 || ch==115){
    cursor_y+=20;
    cleardevice();
}
if(ch==87 || ch==119) {
        cursor_y-=20;
cleardevice();
}
    if(ch==13){
        if(cursor_y==170){
            easy();
        }
        else if(cursor_y==190){
            medium();
        }
        else if(cursor_y==210){
            hard();
        }
        else if(cursor_y==230){
            help();
        }
        else if(cursor_y==250){
            Quit();
        }
    }
}
    outtextxy(240,cursor_y,">");
}
return 0;
}

void dead()
{
    checkdied = false;
    snake_size = 5;
    score = 0;
    cleardevice();
}
int easy(){
clearviewport();
spd+=20;
cin >> highscore;
    cleardevice();
     freopen("highscore.dat","r",stdin);
     printf("%d",highscore);
    char ch;
    string key = "right";
    int maxx = getmaxx() + 1;
    int maxy = getmaxy()-50 -1;
    int x = 13,y = 13;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    while(true)
    {
        clearviewport();
        if(score >0 && score%5==4){
            BONUS = true;
        }
        else
        {
            bonus = 500;
            BONUS = false;
        }
        if(!BONUS || bonus == 0)
        {
            setcolor(BLACK);
            outtextxy(250,10,"Hurry!!");
            setcolor(MAGENTA);
            setfillstyle(SOLID_FILL,MAGENTA);
            circle(food_x,food_y,5);
            floodfill(food_x,food_y,MAGENTA);

        }
        else
        {
            setcolor(BLUE);
            setfillstyle(SOLID_FILL,BLUE);
            circle(food_x,food_y,5);
            floodfill(food_x,food_y,BLUE);

            char spp[1000];
            setcolor(BLACK);
            sprintf(spp,"Hurry!! %d",bonus);
            outtextxy(250,10,"Hurry!!");
            setcolor(MAGENTA);
            outtextxy(250,10,spp);

        }
        maxx = getmaxx()+1;
        maxy = getmaxy()-50-1;
        setcolor(WHITE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch();
            if(ch == 0)
                ch = getch();
            if(ch == 72 && key != "down" )
                key = "up";
            if(ch == 80 && key != "up")
                key = "down";
            if(ch == 75 && key != "right")
                key = "left";
            if(ch == 77 && key != "left")
                key = "right";
            if(ch == 27)
            {
                cleardevice();
                return 0;
            }


        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else
        {
            for(int _size = snake_size-2; _size >= 0; _size--)
            {
                snake_x[_size+1] = snake_x[_size];
                snake_y[_size+1] = snake_y[_size];
            }
            snake_x[0] = x;
            snake_y[0] = y;

            setcolor(RED);
            circle(snake_x[0],snake_y[0],8);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(snake_x[0],snake_y[0],RED);

            setcolor(GREEN);
            for(int _size = 1; _size < snake_size; _size++)
            {
                circle(snake_x[_size],snake_y[_size],5);
                setfillstyle(SOLID_FILL,GREEN);
                floodfill(snake_x[_size],snake_y[_size],GREEN);
            }

            char ara[100];
            sprintf(ara,"Score: %d",score);
            setcolor(WHITE);
            outtextxy(00,maxy+10,ara);
            sprintf(ara,"Bestscore: %d",highscore);
            setcolor(WHITE);
            outtextxy(450,maxy+10,ara);

            delay(spd);

        }
        if(x == food_x && y== food_y)
        {
            snake_size++;
            score++;

            if(score%5==0 && score>0)
                score+=bonus;

            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;

            if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
            {
                while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
                {
                    food_x = rand()%maxx,food_y = rand()%maxy;
                    temp = food_x%13;
                    food_x-=temp;
                    temp = food_y%13;
                    food_y-=temp;
                }
            }
        }
        if(key == "right")
            x = x+13;
        if(x > maxx)
            x =0;
        if(key == "left")
            x = x-13;
        if(x < 0)
            x = maxx-(maxx%13);
        if(key == "up")
            y = y-13;
        if(y > maxy)
            y = 0;
        if(key == "down")
            y = y+13;
        if(y < 0)
            y = maxy-(maxy%13);
        check_level();
        if(checkdied)
        {
            dead();
            return 0;
        }

        if(BONUS)
        {
            if(bonus>0)
                bonus-=10;
        }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size; _size++)
        {
            circle(snake_x[_size],snake_y[_size],5);
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(snake_x[_size],snake_y[_size],BLACK);
        }

    }
}

void check()
{
    freopen("highscore.dat","w",stdout);
    if(highscore < score){
        cout << score << endl;
    }

    else
        cout << highscore << endl;

    for(int i = 1; i < snake_size; i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
        {

            cleardevice();
            setcolor(BLUE);
            settextstyle(10,0,5);
            outtextxy(200,200," GAME OVER !");
            while(1)
            {
                if(kbhit())
                {
                    char ch = getch();
                    if(ch == 13)
                    {
                        checkdied = true;
                        cleardevice();
                        return;
                    }
                }
            }
        }
    }
}

int medium(){
clearviewport();

    cleardevice();
        freopen("highscore.dat","r",stdin);
        cin >> highscore;
    char ch;
    string key = "right";
    int maxx = getmaxx() + 1;
    int maxy = getmaxy()-50 -1;
    int x = 13,y = 13;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    while(true)
    {
        clearviewport();
        if(score >0 && score%5==4){
            BONUS = true;
        }
        else
        {
            bonus = 500;
            BONUS = false;
        }
        if(!BONUS || bonus == 0)
        {
            setcolor(BLACK);
            outtextxy(250,10,"Hurry!!");
            setcolor(MAGENTA);
            setfillstyle(SOLID_FILL,MAGENTA);
            circle(food_x,food_y,5);
            floodfill(food_x,food_y,MAGENTA);

        }
        else
        {
            setcolor(BLUE);
            setfillstyle(SOLID_FILL,BLUE);
            circle(food_x,food_y,5);
            floodfill(food_x,food_y,BLUE);

            char spp[1000];
            setcolor(BLACK);
            sprintf(spp,"Hurry!! %d",bonus);
            outtextxy(250,10,"Hurry!!");
            setcolor(MAGENTA);
            outtextxy(250,10,spp);
        }
        maxx = getmaxx()+1;
        maxy = getmaxy()-50-1;
        setcolor(WHITE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch();
            if(ch == 0)
                ch = getch();
            if(ch == 72 && key != "down" )
                key = "up";
            if(ch == 80 && key != "up")
                key = "down";
            if(ch == 75 && key != "right")
                key = "left";
            if(ch == 77 && key != "left")
                key = "right";
            if(ch == 27)
            {
            outtext("U PAUSE GAME\nRESUME GAME OR EXIT? (R/E and press ENTER)\n");
            char c;
            c=getch();
            if(c=='r' || c=='R') cleardevice();
            else menu();
                return 0;
            }

        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else
        {
            for(int _size = snake_size-2; _size >= 0; _size--)
            {
                snake_x[_size+1] = snake_x[_size];
                snake_y[_size+1] = snake_y[_size];
            }
            snake_x[0] = x;
            snake_y[0] = y;

            setcolor(RED);
            circle(snake_x[0],snake_y[0],8);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(snake_x[0],snake_y[0],RED);

            setcolor(GREEN);
            for(int _size = 1; _size < snake_size; _size++)
            {
                circle(snake_x[_size],snake_y[_size],5);
                setfillstyle(SOLID_FILL,GREEN);
                floodfill(snake_x[_size],snake_y[_size],GREEN);
            }

            char ara[100];
            sprintf(ara,"Score: %d",score);
            setcolor(WHITE);
            outtextxy(00,maxy+10,ara);
            sprintf(ara,"Bestscore: %d",highscore);
            setcolor(WHITE);
            outtextxy(450,maxy+10,ara);

            delay(spd);

        }
        if(x == food_x && y== food_y)
        {
            snake_size++;
            score++;
            if(score%5==0 && score>0)
                score+=bonus;

            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;

            if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
            {
                while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
                {
                    food_x = rand()%maxx,food_y = rand()%maxy;
                    temp = food_x%13;
                    food_x-=temp;
                    temp = food_y%13;
                    food_y-=temp;
                }
            }
        }
        if(key == "right")
            x = x+13;
        if(x > maxx)
            x =0;
        if(key == "left")
            x = x-13;
        if(x < 0)
            x = maxx-(maxx%13);
        if(key == "up")
            y = y-13;
        if(y > maxy)
            y = 0;
        if(key == "down")
            y = y+13;
        if(y < 0)
            y = maxy-(maxy%13);
        check_level();
        if(checkdied)
        {
            dead();
            return 0;
        }

        if(BONUS)
        {
            if(bonus>0)
                bonus-=10;
        }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size; _size++)
        {
            circle(snake_x[_size],snake_y[_size],5);
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(snake_x[_size],snake_y[_size],BLACK);
        }

    }
}
void high()
{
    freopen("highscore.dat","r",stdin);
    char ara[100];
    cin >> highscore;
    sprintf(ara,"%d",highscore);
    setcolor(WHITE);
    outtextxy(330,300,ara);
}
int hard(){

    freopen("highscore.dat","r",stdin);
    cin >> highscore;
    spd-=30;
clearviewport();
    cleardevice();
    char ch;
    string key = "right";
    int maxx = getmaxx() + 1;
    int maxy = getmaxy()-50 -1;
    int x = 13,y = 13;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    while(true)
    {
        clearviewport();
        if(score >0 && score%5==4){
            BONUS = true;
        }
        else
        {
            bonus = 500;
            BONUS = false;
        }
        if(!BONUS || bonus == 0)
        {
            setcolor(BLACK);
            outtextxy(250,10,"Hurry!!");
            setcolor(MAGENTA);
            setfillstyle(SOLID_FILL,MAGENTA);
            circle(food_x,food_y,5);
            floodfill(food_x,food_y,MAGENTA);
        }
        else
        {
            setcolor(BLUE);
            setfillstyle(SOLID_FILL,BLUE);
            circle(food_x,food_y,5);
            floodfill(food_x,food_y,BLUE);

            char spp[1000];
            setcolor(BLACK);
            sprintf(spp,"Hurry!! %d",bonus);
            outtextxy(250,10,"Hurry!!");
            setcolor(MAGENTA);
            outtextxy(250,10,spp);
        }
        maxx = getmaxx()+1;
        maxy = getmaxy()-50-1;
        setcolor(WHITE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch();
            if(ch == 0)
                ch = getch();
            if(ch == 72 && key != "down" )
                key = "up";
            if(ch == 80 && key != "up")
                key = "down";
            if(ch == 75 && key != "right")
                key = "left";
            if(ch == 77 && key != "left")
                key = "right";
            if(ch == 27)
            {
                outtext("U PAUSE GAME\nRESUME GAME OR EXIT? (R/E and press ENTER)\n");
            char c;
            c=getch();
            if(c=='r' || c=='R') cleardevice();
            else menu();
                return 0;
            }
        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else
        {
            for(int _size = snake_size-2; _size >= 0; _size--)
            {
                snake_x[_size+1] = snake_x[_size];
                snake_y[_size+1] = snake_y[_size];
            }
            snake_x[0] = x;
            snake_y[0] = y;

            setcolor(RED);
            circle(snake_x[0],snake_y[0],8);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(snake_x[0],snake_y[0],RED);

            setcolor(GREEN);
            for(int _size = 1; _size < snake_size; _size++)
            {
                circle(snake_x[_size],snake_y[_size],5);
                setfillstyle(SOLID_FILL,GREEN);
                floodfill(snake_x[_size],snake_y[_size],GREEN);
            }

            char ara[100];
            sprintf(ara,"Score: %d",score);
            setcolor(WHITE);
            outtextxy(00,maxy+10,ara);
            sprintf(ara,"High Score: %d",highscore);
            setcolor(WHITE);
            outtextxy(450,maxy+10,ara);

            delay(spd);

        }
        if(x == food_x && y== food_y)
        {
            snake_size++;
            score++;
            if(score%5==0 && score>0)
                score+=bonus;

            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;

            if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
            {
                while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
                {
                    food_x = rand()%maxx,food_y = rand()%maxy;
                    temp = food_x%13;
                    food_x-=temp;
                    temp = food_y%13;
                    food_y-=temp;
                }
            }
        }
        if(key == "right")
            x = x+13;
        if(x > maxx)
            x =0;
        if(key == "left")
            x = x-13;
        if(x < 0)
            x = maxx-(maxx%13);
        if(key == "up")
            y = y-13;
        if(y > maxy)
            y = 0;
        if(key == "down")
            y = y+13;
        if(y < 0)
            y = maxy-(maxy%13);
        check_level();
        if(checkdied)
        {
            dead();
            return 0;
        }

        if(BONUS)
        {
            if(bonus>0)
                bonus-=10;
        }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size; _size++)
        {
            circle(snake_x[_size],snake_y[_size],5);
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(snake_x[_size],snake_y[_size],BLACK);
        }

    }
}
int help(){
    clearviewport();
    setcolor(WHITE);
    outtextxy(100,100,"Move the snake using the Arrow case.");
    outtextxy(100,130,"Press 'ESC' to Pause and Resume Game Or Exit Game");
    outtextxy(100,150,"Press any key to go to the menu");
    char ch = getch();
    clearviewport();
return 0;
}
int Quit(){
    exit(0);
return 0;
}
void check_level()
{
    freopen("highscore.dat","w",stdout);
if(highscore < score){
        cout << score << endl;
    }

    else
        cout << highscore << endl;
    for(int i = 1; i < snake_size; i++)
    {
        if((snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) || (snake_x[0] == getmaxx() || snake_x[0] == 0 || snake_y[0] == (getmaxy() - 50) || snake_y[0] == 0 ) )
        {

            cleardevice();
            setcolor(YELLOW);
            settextstyle(10,0,5);
            outtextxy(200,200," GAME OVER!");
            settextstyle(10,0,2);
            setcolor(WHITE);
            outtextxy(150,250,"If you want to menu,Please press Enter");
            while(1)
            {
                if(kbhit())
                {
                    char ch = getch();
                    if(ch == 13)
                    {
                        checkdied = true;
                        cleardevice();
                         main();
                        return;
                    }
                }
            }
        }
    }
}

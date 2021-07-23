#include<iostream>
#include<vector>
#include<conio.h>
#include<windows.h>
using namespace std;

enum eDirection {Stop=0,Left,Right,Up,Down};
eDirection dir;

vector<pair<int,int>>tail(200);

typedef struct
{
    int high;
} highest;

string gap="\t\t\t\t\t";
string endline="\n";

int width=10,height =15;
int ranx,rany,tl=1;
int x=width/2, y=height/2;
int score=0;

bool gameover=0;

void sound()
{
    Beep(500, 250);
    Beep(500, 200);
    Sleep(200);
    Beep(600, 300);
}
void print_high()
{
    highest h;
    FILE *fp;
    fp= fopen("highest.txt","r");
    int hi=score;
    int r=fread(&h,sizeof(h),1,fp);
    fclose(fp);
    fp=fopen("highest.txt","w");
    if(r==0 || h.high<hi)
    {
        h.high=hi;
    }
    else if(h.high>hi)
    {
        hi=h.high;
    }
    fwrite(&h,sizeof(h),1,fp);
    fclose(fp);
cout<<endl<<gap<<"   HIGHEST SCORE : "<<hi<<endl;

}

void System()
{
    ranx=1+(rand()%(width-2));
    rany=1+(rand()%(height-1));

}

void draw()
{
    cout<<gap<<"    S N A K E  G A M E"<<endl;
    cout<<gap<<" ________________________";
    cout<<"\n\t\t CONTROLS\n\t\t----------\n";
    cout<<"\t\t    "<<char(30)<<endl;
    cout<<"\t\t"<<char(17)<<"\t"<<char(16)<<endl;
    cout<<"\t\t    "<<char(31)<<endl;

    cout<<endline;
    for(int i=0; i<=height; i++)
    {
        cout<<gap<<"   ";
        for(int j=0; j<=width; j++)
        {


            if((i==0||i==height)||(j==0||j==width))
            {
                cout<<'#'<<" ";
            }
            else  if((rany==i)&&(ranx==j))
            {
                cout<<'*'<<' ';
            }
            else  if((y==i)&&(x==j))
            {
                cout<<'O'<<' ';

            }
            else
            {
                bool flag=0;
                for(int k=0; k<tl; k++)
                {
                    if(tail[k].first== j&& tail[k].second==i )
                    {
                        cout<<'o'<<' ';
                        flag=1;
                    }
                }
                if(!flag)
                {
                    cout<<"  ";
                }
            }
        }
        cout<<endl;
    }
    cout<<endl<<gap<<"     YOUR SCORE  : "<< score<<endl;

}
void input()
{

    if(_kbhit())
    {
        int x= int(_getch());
        switch(x)
        {
        case 75:

            dir =Left;
            break ;

        case 80:
        {
            dir=Down;
            break ;
        }
        case 77:
        {
            dir=Right;
            break ;
        }
        case 72:
        {
            dir=Up;
            break ;
        }
        }
    }
}

void logic()
{
    switch(dir)
    {
    case Left :
        x--;
        break;
    case Right :
        x++;
        break;
    case Up :
        y--;
        break;
    case Down :
        y++;
        break;

    }

    if(x==0)
    {
        x=width;
    }
    else if(x==width)
    {
        x=1;
    }
    if(y==0)
    {
        y=height;
    }
    else if(y==height)
    {
        y=1;
    }

    if(x==ranx && y==rany)
    {
        tl++;
        score+=25;
        Beep(600,100);
        System();
    }

    for(int i=1; i<tl; i++)
    {
        if(x==tail[i].first && y==tail[i].second)
        {
            gameover =1;
            return ;
        }
    }
    int tempx=x,tempy=y;
    for(int i=0; i<tl; i++)
    {
        swap(tempx,tail[i].first);
        swap(tempy,tail[i].second);
    }
}

int main()
{
    System();

    while(1)
    {

        draw();
        input();
        logic();
        if(gameover)
        { print_high();
            sound();
            break;
        }
        Sleep(20);

        system("cls");

    }

    _getch();

}

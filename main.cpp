#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <fstream>



using namespace std;



void BinaryWrite(int score, string name){

   ofstream out("highscores.dat",ios::out | ios::binary);

   if(!out.is_open()){
     cout << "error" << endl;
     return;
   }

   const char* nameCStr = name.c_str();

   out.write((char*)&score,sizeof(score));
   out.write(nameCStr,sizeof(nameCStr));

   out.close();
}

void BinaryRead(){

   ifstream in("highscores.dat",ios::in | ios::binary);

   if(!in.is_open()){

      cout << "error opening" << endl;
   }

   char* ageStr;
   int age;
   char* name;

    in.seekg(0,ios::end);
    int size = (int) in.tellg();
     in.seekg(0,ios::beg);

     in.read((char*)ageStr,sizeof(int));
     cout << ageStr << endl;
}




int main()
{
    start:
    string name;
    char choice;

    cout<< "Welcome to RABSOOSNACK\n"
        << "to play enter 1\n"
        << "to see the high scores enter 2\n"
        << "to quit enter 3\n\n";

    cin>>choice;

    switch(choice){
        case '3':
            goto endofgame;
        case '2':
            BinaryRead();
            cout<< "\n\npress any key to return";
            goto start;
        case '1':
            goto label;

    }

    label:
    char grid[10][10], keyPressed;
    std::fill(&grid[0][0],&grid[10][0],'.');

    int xvel=-1, yvel=0, x=5, y=5,gamespeed = 1000 ,
    targetx = (rand()%10), targety = (rand()%10), score=0;


    grid[x][y] = '0';

    while(x>-1 && x<10 && y>-1 && y<10){
        system("CLS");
        if(_kbhit()){
            switch(getch()){
                case 'w':
                    yvel=-1;
                    xvel=0;
                    break;
                case 's':
                    yvel=1;
                    xvel=0;
                    break;
                case 'a':
                    yvel=0;
                    xvel=-1;
                    break;
                case 'd':
                    yvel=0;
                    xvel=1;
                    break;
            }
        }


        grid[x][y] = '.';
        y = y+yvel;
        x = x+xvel;
        if(x<0 || x>9 || y<0 || y>9)
            grid[x-xvel][y-yvel] = 'H';
        else
            grid[x][y] = '0';

        if((x == targetx) && (y == targety)){
            targetx = (rand()%10);
            targety = (rand()%10);
            gamespeed = (gamespeed - (300*(gamespeed > 400)) - (100*(gamespeed > 100))) - (10*(gamespeed<=100)*(gamespeed>0));
            score++;

        }


        grid[targetx][targety] = 'X';

        cout<< gamespeed << endl;


        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                cout<< grid[j][i] << "   ";
            }
            cout<<endl<<endl;
        }

        cout<<endl;
        cout<<"Score: "<< score <<endl;
        cout<<"Game Speed: "<<(1000-gamespeed);
        Sleep(gamespeed);

    }
    cout<<endl<<"GAME OVER!!!"<<endl<<"Enter your name: ";
    cin>>name;

    BinaryWrite(score,name);

    cout<<"Play again??\n"
        <<"press 1 to play again\n"
        <<"press 2 to quit\n";
    cin>> choice;

    if(choice == '1')
        goto label;

    endofgame:
    cout<<"Thanks for playing RAPSOOSNACKK, GOODBYE\n\n";
    return 0;
}

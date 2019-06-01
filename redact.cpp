#include "table.h"
#include "table.cpp"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;
template<typename V>
const char* write(table<V>&buff,size_t lx,size_t ly,size_t size_y,size_t size_x){
    const char *out(NULL);
	if(!buff.empty()){
		system("cls");
		cout<<"==========================================================="<<endl;
		cout<<"1.[Esc]    =Exit             [TAB] = GoTo elem[i][j]"<<endl;
		cout<<"2.[PgDown] =Fill from file   [PgUp]=Save in File"<<endl;
		cout<<"3.[ENTER]  =Redact elem"<<endl;
		cout<<"==========================================================="<<endl;
		V value(NULL);
		if(buff.size_r()>=size_y){
            if(buff.size_c()>=size_x){
                for(size_t i=ly;i<size_y;i++){
                    for(size_t j=lx;j<size_x;j++){
                        cout.width(6);
                        buff.get(i,j,value);
                        cout<<value<<" ";
                    }
                    cout<<endl;
                }
            }
            else{
                for(size_t i=ly;i<size_y;i++){
                    for(size_t j=0;j<buff.size_c();j++){
                        cout.width(6);
                        buff.get(i,j,value);
                        cout<<value<<" ";
                    }
                    cout<<endl;
                }
            }
        }
        else{
            if(buff.size_c()>=size_x){
                for(size_t i=0;i<buff.size_r();i++){
                    for(size_t j=lx;j<size_x;j++){
                        cout.width(6);
                        buff.get(i,j,value);
                        cout<<value<<" ";
                    }
                cout<<endl;
                }
            }
            else{
                for(size_t i=0;i<buff.size_r();i++){
                    for(size_t j=0;j<buff.size_c();j++){
                        cout.width(6);
                        buff.get(i,j,value);
                        cout<<value<<" ";
                    }
                    cout<<endl;
                }
            }
        }
    }
    else{
        out="empty table :( ";
    }
    return out;
}
template<typename V>
const char* redact(table<V> &buff){
    int size_y=10,size_x=10,lx=0,ly=0,cord_y=-1,cord_x=-1,x,y;
    V buff_value;
    V current_value;
    const char *out(NULL);
    char *filename(NULL);
    if(buff.empty())out="empty table";
    else{
        write(buff,lx,ly,size_y,size_x);
        bool exit(false);
        int ch;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD position ={1,5};
		SetConsoleCursorPosition(hConsole,position);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		while(!exit){
            ch=_getch();
            switch(ch){
            case 224:
                {
                    switch(_getch()){
                    case 73:
                        {
                            out=NULL;
                            system("cls");
                            std::cout<<"press file name >>";
                            std::cin>>filename;
                            strcat(filename,".txt");
                            std::ofstream fout;
                            fout.open(filename);
                            out=buff.save(fout);
                            fout.close();
                            if(!out){
                                exit=true;
                            }
                            else{
                                write(buff,lx,ly,size_y,size_x);
                            }
                            position={1,5};
                            SetConsoleCursorPosition(hConsole, position);
                            SetConsoleCursorPosition(hConsole, position);
                            break;
                        }
                    case 81:
                    {
                        out=NULL;
                        system("cls");
                        cout<<"press file name >>";
                        cin>>filename;
                        strcat(filename,".txt");
                        ifstream fin;
                        fin.open(filename);
                        buff.destroy();
                        out=buff.get_file(fin);
                        if(!out){
                            write(buff,lx,ly,size_y,size_x);
                            position={1,5};
							SetConsoleCursorPosition(hConsole, position);
							SetConsoleCursorPosition(hConsole, position);
                        }
                        else{
                            cout<<out;
                            buff.destroy();
                            exit=true;
                        }
                        break;
                    }
                    case 72:
                    {
                        if(position.Y>5){
                            position.Y--;
                            SetConsoleCursorPosition(hConsole, position);
                            SetConsoleCursorPosition(hConsole, position);
                        }
                        if(position.Y==5){
                            if(size_y>10){
                                ly--;
                                size_y--;
                                write(buff,lx,ly,size_y,size_x);
                                position.Y=5;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        break;
                    }
                    case 80:
                    {
                        if(buff.size_r()>size_y){
                            if(position.Y<14){
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                            if(position.Y==14){
                                ly++;
                                size_y++;
                                write(buff,lx,ly,size_y,size_x);
                                position.Y=14;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                        }
                        else{
                            if(position.Y<buff.size_r()-ly+4){
                                position.Y++;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                                }
                            }
                            break;
                        }
                        case 77:
                        {
                            if(buff.size_c()>size_x){
                                if(position.X<60){
                                    position.X++;
                                    SetConsoleCursorPosition(hConsole, position);
                                    SetConsoleCursorPosition(hConsole, position);
                                }
                                if(position.X==60){
                                    lx++;
                                    size_x++;
                                    write(buff,lx,ly,size_y,size_x);
                                     position.X=59;
                                    SetConsoleCursorPosition(hConsole, position);
                                    SetConsoleCursorPosition(hConsole, position);
                                }
                            }
                            else{
                                if(position.X<(buff.size_c()*6-lx*6-1)){
                                    position.X++;
                                    SetConsoleCursorPosition(hConsole, position);
                                    SetConsoleCursorPosition(hConsole, position);
                                }
                            }
                            break;
                        }
                        case 75:
                        {
                            if(position.X>1){
                                position.X--;
                                SetConsoleCursorPosition(hConsole, position);
                                SetConsoleCursorPosition(hConsole, position);
                            }
                            if(position.X==1){
                                if(size_x>10){
                                    lx--;
                                    size_x--;
                                    system("cls");
                                    write(buff,lx,ly,size_y,size_x);
                                    position.X=1;
                                    SetConsoleCursorPosition(hConsole, position);
                                    SetConsoleCursorPosition(hConsole, position);
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                        case 13:
                        {
                            int checker=0;
                            system("cls");
                            while((!cin)||(checker<1)||(checker>2)){
                                system("cls");
                                cout<<"Change elem ?"<<endl<<"1.Yes"<<endl<<"2.NO"<<endl;
                                cin>>checker;
                            }
                            if(checker==1){
                                system("cls");
                                x=position.X/6+lx;
                                y=position.Y-5+ly;
                                buff.get(y,x,current_value);
                                cout<<x<<" "<<y<<endl<<current_value<<" "<<"press elem >>";
                                cin>>buff_value;
                                while(!cin){
                                    system("cls");
                                    cin.clear();
                                    std::cin.ignore(32767, '\n');
                                    cout<<x<<" "<<y<<endl<<current_value<<" "<<"press elem >>";
                                    cin>>buff_value;
                                }
                                buff.set(y,x,buff_value);
                                write(buff,lx,ly,size_y,size_x);
                            }
                            else{
                                write(buff,lx,ly,size_y,size_x);
                            }
                            position = {1, 5};
                            SetConsoleCursorPosition(hConsole, position);
                            SetConsoleCursorPosition(hConsole, position);
                            break;
                        }
                        case 9:
                        {
                                system("cls");
                                cord_y=-1;
                                cord_x=-1;
                                cout<<"CORD Y:";
                                cin>>cord_y;
                                while((!cin)||(cord_y<0)||(cord_y>buff.size_r())){
                                    system("cls");
                                    cin.clear();
                                    cin.ignore(32767,'\n');
                                    cout<<"CORD Y:";
                                    cin>>cord_y;
                                }
                                system("cls");
                                cout<<"CORD X:";
                                cin>>cord_x;
                                while((!cin)||(cord_x<0)||(cord_x>buff.size_c())){
                                     system("cls");
                                    cin.clear();
                                    cin.ignore(32767,'\n');
                                    cout<<"CORD X:";
                                    cin>>cord_x;
                                }

                        }
            }
        }
    }
    return out;
}

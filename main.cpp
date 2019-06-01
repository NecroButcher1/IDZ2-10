#include "redact.h"
#include "exceptions.h"
#include "sort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
//using namespace std;
void menu();
void menu_fill();
void size(int&,int&);
void null(int&,int&);
int main()
{
    srand(time(NULL));
    table<int> current;
    const char *out;
    int buff_value,row(0),col(0),check(0),check_fill(0);
    while(check!=4){
        menu();
        cin>>check;
        while((!cin)||(check<1)||(check>4)){
            system("cls");
            cin.clear();
            cin.ignore(32767,'\n');
            menu();
            cin>>check;
        }
        if(check==1){
            system("cls");
            current.destroy();
            menu_fill();
            cin>>check_fill;
            while((!cin)||(check_fill<1)||(check_fill>4)){
                system("cls");
                cin.clear();
                cin.ignore(32767,'\n');
                menu_fill();
                cin>>check_fill;
            }
            if(check_fill==1){
                system("cls");
                size(row,col);
                current.create(row,col);
                out=NULL;
                for(size_t i=0;((i<row)&&(!out));i++){
                    for(size_t j=0;((j<col)&&(!out));j++){
                        system("cls");
                        cout<<"["<<i<<"]"<<":["<<j<<"]"<<" >>";
                        cin>>buff_value;
                        if(!cin){
                            cin.clear();
                            cin.ignore(32767,'\n');
                            out="incorrect data";
                            exceptions fail(out);
                            current.destroy();
                        }
                        else{
                            out=current.set(i,j,buff_value);
                            if(out){
                                exceptions fail(out);
                                current.destroy();
                            }
                        }
                    }
                }
                null(check,check_fill);
            }
            if(check_fill==2){
                system("cls");
                out=NULL;
                size(row,col);
                current.create(row,col);
                for(size_t i=0;i<row;i++){
                    for(size_t j=0;j<col;j++){
                        buff_value=rand()%2000-1000;
                        current.set(i,j,buff_value);
                    }
                }
                null(check,check_fill);
            }
            if(check_fill==3){
                out=NULL;
                system("cls");
                cout<<"press file name >>";
                char *filename;
                cin>>filename;
                strcat(filename,".txt");
                ifstream fin;
                fin.open(filename);
                current.destroy();
                out=current.get_file(fin);
                if(out)exceptions fail(out);
                else cout<<"excellent fill"<<endl;
                null(check,check_fill);
            }
        }
        if(check==2){
            system("cls");
            out=NULL;
            out=redact(current);
            if(out)exceptions fail(out);
            null(check,check_fill);
        }
        if(check==3){
            system("cls");
            out=NULL;
            out=sort(current);
            if(out)exceptions fail(out);
            else cout<<"sort table"<<endl;
            null(check,check_fill);
        }
    }
    return 0;
}
void size(int &_row,int &_col){
    _row=0;_col=0;
    cout<<"Read row >>";
    cin>>_row;
    while((_row<1)||(!cin)){
        system("cls");
        cin.clear();
        cin.ignore(32767,'\n');
        cout<<"Read row >>";
        cin>>_row;
    }
    cout<<"Read col>>";
    while((_col<1)||(!cin)){
        system("cls");
        cin.clear();
        cin.ignore(32767,'\n');
        cout<<"Read col >>";
        cin>>_col;
    }
}
void null(int &t1,int &t2){t1=0;t2=0;}
void menu(){
    cout<<"==============="<<endl<<"1.Fill table"<<endl<<"2.see and redact table"<<endl<<"3.Sort"<<endl<<"4.exit"<<endl<<">>";
}
void menu_fill(){cout<<"1.fill from keyboard"<<endl<<"2.fill random"<<endl<<"3.from file"<<endl<<">>";}

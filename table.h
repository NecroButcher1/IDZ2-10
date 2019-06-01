#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <ostream>
template<typename T>
class table{
private:
    int row,col;
    T **body;
public:
    table():row(0),col(0),body(NULL){};
    explicit table(table<T> &copy):row(copy.row),col(copy.col){
        for(size_t i=0;i<row;i++){
            for(size_t j=0;j<col;j++)body[i][j]=copy.body[i][j];
        }
    }
    const T* operator[](size_t);
    const char* save(std::ostream&);
    const char* get_file(std::ifstream&);
    const char* create(int,int);
    const char* set(int,int,T);
    const char* get(int,int,T&);
    int size_r();
    int size_c();
    bool empty();
    void destroy();
    ~table(){destroy();}
};


#endif // TABLE_H_INCLUDED

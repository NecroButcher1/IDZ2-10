#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "exceptions.h"
#include <iostream>
template<typename T>
class table{
private:
    int row,col;
    T **body;
    template<typename V>friend const char* sort(table<V>&);
public:
    table():row(0),col(0),body(NULL){};
    table(table<T> &copy):row(copy.row),col(copy.col){
        for(size_t i=0;i<row;i++){
            for(size_t j=0;j<col;j++){
                body[i][j]=copy.body[i][j];
            }
        }
    }
    const char* create(int,int);
    const char* set(int,int,T);
    const char* get(int,int,T&);
    int get_row();
    int get_col();
    bool empty();
    void destroy();
    ~table(){destroy();}
};


#endif // TABLE_H_INCLUDED

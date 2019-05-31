#include "table.h"
template<typename T>
int table<T>::get_row(){
    return row;
}
template<typename T>
int table<T>::get_col(){
    return col;
}
template<typename T>
bool table<T>::empty(){
    return (!body)?true:false;
}
template<typename T>
const char* table<T>::create(int _row,int _col){
    const char* str(NULL);
    if(_row<1||_col<1)str="incorrect data";
    else{
        row=_row;
        col=_col;
        body= new T*[row];
        for(size_t i=0;i<row;i++){
            body[i]=new T[col];
        }
    }
    return str;
}
template<typename T>
const char* table<T>::set(int i,int j,T _data){
    const char *str(NULL);
    if((i<0)||(j<0)||(i>row)||(j>col))str="incorrect data";
    else{
        body[i][j]=_data;
    }
    return str;
}
template<typename T>
const char* table<T>::get(int i,int j,T &_data){
    const char *str(NULL);
    _data=0;
    if((i<0)||(j<0)||(i>row)||(j>col))str="incorrect data";
    else{
        if(body==NULL)str="empty table";
        else{
            _data=body[i][j];
        }
    }
    return str;
}
template<typename V>
const char* sort(table<V> &buff){
    const char *out(NULL);
    if(buff.empty())out="Empty table";
    else{
        V buff_value;
        V *key=new V[buff.col];
        for(size_t i=0;i<buff.col;i++)key[i]=0;
        for(size_t i=0;i<buff.row;i++){
            for(size_t ii=0;ii<buff.col;ii++){
                if(buff.body[i][ii]<0)key[ii]++;
            }
        }
        size_t buff_idx(0);
        V *tmp_col = new V[buff.col];
        for(size_t i=0;i<buff.col-1;i++){
            buff_idx=i;
            buff_value=key[i];
            for(size_t idx=0;idx<buff.row;idx++)tmp_col[idx]=buff.body[idx][i];
            for(size_t ii=i+1;ii<buff.col;ii++){
                if(key[ii]<key[buff_idx]){
                    buff_idx=ii;
                }
            }
            buff_value=key[i];
            for(size_t idx=0;idx<buff.row;idx++)tmp_col[idx]=buff.body[idx][i];
            key[i]=key[buff_idx];
            for(size_t idx=0;idx<buff.row;idx++)buff.body[idx][i]=buff.body[idx][buff_idx];
            key[buff_idx]=buff_value;
            for(size_t idx=0;idx<buff.row;idx++)buff.body[idx][buff_idx]=tmp_col[idx];
           // std::cout<<key[i]<<" ";
        }
        //std::cout<<std::endl;
        //for(size_t i=0;i<buff.col;i++)std::cout<<key[i]<<" ";
    }
    return out;
}
template<typename T>
void table<T>::destroy(){
    if(body!=NULL){
        for(size_t i=0;i<row;i++)delete[]body[i];
        delete[]body;
        body=NULL;
        row=0;
        col=0;
    }
}

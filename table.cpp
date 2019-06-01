#include "table.h"
template<typename T>
int table<T>::size_r(){
    return row;
}
template<typename T>
int table<T>::size_c(){
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
/*template<typename V>
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
}*/
template<typename T>
const char *table<T>::save(std::ostream &out){
    const char *out1(NULL);
    if(empty())out1="empty table";
    else{
        out<<row<<std::endl;
        out<<col<<std::endl;
        for(size_t i=0;i<row;i++){
            for(size_t j=0;j<col;j++){
                out<<body[i][j]<<" ";
            }
            out<<std::endl;
        }
    }
    return out1;
}
template<typename T>
const char *table<T>::get_file(std::ifstream& in){
    const char *out(NULL);
    size_t num(0);
    int _row(0),_col(0);
    destroy();
    if(!in.is_open())out="Error open file";
    else{
        in.seekg(0,std::ios::end);
        if(in.tellg()==0)out="empty file";
        else{
            in.seekg(0,std::ios::beg);
            in>>_row;
            if(in.fail())out="Incorrect data";
            in>>_col;
            if(in.fail())out="Incorrect data";
            if(!out)create(_row,_col);
            for(size_t i=0;((i<row)&&(!out));i++){
                for(size_t ii=0;((ii<col)&&(!out));ii++){
                    in>>body[i][ii];
                    if(in.fail()){
                        out="Incorrect data";
                        num=0;
                    }
                    else num++;
                }
            }
            if((out)||(num!=_row*_col))destroy();
        }
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

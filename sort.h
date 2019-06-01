#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
template<typename T>
const char *sort(table<T> &buff){
    const char *out(NULL);
    if(buff.empty())out="Empty table";
    else{
        T buff_value;
        T *key=new T[buff.size_c()];
        for(size_t i=0;i<buff.size_c();i++)key[i]=0;
        for(size_t i=0;i<buff.size_r();i++){
            for(size_t ii=0;ii<buff.size_c();ii++){
                buff.get(i,ii,buff_value);
                if(buff_value<0)key[ii]++;
            }
        }
        size_t buff_idx(0);
        T *tmp_col = new T[buff.size_c()];
        for(size_t i=0;i<buff.size_c()-1;i++){
            buff_idx=i;
            buff_value=key[i];
            for(size_t idx=0;idx<buff.size_r();idx++){
                    buff.get(idx,i,buff_value);
                    tmp_col[idx]=buff_value;
            }
            for(size_t ii=i+1;ii<buff.size_c();ii++){
                if(key[ii]<key[buff_idx]){
                    buff_idx=ii;
                }
            }
            buff_value=key[i];
            for(size_t idx=0;idx<buff.size_r();idx++){
                    buff.get(idx,i,buff_value);
                    tmp_col[idx]=buff_value;
            }
            key[i]=key[buff_idx];
            for(size_t idx=0;idx<buff.size_r();idx++){
                    buff.get(idx,buff_idx,buff_value);
                    buff.set(idx,i,buff_value);
            }
            key[buff_idx]=buff_value;
            for(size_t idx=0;idx<buff.size_r();idx++){
                buff.set(idx,buff_idx,tmp_col[idx]);
            }
           // std::cout<<key[i]<<" ";
        }
        //std::cout<<std::endl;
        //for(size_t i=0;i<buff.col;i++)std::cout<<key[i]<<" ";
    }
    return out;
}

#endif // SORT_H_INCLUDED

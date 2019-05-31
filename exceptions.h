#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED
#include <iostream>
class exceptions{
private:
    const char *messages;
public:
    exceptions():messages(NULL){};
    exceptions(const char* _messages):messages(_messages){
         std::cout<<messages<<std::endl;
    }
};


#endif // EXCEPTIONS_H_INCLUDED

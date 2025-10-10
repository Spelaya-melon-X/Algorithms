#include <unistd.h>
#include <iostream>


int main(int argc ,char ** argv ){
    char** arg = argv;
    for ( ; *arg!= nullptr ; ++arg) {
        std::cout << "ARG: " << *arg << std::endl;
    }

    ++arg; 
    for (;*arg != nullptr ; ++arg) {
        std::cout << "ENV: " << *arg << std::endl;
    }


};
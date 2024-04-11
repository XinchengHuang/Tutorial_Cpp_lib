#include <iostream>
#include <cstdlib>
#include "../include/demo.hpp"

enum computetype {add = 1, mul, sub, divs};

int main(int argc, char *argv[])
{   
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "<computetype: 1 for add, 2 for multiply, 3 for subtract, 4 for divise>" << std::endl;
        return 1;
    }
        
    int a, b, num;
    
    do{
        std::cout << "input two integer, use space to seperate them..." << std::endl;
        std::cin >> a >> b;
        if(std::atoi(argv[1]) == add){
            int2ascii(num = Add(a, b));
            break;
        }
        
        else if(std::atoi(argv[1]) == mul){
            int2ascii(num = Multiply(a, b));
            break;
        }
            
        else if(std::atoi(argv[1]) == sub){
            int2ascii(num = Subtract(a, b));
            break;
        }
            
        else if(std::atoi(argv[1]) == divs){
            int2ascii(num = Divise(a, b));
            break;
        }
            
        else{
            std::cerr << "Error: " << std::atoi(argv[1]) << "out of range!" << std::endl;
            return 2;
        }
    }while(a > 127 || b > 127);

    std::cout << "Done!" << std::endl;
    return 0;
}
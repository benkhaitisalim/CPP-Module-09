#include "RPN.hpp"

int main(int ac , char **av)
{
    if(ac != 2)
    {
        std::cout << "Error : argument is not 2" << std::endl;
    }
    else 
    {
        RPN rpn;
        rpn.calculation(av[1]);
    }
    return 0;
}
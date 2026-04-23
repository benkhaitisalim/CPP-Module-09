#include "RPN.hpp"


RPN::RPN(){}
RPN::RPN(const RPN &other):_container(other._container){}
RPN &RPN::operator=(const RPN &other)
{
    if(this != &other)
    {
        _container = other._container;
    }
    return *this;
}
RPN::~RPN(){}


void RPN::calculation(std::string s)
{
    for(size_t i = 0; i < s.size();i++)
    {
        char c = s[i];
        if(isspace(c))
        {
            continue;
        }
        if(isdigit(c))
        {
            this->_container.push(c - '0');
        }
        else if(c == '+' || c == '-' || c == '/' || c == '*')
        {
            if(this->_container.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }
            int rhs = this->_container.top(); this->_container.pop();
            int lhs = this->_container.top(); this->_container.pop();
            if(c == '+')
            {
                this->_container.push(lhs + rhs);
            }
            else if(c == '-')
            {
                this->_container.push(lhs - rhs);
            }
            else if(c == '*')
            {
                this->_container.push(lhs * rhs);
            }
            else if(c == '/')
            {
                if(rhs == 0)
                    std::cerr << "Error" << std::endl;
                this->_container.push(lhs / rhs);
            }
        }   
        else 
        {
            std::cerr << "Error" << std::endl;
            return ;
        }
    }
    if(this->_container.size() != 1)
    {
        std::cerr << "Error" << std::endl;
    }
    else 
    {
        std::cout << this->_container.top() << std::endl;
    }
}

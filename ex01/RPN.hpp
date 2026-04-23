#include <iostream>
#include <string>
#include <stack>

class RPN {
    private:
    std::stack<int> _container;
    public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();
    void calculation(std::string s);
};
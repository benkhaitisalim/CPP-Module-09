#pragma once
#include <sstream>
#include <sys/time.h>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <string>
#include <ctime>
#include <set>



class PmergeMe
{
    private :
    std::vector<int> _vector;
    std::deque<int> _deque;
    template <typename T>
    void SortWithFordJohnson(T&container);
    template <typename T>
    void BinaryInsert(T& Chain,int value);
    template <typename T>
    void insertPanding(T& mainChain, std::vector<int>& pending);

    public :
    PmergeMe();
    PmergeMe(const PmergeMe&other);
    PmergeMe &operator=(const PmergeMe&other);
    ~PmergeMe();
    void parsing(int ac, char **av);
    void execute();
    void printAfter();
    void PrintBefore();
};
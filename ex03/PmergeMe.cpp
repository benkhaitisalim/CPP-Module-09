#include "PmergeMe.hpp"
   
   
PmergeMe::PmergeMe()
{

}
PmergeMe::PmergeMe(const PmergeMe &other):_vector(other._vector),_deque(other._deque)
{
}
PmergeMe &PmergeMe::operator=(const PmergeMe&other)
{
    if(this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}
PmergeMe::~PmergeMe()
{

}

template <typename T>
void PmergeMe::BinaryInsert(T& Chain,int value)
{
    typename T::iterator pos = std::lower_bound(Chain.begin(),Chain.end(),value);
    Chain.insert(pos,value);
}

template <typename T>
std::vector<std::pair<int,int> > makePair(const T& container)
{
    std::vector<std::pair<int,int> > pairs;
    typename T::const_iterator it = container.begin();
    while(it != container.end())
    {
        int a = *it++;
        if(it == container.end())
        {
            break;
        }
        int b = *it++;
        if(a < b)
            pairs.push_back(std::make_pair(a,b));
        else 
            pairs.push_back(std::make_pair(b,a));
    }
    return pairs;
}
std::vector<size_t> jacobsthalSequence(int limit)
{
    std::vector<size_t> seq;
    seq.push_back(0);
    seq.push_back(1);
    while(true)
    {
        int n = seq.size();
        int next = seq[n - 1] + 2 * seq[n - 2];
        if(next >= limit)
        {
            break;
        }
        seq.push_back(next);
    }
    return seq;
}

template <typename T>
void PmergeMe::insertPanding(T& mainChain, std::vector<int>& pending)
{
    std::vector<size_t> order = jacobsthalSequence(pending.size());
    std::vector<bool> inserted(pending.size(),false);
    for(size_t i = 0; i < order.size(); i++)
    {
        size_t idx = order[i];
        if(idx < pending.size() && !inserted[idx])
        {
            BinaryInsert(mainChain,pending[idx]);
            inserted[idx] = true;
        }
    }
    for(size_t i= 0; i < pending.size();i++)
    {
        if(!inserted[i])
        {
            BinaryInsert(mainChain,pending[i]);
        }
    }

}
template <typename T>
void PmergeMe::SortWithFordJohnson(T&container)
{
    if(container.size() <= 1)
        return;
    int straggler;
    bool hasStraggler = container.size() % 2;
    if(hasStraggler)
    {
        straggler = container.back();
        container.pop_back();
    }
    std::vector<std::pair<int,int> > pairs = makePair(container);
    
    T mainChain;
    std::vector<int> pending;
    for(size_t i = 0; i < pairs.size();i++)
    {
        pending.push_back(pairs[i].first);
        mainChain.push_back(pairs[i].second);
    }
    SortWithFordJohnson(mainChain);
    insertPanding(mainChain, pending);
    if(hasStraggler)
    {
        BinaryInsert(mainChain,straggler);
    }
    container = mainChain;
}
void PmergeMe::printAfter()
{
    std::cout << "After:    ";
    for(size_t i = 0; i < _vector.size();i++)
    {
        std::cout << _vector[i];
        if(i < _vector.size() - 1)
        {
            std::cout <<  " ";
        }
    }
    std::cout <<  std::endl;
}

void PmergeMe::PrintBefore()
{
    std::cout << "Before:   ";
    for(size_t i = 0; i < _vector.size();i++)
    {
        std::cout << _vector[i];
        if(i < _vector.size() - 1)
        {
            std::cout <<  " ";
        }
    }
    std::cout <<  std::endl;
}

void PmergeMe::parsing(int ac, char **av)
{
    std::set<int> seen;
    for (int i = 1; i < ac; ++i) 
    {
        std::istringstream iss(av[i]);
        long n;
        if (!(iss >> n) || !iss.eof()) 
        {
            std::cerr << "invalid argument : " << av[i] << std::endl;
            exit(1);

        }
        if (n < 0 || n > 2147483647) 
        {
            std::cerr << "out of range: " << av[i] << std::endl;
            exit(1);

        }
        if (seen.insert(static_cast<int>(n)).second == false)
        {
            std::cerr << "Error: duplicate number: " << av[i] << std::endl;
            exit(1);
        }

        _vector.push_back(static_cast<int>(n));
        _deque.push_back(static_cast<int>(n));
    }
    if (_vector.empty()) 
    {
        std::cerr << "no input provided" << std::endl;
    }
}


void PmergeMe::execute()
{
    PrintBefore();
    struct timeval start__v, end_v;
    gettimeofday(&start__v,NULL);
    SortWithFordJohnson(_vector);
    gettimeofday(&end_v,NULL);

    struct timeval start_d, end_d;
    gettimeofday(&start_d,NULL);
    SortWithFordJohnson(_deque);
    gettimeofday(&end_d,NULL);
    printAfter();

    double elapsed_us_v = ((end_v.tv_sec - start__v.tv_sec) * 1000000.0) + 
                        (end_v.tv_usec - start__v.tv_usec);
    double elapsed_us_d = ((end_d.tv_sec - start_d.tv_sec) * 1000000.0) + 
                        (end_d.tv_usec - start_d.tv_usec);

    std::cout << "Time to process a range of " << _vector.size() 
            << " elements with std::vector : " << elapsed_us_v << " us" << std::endl;
    std::cout << "Time to process a range of " << _deque.size() 
            << " elements with std::deque : " << elapsed_us_d << " us" << std::endl;
}



#include "PmergeMe.hpp"
 
int main(int argc, char** argv) {
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <positive integers...>" << std::endl;
        return 1;
    }
    try
    {
        PmergeMe pm;
        pm.parsing(argc, argv);
        pm.execute();
 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
    return 0;
}
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) 
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) 
{
    if (this != &other) {
        this->_data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::_isValidDate(const std::string& date) const 
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2008 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
}

static std::string trim(const std::string &str) 
{
    size_t start = str.find_first_not_of(" \t");
    if(start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void BitcoinExchange::loadData(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
            std::cerr << "Error: could not open database." << std::endl;
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) 
    {
        size_t delim = line.find(',');
        if (delim != std::string::npos) 
        {
            std::string date = line.substr(0, delim);
            double rate = std::atof(line.substr(delim + 1).c_str());
            _data[date] = rate; 
        }
    }
}

void BitcoinExchange::processInput(const std::string& filename) 
{
    std::ifstream file(filename.c_str());
    if (!file.is_open()) 
            std::cerr << "Error: could not open file." << std::endl;

    std::string line;

    while (std::getline(file, line)) 
    {
        if (line.empty()) 
            continue;

        size_t delim = line.find('|');
        if (delim == std::string::npos) 
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, delim));
        std::string valStr = trim(line.substr(delim + 1));

        if (!_isValidDate(date)) 
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        char* endPtr;
        double amount = std::strtod(valStr.c_str(), &endPtr);
        if (*endPtr != '\0' && !std::isspace(*endPtr)) 
        {
             std::cerr << "Error: bad input => " << valStr << std::endl;
             continue;
        }

        if (amount < 0) 
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (amount > 1000) 
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        std::map<std::string, double>::iterator it = _data.lower_bound(date);

        if (it == _data.end() || it->first != date) 
        {
            if (it == _data.begin()) 
            {
                std::cerr << "Error: date earlier than database => " << date << std::endl;
                continue;
            }
            --it;
        }

        std::cout << date << " => " << amount << " = " << (amount * it->second) << std::endl;
    }
    file.close();
}
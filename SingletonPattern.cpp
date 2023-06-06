/**
 * Singleton Design Pattern is a Creational Design Pattern
 * You can only have a single instance of a class
 * Used in loggers or file systems
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class Logger
{
private:
    Logger() { std::cout << "Logger created" << std::endl; }
    ~Logger()
    {
        delete _my_instance;
        std::cout << "Logger deleted" << std::endl;
    }

    static Logger *_my_instance;

    std::vector<std::string> _logMessages;

public:
    static Logger *getInstance(); // this is a static method because it has to handle static data

    void printLogMessage();
    void addLogMessage(std::string);
};

Logger *Logger::getInstance()
{
    // We need to allocate memory to the Logger where the Logger will stay
    // When we create an object like Logger log = Logger(); we allocate memory on the stack
    // But with singleton, we don't create an object. So we need to allocate memory manually here
    if (_my_instance == nullptr) // i.e. creating the Logger for the first time
    {
        _my_instance = new Logger;
    }

    return _my_instance;
}

Logger *Logger::_my_instance = nullptr; // instantiate the pointer

void Logger::printLogMessage()
{
    std::cout << "Printing the log" << std::endl;
    for (const auto &i : _logMessages)
    {
        std::cout << i << std::endl;
    }
}

void Logger::addLogMessage(std::string message)
{
    _logMessages.push_back(message);
}

int main()
{
    // I use the getInstance() to get an instance of the Logger class
    // next we use the printLogMessage() to access the method in the Logger class
    // Since getInstance() is a static method, we can directly access it in the main without an object
    Logger::getInstance()->addLogMessage("Hello Log1");
    Logger::getInstance()->addLogMessage("and Log2");
    Logger::getInstance()->addLogMessage("coming... Log3");
    Logger::getInstance()->printLogMessage();

    // Note the destructor is not called automatically.
    // Hence we need to write a small function that calls the destructor
    // This function needs to be called manually

    return 0;
}
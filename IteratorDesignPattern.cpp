#include <iostream>
#include <vector>

void NormalInterator(std::vector<int> vec)
{
    std::cout << "Normal Iterator" << std::endl;
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        // std::cout << *it << std::endl;
        std::cout << ++(*it) << std::endl; // legal to increment since the iterator is not constant
    }
}

void ConstIterator(std::vector<int> vec)
{
    std::cout << "Const Iterator" << std::endl;
    for (auto it = vec.cbegin(); it != vec.cend(); it++)
    {
        std::cout << *it << std::endl;
        // std::cout << (*it)++ << std::endl;   // illegal since the iterator is const
    }
}

void ReverseIterator(std::vector<int> vec)
{
    std::cout << "Reverse Iterator" << std::endl;
    for (auto it = vec.rbegin(); it != vec.rend(); it++)
    {
        std::cout << *it << std::endl;
    }
}

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};

    NormalInterator(vec);
    ConstIterator(vec);
    ReverseIterator(vec);

    return 0;
}
#include <iostream>
#include <vector>
#include "print_ip.h"


template <typename T>
void print_ip(T&& input)
{
    auto natural = (unsigned)input;
    std::vector <std::string> temp;
    auto it = temp.begin();
    auto mem_size = sizeof(natural);
    decltype(natural) mask{255};
    for (int i=0;i<mem_size;i++)
    {   
        int8_t low_byte{natural & mask};
        temp.emplace(it, std::move(low_byte));
        natural = natural >> 8;
    }
    print_ip(std::move(temp));
}


template <typename T>
void print_ip(const char input[])
{
    std::cout << input << std::endl;
}


// template <typename T>
// void print_ip(T&& input)
// {
//     for(auto it=input.begin();it!=input.end();it++){
//         if (it != input.begin())
//         {
//             std::cout << ".";
//         }
//         std::cout << *it;
//     }
//     std::cout << std::endl;
// }


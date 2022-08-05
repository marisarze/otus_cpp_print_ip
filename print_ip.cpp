#include <iostream>
#include <vector>
#include "print_ip.h"


template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
print_ip(T&& input)
{
    auto natural = (unsigned)input;
    std::vector <decltype(natural)> temp;
    auto it = temp.begin();
    auto mem_size = sizeof(input);
    decltype(natural) mask{255};
    for (int i=0;i<mem_size;i++)
    {   
        temp.insert(temp.begin(), natural & mask);
        natural = natural >> 8;
    }
    
    for(auto it = temp.begin();it != temp.end(); ++it){
        if (it != temp.begin())
        {
            std::cout << ".";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
    //print_ip(temp);
};


template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, T>::type
print_ip(T&& input)
{
    std::cout << input << std::endl;
};


template<class T, class = void>
struct is_vector: std::false_type {};
template<class X>
struct is_vector<std::vector<X> >: std::true_type {};

template<class T, class = void>
struct is_list: std::false_type {};
template<class X>
struct is_list<std::list<X> >: std::true_type {};

template <typename T>
typename std::enable_if<is_vector<T>::value || is_list<T>::value, T>::type
print_ip(T&& input)
{
    for(auto it=input.begin();it!=input.end();it++){
        if (it != input.begin())
        {
            std::cout << ".";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
};


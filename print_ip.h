#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <list>
#include <tuple>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(T&& input)
{
    auto natural = (uint64_t)input;
    std::vector <decltype(natural)> temp;
    int mem_size = sizeof(input);
    auto mask = decltype(natural)(255);
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
}


template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(T&& input)
{
    std::cout << input << std::endl;
}


template<class T, class = void>
struct is_vector: std::false_type {};
template<class X>
struct is_vector<std::vector<X> >: std::true_type {};

template<class T, class = void>
struct is_list: std::false_type {};
template<class X>
struct is_list<std::list<X> >: std::true_type {};

template <typename T>
typename std::enable_if<is_vector<T>::value || is_list<T>::value, void>::type
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
}


template <typename...>
struct is_all_same {
    static constexpr bool value = true;
};

template <typename A, typename B, typename... OTHER>
struct is_all_same <A, B, OTHER...>{
    static constexpr bool value =
        std::is_same<A, B>::value && is_all_same<B, OTHER...>::value;
};


template<typename>
struct is_tuple: std::false_type {};
template<typename... Types>
struct is_tuple<std::tuple<Types...>>: std::true_type {};


template<typename... Types>
struct is_uniform_tuple: std::false_type {};
template<typename... Types>
struct is_uniform_tuple<std::tuple<Types...>>: std::true_type {
    static constexpr bool value = is_all_same<Types...>::value;
};


template <typename T, std::size_t I>
struct utility_struct
{
    static constexpr void fill_content(const T& input, std::string& content){
        content = "."+std::to_string(std::get<I>(input)) + content;
        utility_struct<T, I-1>::fill_content(input, content);
    };
};


template <typename T>
struct utility_struct<T, 0>
{
    static constexpr void fill_content(const T& input, std::string& content){
        content = std::to_string(std::get<0>(input)) + content;
    };
};




template <typename T>
typename std::enable_if<is_uniform_tuple<T>::value, void>::type
print_ip(T&& input)
{
    std::string content = "\n";
    utility_struct<T, (std::tuple_size<T>::value)-1>::fill_content(input, content);
    std::cout << content;
}
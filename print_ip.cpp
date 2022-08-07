#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <list>
#include <tuple>
#include "version.h"


/**
 * @file print_ip.cpp
 * @author marisarze (you@domain.com)
 * @brief functions for printing ip
 * @version PROJECT_VERSION_PATCH
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */




/**
 * @brief the function of printing ip addresses implemented through SFINAE, presented as an integral (long int, int, et. al.) at the input
 * 
 * @tparam T parameter can be omitted, T is integral type
 * @param input intgral type parameter
 * @return void type 
 */
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


/**
 * @brief function of printing ip addresses implemented through SFINAE, presented as std::string
 * 
 * @tparam T parameter can be omitted, it is assumed that the current function is working only if T is an std::string
 * @param input assumed it is std::string parameter
 * @return void type 
 */
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(T&& input)
{
    std::cout << input << std::endl;
}


/**
 * @brief helper structure for type checking as a vector in templates (extended structure)
 * * this structure has a bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to vector type
 * @tparam T abstract parameter for extended false_type structure
 * @tparam class dummy template parameter for extended specialization
 */
template<class T, class = void>
struct is_vector: std::false_type {};


/**
 * @brief helper structure for type checking as a vector in templates (reduced structure)
 * * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to vector type
 * @tparam X reducable to std::vector<X> parameter
 */
template<class X>
struct is_vector<std::vector<X> >: std::true_type {};


/**
 * @brief helper structure for type checking as a list in templates (extended structure)
 * * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to list type
 * @tparam T abstract parameter for extended false_type structure
 * @tparam class dummy template parameter for extended specialization
 */
template<class T, class = void>
struct is_list: std::false_type {};


/**
 * @brief helper structure for type checking as a list in templates (reduced structure)
 * * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to list type
 * @tparam X reducable to std::list<X> parameter
 */
template<class X>
struct is_list<std::list<X> >: std::true_type {};


/**
 * @brief the function of printing ip addresses implemented through SFINAE, presented as std::list or std::vector container
 * 
 * @tparam T parameter can be omitted, T is std::list or std::vector container
 * @param input std::list or std::vector container
 * @return void type 
 */
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


/**
 * @brief helper structure for checking the same type in template input (partial specialization)
 * 
 * @tparam template parameter is empty 
 */
template <typename...>
struct is_all_same {
    static constexpr bool value = true;
};


/**
 * @brief helper structure for checking the same type in template input (common specialization)
 * 
 * @tparam A first template parameter
 * @tparam B second template parameter
 * @tparam OTHER other pack parameter
 */
template <typename A, typename B, typename... OTHER>
struct is_all_same <A, B, OTHER...>{
    static constexpr bool value =
        std::is_same<A, B>::value && is_all_same<B, OTHER...>::value;
};


/**
 * @brief helper structure for type checking as a tuple in templates (common variant)
 * * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to tuple type
 * @tparam template parameter is empty 
 */
template<typename>
struct is_tuple: std::false_type {};


/**
 * @brief helper structure for type checking as a tuple in templates (reduced variant)
 * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to tuple type
 * 
 * @tparam Types parameter pack for creating tuple
 */
template<typename... Types>
struct is_tuple<std::tuple<Types...>>: std::true_type {};


/**
 * @brief helper structure for type checking as a uniform tuple (common variant)
 * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to uniform tuple type (all template parameters is same)
 * 
 * @tparam template parameter is empty 
 */
template<typename...>
struct is_uniform_tuple: std::false_type {};


/**
 * @brief helper structure for type checking as a uniform tuple (partial variant)
 * this structure has bool member attribute "value", which stores information about 
 * whether the template parameter of this structure belongs to uniform tuple type (all template parameters is same)
 * 
 * @tparam Types 
 */
template<typename... Types>
struct is_uniform_tuple<std::tuple<Types...>>: std::true_type {
    static constexpr bool value = is_all_same<Types...>::value;
};



/**
 * @brief auxiliary recursive structure to combine the inside of the structure into one line (common variant)
 * 
 * @tparam T type of input tuple
 * @tparam I tuple element index
 */
template <typename T, std::size_t I>
struct utility_struct
{
    /**
     * @brief main member function to fill the print string
     * Elements are combined through the delimiter "."
     * 
     * @param input considered tuple for printing 
     * @param content target string
     */
    static void fill_content(T&& input, std::string& content){
        content = "."+std::to_string(std::get<I>(input)) + content;
        utility_struct<T, I-1>::fill_content(std::forward<T>(input), content);
    };
};


/**
 * @brief auxiliary recursive structure to combine the inside of the structure into one line (partial version)
 * 
 * @tparam T type of input tuple
 */
template <typename T>
struct utility_struct<T, 0>
{
    /**
     * @brief main member function to fill the print string
     * Elements are combined through the delimiter "."
     * 
     * @param input considered tuple for printing 
     * @param content target string
     */
    static void fill_content(T&& input, std::string& content){
        content = std::to_string(std::get<0>(input)) + content;
    };
};


/**
 * @brief the function of printing ip addresses implemented through SFINAE, presented as uniform tuple
 * (identical type elements) 
 * 
 * @tparam T type of input tuple
 * @param input considered tuple for printing 
 * @return void
 */
template <typename T>
typename std::enable_if<is_uniform_tuple<T>::value, void>::type
print_ip(T&& input)
{
    std::string content = "\n";
    utility_struct<T, (std::tuple_size<T>::value)-1>::fill_content(std::forward<T>(input), content);
    std::cout << content;
}
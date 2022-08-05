#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <list>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
print_ip(T&& input);


template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, T>::type
print_ip(T&& input);


template <typename T>
typename std::enable_if<is_vector<T>::value || is_list<T>::value, T>::type
print_ip(T&& input);

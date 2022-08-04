#pragma once
#include <string>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type 
print_ip(T&& input)


template <typename T>
void print_ip(T&& input)


template <typename T>
void print_ip(T&& input);

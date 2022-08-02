#include "../print_ip.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <string>

TEST(TestSimple, TestGetIpPool){

    std::stringstream buffer;
    auto backup = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    print_ip( int8_t{-1} );
    print_ip( int16_t{0} );
    print_ip( int32_t{2130706433} );
    print_ip( int64_t{8875824491850138409} );
    print_ip( std::string{"Hello, World!"} );
    print_ip( std::vector<int>{100, 200, 300, 400} );
    print_ip( std::list<short>{400, 300, 200, 100} );
    print_ip( std::make_tuple(123, 456, 789, 0) ); 

    std::string expected{
        "255\n
        0.0\n
        127.0.0.1\n
        123.45.67.89.101.112.131.41\n
        Hello, World!\n
        100.200.300.400\n
        400.300.200.100\n
        123.456.789.0\n"
    };

    auto result = buffer.str();
    std::cout.rdbuf(backup);
    EXPECT_EQ(result, expected);
}

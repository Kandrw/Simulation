#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <iostream>

struct dec_info;


class Output
{
public:
    static dec_info *head, *end;
    static int size_dec;
    int len_out = 10;
    static int mode; // 0 - console, 1 - debag widget, 2 - 0 and 1 mode
public:

    static void initialization();
    static void cout(std::string input);
    static std::string get_buffer();
    static std::string get_and_delete_dec();
    static int free_dec(int count);
};





struct dec_info{
    dec_info *next, *prev;
    std::string info;
};


#endif // OUTPUT_HPP

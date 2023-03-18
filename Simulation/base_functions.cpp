#include "base_functions.hpp"

#include <cmath>
#include <iostream>





//прибавить к числу процент от этого числа
int add_percentage(int number, int percent){
    int minus = 1;
    if(number < 0){
        minus = -1;
        number *= -1;
    }
    double per_1 = (double)number / 100;
    return (minus * number) + ((double)percent * per_1);
}
int distance_points(int x1, int y1, int x2, int y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}


std::string random_color_16_str(){
    std::string color = "#";
    int pos;
    for(int i = 0; i < 6; ++i){
        pos = rand() % 16;
        if(pos > 9){
            switch (pos)
            {
            case 10:
                color += "A";
                break;
            case 11:
                color += "B";
                break;
            case 12:
                color += "C";
                break;
            case 13:
                color += "D";
                break;
            case 14:
                color += "E";
                break;
            case 15:
                color += "F";
                break;
            default:
                break;
            }
        }
        else{
            color += std::to_string(pos);
        }
    }
    std::cout<<"color = "<<color<<std::endl;
    return color;
}




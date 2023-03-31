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


double distance_points_lat_lon(double lat1, double lon1, double lat2, double lon2, double R){
    double sin1=sin( (lat1-lat2) / 2.0 );
    double sin2=sin( (lon1-lon2) / 2.0 );
    return 2.0 * R * asin( sqrt( sin1 * sin1 + sin2 * sin2 * cos(lat1) * cos(lat2) ) );
}

double xy_to_lon(double x, double y){
    return atan2(x, y);
}
double zR_to_lat(double z, double R){
    return asin(z / R);
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




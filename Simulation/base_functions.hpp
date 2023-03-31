#ifndef BASE_FUNCTIONS_HPP
#define BASE_FUNCTIONS_HPP

#include <iostream>

int add_percentage(int number, int percent);
int distance_points(int x1, int y1, int x2, int y2);
std::string random_color_16_str();
double distance_points_lat_lon(double lat1, double lon1, double lat2, double lon2, double R = 6371.0);


#endif // BASE_FUNCTIONS_HPP

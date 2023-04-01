#include "Coordinates.hpp"

#include <cmath>

//--------------------------------------

double Coordinates::R = 6371.0;

Coordinates::Coordinates(int x, int y) : x(x), y(y)
{
    z = 0;
    lat = 0.0;
    lon = atan2((double)x, (double)y);

}
Coordinates::Coordinates(int x, int y, int z) : x(x), y(y), z(z)
{
    lon = atan2((double)x, (double)y);
    lat = asin((double)z / R);
}
// Не доделана
Coordinates::Coordinates(double lat, double lon){
    this->lat = lat;
    this->lon = lon;
    x = R * cos(lat) * cos(lon);
    y = R * cos(lat) * sin(lon);
    z = R * sin(lat);
}
//Доделать
Coordinates::~Coordinates(){
    //delete this;

}
int Coordinates::get_x(){
    return x;
}
int Coordinates::get_y(){
    return y;
}
int Coordinates::get_z(){
    return z;
}
void Coordinates::set_x(int x){
    this->x = x;
    lon = atan2((double)x, (double)y);
}
void Coordinates::set_y(int y){
    this->y = y;
    lon = atan2((double)x, (double)y);
}
void Coordinates::set_z(int z){
    this->z = z;
    lat = asin((double)this->z / R);
}
double Coordinates::get_lat(){
    return lat;
}
double Coordinates::get_lon(){
    return lon;
}
void Coordinates::set_lat(double lat){
    this->lat = lat;
    z = R * sin(this->lat);
}
void Coordinates::set_lon(double lon){
    this->lon = lon;
    x = R * cos(this->lat) * cos(this->lon);
    y = R * cos(this->lat) * sin(this->lon);
}



//-----------------------------------------

Point_xy::Point_xy(int x, int y){
    this->x = x;
    this->y = y;
}
Point_xy::~Point_xy(){

}
int Point_xy::get_x(){
    return x;
}
int Point_xy::get_y(){
    return y;
}
void Point_xy::set_x(int x){
    this->x = x;
}
void Point_xy::set_y(int y){
    this->y = y;
}

//---------------------------
Point_xyz::Point_xyz(double x, double y, double z) : x(x), y(y), z(z){}

Point_xyz::~Point_xyz(){}
double Point_xyz::get_x(){
    return x;
}
double Point_xyz::get_y(){
    return y;
}
double Point_xyz::get_z(){
    return z;
}
void Point_xyz::set_x(double x){
    this->x = x;
}
void Point_xyz::set_y(double y){
    this->y = y;
}
void Point_xyz::set_z(double z){
    this->z = z;
}


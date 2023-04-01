#ifndef COORDINATES_HPP
#define COORDINATES_HPP



class Coordinates{
public:
    Coordinates(int x, int y);
    Coordinates(int x, int y, int z);
    Coordinates(double lat, double lon);

    ~Coordinates();
    int get_x();
    int get_y();
    int get_z();

    void set_x(int x);
    void set_y(int y);
    void set_z(int z);
    double get_lat();
    double get_lon();

    void set_lat(double lat);
    void set_lon(double lon);



private:
    int x, y, z;
    double lat, lon;
    //double R = 6371.0
    static double R;
    //static double scale_lon;

};
//---------------------

class Point_xy{
private:
    int x, y;
public:
    Point_xy(int x, int y);
    ~Point_xy();
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
};

//--------------------
// Не используется
class Point_xyz{
private:
    double x, y, z;
public:
    Point_xyz(double x, double y, double z);
    ~Point_xyz();
    double get_x();
    double get_y();
    double get_z();
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
};

#endif // COORDINATES_HPP

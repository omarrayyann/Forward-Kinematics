//
//  Point.h
//  Kin
//
//  Created by Omar Rayyan on 03/12/2021.
//

#ifndef Point_h
#define Point_h


class Point{
private:
    double x, y;
public:
    /* Constructors */
    // Default Constructor
    Point(){
        x = 0;
        y = 0;
    }
    // Non-Defult Constructor
    Point(double xNew, double yNew){
        x = xNew;
        y = yNew;
    }
    /* Getters */
    // X Getter
    double getX(){
        return x;
    }
    // Y Getter
    double getY(){
        return y;
    }
    // Coordinate Getter
    string getCoordinate(){
        string coordinate = "(" + to_string(x) + ", " + to_string(y) + ")";
        return coordinate;
    }
    /* Setters */
    // X Setter
    void setX(double xNew){
        x = xNew;
    }
    // Y Setter
    void setY(double yNew){
        y = yNew;
    }
    /* Functions */
    // Print Point Info
    void printInfo(){
        cout << "(" << x << ", " << y << ")";
    }
    // Distance from Origin
    double distanceFromOrigin(){
        return sqrt(pow(x, 2)+pow(y, 2));
    }
};

#endif /* Point_h */

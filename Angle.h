//
//  Angle.h
//  Kin
//
//  Created by Omar Rayyan on 03/12/2021.
//

#ifndef Angle_h
#define Angle_h


class Angle{
private:
    /* Variables Declaration */
    // Double Declaration
    double angle;
public:
    /* Constructors */
    // default constructor
    Angle(){
        angle = 0;
    }
    // non-defult constructor
    Angle(double a){
        angle = a;
    }
    /* Getters */
    // Get Angle
    double getAngle(){
        return angle;
    }
    /* Setters */
    // Set Angle
    void setAngle(double a){
        angle = a;
    }
    /* Functions */
    // Trigonometric Values
    // get Sine of Angle
    double getSin(){
        return  sin(angle);
    }
    // get Cosine of Angle
    double getCos(){
        return cos(angle);
    }
    // get Tangent of Angle
    double getTan(){
        return tan(angle);
    }
};

#endif /* Angle_h */

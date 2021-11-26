// Assignment 4

#include <iostream>
#include <cmath>

#define PI 3.14159265


using namespace std;


class Point;
class Robot;
class Segment;

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
    double disatnceFromOrigin(){
        return sqrt(pow(x, 2)+pow(y, 2));
    }
};

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
        return sin(angle*PI/180);
    }
    // get Cosine of Angle
    double getCos(){
        return cos(angle*PI/180);
    }
    // get Tangent of Angle
    double getTan(){
        return tan(angle);
    }
};

class Segment{
private:
    /* Variables Declaration */
    // Boolean Declaration
    bool rootSegment = false;
    // Segment Declaration
    Segment *parentSegment;
    // Points Declaration
    Point startPoint, endPoint;
    // Doubles Declaration
    Angle angleRelativeToParentSegment, angleOfElevation;
    // Doubles Declaration
    double length;
public:
    /* Constructors */
    // default constructor
    Segment(){
        startPoint = Point(0, 0);
        length = 0;
        angleRelativeToParentSegment = 0;
        angleOfElevation = 0;
    }
    /* non-defult constructors */
    // has a parent
    Segment(Segment *parent, double l, Angle a){
        rootSegment = false;
        startPoint = parent->getEndPoint();
        length = l;
        angleRelativeToParentSegment = a;
        rootSegment = false;
        parentSegment = parent;
        updateAngleOfElevation();
        updateEndPoint();
        
    }
    // no parent (root)
    Segment(Point start, double l, Angle a){
        rootSegment = true;
        startPoint = start;
        length = l;
        angleRelativeToParentSegment = a;
        angleOfElevation = a;
        updateEndPoint();
    }
    /* Getters */
    // Get Start Point
    Point getStartPoint(){
         return startPoint;
    }
    // Get End Point
    Point getEndPoint(){
         return endPoint;
    }
    // Get Length
    double getLength(){
        return length;
    }
    // Get Angle Relative to Parent Segment
    Angle getAngleRelativeToParentSegment(){
        return angleRelativeToParentSegment;
    }
    // Get Angle of Elevation
    Angle getAngleOfElevation(){
        return angleOfElevation;
    }
    // Get ParentSegment
    Segment getParentSegment(){
        return *parentSegment;
    }
    /* Setters */
    // Set Start Point
    void setStartPoint(Point point){
        startPoint = point;
        updateAngleOfElevation();
        updateEndPoint();
    }
    // Set Length
    void setLength(double l){
        length = l;
        updateAngleOfElevation();
        updateEndPoint();
    }
    // Set Angle
    void setAngleRelativeToParentSegment(Angle a){
        angleRelativeToParentSegment = a;
        updateAngleOfElevation();
        updateEndPoint();
    }
    // Set Parent Segment
    void setParentSegment(Segment parent){
        *parentSegment = parent;
    }
    /* Functions */
    // Print Segment Info
    void printInfo(){
        cout << "Starting Point: " << startPoint.getCoordinate() << endl;
        cout << "Ending Point: " << endPoint.getCoordinate() << endl;
        cout << "Angle Relative to Parent Segment: " << angleRelativeToParentSegment.getAngle() << endl;
        cout << "Angle of Elevation: " << angleOfElevation.getAngle() << endl;
        cout << "Length : " << length << endl;
        cout << "Disatnce of Start Point from Origin : " << startPoint.disatnceFromOrigin() << endl;
        cout << "Disatnce of End Point from Origin : " << endPoint.disatnceFromOrigin() << endl;
    }
    // Update Both Angle of Elevation and End Point
    void updateSegment(){
        updateAngleOfElevation();
        updateEndPoint();
    }
    // Update Angle of Elevation
    void updateAngleOfElevation(){
    // Getting Angle of Elevation of Parent
    Angle parentAngleOfElevation = parentSegment->getAngleOfElevation();
    // Getting Angle of Elevation of Current Segment
    angleOfElevation.setAngle(parentAngleOfElevation.getAngle() - 180 + angleRelativeToParentSegment.getAngle());
    }
    
    // Update End Point
    void updateEndPoint(){
        endPoint.setX(startPoint.getX() + length*angleOfElevation.getCos());
        endPoint.setY(startPoint.getY() + length*angleOfElevation.getSin());
    }

    
    
};


class Robot{
    
private:
    Segment *segments = new Segment[0];
    int numberOfSegments = 0;
public:
    /* Functions */
    // Add Segment
    void addRootSegment(Point start, double l, Angle a){
        numberOfSegments++;
        Segment *tempSegments = new Segment[numberOfSegments];
        for(int i = 0; i < numberOfSegments-1; i++){
            tempSegments[i] = segments[i];
        }
        Segment *segment;
        if (numberOfSegments>1) {
             segment = new Segment(&segments[numberOfSegments-2], l, a);
        }
        else{
            segment = new Segment(start, l, a);
        }
        tempSegments[numberOfSegments-1] = *segment;
        delete [] segments;
        segments = tempSegments;
    }
    
    void addSegment(double l, Angle a){
        numberOfSegments++;
        Segment *tempSegments = new Segment[numberOfSegments];
        for(int i = 0; i < numberOfSegments-1; i++){
            tempSegments[i] = segments[i];
        }
        Segment *segment;
        if (numberOfSegments>1) {
             segment = new Segment(&segments[numberOfSegments-2], l, a);
        }
        else{
            segment = new Segment(Point(0, 0), l, a);
        }
        tempSegments[numberOfSegments-1] = *segment;
        delete [] segments;
        segments = tempSegments;
    }
    // Remove Segment
    void removeSegment(){
        numberOfSegments--;
        Segment *tempSegments = new Segment[numberOfSegments];
        for(int i = 0; i < numberOfSegments; i++){
            tempSegments[i] = segments[i];
        }
        delete [] segments;
        segments = tempSegments;
    }
    void updateAllSegments(){
        
    }
    // Print All Segments
    void print(){
        for(int i = 0; i < numberOfSegments; i++){
            cout << "Segment #" << i+1 << endl;
            segments[i].printInfo();
            cout << endl;
        }
    }
      
    };


int main() {
    Robot robot;
    robot.addSegment(6, Angle(60));
    robot.addSegment(6, Angle(60));
    robot.print();
}

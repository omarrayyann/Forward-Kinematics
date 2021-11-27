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
    double distanceFromOrigin(){
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
    Segment(Segment &parent, double l, Angle a){
        rootSegment = false;
        length = l;
        angleRelativeToParentSegment = a;
        rootSegment = false;
        parentSegment = &parent;
        updateSegment();
    }
    // no parent (root)
    Segment(Point start, double l, Angle a){
        rootSegment = true;
        startPoint = start;
        length = l;
        angleRelativeToParentSegment = a;
        parentSegment = NULL;
        updateSegment();
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
    Segment* getParentSegment(){
        return parentSegment;
    }
    /* Setters */
    // Set Start Point
    void setStartPoint(Point point){
        startPoint = point;
        updateSegment();

    }
    // Set Length
    void setLength(double l){
        length = l;
        updateSegment();

    }
    // Set Angle
    void setAngleRelativeToParentSegment(Angle a){
        angleRelativeToParentSegment = a;
        updateSegment();

    }
    // Set Parent Segment
    void setParentSegment(Segment *parent){
        parentSegment = parent;
    }
    /* Functions */
    // Print Segment Info
    void printInfo(){
        cout << "Starting Point: " << startPoint.getCoordinate() << endl;
        cout << "Ending Point: " << endPoint.getCoordinate() << endl;
        cout << "Angle Relative to Parent Segment: " << angleRelativeToParentSegment.getAngle() << endl;
        cout << "Angle of Elevation: " << angleOfElevation.getAngle() << endl;
        cout << "Length : " << length << endl;
        cout << "Distance of Start Point from Origin : " << startPoint.distanceFromOrigin() << endl;
        cout << "Distance of End Point from Origin : " << endPoint.distanceFromOrigin() << endl;
    }
    // Update Both Angle of Elevation and End Point
    void updateSegment(){
        if (!rootSegment){
            // Getting Angle of Elevationx of Parent
            Segment parent = *parentSegment;
            Angle parentAngleOfElevation = parent.
            getAngleOfElevation();
            // Getting Angle of Elevation of Current Segment
            angleOfElevation.setAngle(parentAngleOfElevation.getAngle() - 180 + angleRelativeToParentSegment.getAngle());
            startPoint = parent.getEndPoint();
            cout << "New Start Point" << startPoint.getCoordinate() << endl;
        }
        else{
            angleOfElevation.setAngle(angleRelativeToParentSegment.getAngle());
        }
        endPoint.setX(startPoint.getX() + length*angleOfElevation.getCos());
        endPoint.setY(startPoint.getY() + length*angleOfElevation.getSin());
    }
  

    
    
};


class Robot{
    
private:
    
    int numberOfSegments = 0;
public:
    Segment *segments = new Segment[0];

    /* Functions */
    // Add Segment
    void addRootSegment(Point start, double l, Angle a){
        numberOfSegments++;
        Segment *tempSegments = new Segment[numberOfSegments];
        for(int i = 0; i < numberOfSegments-1; i++){
            tempSegments[i] = segments[i];
        }
        Segment *segment;
        segment = new Segment(start, l, a);
        tempSegments[numberOfSegments-1] = *segment;
        delete [] segments;
        segments = tempSegments;
    }
    
    void addSegment(double l, Angle a){
        numberOfSegments++;
        Segment *tempSegments = new Segment[numberOfSegments];
        for(int i = 0; i < numberOfSegments-1; i++){
            tempSegments[i] = segments[i];
            if (i!=0){
                tempSegments[i].setParentSegment(&tempSegments[i-1]);
            }
        }
        Segment *segment;
        segment = new Segment(segments[numberOfSegments-2], l, a);
        tempSegments[numberOfSegments-1] = *segment;
        tempSegments[numberOfSegments-1].setParentSegment(&tempSegments[numberOfSegments-2]);
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
    // Change Angle of Segment
    void updateSegmentAngle(int n, Angle angle){
        segments[n].setAngleRelativeToParentSegment(angle);
        for (int i = n; i < numberOfSegments; i++){
            segments[i].updateSegment();
        }
        print();
    }
    // Get Segment
    Segment getSegment(int n){
        if (n<numberOfSegments){
            return segments[n];}
        else{
            return Segment(Point(0,0), 0, Angle(0));
        }
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
    // Get End Point
    Point getEndPoint(){
        return segments[numberOfSegments-1].getEndPoint();}
  
    // get number of segments
    int getNumberOfSegments(){
        return numberOfSegments;}
};












int main() {
    Robot robot;
    
    cout << "Forward Kinematics" << endl;
    while(1){
    cout << endl << "Choose an Option to Proceed:\n1- Add Segment\n2- Delete Segment\n3- Modify a Segment Angle\n4- Modify a Segment Length\n5- Move to Defualt Position\n6- Print End Point\n7- Print Number of Segments\n8- Print Robot" << endl << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            double length;
            double angle;
            if (robot.getNumberOfSegments()>0){
                cout << endl <<"Segment to Add\nLength: ";
                cin >> length;
                cout << "Angle between it and the previous segment: ";
                cin >> angle;
                robot.addSegment(length, Angle(angle));
            }
            else{
                cout << endl << "Parent Segment to Add\nLength: ";
                cin >> length;
                cout << "Angle of Elevation: ";
                cin >> angle;
                robot.addRootSegment(Point(0, 0) ,length, Angle(angle));
            }
            cout << "Segment was Added Successfully!" << endl;
            break;
        case 2:
            if (robot.getNumberOfSegments()>0){
                Segment lastSegment = robot.getSegment(robot.getNumberOfSegments()-1);
                cout << endl;
                lastSegment.printInfo();
                cout << endl << "Are you sure you want to delete the last segement with the following properties (y/n) ?";
                string choice;
                cin >> choice;
                if (choice=="Y"||choice=="y"){
                    robot.removeSegment();
                    cout << "Segment was Removed Successfully!" << endl;
                }
            }
            else{
                cout << "No segments to delete" << endl;
            }
            break;
        case 3:
            cout << "Enter the order of the segment you wanna change the angle of: ";
            int choice;
            cin >> choice;
            choice--;
            if (robot.getNumberOfSegments()>choice){
                cout << "Segment #" << choice+1 << " current angle relative to previous segment: " << robot.getSegment(choice).getAngleRelativeToParentSegment().getAngle() << endl;
                cout << "Enter new Angle: ";
                double angle;
                cin >> angle;
                robot.updateSegmentAngle(choice, Angle(angle));
                cout << "Angle was updated successfully" << endl;
            }
            else{
                cout << "Segment " << choice+1 << " does not exist" << endl;
            }
            break;
        case 6:
            if (robot.getNumberOfSegments()>0){
                cout << "End Point: " << robot.getEndPoint().getCoordinate() << endl;}
            else{
                cout << "No segments available" << endl;
            }
            break;
        case 7:
            cout << "Number of Segments: " << robot.getNumberOfSegments() << endl;
            break;
        case 8:
            robot.print();
            break;
        case 9:
            cout << "First segment address: " << &robot.segments[0] << endl;
            cout << "Second segment address: " << &robot.segments[1] << endl;

            break;
        default:
            break;
    }
    }
    
    
    
//
//
//    robot.addSegment(6, Angle(60));
//    robot.addSegment(6, Angle(60));
//    robot.print();
//    cout << robot.getEndPoint().getCoordinate() << endl;
    
    
}

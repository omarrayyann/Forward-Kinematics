//
//  Segment.h
//  Kin
//
//  Created by Omar Rayyan on 03/12/2021.
//

#ifndef Segment_h
#define Segment_h
#define PI 3.14159265

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
        cout << "Angle Relative to Parent Segment: " << angleRelativeToParentSegment.getAngle() << " radians" << endl;
        cout << "Angle of Elevation: " << angleOfElevation.getAngle() << " radians" << endl;
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
            angleOfElevation.setAngle(parentAngleOfElevation.getAngle() - PI + angleRelativeToParentSegment.getAngle());
            startPoint = parent.getEndPoint();
        }
        else{
            angleOfElevation.setAngle(angleRelativeToParentSegment.getAngle());
        }
        endPoint.setX(startPoint.getX() + length*angleOfElevation.getCos());
        endPoint.setY(startPoint.getY() + length*angleOfElevation.getSin());
    }
  

    
    
};

#endif /* Segment_h */

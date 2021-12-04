//
//  Robot.h
//  Kin
//
//  Created by Omar Rayyan on 03/12/2021.
//

#ifndef Robot_h
#define Robot_h


class Robot{
    
private:
    
    int numberOfSegments;
    Segment *segments = new Segment[0];

public:
    // default constructor
    Robot(){
        numberOfSegments = 0;
    }
    // non-default constructor
    Robot(int n){
        numberOfSegments = n;
    }
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
    // Change Angle of Segment
    void updateSegmentAngle(int n, Angle angle){
        segments[n].setAngleRelativeToParentSegment(angle);
        for (int i = n; i < numberOfSegments; i++){
            segments[i].updateSegment();
        }    }
    // Change More than one Segment angl
    void updateSegmentAngleArray(double *angleArray){
        for (int b = 0; b < numberOfSegments; b++){
        segments[b].setAngleRelativeToParentSegment(Angle(angleArray[b]));
        for (int i = b; i < numberOfSegments; i++){
            segments[i].updateSegment();
        }}
        
    }
    // Change Length of Segment
    void updateSegmentLength(int n, double length){
        segments[n].setLength(length);
        for (int i = n; i < numberOfSegments; i++){
            segments[i].updateSegment();
        }
    }
    // Get Segment
    Segment getSegment(int n){
        if (n<numberOfSegments){
            return segments[n];}
        else{
            return Segment(Point(0,0), 0, Angle(0));
        }
    }
    // Move the robot segmnets to the default position
    void moveToDefaultPosition(){
        for (int i = 0; i < numberOfSegments; i++){
            if (i==0){
                segments[i].setAngleRelativeToParentSegment(0);}
            else{
                segments[i].setAngleRelativeToParentSegment(PI);}
            segments[i].updateSegment();
        }
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

#endif /* Robot_h */

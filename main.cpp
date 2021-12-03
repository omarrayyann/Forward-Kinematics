// Assignment 4

#include <iostream>
#include <cmath>
#include <string>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "Point.h"
#include "Angle.h"
#include "Segment.h"
#include "Robot.h"

#define PI 3.14159265

using namespace std;

// Generate Image of current Pose and opens the image
void generateImage(Robot robot){
    
    vector<double> y {0};
    vector<double> x {0};
    
    // for looping to plot all the robot points
    for(int i = 0; i < robot.getNumberOfSegments(); i++){
    
        Segment currentSegment = robot.getSegment(i);
        cout << currentSegment.getEndPoint().getCoordinate() << endl;

        x.push_back(currentSegment.getEndPoint().getX());
        y.push_back(currentSegment.getEndPoint().getY());
     

    }
    
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    
    DrawScatterPlot(imageRef, 600, 400, &x, &y);
    
    vector<double> *pngData = ConvertToPNG(imageRef->image);
    
    WriteToFile(pngData, "plot.png");
    
    system ("open plot.png");

    DeleteImage(imageRef->image);
}


int main() {

    
    Robot robot;
    cout << "Forward Kinematics\n\nRobot was created successfully" << endl;
    while(1){
        cout << endl << "1- Add Segment\n2- Delete Segment\n3- Modify a Segment\n4- Move to Default Position\n5- Print End Point\n6- Print Number of Segments\n7- Print Robot\n\nChoose an Option to Proceed: " ;
    string choice;
    int segN;
    cin >> choice;
        if (choice=="1"){
            double length;
            double angle;
            if (robot.getNumberOfSegments()>0){
                cout << endl <<"Segment to Add\nLength: ";
                cin >> length;
                while (length<=0){
                    cout << "Lenght can't be less than 0, please try again" << endl;
                    cout << endl <<"Length: ";
                    cin >> length;
                }
                cout << "Angle between it and the previous segment (radians): ";
                cin >> angle;
                while (angle<0){
                    cout << "Angle can't be less than, please try again" << endl;
                    cout << endl <<"Angle between it and the previous segment (radians): ";
                    cin >> angle;
                }
                robot.addSegment(length, Angle(angle));
            }
            else{
                cout << endl << "Parent Segment to Add\nLength: ";
                cin >> length;
                cout << "Angle of Elevation (radians): ";
                cin >> angle;
                robot.addRootSegment(Point(0, 0) ,length, Angle(angle));
            }
            cout << "Segment was Added Successfully!" << endl;
        }
        else if (choice=="2"){
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
        }
        else if (choice=="3"){
            cout << "1- Modify the angle of one segment\n2- Modify the angle of multiple segments\n3- Modify the length of one segment\n4- Modify the lenght of multiple segments\n" << endl;
            char choice2;
            cin >> choice2;
            switch (choice2) {
                case '1':
                    cout << "Enter the order of the segment you wanna change the angle of: ";
                    cin >> segN;
                    segN--;
                    if (robot.getNumberOfSegments()>segN){
                        cout << "Segment #" << segN+1 << " current angle relative to previous segment: " << robot.getSegment(segN).getAngleRelativeToParentSegment().getAngle() << endl;
                        cout << "Enter new Angle: ";
                        double angle;
                        cin >> angle;
                        robot.updateSegmentAngle(segN, Angle(angle));
                        cout << "Angle was updated successfully" << endl;
                    }
                    else{
                        cout << "Segment " << segN+1 << " does not exist" << endl;
                    }
                    break;
                case '2':
                   if (robot.getNumberOfSegments()>0){
                        for (int i = 0; i<robot.getNumberOfSegments(); i++){
                        cout << "Segment #" << i+1 << " current angle relative to previous segment: " << robot.getSegment(i).getAngleRelativeToParentSegment().getAngle() << endl;
                        cout << "Enter new Angle: ";
                        double angle;
                        cin >> angle;
                        robot.updateSegmentAngle(i, Angle(angle));
                            cout << "Angle of segment #" << i <<  " was updated successfully to " << angle << " radians" << endl;}
                    }
                    else{
                        cout << "No Segments exist" << endl;
                    }
                    break;
                case '3':
                    cout << "Enter the order of the segment you wanna change the length of: ";
                    cin >> segN;
                    segN--;
                    if (robot.getNumberOfSegments()>segN){
                        cout << "Segment #" << segN+1 << " current length: " << robot.getSegment(segN).getLength() << endl;
                        cout << "Enter new Length: ";
                        double length;
                        cin >> length;
                        robot.updateSegmentLength(segN, length);
                        cout << "Length was updated successfully" << endl;
                    }
                    else{
                        cout << "Segment " << segN+1 << " does not exist" << endl;
                    }
                    break;
                case '4':
                    if (robot.getNumberOfSegments()>0){
                         for (int i = 0; i<robot.getNumberOfSegments(); i++){
                             cout << "Segment #" << i+1 << " current length: " << robot.getSegment(i).getLength() << endl;
                             cout << "Enter new Length: ";
                             double length;
                             cin >> length;
                             robot.updateSegmentLength(i, length);
                             cout << "Angle of length #" << i <<  " was updated successfully" << endl;}                     }
                     else{
                         cout << "No Segments exist" << endl;
                     }
                     break;

                default:
                    break;
            }
        }
        else if (choice=="4"){
            robot.moveToDefaultPosition();
            cout << "Robot segments were moved to teh default position successfully" << endl;}
        else if (choice=="5"){
            if (robot.getNumberOfSegments()>0){
                cout << "End Point: " << robot.getEndPoint().getCoordinate() << endl;}
            else{
                cout << "No segments available" << endl;
            }}
        else if (choice=="6"){
            cout << "Number of Segments: " << robot.getNumberOfSegments() << endl;
        }
        else if (choice=="7"){
            robot.print();
            generateImage(robot);
        }
        
    }
    

    
}

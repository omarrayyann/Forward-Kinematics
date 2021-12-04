# Forward-Kinematics

The objective was to develop a software that can simulate the motion of a multi-degree of freedom kinematic chains that form the structure of a robotic system. The links of the robot were modeled as rigid bodies and its joints are assumed to provide pure rotation or translation. The program enables the user to modify the robot as many times desired to new positions. Moreover, the user will be able to get the end point at any time and display the pose of the robot as a .PNG image.

![icon](https://user-images.githubusercontent.com/77675540/144719750-c5cc6108-fb1c-4576-902f-60502a44844a.png)

***Relevant Information:***

Figure 1: (left) Example of a robot chain with three segments, (right) the parameters of a segment.
The system has the following components:
1. A segment: A segment is a rigid member connecting two joints. As shown in Figure 1(right), a
segment has the following parameters: a starting point (x1 and y1 coordinates), a length, an angle
(different technique may have different references for measuring the angle for a segment, so make
your assumption clear), and an end point (x2 and y2 coordinates). Note that the coordinates of the
end point can be calculated given the start point coordinates, the length, and the angle.
2. A Robot: A robot is comprised of a chain of segments that are connected via joints. The first
segment is called the root as it is connected to the robot base/ground. A robot can have multiple
segments, which is commonly known as the degrees of freedom. The end effector of the robot is
the end point of the last segment (noted as (x,y) in Figure 1-left). In order to determine the position
of the end effector, the position/orientation of all the segments must be determined – which is
usually controlled through the angles of the segments. The forward kinematic analysis involves
calculating the end effector position for a specific set of angles for the segments. The inverse
kinematics analysis involves calculating the angles of all the segments that move the end effector
to a particular position. This assignment will focus on the forward kinematics analysis.

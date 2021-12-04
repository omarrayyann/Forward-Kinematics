# Forward-Kinematics

The objective was to develop a software that can simulate the motion of a multi-degree of freedom kinematic chains that form the structure of a robotic system. The links of the robot were modeled as rigid bodies and its joints are assumed to provide pure rotation or translation. The program enables the user to modify the robot as many times desired to new positions. Moreover, the user will be able to get the end point at any time and display the pose of the robot as a .PNG image.

***Relevant Information:***

A segment: A segment is a rigid member connecting two joints. As shown in Figure 1(right), a segment has the following parameters: a starting point (x1 and y1 coordinates), a length, an angle (relative to the parent angle), and an end point (x2 and y2 coordinates).

A Robot: A robot is comprised of a chain of segments that are connected via joints. The first segment is called the root as it is connected to the robot base/ground and starts from origin (0,0) . A robot can have multiple segments, which is commonly known as the degrees of freedom. The end effector of the robot is the end point of the last segment (noted as (x,y) in Figure 1-left). To determine the position of the end effector, the position/orientation of all the segments will be determined – which is usually controlled through the angles of the segments. The forward kinematic analysis involves calculating the end effector position for a specific set of angles for the segments.
 
 

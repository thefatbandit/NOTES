#include "ros/ros.h"
#include "std_msgs/String.h"
//#include "teb_local_planner/FeedbackMsg.h"
#include "geometry_msgs/PoseArray.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include <bits/stdc++.h>
//#include "nav_msgs/Path.h"

using namespace ros;
using namespace std;

float velocity=0.1;
float omega;

float convert_quaternion_euler(float q3, float q2)
{
    float val=(atan((2*q2*q3)/(1-(2*q2*q2))));
    val=(180*val)/3.14;
    if(q2 >= 0 && val>=0)
        return (3.14*val)/180;
    else if(q2 < 0 && val<0)
        return ((val+360)*3.14)/180;
    else if(q2 >= 0 && val<0)
        return (3.14*(val+180))/180;
    else if(q2 < 0 && val>=0)
        return (3.14*(180+val))/180;
}

float ld_dhundh()
{
    float k,ld;
    k=0.8;
    ld = k*velocity;
    return ld;
}

float find_diff(float thetaf, float thetai)
{
    if((thetaf - thetai)>3.14)
        return ((thetaf - thetai)-6.28);
    if((thetaf - thetai)<-3.14)
        return (6.28 + (thetaf - thetai));
    return (thetaf-thetai);
}


void callback(const geometry_msgs::PoseArray::ConstPtr& current_pose)
{
    //cout<<(*current_pose).poses[0].position.x<<" , "<<(*current_pose).poses[1].position.x<<endl;
    float q2,q3,thetai,p2,p3,ix,iy,fx,fy,thetaf,alpha,kappa;
    float ld,k;
    q2 = (*current_pose).poses[0].orientation.z;
    q3 = (*current_pose).poses[0].orientation.w;
    thetai = convert_quaternion_euler(q3,q2);
    //cout<<(180*theta)/3.14<<"     z= "<< q2 << "   w= "<< q3<<endl;
    ix = (*current_pose).poses[0].position.x;
    iy = (*current_pose).poses[0].position.y;
    ld = ld_find();
    int i=0;
    float diff=0;
    while(diff>=0)
    {
        i++;
        fx=(*current_pose).poses[i].position.x;
        fy=(*current_pose).poses[i].position.y;
        diff = ld - sqrt((fx-ix)*(fx-ix) + (fy-iy)*(fy-iy));
        
    }
    q2 = (*current_pose).poses[i].orientation.z;
    q3 = (*current_pose).poses[i].orientation.w;
    thetaf = convert_quaternion_euler(q3,q2);
    alpha = find_diff(thetaf,thetai);
    kappa = (sin(alpha))/ld;
    cout<<"kappa "<<kappa<<endl;
    omega = kappa*velocity;
    cout<<"OMEGA : "<<omega<<endl;
}  

void vel(const geometry_msgs::Twist::ConstPtr& v)
{
    velocity = (*v).linear.x;
    cout <<"VELOCITY : "<<velocity<<endl;
}

int main(int argc, char **argv)
{
    // init(argc, argv, "listener");
    init(argc, argv, "pp");
    NodeHandle n;
    Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel2", 1000);
    cout<<"1"<<endl;
    geometry_msgs::Twist control;
    Rate loop_rate(10);
        Subscriber sub = n.subscribe("/move_base/TebLocalPlannerROS/teb_poses",1000,callback);
        cout<<"2"<<endl;
        Subscriber sub1 = n.subscribe("/cmd_vel",1000,vel);
        cout<<"3"<<endl;
    while(ok())
    {
        cout<<"4"<<endl;
        control.linear.x = velocity;
        control.linear.y = 0;
        control.linear.z = 0;
        control.angular.z = omega;
        control.angular.x = 0;
        control.angular.y = 0;
        chatter_pub.publish(control);
        spinOnce();
        loop_rate.sleep();

    }
    return 0;
}

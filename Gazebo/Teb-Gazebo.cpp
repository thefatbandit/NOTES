#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "gazebo/ModelState.h"
using namespace ros;
using namespace std;
gazebo::ModelState modelstate;
void callback(const geometry_msgs::Twist &start_twist)
{
    modelstate.twist = (*start_twist);
}

void chal_jaana(const nav_msgs::Odometry::ConstPtr& msg)
{
    modelstate.pose.position.x = msg->pose.pose.position.x;
    modelstate.pose.position.y = msg->pose.pose.position.y;
    modelstate.pose.position.z = msg->pose.pose.position.z;
    modelstate.pose.orientation.x = msg->pose.pose.orientation.x;
    modelstate.pose.orientation.y = msg->pose.pose.orientation.y;
    modelstate.pose.orientation.z = msg->pose.pose.orientation.z;
    modelstate.pose.orientation.w = msg->pose.pose.orientation.w;
}

int main(int argc, char **argv)
{
    init(argc, argv, "listener");
    NodeHandle n;
    ServiceClient client = n.serviceClient<gazebo::SetModelState>("/gazebo/set_model_state");
    gazebo::SetModelState setmodelstate;
    modelstate.model_name = (std::string) "prius";
    modelstate.reference_frame = (std::string) "world";
    Subscriber sub = n.subscribe("cmd_vel", 1000, callback);
    Subscriber sub1 = n.subscribe("base_pose_ground_truth", 1000, chal_jaana);
    setmodelstate.request.model_state = modelstate;
    client.call(setmodelstate);
    spin();
    return 0;
}

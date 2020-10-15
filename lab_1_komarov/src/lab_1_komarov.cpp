#include "ros/ros.h"
#include <iostream>
#include "std_msgs/Int64.h"
#include "std_msgs/Int8.h"
using namespace std;

ros::Publisher g_value_pub;

std_msgs::Int64 fibonacci(std_msgs::Int8 input_number)
{
    __int64_t mas[3] = {0, 1, 1};
    std_msgs::Int64 output_number;
    for(int i = 3; i < input_number.data; i++)
    {
        mas[0] = mas[1];
        mas[1] = mas[2];
        mas[2] = mas[0] + mas[1];
    }
    output_number.data = mas[2];
    return output_number;
}

void recieve(const std_msgs::Int8& input_number)
{
    ROS_INFO("Received: %d", input_number.data);
    if(input_number.data < 1 || input_number.data > 42)
    {
        ROS_WARN("The value is not in the range from 1 to 42");
    }
    else
    {
        std_msgs::Int64 fibonacci_number = fibonacci(input_number);
        ROS_INFO("Fibonacci value: %ld", fibonacci_number.data);
        g_value_pub.publish(fibonacci_number);
    }
    return;
}     
                                                                                                                           
int main(int argc, char **argv)
{
    ROS_INFO("Start lab_1_komarov package");
    
    ros::init(argc, argv, "fibonacci_number");
    ros::NodeHandle n;

    ros::Publisher fibonacci_number_pub = n.advertise<std_msgs::Int8>("/fibonacci_number", 10);
    ros::Subscriber value_sub = n.subscribe("/fibonacci_number", 10, recieve);
    g_value_pub = n.advertise<std_msgs::Int64>("/value", 10);

    ros::Rate loop_rate(1);
    std_msgs::Int8 number;

    while(ros::ok)
    {
        number.data = rand() % 100 + 0;
        fibonacci_number_pub.publish(number);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
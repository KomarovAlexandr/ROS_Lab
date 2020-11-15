#include "ros/ros.h"
#include "lab_2_komarov/GetGreatestCommonDivisor.h"
#include <iostream>

using namespace std;

int get_greatest_common_divisor(int a, int b, int c);


bool server_answer(lab_2_komarov::GetGreatestCommonDivisor::Request &req, 
                    lab_2_komarov::GetGreatestCommonDivisor::Response &resp)
{
    ROS_INFO("request: a = %d, b = %d, c = %d", 
            req.input_numbers[0],
            req.input_numbers[1],
            req.input_numbers[2]);
    resp.greatest_common_divisor = get_greatest_common_divisor(req.input_numbers[0],
                                                                req.input_numbers[1],
                                                                req.input_numbers[2]);
    return true;
}


int main(int argc, char**argv){
    ros::init(argc, argv, "greates_common_divisor_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("array_for_server", server_answer);
    ROS_INFO("Start Server");
    ros::spin();

    return 0;
    
}


int get_greatest_common_divisor(int a, int b, int c)
{
    int divisor = 0;
    for(int i = 1; i <= a; i++)
    {
        if(a % i == 0 && b % i == 0 && c % i == 0)
        {
            divisor = i;
        }
 
    }
    return divisor;
}
#include "ros/ros.h"
#include "lab_2_komarov/GetGreatestCommonDivisor.h"
#include <iostream>

using namespace std;

int main(int argc, char**argv){
    ros::init(argc, argv, "client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<lab_2_komarov::GetGreatestCommonDivisor>("array_for_server");
    lab_2_komarov::GetGreatestCommonDivisor srv;

    srand(static_cast<unsigned int>(time(0)));

    ros::Rate loop_rate(1);

    while(ros::ok())
    {
        int array[3] = {0};
        array[0] = rand();
        array[1] = rand();
        array[2] = rand();

        cout << "a = " << array[0] << "; b = " << array[1] << "; c = " << array[2] << endl;

        for(int i = 0; i < 3; i++){
            srv.request.input_numbers[i] = array[i];
        }

        if(client.call(srv))
        {
            cout << "greates common division = " << srv.response.greatest_common_divisor << endl;
        }
        else
        {
            cout << "fraail" << endl;
            return 0;
        }
        
        loop_rate.sleep();
    }

}
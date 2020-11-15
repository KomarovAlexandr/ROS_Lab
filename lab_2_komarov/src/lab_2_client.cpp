#include "ros/ros.h"
#include "lab_2_komarov/GetGreatestCommonDivisor.h"
#include <iostream>

using namespace std;

int main(int argc, char**argv){
    ros::init(argc, argv, "client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<lab_2_komarov::GetGreatestCommonDivisor>("array_for_server");
    lab_2_komarov::GetGreatestCommonDivisor srv;

    while(ros::ok())
    {
        int array[3] = {0};
        cout << "enter a = ";
        cin >> array[0];
        cout << "enter b = ";
        cin >> array[1];
        cout << "enter c = ";
        cin >> array[2];

        for(int i = 0; i < 3; i++){
            srv.request.input_numbers[i] = array[i];
        }

        if(client.call(srv))
        {
            cout << "greates common division = " << srv.response.greatest_common_divisor << endl;
        }
        else
        {
            cout << "fail" << endl;
            return 0;
        }
    }

}
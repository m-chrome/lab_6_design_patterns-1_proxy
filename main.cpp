#include <iostream>
#include <string>
#include "weather_system.hpp"

using namespace std;
using namespace weathersystem;

int main()
{
    ifstream user_dtb;
    user_dtb.open("user_dtb.txt");
    if (!user_dtb)
    {
        cout << "Can't open file!"<< endl;
        return 1;
    }

    struct
    {
        string name;
        string password;
    } user;

    Actual_Weather session;

    while (user_dtb >> user.name >> user.password)
    {
        session.emplaceUser(user.name, user.password);
    }

    session.showData();
    Weather_system *viewer = new Proxy_Watcher(session);
    cout << endl;
    viewer->showData();
    cout << "Actual Weather" << endl;
    cout << "Для просмотра погоды необходимо авторизоваться в системе." << endl;
    cout << "Ваш логин: ";
    cin >> user.name;
    viewer->requestForecast(user.name);
    bool flag = viewer->identification(user.name);
    cout << flag;

    return 0;
}


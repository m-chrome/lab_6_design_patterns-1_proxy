#include <iostream>
#include <string>
#include "weather_system.hpp"

using namespace std;
using namespace weathersystem;

int main()
{
    // Proxy remake
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

    Proxy_Watcher *viewer = new Proxy_Watcher;

    while (user_dtb >> user.name >> user.password)
    {
        viewer->emplaceUser(user.name, user.password);
    }

    cout << "Actual Weather" << endl;
    cout << "Для просмотра погоды необходимо авторизоваться в системе." << endl;
    cout << "Ваш логин: ";
    cin >> user.name;
    try
    {
        viewer->requestForecast(user.name);
    }
    catch(deny_request)
    {
        cout << "Запрос отклонён." << endl;
    }

    delete viewer;
    return 0;
}


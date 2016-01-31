#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "weather_system.hpp"

using namespace std;

namespace weathersystem
{
    // Реализация методов реальной системы
    Actual_Weather::Actual_Weather()
    {
        log.open("log.txt");
    }

    Actual_Weather::Actual_Weather(string login, string password)
    {
        this->emplaceUser(login, password);
    }

    Actual_Weather::~Actual_Weather()
    {
        dtb.clear();
    }

    void Actual_Weather::emplaceUser(const string& login, const string& password)
    {
        dtb.emplace(login, password);
    }

    bool Actual_Weather::identification(const string& login)
    {
        map <string, string> :: iterator key = dtb.find(login);
        string password;
        if (key != dtb.end())
        {
            cout << "Аутентификация пользователя." << endl;
            cout << "Пользователь: " << login << endl;
            cout << "Пароль: ";
            cin >> password;
            if (password == key->second)
            {
                cout << login << ", вход успешно выполнен!" << endl;
                return 0;
            }
            else
                cout << "Неверный пароль!" << endl;
            return 1;
        }
        else
        {
            cout << "Пользователь отсутствует в базе." << endl;
            return 1;
        }
    }

    // Реализация методов прокси
    bool Proxy_Watcher::identification(const string& login)
    {
        logging(weather->identification(login), login);
        return weather->identification(login);
    }

    void Proxy_Watcher::logging(const bool& idFlag, const string& login)
    {
        if (idFlag == 0)
        {
            (weather->log) << "Пользователь " << login << " получил доступ к прогнозу погоды." << endl;
        }
    }
}


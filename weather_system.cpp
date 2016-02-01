#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "weather_system.hpp"

using namespace std;

namespace weathersystem
{
    // Реализация методов реальной системы
    Actual_Weather::Actual_Weather()
    {
        forecast.open("forecast.txt");
        if (!forecast)
        {
            cout << "Can't open file!"<< endl;
        }
    }

    Actual_Weather::~Actual_Weather()
    {
        dtb.clear();
        forecast.close();
    }

    void Actual_Weather::emplaceUser(const string& login, const string& password)
    {
        dtb.emplace(login, password);
    }

    bool Actual_Weather::identification(const string& login)
    {
        map <string, string> :: iterator key = dtb.find(login);
        if (key != dtb.end())
        {
            string password;
            current.name=login;
            cout << "Аутентификация пользователя." << endl;
            cout << "Пользователь: " << login << endl;
            cout << "Пароль: ";
            cin >> password;
            if (password == key->second)
            {
                current.password=password;
                current.authFlag=0;
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

    void Actual_Weather::showForecast()
    {
        char buff[1000];
        while (forecast.getline(buff, 1000))
        {
            cout << buff << endl;
        }
    }

    // Реализация методов прокси

    Proxy_Watcher::Proxy_Watcher()
    {
        weather = new Actual_Weather();
    }

    // Конструктор копирования уже заполненного объекта
    Proxy_Watcher::Proxy_Watcher(Actual_Weather &obj)
    {
        weather=&obj;
        log.open("log.txt");
    }

    // Деструктор прокси
    Proxy_Watcher::~Proxy_Watcher()
    {
        log.close();
        weather=NULL;
    }

    void Proxy_Watcher::requestForecast(const string& login)
    {
        cout << "Work!" << endl;
        current.name=login;
        current.autFlag=identification(login);
        if (current.autFlag == 0)
        {
            showForecast();
            logging();
        }
        exitSystem();
    }

    bool Proxy_Watcher::identification(const string& login)
    {
        return weather->identification(login);
    }

    void Proxy_Watcher::exitSystem()
    {
        current.name.clear();
        weather->exitSystem();
    }

    void Proxy_Watcher::logging()
    {
        if (current.autFlag == 0)
        {
            log << "Пользователь " << current.name << " получил доступ к прогнозу погоды." << endl;
        }
    }

    void Proxy_Watcher::showForecast()
    {
        weather->showForecast();
    }
}


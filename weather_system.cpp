#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
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
            {
                cout << "Неверный пароль!" << endl;
                return 1;
            }
        }
        else
        {
            throw not_found();
        }
    }

    void Actual_Weather::showForecast()
    {
        char buff[1000];
        cout << endl;
        while (forecast.getline(buff, 1000))
        {
            cout << buff << endl;
        }
        cout << endl;
    }

    // Реализация методов прокси

    Proxy_Watcher::Proxy_Watcher()
    {
        weather = new Actual_Weather();
        //log.open("log.txt", std::ios::app);
    }

    // Конструктор копирования уже заполненного объекта
    Proxy_Watcher::Proxy_Watcher(Actual_Weather &obj)
    {
        weather=&obj;

    }

    // Деструктор прокси
    Proxy_Watcher::~Proxy_Watcher()
    {
        delete weather;
    }

    void Proxy_Watcher::requestForecast(const string& login)
    {
        cout << "Запрос прогноза погоды:" << endl;
        current.name=login;
        try
        {
            current.autFlag=identification(login);
        }
        catch(not_found)
        {
            cout << "Пользователь не найден в базе." << endl;
            throw deny_request();
        }
        if (current.autFlag == 0)
        {
            showForecast();
            logging();
        }
    }

    bool Proxy_Watcher::identification(const string& login)
    {
        return weather->identification(login);
    }

    void Proxy_Watcher::logging()
    {
        log.open("log.txt", std::ios::app);

        if (current.autFlag == 0)
        {
            time_t currentt;
            time(&currentt);
            tm *viewtime = localtime(&currentt);
            log <<  asctime(viewtime) << "Пользователь " << current.name
                 << " получил доступ к прогнозу погоды." << endl<< endl;
        }
        log.close();
    }

    void Proxy_Watcher::showForecast()
    {
        weather->showForecast();
    }

    void Proxy_Watcher::emplaceUser(const string& login, const string& password)
    {
        weather->emplaceUser(login, password);
    }
}


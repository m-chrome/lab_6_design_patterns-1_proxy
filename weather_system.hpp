#ifndef WEATHER_SYSTEM_HPP
#define WEATHER_SYSTEM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace weathersystem
{
    class Weather_system
    {
        public:
            // Базовый интерфейс

            // Добавление нового пользователя в базу данных
            virtual void emplaceUser(const string&, const string&) {}

            // Запрос прогноза погоды по логину пользователя
            virtual void requestForecast(const string&) {}

            // Идентификация пользователя с помощью логина
            virtual bool identification(const string&) {}

            // Выход из системы
            virtual void exitSystem(){}

            // Логгирование
            virtual void logging(){}

            // Показ прогноза погоды
            virtual void showForecast(){}

            virtual void showData(){}
    };

    class Actual_Weather : public Weather_system
    {
        private:
            map <string, string> dtb;
            ifstream forecast;
            struct user
            {
                string name;
                string password;
                bool authFlag;
            } current;

        public:
            Actual_Weather();
            ~Actual_Weather();

            // Добавить пользователя в базу данных
            virtual void emplaceUser(const string& login, const string& password);

            // Идентификация нужного пользователя. При успешной аутентификации
            // возвращает 0, 1 - при всех остальных случаях
            virtual bool identification(const string& login);

            // Показывает авторизованному пользователю прогноз погоды
            virtual void showForecast();

            virtual void showData()
            {
                for (auto &it: dtb)
                     cout << it.first << ' ' << it.second << endl;
            }
    };

    class Proxy_Watcher : public Weather_system
    {
        private:
            Weather_system *weather;
            struct user
            {
                string name;
                bool autFlag;
            } current;

            ofstream log;

        public:
            Proxy_Watcher();
            Proxy_Watcher(Actual_Weather &obj);
            ~Proxy_Watcher();

            virtual void requestForecast(const string& login);
            virtual bool identification(const string& login);
            virtual void exitSystem();
            virtual void logging();
            virtual void showForecast();
    };
}
#endif // WEATHER_SYSTEM_HPP

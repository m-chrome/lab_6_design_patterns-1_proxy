#ifndef WEATHER_SYSTEM_HPP
#define WEATHER_SYSTEM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

namespace weathersystem
{
    class not_found {};
    class wrong_pass {};
    class deny_request {};

    class Actual_Weather
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
            void emplaceUser(const string& login, const string& password);

            // Идентификация нужного пользователя. При успешной аутентификации
            // возвращает 0, при неверной аутентификации - 1
            // кидает ислючение, если пользователь отсутствует
            bool identification(const string& login);

            // Показывает авторизованному пользователю прогноз погоды
            void showForecast();
    };

    class Proxy_Watcher
    {
        private:
            Actual_Weather *weather;
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

            // Методы, которые от Actual_Weather
            void emplaceUser(const string& login, const string& password);
            bool identification(const string& login);
            void showForecast();

            // Свои
            void requestForecast(const string& login);
            void logging();
    };
}
#endif // WEATHER_SYSTEM_HPP

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
            // возвращает 0, 1 - при всех остальных случаях
            bool identification(const string& login);

            // Показывает авторизованному пользователю прогноз погоды
            void showForecast();

            void showData()
            {
                for (auto &it: dtb)
                     cout << it.first << ' ' << it.second << endl;
            }
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

            void requestForecast(const string& login);
            bool identification(const string& login);
            void exitSystem();
            void logging();
            void showForecast();

            // Добавить пользователя в базу данных
            void emplaceUser(const string& login, const string& password);

    };
}
#endif // WEATHER_SYSTEM_HPP

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
            virtual ~Actual_Weather();

            // Добавить пользователя в базу данных
            virtual void emplaceUser(const string& login, const string& password);

            // Идентификация нужного пользователя. При успешной аутентификации
            // возвращает 0, при неверной аутентификации - 1
            // кидает ислючение, если пользователь отсутствует
            virtual bool identification(const string& login);

            // Показывает авторизованному пользователю прогноз погоды
            virtual void showForecast();
    };

    class Proxy_Watcher : public Actual_Weather
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
            virtual ~Proxy_Watcher();

            // Унаследованные
            virtual void emplaceUser(const string& login, const string& password);
            virtual bool identification(const string& login);
            virtual void showForecast();

            // Свои
            void requestForecast(const string& login);
            void logging();


    };
}
#endif // WEATHER_SYSTEM_HPP

#ifndef WEATHER_SYSTEM_HPP
#define WEATHER_SYSTEM_HPP

#include <fstream>
#include <string>
#include <map>

using namespace std;

namespace weathersystem
{
    class Weather_system
    {
        public:
            virtual bool identification(string)=0;
            virtual void emplaceUser(string, string)=0;
            virtual void logging(bool, string)=0;
    };

    class Actual_Weather : public Weather_system
    {
        private:
            // Контейнер для заполнения данными пользователя
            // Ключ - имя пользователя
            // Значение - пароль
            // Для ускорения поиска и ассоциаций
            map <string, string> dtb;

        public:
            ofstream log;

            Actual_Weather();
            Actual_Weather(string login, string password);
            ~Actual_Weather();

            // Интерфейс
            // Добавление нового пользователя в базу данных
            // По умолчанию, входные данных подходят стандартам логина и пароля
            virtual void emplaceUser(const string& login, const string& password);

            // Идентификация нужного пользователя. При успешной аутентификации
            // возвращает 1, 0 - при всех остальных случаях
            virtual bool identification(const string& login);

    };

    class Proxy_Watcher : public Weather_system
    {
        private:
            Actual_Weather *weather;

        public:
            virtual bool identification(const string& login);
            virtual void logging(const bool& idFlag, const string& login);
    };
}
#endif // WEATHER_SYSTEM_HPP

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tgbot/tgbot.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <curl/curl.h>
#include "cpp-httplib/httplib.h"
#include "json.h/json.h"
#include "nlohmann/json.hpp"
#include "windows.h"
#include <future>

#include "tgbot/tools/StringTools.h" 
#include <iomanip>
#include <cstdio>
#include <random>
#include <string>

#define SQLITECPP_COMPILE_DLL
#include "SQLiteCpp/SQLiteCpp.h"

using namespace std;
using namespace TgBot;


SQLite::Database Data("UserAndStatus.db", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
void createtable()
{
    Data.exec("CREATE TABLE IF NOT EXISTS usstat (ID INTEGER PRIMARY KEY, Username TEXT, Status TEXT, UserID INTEGER)");
}

/// <summary>
/// ищет пользователя по юзернейму
/// </summary>
string SearchUser(string Username)
{
    createtable();
    string User;
    string p = "'";
    string result;
    SQLite::Statement query(Data, ("SELECT * FROM usstat WHERE Username =" + p + Username + p));
    while (query.executeStep())
    {
        string user = query.getColumn(1);
        User = user;
    }
    result = "User:" + User;
    return result;
}

bool TakeQuestion(string n)
{
    for (auto f : n)
    {
        if (f == '?')
        {
            return true;
        }
    }
    return false;
}







string get_time_as_str()
{
    time_t now = time(NULL);
    tm* ptr = localtime(&now);
    char buff[32];
    strftime(buff, 32, "%d %B %Y %T ", ptr);
    return buff;
}




static size_t Writer(char* buffer, size_t size, size_t nmemb, std::string* html)
{
    int result = 0;

    if (buffer != NULL)
    {
        html->append(buffer, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

string get_request(string link)
{
    CURL* curl;
    string data;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return data;
}

/// <summary>
/// Получение валюты с сайта по вводу аргумента 
/// </summary>
float get_currency(float what)
{
    auto js_obj = nlohmann::json::parse(get_request("https://www.cbr-xml-daily.ru/daily_json.js"));

    if (what == 1)
    {
        return js_obj["Valute"]["USD"]["Value"].get<float>();
    }
    else if (what == 2)
    {
        return js_obj["Valute"]["EUR"]["Value"].get<float>();
    }

    return 0;
}




/// <summary>
/// Рандомная шутка
/// </summary>
string Punchline()
{
    auto js = nlohmann::json::parse(get_request("https://official-joke-api.appspot.com/random_joke"));
    string k = " ";
    string Setup = js["setup"].get<string>();
    string Punch = js["punchline"].get<string>();
    string punchline = Setup + k + Punch;
    return punchline;
}

string YesNoMaybe()
{
    string k = " ";
    auto js = nlohmann::json::parse(get_request("https://yesno.wtf/api"));
    string image = js["image"].get<string>(); 
    string image1 = js["answer"].get<string>();
    string Imagee = image1 + k + image;
    return Imagee;
}







/// <summary>
/// Генерация пароля по заданной длинне
/// </summary>
string generateRandomParol(std::size_t length) {
    static const string chars("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890/");

    static const std::size_t charsLen = chars.length();
    string result;

    random_device randomDevice;
    mt19937 randomSeed(randomDevice());
    uniform_int_distribution<std::size_t> generator(0, charsLen - 1);

    for (std::size_t i = 0; i < length; ++i) {
        result += chars[generator(randomSeed)];
    }
    return result;
}
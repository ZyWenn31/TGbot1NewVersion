#include "Functions.h"




using namespace std;
using namespace TgBot;

vector<string>bot_commands = { "start"};


vector<int>UsersID;

string MessageText = "Hello, everyone";

void GoMessegeToUsers()
{
    SQLite::Statement query(Data, "SELECT UserID FROM usstat");
    while (query.executeStep())
    {
        int Userid = query.getColumn(0);
        UsersID.push_back(Userid);
    }
}

bool HelloToUser(string n, string user, int ID)
{
    if (n == "User:")
    {
        SQLite::Statement insert(Data, "INSERT INTO usstat (Username, Status, UserID) VALUES (?, ?, ?)");
        insert.bind(1, user);
        insert.bind(2, "Member");
        insert.bind(3, ID);
        insert.exec();
        return true;
    }
    {
        return false;
    }
}

int main()
{
    TgBot::Bot bot("6595208040:AAHqjDoPmntRnsvaBF4zBb5-g4FiEZkMJdA");
   



    //Клавиатуры

    //hello клавиатура
   /* InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> buttons;
    InlineKeyboardButton::Ptr fine_btn(new InlineKeyboardButton), No_fine_btn(new InlineKeyboardButton);
    fine_btn->text = "Im fine";
    fine_btn->callbackData = "im Fine";
    No_fine_btn->text = "im not fine";
    No_fine_btn->callbackData = "im not fine";
    buttons.push_back(fine_btn);
    buttons.push_back(No_fine_btn);
    keyboard->inlineKeyboard.push_back(buttons);*/

    //out Клавиатура
    InlineKeyboardMarkup::Ptr outKey(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> Keout;
    InlineKeyboardButton::Ptr outBTN(new InlineKeyboardButton);
    outBTN->text = u8"На главную";
    outBTN->callbackData = u8"На главную";
    Keout.push_back(outBTN);
    outKey->inlineKeyboard.push_back(Keout);

    //YesNo Клавиатура
    InlineKeyboardMarkup::Ptr YesKey(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> Keyes;
    InlineKeyboardButton::Ptr GoBtn(new InlineKeyboardButton);
    GoBtn->text = "GO";
    GoBtn->callbackData = "GO";
    Keyes.push_back(GoBtn);
    Keout.push_back(outBTN);
    YesKey->inlineKeyboard.push_back(Keyes);
    YesKey->inlineKeyboard.push_back({ outBTN });

    //joke Клавиатура
    InlineKeyboardMarkup::Ptr joKey(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> Kejok;
    InlineKeyboardButton::Ptr jkBtn(new InlineKeyboardButton);
    jkBtn->text = u8"Следующая шутка";
    jkBtn->callbackData = u8"Следующая шутка";
    Kejok.push_back(jkBtn);
    Keout.push_back(outBTN);
    joKey->inlineKeyboard.push_back({ jkBtn });
    joKey->inlineKeyboard.push_back({ outBTN });

    //Главная клавиатура 
    InlineKeyboardMarkup::Ptr Generalkeyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> GeneralBTNS;
    InlineKeyboardButton::Ptr TimeFunct(new InlineKeyboardButton), PasswordFunct(new InlineKeyboardButton), JokeFunct(new InlineKeyboardButton), QuestionFunct(new InlineKeyboardButton), RRRRRRRR(new InlineKeyboardButton);
    TimeFunct->text = u8"Узнать время";
    TimeFunct->callbackData = u8"Узнать время";
    PasswordFunct->text = u8"Получить пароль";
    PasswordFunct->callbackData = u8"Получить пароль";
    JokeFunct->text = u8"Получить шутку";
    JokeFunct->callbackData = u8"Получить шутку";
    QuestionFunct->text = u8"Получить ответ на вопрос";
    QuestionFunct->callbackData = u8"Получить ответ на вопрос";
    RRRRRRRR->text = u8"Сообщение";
    RRRRRRRR->callbackData = u8"Сообщение";
    GeneralBTNS.push_back(TimeFunct);
    GeneralBTNS.push_back(PasswordFunct);
    GeneralBTNS.push_back(JokeFunct);
    GeneralBTNS.push_back(QuestionFunct);
    GeneralBTNS.push_back(RRRRRRRR);
    Generalkeyboard->inlineKeyboard.push_back({ TimeFunct });
    Generalkeyboard->inlineKeyboard.push_back({ PasswordFunct });
    Generalkeyboard->inlineKeyboard.push_back({ JokeFunct });
    Generalkeyboard->inlineKeyboard.push_back({ QuestionFunct });
    Generalkeyboard->inlineKeyboard.push_back({ RRRRRRRR });


    //password клавиатура
    InlineKeyboardMarkup::Ptr keyboardToPassword(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> PassBtn;
    InlineKeyboardButton::Ptr eightBtn(new InlineKeyboardButton), nineBtn(new InlineKeyboardButton), tenBtn(new InlineKeyboardButton), elevBtn(new InlineKeyboardButton), twelvBtn(new InlineKeyboardButton), moreBtn(new InlineKeyboardButton);
    eightBtn->text = "8";
    nineBtn->text = "9";
    tenBtn->text = "10";
    elevBtn->text = "11";
    twelvBtn->text = "12";
    moreBtn->text = "more";
    eightBtn->callbackData = "8";
    nineBtn->callbackData = "9";
    tenBtn->callbackData = "10";
    elevBtn->callbackData = "11";
    twelvBtn->callbackData = "12";
    moreBtn->callbackData = "more";
    PassBtn.push_back(eightBtn);
    PassBtn.push_back(nineBtn);
    PassBtn.push_back(tenBtn);
    PassBtn.push_back(elevBtn);
    PassBtn.push_back(twelvBtn);
    PassBtn.push_back(moreBtn);
    Keout.push_back(outBTN);
    keyboardToPassword->inlineKeyboard.push_back(PassBtn);
    keyboardToPassword->inlineKeyboard.push_back({ outBTN });
    //Конец клавиатур

    
  

    bot.getEvents().onCommand("start", [&bot, &Generalkeyboard, &outKey](TgBot::Message::Ptr message)
        {
            bot.getApi().sendMessage(message->chat->id, u8"Привет, \t" + message->chat->firstName);
            if (HelloToUser(SearchUser(message->chat->username), message->chat->username, message->chat->id))
            {
                bot.getApi().sendMessage(message->chat->id, u8"Вы успешно зарегестрированы");
                cout << "New registed user: " << message->chat->username << endl;
            }
            else
            {
                bot.getApi().sendMessage(message->chat->id, u8"Вы успешно авторизованы");
                cout << "autarization user: " << message->chat->username << endl;
            }
            bot.getApi().sendMessage(message->chat->id, u8"Добро пожаловать в бота <название бота>, бот умеет:\n - Показывать время\n - генерировать шутки на различные темы\n - давать односложный ответ на вопрос\n - генерировать пароли различной длинны\n Бот предназначен для ежедневного использования, по всем вопросам писать в поддержку : @Пример.\n Приятного использования!", false, 0, Generalkeyboard);
        });

    bot.getEvents().onCallbackQuery([&bot, &Generalkeyboard, &outKey, &YesKey, &keyboardToPassword](CallbackQuery::Ptr query)
        {
            if (query->data == u8"На главную")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"Добро пожаловать в бота <название бота>, бот умеет:\n - Показывать время\n - генерировать шутки на различные темы\n - давать односложный ответ на вопрос\n - генерировать пароли различной длинны\n Бот предназначен для ежедневного использования, по всем вопросам писать в поддержку : @Пример.\n Приятного использования!", false, 0, Generalkeyboard);
            }
        });

    bot.getEvents().onCallbackQuery([&bot, &Generalkeyboard, &outKey](CallbackQuery::Ptr query)
        {
            if (query->data == u8"Сообщение")
            {
                GoMessegeToUsers();
                try {
                    for (const auto& userID : UsersID) {
                        bot.getApi().sendMessage(userID, to_string(userID));
                    }
                }
                catch (const TgBot::TgException& ex) {
                    std::cerr << "Ошибка при отправке сообщения: " << ex.what() << std::endl;
                    return 1;
                }

                std::cout << "Сообщения успешно отправлены!" << std::endl;
                return 0;
                cout << "(Time) function was used be the user: " << query->message->chat->username << endl;
            }
        });


    bot.getEvents().onCallbackQuery([&bot, &keyboardToPassword, &Generalkeyboard](CallbackQuery::Ptr query)
        {
            if (query->data == u8"Получить пароль")
            {

                bot.getApi().sendMessage(query->message->chat->id, u8"Сколько символов должен содержать пароль?\t", false, 0, keyboardToPassword);
                cout << "(Password) function was used be the user: " << query->message->chat->username << endl;
            }
        });

    bot.getEvents().onCallbackQuery([&bot, &keyboardToPassword, &outKey](CallbackQuery::Ptr query)
        {
            if (query->data == "8")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"Твой сгенерированный пароль:"); // Сделать отправление сообщения как тут
                bot.getApi().sendMessage(query->message->chat->id, generateRandomParol(8), false, 0, outKey);
            }
            else if (query->data == "9")
            {
                bot.getApi().sendMessage(query->message->chat->id, "Your generated password:");
                bot.getApi().sendMessage(query->message->chat->id, generateRandomParol(9), false, 0, outKey);
            }
            else if (query->data == "10")
            {
                bot.getApi().sendMessage(query->message->chat->id, "Your generated password:");
                bot.getApi().sendMessage(query->message->chat->id, generateRandomParol(10), false, 0, outKey);
            }
            else if (query->data == "11")
            {
                bot.getApi().sendMessage(query->message->chat->id, "Your generated password:");
                bot.getApi().sendMessage(query->message->chat->id, generateRandomParol(11), false, 0, outKey);
            }
            else if (query->data == "12")
            {
                bot.getApi().sendMessage(query->message->chat->id, "Your generated password:");
                bot.getApi().sendMessage(query->message->chat->id, generateRandomParol(12), false, 0, outKey);
            }
            else if (query->data == "more")
            {
                bot.getApi().sendMessage(query->message->chat->id, "Your generated password:");
                bot.getApi().sendMessage(query->message->chat->id, generateRandomParol(20), false, 0, outKey);
            }
        });




    /* bot.getEvents().onCommand("hello", [&bot, &keyboard](TgBot::Message::Ptr message)
         {
             bot.getApi().sendMessage(message->chat->id, "Hello how are you? \t", false, 0, keyboard);
             cout << "Long poll 'hello' to user: " << message->chat->username << endl;
         });

     bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) {
         if (query->data == "im Fine")
         {
             bot.getApi().sendMessage(query->message->chat->id, "I'm happy for you :)");
         }
         else if (query->data == "im not fine")
         {
             bot.getApi().sendMessage(query->message->chat->id, "Don't worry :)");
         }
         });*/

    bot.getEvents().onCallbackQuery([&bot, &Generalkeyboard, &outKey](CallbackQuery::Ptr query)
        {
            if (query->data == u8"Узнать время")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"Moscow time is:\n" + get_time_as_str(), false, 0, outKey);
                cout << "(Time) function was used be the user: " << query->message->chat->username << endl;
            }
        });


    bot.getEvents().onCallbackQuery([&bot, &Generalkeyboard, &joKey, &outKey](CallbackQuery::Ptr query)
        {
            if (query->data == u8"Получить шутку")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"При нажатии на кнопку (Следующая шутка), вы увидете шутку на случайную тему.\t", false, 0, joKey);
                cout << "(joke) function was used be the user: " << query->message->chat->username << endl;
            }
        });

    bot.getEvents().onCallbackQuery([&bot, &joKey, &outKey](CallbackQuery::Ptr query)
        {
            if (query->data == u8"Следующая шутка")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"Сгенерированная шутка:\n" + Punchline(), false, 0, joKey);
            }
        });



    bot.getEvents().onCallbackQuery([&bot, &YesKey, &outKey, &Generalkeyboard](CallbackQuery::Ptr query)
        {
            if (query->data == u8"Получить ответ на вопрос")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"При нажатии на кнопку вы сможете ввести вопрос, подрузумивающий однозначный ответ (Да/Нет), и с малой вероятностью (может быть), будьте внимательны, кнопку следует нажимать только единожды, при последующем нажатии работа будет неверной.\t", false, 0, YesKey);
                cout << "(question) function was used be the user: " << query->message->chat->username << endl;
            }
        });

    bot.getEvents().onCallbackQuery([&bot, &outKey, &YesKey](CallbackQuery::Ptr query)
        {
            if (query->data == "GO")
            {
                bot.getApi().sendMessage(query->message->chat->id, u8"Введите вопрос, обязательно используйте знак (?) в конце:");
                bot.getEvents().onNonCommandMessage([&bot, &outKey](Message::Ptr message)
                    {
                        if (TakeQuestion(message->text))
                        {
                            bot.getApi().sendMessage(message->chat->id, u8"Полученный ответ:\t" + YesNoMaybe(), false, 0, outKey);
                            cout << "user " << message->chat->username << " Get answer" << endl;
                        }
                    });
            }
        });


    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)
        {
            for (const auto& command : bot_commands)
            {
                if ("/" + command == message->text || TakeQuestion(message->text))
                {
                    return;
                }
            }
            bot.getApi().sendMessage(message->chat->id, u8"Неизвестная команда");
        });

    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
        return 0;
    }
}
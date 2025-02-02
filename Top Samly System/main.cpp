#ifndef _UNISTD_H
#define _UNISTD_H
#include <io.h>
#include <process.h>
#endif
#include <iostream>
#include <vector>
#include <ctime>
#include <utility>
#include <stack>
#include "hashe.h"
#include "Rand.h"
#include "windows.h"
#include <fstream>

const int Main_Menu_Len = 5;
const int App_Menu_Len = 4;

bool Login_State = 0;

bool Restart_State = 0;

namespace datas {
    namespace user_info {
        int User_id;
        std::string Username, Password;
    }
    namespace App_Data {
        struct App {
            std::string App_Name;
            std::string App_Description;
            int Storage;
        } Apps[100];
    }
    namespace Menu_ {
        std::string Main_Menu[Main_Menu_Len + 5];
        std::string App_Menu[App_Menu_Len + 5];
    }
    // todo: App Datas: 应用数据
}

using namespace datas::Menu_;

namespace Log {
    // todo: Log: 日志功能
    struct Log_T {
        std::string type;
        std::string Log_Text;
    };
    namespace Log_Data {
        int len = 0;
        std::vector<Log_T> Logs;
    }
    using namespace Log_Data;
    namespace Combin {
        std::string Init_Log(tm q, std::string Text) {
            len++;
            std::string ans = int_to_string(q.tm_year + 1900) + "." + int_to_string(q.tm_mon + 1) + "." + int_to_string(q.tm_mday) + "  " + int_to_string(q.tm_hour) + " : " + int_to_string(q.tm_min) + " : " + int_to_string(q.tm_sec) + "      " + "Initial    " + Text + '\n';
            return ans;
        }
        std::string Login_Log() {

        }
    }
    namespace Write {
        void Write_in(Log_T Loger) {
            std::string FileNames = Loger.type + ".log";
            int flag_Text = 0;
            if (_access(FileNames.c_str(), 00) != 0) {
                std::string commands = "cd . > " + FileNames;
                system(commands.c_str());
                flag_Text = 1;
            }
            std::ofstream F_loger(FileNames.c_str(), std::ios::out | std::ios::app);
            if (flag_Text) {
                F_loger << "        Time 		      Type			Text\n";
            }
            F_loger << Loger.Log_Text;
        }
    }
}

using namespace Log::Log_Data;
using namespace Log::Combin;
using namespace Log::Write;

namespace Systems {
    tm Get_time() {
        time_t Now_Time;
        time(&Now_Time);
        tm p;
        localtime_s(&p, &Now_Time);
        Write_in({ "Get Time", Init_Log(p, "Get Local Time.") });
        return p;
    }
    void clsS() { // Clean Screen
        system("cls");
        return;
    }
    void PauseS() { // Wait to click keyboard
        system("pause");
        return;
    }
    void slp(double Sec) { // Wait any Sec
        Sleep(int(Sec * 1000));
        return;
    }
    void WL(std::string type, std::string text) { // Write Log
        tm p = Get_time();
        Log::Log_T P;
        P.type = type;
        P.Log_Text = Init_Log(p, text);
        Write_in(P);
        return;
    }
}

using namespace Systems;

namespace App_Options {
    namespace Install_Software {
        // todo: Calculator: 计算器
        namespace Calculator {
            std::string Formulap;
            long double Plus(long double Plus1, long double Plus2) {
                return Plus1 + Plus2;
            }
            long double Subtraction(long double Sub1, long double Sub2) {
                return Sub1 - Sub2;
            }
            long double Times(long double Times1, long double Times2) {
                return Times1 * Times2;
            }
            long double Div(long double Div1, long double Div2) {
                return Div1 * 1.0 / Div2;
            }
            namespace Check_Formulas {
                std::vector<std::pair<std::string, int>> word;
                int idx = 0;
                int sym;
                int err = 0;
                void T();
                void F();
                int word_analysis(std::vector<std::pair<std::string, int>>& word, std::string expr)
                {
                    for (int i = 0; i < expr.length(); ++i)
                    {
                        if (expr[i] == '(' || expr[i] == ')' || expr[i] == '+'
                            || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
                        {
                            std::string tmp;
                            tmp.push_back(expr[i]);
                            switch (expr[i])
                            {
                            case '+':
                                word.push_back(make_pair(tmp, 1));
                                break;
                            case '-':
                                word.push_back(make_pair(tmp, 2));
                                break;
                            case '*':
                                word.push_back(make_pair(tmp, 3));
                                break;
                            case '/':
                                word.push_back(make_pair(tmp, 4));
                                break;
                            case '(':
                                word.push_back(make_pair(tmp, 6));
                                break;
                            case ')':
                                word.push_back(make_pair(tmp, 7));
                                break;
                            }
                        }
                        else if (expr[i] >= '0' && expr[i] <= '9')
                        {
                            std::string tmp;
                            while (expr[i] >= '0' && expr[i] <= '9')
                            {
                                tmp.push_back(expr[i]);
                                ++i;
                            }
                            if (expr[i] == '.')
                            {
                                ++i;
                                if (expr[i] >= '0' && expr[i] <= '9')
                                {
                                    tmp.push_back('.');
                                    while (expr[i] >= '0' && expr[i] <= '9')
                                    {
                                        tmp.push_back(expr[i]);
                                        ++i;
                                    }
                                }
                                else
                                {
                                    return -1;
                                }
                            }
                            word.push_back(make_pair(tmp, 5));
                            --i;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                    return 0;
                }
                void Next()
                {
                    if (idx < word.size())
                        sym = word[idx++].second;
                    else
                        sym = 0;
                }
                void E()
                {
                    T();
                    while (sym == 1 || sym == 2)
                    {
                        Next();
                        T();
                    }
                }
                void T()
                {
                    F();
                    while (sym == 3 || sym == 4)
                    {
                        Next();
                        F();
                    }
                }
                void F()
                {
                    if (sym == 5)
                    {
                        Next();
                    }
                    else if (sym == 6)
                    {
                        Next();
                        E();
                        if (sym == 7)
                        {
                            Next();
                        }
                        else
                        {
                            err = -1;
                        }
                    }
                    else
                    {
                        err = -1;
                    }
                } // The code Powered by https:// blog.csdn.net/lisonglisonglisong . About https:// blog.csdn.net
            }
            using namespace Check_Formulas;
            bool Check_Formula(std::string Formulap) {
                int flag = 1;
                int error_number = word_analysis(word, Formulap);
                if (error_number == -1) {
                    flag = 0;
                }
                else {
                    Next();
                    E();
                    if (sym == 0 && err == 0) {
                        flag = 1;
                    }
                    else {
                        flag = 0;
                    }
                }
                return flag;
            }
            bool Check_Formula2(std::string Formulap) {
                for (int i = 0; i < Formulap.length(); i++) {
                    if (Formulap[i] == '&' || Formulap[i] == '|' || Formulap[i] == '^' || Formulap[i] == ' ' || Formulap[i] == '%' || Formulap[i] == '!' || Formulap[i] == '?') {
                        return false;
                    }
                }
                return true;
            }
            bool Check_Formula_Right() {
                if (!Check_Formula(Formulap) || !Check_Formula2(Formulap)) {
                    clsS();
                    std::cout << "The formula isn't right!";
                    return true;
                }
                return false;
            }
            void ONEN() {
                clsS();
                std::cout << "Please enter your want to complete formula (Don't enter big bracket, middle bracket and space):  ";
                std::cin >> Formulap;
                if (!Check_Formula_Right()) {
                    return;
                }
                
            }
            void SPAN() {

            }
            void Main_UI() {
                system("cls");
                std::cout << R"(
Welcome to use Top Samly Calculator
You can run option number of under the this line:
1. General Complete (Only include Plus, Subtraction, Times and Div. Don't enter T of F)
2. Special Complete (Include 1. 2. 's Complete and AND, OR and XOR)
3. Exit (Close Top Samly Calculator)
)";
                while (1) {
                    int option_;
                    std::cin >> option_;
                    if (option_ == 1) {
                        clsS();
                        ONEN();
                    }
                    if (option_ == 2) {
                        clsS();
                        SPAN();
                    }
                    if (option_ == 3) {
                        clsS();
                        return;
                    }
                    clsS();
                }
            }
        }
    }
    namespace System_Software {
        // todo: Settings: 设置
    }
}

using namespace datas::user_info;
using namespace datas::App_Data;

namespace Load {
    void Init() {
        Apps[1].App_Name = "Calculator";
        Apps[1].App_Description = "You can use this software to compute complex formula.";
        Apps[1].Storage = 436;

        Apps[2].App_Name = "Settings";
        Apps[2].App_Description = "You can change system's settings.";
        Apps[2].Storage = 1536;

        Apps[3].App_Name = "About";
        Apps[3].App_Description = "About Top Samly System.";
        Apps[3].Storage = 216;

        Main_Menu[1] = "Login Top Samle System";
        Main_Menu[2] = "Sleep";
        Main_Menu[3] = "Restart";
        Main_Menu[4] = "Shutdown";

        App_Menu[1] = "Calculator";
        App_Menu[2] = "Settings";
        App_Menu[3] = "About";

        User_id = 1;

        Username = "3706311722193738805", Password = "1905235540959";
        time_t Now_Time;
        time(&Now_Time);
        tm p;
        srand(time(0));
        localtime_s(&p, &Now_Time);
        Logs.push_back({ "Initial", Init_Log(p, "Initial Rand's Time Seed -> Ready Random Done") });
        Write_in({ "Initial", Init_Log(p, "Initial Rand's Time Seed -> Ready Random Done") });
    }
    void Load_Start() {
        for (int i = 1; i <= 100; i++) {
            std::cout << "Loading...\n";
            std::cout << "|";
            for (int j = 1; j <= i; j++) {
                std::cout << "=";
            }
            for (int j = 1; j <= (100 - i); j++) {
                std::cout << " ";
            }
            std::cout << "|";
            std::cout << "  " << i << "%" << '\n';
            Sleep(20);
            clsS();
        }
        std::cout << R"( 
  _      __        __                             __                                 ______                    ____                __               ____              __             
 | | /| / / ___   / / ____ ___   __ _  ___       / /_ ___       __ __  ___ ___      /_  __/ ___    ___        / __/ ___ _  __ _   / /  __ __       / __/  __ __  ___ / /_ ___   __ _ 
 | |/ |/ / / -_) / / / __// _ \ /  ' \/ -_)     / __// _ \     / // / (_-</ -_)      / /   / _ \  / _ \      _\ \  / _ `/ /  ' \ / /  / // /      _\ \   / // / (_-</ __// -_) /  ' \
 |__/|__/  \__/ /_/  \__/ \___//_/_/_/\__/      \__/ \___/     \_,_/ /___/\__/      /_/    \___/ / .__/     /___/  \_,_/ /_/_/_//_/   \_, /      /___/   \_, / /___/\__/ \__/ /_/_/_/
                                                                                                /_/                                  /___/              /___/                        
)";
        slp(5);
        clsS();
    }
}

namespace LoginUIs {
    // todo: LoginUI: 登录界面
    bool LoginUI() {
        int _error = 0, _e_error = 0;
        std::string username, password;
        while (1) {
            clsS();
            if (_error == 5) {
                _e_error = 0;
                std::cout << "Too many errors!\n";
                std::cout << "Please wait 10 seconds and enter again!";
                slp(10);
            }
            if (_e_error == 3) {
                clsS();
                return false;
            }
            std::cout << "Please enter your username:  ";
            std::cin >> username;
            std::cout << "Please enter your password:  ";
            std::cin >> password;
            clsS();
            std::cout << "Checking...\n";
            username = hashe(username);
            password = hashe(password);
            if (username == Username && password == Password) {
                std::string check_number;
                check_number = verify_Number(16, 0, 9);
                std::cout << "Please enter verify code (Please wait 3 Sec):                      ";
                slp(3);
                std::cout << "(" << check_number << ")";
                for (int i = 1; i <= 38; i++) {
                    std::cout << '\b';
                }
                std::string check_number_temp;
                std::cin >> check_number_temp;
                if (check_number_temp != check_number) {
                    std::cout << "Verify code isn't right!\n";
                    continue;
                }
                Login_State = 1;
                std::cout << "Username and password is right!";
                slp(0.5);
                clsS();
                return true;
            }
            else {
                _error++;
                std::cout << "Username and password isn't right!";
            }
        }
    }
}

using namespace Load;
using namespace LoginUIs;
using namespace Systems;

namespace Option_ {
    void Sleep_O() {
        clsS();
        PauseS();
        system("cls");
        return;
    }
    void Restart_O() {
        Restart_State = 1;
        if (!Restart_State) std::cout << "Please close Top Samly System and start Top Samly System.";
        return;
    }
    void Shutdown_O() {
        clsS();
        std::cout << "Shutdown...\n";
        slp(2);
        exit(0);
        return;
    }
    void Calculator_O() {
        App_Options::Install_Software::Calculator::Main_UI();
    }
}

namespace Options {

    void Main_Menu_Output() {
        std::cout << R"(
            Welcome to use Top Samly System
)";
        for (int i = 1; i <= Main_Menu_Len - 1; i++) {
            std::cout << "               " << i << ".  " << Main_Menu[i] << '\n';
        }
    }

    void App_Menu_Output() {
        std::cout << R"(
            Welcome to use Top Samly System
)";
        for (int i = 1; i <= App_Menu_Len - 1; i++) {
            std::cout << "               " << i << ".  " << App_Menu[i] << '\n';
        }
    }
    
    void Main_() {
        while (1) {
            if (Restart_State) {
                Option_::Restart_O();
            }
            else if (!Login_State) {
                Main_Menu_Output();
            }
            else {
                App_Menu_Output();
            }
            std::cout << "        Please enter your want to run of option number:  ";
            int option_ = -1;
            std::cin >> option_;
            // Not Login Top Samly System
            if (option_ == 1 && !Login_State) {
                if (!LoginUI()) {
                    tm Ntime = Get_time();
                    Write_in({ "Users' Dangerous", Init_Log(Ntime, "Find Fangerous. It can threaten user security!") });
                    std::cout << "Find Dangerous!\n";
                    exit(0);
                }
                continue;
            }
            if (option_ == 2 && !Login_State) {
                Option_::Sleep_O();
                continue;
            }
            if (option_ == 3 && !Login_State) {
                Option_::Restart_O();
                continue;
            }
            if (option_ == 4 && !Login_State) {
                Option_::Shutdown_O();
                continue;
            }
            
            // Login in to Top Samly System
            if (option_ == 1 && Login_State) {
                Option_::Calculator_O();
                continue;
            }
        }
    }
}

using namespace Options;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    // test Hash Function
    /*for (;;) {
        std::string x;
        std::cin >> x;
        std::cout << hashe(x) << '\n';
    }*/
    // Initial this Top Samly System
    Init();
    // Start to Load.
    Load_Start();
    // Do Main Options
    Main_();     
    return 0;
}
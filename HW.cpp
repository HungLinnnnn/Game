#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <list>
#include <conio.h>
#include <chrono>
using namespace std;

#define BORDER_UP 2 // border for the objects in the game
#define BORDER_DOWN 20
#define BORDER_LEFT 33
#define BORDER_LEFT_WIDE 2
#define BORDER_RIGHT 93
#define BORDER_RIGHT_WIDE 115
#define TIME_LIMIT 30
#define TIME_POS_X 20
#define TIME_POS_Y 0
#define CUR_SCORE_POS_X 50
#define CUR_SCORE_POS_Y 0
#define HIS_SCORE_POS_X 80
#define HIS_SCORE_POS_Y 0
#define INTERVAL_BETWEEN_EACH_LOOP 20
int HISTORY_HIGH_SCORE = 0;
void gowhere(double x, double y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x; // start from 0
    dwPos.Y = y; // start from 0
    SetConsoleCursorPosition(hCon, dwPos);
}
void line()
{
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<10; j++)
        {
            gowhere(36+i*6,BORDER_DOWN-j);
            cout << '|';
        }
    }
    gowhere(BORDER_LEFT,BORDER_DOWN+3);
    cout << "S";
    gowhere(BORDER_LEFT+6,BORDER_DOWN+3);
    cout << "D";
    gowhere(BORDER_LEFT+12,BORDER_DOWN+3);
    cout << "F";
    gowhere(BORDER_LEFT+18,BORDER_DOWN+3);
    cout << "J";
    gowhere(BORDER_LEFT+24,BORDER_DOWN+3);
    cout << "K";
    gowhere(BORDER_LEFT+30,BORDER_DOWN+3);
    cout << "L";

}
class note
{
private:
    double x;
    double y;
    char key;
public:
    note(double x1, double y1, int random_x)
    {
        this->x = x1;
        this->y = y1;
        switch(random_x)
        {
        case 0:
            key = 's'; break;
        case 1:
            key = 'd'; break;
        case 2:
            key = 'f'; break;
        case 3:
            key = 'j'; break;
        case 4:
            key = 'k'; break;
        case 5:
            key = 'l'; break;
        }

    }
    double X() { return x; }
    double Y() { return y; }
    void Draw();
    void Erase();
    void Move(bool displayed);
    char Get_key();
};
char note::Get_key()
{
    return key;
}
void note::Draw()
{
    gowhere(x,y);
    cout << "O";
}
void note::Erase()
{
    gowhere(x,y);
    cout << " ";
}
void note::Move(bool displayed)
{
    Erase();
    y += 1;
    if (displayed)
    {
        Draw();
    }
}

void Initialize()
{
    SetConsoleTitle("Peko");

    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

void DrawWhiteSpace(int a_x, int a_y, int b_x, int b_y)
{
    for (int i = a_x; i <= b_x; i++)
    {
        for(int j = a_y; j <= b_y; j++)
        {
            gowhere(i,j);
            cout << " ";
        }
    }
}
void WelcomeMessage()
{
    DrawWhiteSpace(0, 0, BORDER_RIGHT_WIDE, BORDER_DOWN);
    int x = 20;
    int y = 10;
    gowhere(x, y  ); cout <<"  ______     _______     _      _     _______  ";
    gowhere(x, y+1); cout <<" |  __  |   |  _____|   | |    / /   |  ___  | ";
    gowhere(x, y+2); cout <<" | |  | |   | |         | |   / /    | |   | | ";
    gowhere(x, y+3); cout <<" | |__| |   | |_____    | |__/ /     | |   | | ";
    gowhere(x, y+4); cout <<" |  ____|   |  _____|   |  __ /      | |   | | ";
    gowhere(x, y+5); cout <<" | |        | |_____    | |  \\ \\     | |___| | ";
    gowhere(x, y+6); cout <<" |_|        |_______|   |_|   \\_\\    |_______| ";
    gowhere(31, y+12); cout << "Press \"Enter\" to play.";
}
void UpdateInfoBar(int gameScore, std::chrono::seconds leftTime)
{
    gowhere(TIME_POS_X, TIME_POS_Y); cout << "剩餘時間: " << leftTime.count() << "   ";
    gowhere(CUR_SCORE_POS_X, CUR_SCORE_POS_Y); cout << "分數: " << gameScore << "  ";
    gowhere(HIS_SCORE_POS_X, HIS_SCORE_POS_Y); cout << "歷史高分: " << HISTORY_HIGH_SCORE;
    if (gameScore >= HISTORY_HIGH_SCORE)
    {
        HISTORY_HIGH_SCORE = gameScore;
        gowhere(HIS_SCORE_POS_X, HIS_SCORE_POS_Y); cout << "歷史高分: " << HISTORY_HIGH_SCORE;
    }
}
bool StartGame()
{
    DrawWhiteSpace(0, 0, BORDER_RIGHT_WIDE, BORDER_DOWN+3);

    std::chrono::seconds timeLimit(TIME_LIMIT);
    std::chrono::seconds duration(0);
    std::chrono::seconds leftTime(TIME_LIMIT);
    auto start = chrono::steady_clock::now();
    int gameScore = 0;

    list<note> notes;
    list<note>::iterator n;
    gameScore = 0;

    srand(time(nullptr));
    //int mapLength = BORDER_DOWN - BORDER_UP + 1;
    //int mapWidth = BORDER_RIGHT - BORDER_LEFT + 1;
    double rnX = 0;
    double rnY = 0;
    for (int i = 0; i < 400; i++)
    {
        int random_x = rand() % 6;
        rnX = 6*random_x + BORDER_LEFT;
        rnY = BORDER_DOWN - i*1;
        notes.push_back(note(rnX, rnY, random_x));
    }
    n = notes.begin();
    for (int i = 0; i < 10; i++)
    {
        n->Draw();
        n++;
    }
    while (duration < timeLimit)
    {
        line();
        char press_key = getch();
        if (press_key == notes.begin()->Get_key())
        {
             gameScore ++;
             n = notes.begin();
             n->Erase();
             n = notes.erase(n);
             int i=0;
             for (n = notes.begin(); n!= notes.end(); n++)
             {
                 if (i < 10)
                 {
                     n->Move(1);
                 }
                 else
                 {
                     n->Move(0);
                 }
                 i++;
             }
        }
        else
        {
            int i = 0;
            for (n = notes.begin(); n!= notes.end(); n++)
            {
                if (i < 10)
                {
                    n->Draw();
                }
                i++;
            }
        }
        auto t1 = chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - start);
        leftTime = timeLimit - duration;

        UpdateInfoBar(gameScore, leftTime);

        //Sleep(INTERVAL_BETWEEN_EACH_LOOP);
    }
}
PlayAgainMessage()
{
    DrawWhiteSpace(0, 0, BORDER_RIGHT, BORDER_DOWN+5);
    int x = 10;
    int y = 10;
    gowhere(x, y+8); cout << " 再玩一次請按 y 結束請按 n ";
}
bool PlayAgainOrNot()
{
    PlayAgainMessage();

    char playAgainKey = '0';
    bool VaildKeyForPlayAgain = false;

    while (!VaildKeyForPlayAgain) // prevent the user from pressing inappropriate keys
    {
        playAgainKey = getch();

        if (playAgainKey == 'y'  || playAgainKey == 'n')
        {
            VaildKeyForPlayAgain = true;
        }
    }

    if (playAgainKey == 'n' || playAgainKey == 'N')
        return false;
    else
        return true;
}
int main()
{
    Initialize();

    WelcomeMessage();
    char guideKey = getch();

    bool playAgain = true;

    while (playAgain)
    {
        StartGame();
        playAgain = PlayAgainOrNot();
    }

}





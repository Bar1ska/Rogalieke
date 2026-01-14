#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

//подобрать предмет или ударить враждебного моба
void takeOrHit(std::vector <string>& map, int x, int y) 
{
    string str;
    for (int i = 0; i < y; ++i) 
    {
        str += map[x][i];
    }
    str += '*';
    for (int i = y + 1; i < 27; ++i) 
    {
        str += map[x][i];
    }
    map[x] = str;
}

//шаг на право
void stepRight(std::vector <string>& map, int x, int y, char object) 
{
    string str;
    for (int i = 0; i < y; ++i)
    {
        str += map[x][i];
    }
    str += '*';
    str += object;
    for (int i = y + 2; i < 27; ++i)
    {
        str += map[x][i];
    }
    map[x] = str;
}

//шаг на лево
void stepLeft(std::vector <string>& map, int x, int y, char object) 
{
    string str;
    for (int i = 0; i < y - 1; ++i) 
    {
        str += map[x][i];
    }
    str += object;
    str += '*';
    for (int i = y + 1; i < 27; ++i) 
    {
        str += map[x][i];
    }
    map[x] = str;
}

//шаг вниз
void stepDown(std::vector <string>& map, int x, int y, char object) 
{
    string strObject, strStep;
    for (int i = 0; i < y; ++i)
    {
        strObject += map[x][i];
        strStep += map[x + 1][i];
    }
    strObject += '*';
    strStep += object;
    for (int i = y + 1; i < 27; ++i)
    {
        strObject += map[x][i];
        strStep += map[x + 1][i];
    }
    map[x] = strObject;
    map[x + 1] = strStep;
}


// шаг наверх
void stepUp(std::vector <string> &map, int x, int y, char object) 
{
    string strObject, strStep;
    for (int i = 0; i < y; ++i) 
    {
        strObject += map[x][i];
        strStep += map[x - 1][i];
    }
    strObject += '*';
    strStep += object;
    for (int i = y + 1; i < 27; ++i) 
    {
        strObject += map[x][i];
        strStep += map[x - 1][i];
    }
    map[x] = strObject;
    map[x - 1] = strStep;
}

// структура координат НПС
struct CoordinateNPC 
{
    int x;
    int y;
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int numberLevel = 0, button = 0, amountMoney = 0;
    int coordinate[] = { 0, 0 }, coordinateObject[] = { 0, 0 };
    string nameFile[] = {"levels/level1.txt", "levels/level2.txt", 
                         "levels/level3.txt", "levels/level4.txt",
                         "levels/level5.txt", "levels/level6.txt",
                         "levels/level7.txt", "levels/WIN.txt",
                         "levels/LOSE.txt", "levels/secretLevel.txt"};
    std::fstream file;
    std::vector <CoordinateNPC> coordinateNPC;
    std::vector <string> map;
    bool checkLevelComplete = false , checkDied = false;
    while (!checkDied) {
        file.open(nameFile[numberLevel], std::ios_base::in);
        checkLevelComplete = false;
        
        string str;
        while (!file.eof()) 
        {
            file >> str;
            map.push_back(str);
        }

        for (int i = 0; i < 7; ++i) 
        {
            for (int j = 0; j < 27; ++j) 
            {
                switch (map[i][j]) 
                {
                case '@':
                    coordinate[0] = i;
                    coordinate[1] = j;
                    break;
                case 'x':
                    amountMoney += 1;
                    break;
                case 'D':
                    coordinateNPC.push_back({i,j});
                    break;
                }
            }
        }

        while (!checkLevelComplete) 
        {
            system("CLS");

            // СПИСОК КНОПОК!!!
            cout << "==========================" << endl;
            cout << "| w - шаг наверх         |" << endl;
            cout << "| a - шаг на лево        |" << endl;
            cout << "| s - шаг вниз           |" << endl;
            cout << "| d - шаг на право       |" << endl;
            cout << "| f - действие/взять     |" << endl;
            cout << "| q - ударить            |" << endl;
            cout << "|                        |" << endl;
            if (amountMoney > 0) 
            {
                cout << "| тебе осталось взять -  |" << endl;
                cout << "| " << amountMoney << " монет                |" << endl;
            }
            else 
            {
                cout << "| Можно идти к выходу - &|" << endl;
            }
            cout << "==========================" << endl << endl;

            for (int i = 0; i < 7; ++i)
            {
                cout << map[i] << endl;
            }
            
            //кнопавки
            button = _getch();
            switch (button)
            {
            case 'w':
                if (map[coordinate[0] - 1][coordinate[1]] == '*') 
                {
                    stepUp(map, coordinate[0], coordinate[1], '@');
                    coordinate[0] -= 1;
                    
                }
                break;
            
            case 'a':
                if (map[coordinate[0]][coordinate[1] - 1] == '*') 
                {
                    stepLeft(map, coordinate[0], coordinate[1], '@');
                    coordinate[1] -= 1;
                    
                }
                break;
            case 's':
                if (map[coordinate[0] + 1][coordinate[1]] == '*') 
                {
                    stepDown(map, coordinate[0], coordinate[1], '@');
                    coordinate[0] += 1;
                    
                }
                break;
            case 'd':
                if (map[coordinate[0]][coordinate[1] + 1] == '*') 
                {
                    stepRight(map, coordinate[0], coordinate[1], '@');
                    coordinate[1] += 1;
                }
                break;
            case 'f':
                if (map[coordinate[0] - 1][coordinate[1] - 1] == 'x' ||
                    map[coordinate[0] - 1][coordinate[1]] == 'x' ||
                    map[coordinate[0] - 1][coordinate[1] + 1] == 'x' ||
                    map[coordinate[0]][coordinate[1] - 1] == 'x' ||
                    map[coordinate[0]][coordinate[1] + 1] == 'x' ||
                    map[coordinate[0] + 1][coordinate[1] - 1] == 'x' ||
                    map[coordinate[0] + 1][coordinate[1]] == 'x' ||
                    map[coordinate[0] + 1][coordinate[1] + 1] == 'x')
                {
                    if (map[coordinate[0] - 1][coordinate[1] - 1] == 'x') 
                    {
                        coordinateObject[0] = coordinate[0] - 1;
                        coordinateObject[1] = coordinate[1] - 1;
                    }
                    else if (map[coordinate[0] - 1][coordinate[1]] == 'x') 
                    {
                        coordinateObject[0] = coordinate[0] - 1;
                        coordinateObject[1] = coordinate[1];
                    }
                    else if (map[coordinate[0] - 1][coordinate[1] + 1] == 'x') 
                    {
                        coordinateObject[0] = coordinate[0] - 1;
                        coordinateObject[1] = coordinate[1] + 1;
                    }
                    else if (map[coordinate[0]][coordinate[1] - 1] == 'x')
                    {
                        coordinateObject[0] = coordinate[0];
                        coordinateObject[1] = coordinate[1] - 1;
                    }
                    else if (map[coordinate[0]][coordinate[1] + 1] == 'x')
                    {
                        coordinateObject[0] = coordinate[0];
                        coordinateObject[1] = coordinate[1] + 1;
                    }
                    else if (map[coordinate[0] + 1][coordinate[1] - 1] == 'x')
                    {
                        coordinateObject[0] = coordinate[0] + 1;
                        coordinateObject[1] = coordinate[1] - 1;
                    }
                    else if (map[coordinate[0] + 1][coordinate[1]] == 'x')
                    {
                        coordinateObject[0] = coordinate[0] + 1;
                        coordinateObject[1] = coordinate[1];
                    }
                    else if (map[coordinate[0] + 1][coordinate[1] + 1] == 'x')
                    {
                        coordinateObject[0] = coordinate[0] + 1;
                        coordinateObject[1] = coordinate[1] + 1;
                    }

                    takeOrHit(map, coordinateObject[0], coordinateObject[1]);
                    amountMoney -= 1;
                }
                else if (map[coordinate[0] - 1][coordinate[1] - 1] == '&' ||
                         map[coordinate[0] - 1][coordinate[1]] == '&' ||
                         map[coordinate[0] - 1][coordinate[1] + 1] == '&' ||
                         map[coordinate[0]][coordinate[1] - 1] == '&' ||
                         map[coordinate[0]][coordinate[1] + 1] == '&' ||
                         map[coordinate[0] + 1][coordinate[1] - 1] == '&' ||
                         map[coordinate[0] + 1][coordinate[1]] == '&' ||
                         map[coordinate[0] + 1][coordinate[1] + 1] == '&') 
                {
                    map.clear();
                    coordinateNPC.clear();
                    file.close();
                    numberLevel += 1;
                    checkLevelComplete = true;
                }
                else if (map[coordinate[0] - 1][coordinate[1] - 1] == '`' ||
                         map[coordinate[0] - 1][coordinate[1]] == '`' ||
                         map[coordinate[0] - 1][coordinate[1] + 1] == '`' ||
                         map[coordinate[0]][coordinate[1] - 1] == '`' ||
                         map[coordinate[0]][coordinate[1] + 1] == '`' ||
                         map[coordinate[0] + 1][coordinate[1] - 1] == '`' ||
                         map[coordinate[0] + 1][coordinate[1]] == '`' ||
                         map[coordinate[0] + 1][coordinate[1] + 1] == '`')
                {
                    map.clear();
                    coordinateNPC.clear();
                    file.close();

                    file.open(nameFile[9], std::ios_base::in);
                    
                    system("CLS");
                    string temp;

                    while (!file.eof())
                    {
                        std::string tmp;
                        file >> tmp;
                        if (temp.empty())
                            temp += tmp;
                        else
                            temp += '\n' + tmp;
                    }

                    cout << temp;
                    file.close();
                    return 0;
                }
                break;
            case 'q':
                if (map[coordinate[0] - 1][coordinate[1] - 1] == 'D' ||
                    map[coordinate[0] - 1][coordinate[1]] == 'D' ||
                    map[coordinate[0] - 1][coordinate[1] + 1] == 'D' ||
                    map[coordinate[0]][coordinate[1] - 1] == 'D' ||
                    map[coordinate[0]][coordinate[1] + 1] == 'D' ||
                    map[coordinate[0] + 1][coordinate[1] - 1] == 'D' ||
                    map[coordinate[0] + 1][coordinate[1]] == 'D' ||
                    map[coordinate[0] + 1][coordinate[1] + 1] == 'D')
                {
                    if (map[coordinate[0] - 1][coordinate[1] - 1] == 'D')
                    {
                        coordinateObject[0] = coordinate[0] - 1;
                        coordinateObject[1] = coordinate[1] - 1;
                    }
                    else if (map[coordinate[0] - 1][coordinate[1]] == 'D')
                    {
                        coordinateObject[0] = coordinate[0] - 1;
                        coordinateObject[1] = coordinate[1];
                    }
                    else if (map[coordinate[0] - 1][coordinate[1] + 1] == 'D')
                    {
                        coordinateObject[0] = coordinate[0] - 1;
                        coordinateObject[1] = coordinate[1] + 1;
                    }
                    else if (map[coordinate[0]][coordinate[1] - 1] == 'D')
                    {
                        coordinateObject[0] = coordinate[0];
                        coordinateObject[1] = coordinate[1] - 1;
                    }
                    else if (map[coordinate[0]][coordinate[1] + 1] == 'D')
                    {
                        coordinateObject[0] = coordinate[0];
                        coordinateObject[1] = coordinate[1] + 1;
                    }
                    else if (map[coordinate[0] + 1][coordinate[1] - 1] == 'D')
                    {
                        coordinateObject[0] = coordinate[0] + 1;
                        coordinateObject[1] = coordinate[1] - 1;
                    }
                    else if (map[coordinate[0] + 1][coordinate[1]] == 'D')
                    {
                        coordinateObject[0] = coordinate[0] + 1;
                        coordinateObject[1] = coordinate[1];
                    }
                    else if (map[coordinate[0] + 1][coordinate[1] + 1] == 'D')
                    {
                        coordinateObject[0] = coordinate[0] + 1;
                        coordinateObject[1] = coordinate[1] + 1;
                    }

                    takeOrHit(map, coordinateObject[0], coordinateObject[1]);
                    for (int i = 0; i < coordinateNPC.size(); ++i) 
                    {
                        if (coordinateNPC[i].x == coordinateObject[0] && coordinateNPC[i].y == coordinateObject[1]) 
                        {
                            coordinateNPC[i].x = 0;
                            coordinateNPC[i].y = 0;
                        }
                    }
                }
                break;
            }

            //логика хождения НПС
            for (int i = 0; i < coordinateNPC.size(); ++i) 
            {
                if (coordinateNPC[i].x > 0 && coordinateNPC[i].y > 0) 
                {
                    // смерть
                    if (map[coordinateNPC[i].x - 1][coordinateNPC[i].y] == '@' ||
                        map[coordinateNPC[i].x + 1][coordinateNPC[i].y] == '@' ||
                        map[coordinateNPC[i].x][coordinateNPC[i].y - 1] == '@' ||
                        map[coordinateNPC[i].x][coordinateNPC[i].y + 1] == '@') 
                    {
                        checkLevelComplete = true;
                        checkDied = true;
                        file.close();
                    }
                    // поле зрение вверз + шаг
                    else if (map[coordinateNPC[i].x - 2][coordinateNPC[i].y - 2] == '@' ||
                             map[coordinateNPC[i].x - 2][coordinateNPC[i].y - 1] == '@' || 
                             map[coordinateNPC[i].x - 2][coordinateNPC[i].y] == '@' || 
                             map[coordinateNPC[i].x - 2][coordinateNPC[i].y + 1] == '@' || 
                             map[coordinateNPC[i].x - 2][coordinateNPC[i].y + 2] == '@')
                             
                    {
                        stepUp(map, coordinateNPC[i].x, coordinateNPC[i].y, 'D');
                        coordinateNPC[i].x --;
                    }
                    // поле зрение вниз + шаг
                    else if (map[coordinateNPC[i].x + 2][coordinateNPC[i].y - 2] == '@' ||
                             map[coordinateNPC[i].x + 2][coordinateNPC[i].y - 1] == '@' ||
                             map[coordinateNPC[i].x + 2][coordinateNPC[i].y] == '@' ||
                             map[coordinateNPC[i].x + 2][coordinateNPC[i].y + 1] == '@' ||
                             map[coordinateNPC[i].x + 2][coordinateNPC[i].y + 2] == '@' )
                    {
                        stepDown(map, coordinateNPC[i].x, coordinateNPC[i].y, 'D');
                        coordinateNPC[i].x++;
                    }
                    // поле зрение права + шаг
                    else if (map[coordinateNPC[i].x - 1][coordinateNPC[i].y + 1] == '@' ||
                             map[coordinateNPC[i].x - 1][coordinateNPC[i].y + 2] == '@' ||
                             map[coordinateNPC[i].x][coordinateNPC[i].y + 2] == '@' ||
                             map[coordinateNPC[i].x + 1][coordinateNPC[i].y + 1] == '@' ||
                             map[coordinateNPC[i].x + 1][coordinateNPC[i].y + 2] == '@') 
                    {
                        stepRight(map, coordinateNPC[i].x, coordinateNPC[i].y, 'D');
                        coordinateNPC[i].y++;
                    }
                    // поле зрение слева + шаг
                    else if (map[coordinateNPC[i].x - 1][coordinateNPC[i].y - 1] == '@' ||
                        map[coordinateNPC[i].x - 1][coordinateNPC[i].y - 2] == '@' ||
                        map[coordinateNPC[i].x][coordinateNPC[i].y - 2] == '@' ||
                        map[coordinateNPC[i].x + 1][coordinateNPC[i].y - 1] == '@' ||
                        map[coordinateNPC[i].x + 1][coordinateNPC[i].y - 2] == '@')
                    {
                        stepLeft(map, coordinateNPC[i].x, coordinateNPC[i].y, 'D');
                        coordinateNPC[i].y--;
                    }
                }
            }
        }
    }
    system("CLS");
    file.open(nameFile[8], std::ios_base::in);
    
    string temp;

    while (!file.eof())
    {
        std::string tmp;
        file >> tmp;
        if (temp.empty())
            temp += tmp;
        else
            temp += '\n' + tmp;
    }

    cout << temp;
    file.close();
    return 0;
}

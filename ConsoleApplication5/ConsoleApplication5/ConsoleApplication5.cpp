#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
const int sirka = 40;
const int vyska = 20;
class Snake
{
private:
    int x, y;
    vector<pair<int, int>> body;

public:
    Snake(int sirka, int vyska)
    {
        x = sirka / 2;
        y = vyska / 2;
        body.push_back(make_pair(x, y));
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    vector<pair<int, int>> getBody()
    {
        return body;
    }

    void pohyb(char smer)
    {
        // pohni hada do specifickeho smeru
        switch (smer)
        {
        case 'w':
            y--;
            break;
        case 'a':
            x--;
            break;
        case 's':
            y++;
            break;
        case 'd':
            x++;
            break;
        }

        //posune hlavu hada na novou pozici tzv.
        body.insert(body.begin(), make_pair(x, y));

        //odstrani posledni cast hada 
        body.pop_back();
    }

    void grow()
    {
        // pridej novou cast na konec hada
        body.push_back(body[body.size() - 1]);
    }
};

class Fruit
{
private:
    int x, y;
public:
    Fruit(int width, int height)
    {
        srand(time(NULL));
        x = rand() % (width - 2) + 1;
        y = rand() % (height - 2) + 1;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    void vytvor()
    {
        //vytvor novou pozici pro nove ovoce
        srand(time(NULL));
        x = rand() % (sirka - 2) + 1;
        y = rand() % (vyska - 2) + 1;
    }
};

void draw(Snake had, Fruit fruit, int sirka, int vyska)
{
    system("cls");
    //nakresli horni hranici hraciho pole
    for (int i = 0; i < sirka + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < vyska; i++)
    {
        for (int j = 0; j < sirka; j++)
        {
            if (j == 0) {
                //prava hranice hraciho pole
                cout << "#";
            }
            if (i == had.getY() && j == had.getX())
                //hlava hada
                cout << "o";
            else if (i == fruit.getY() && j == fruit.getX())
                //ovoce
                cout << "F";
            else
            {
                bool printed = false;
                for (int k = 1; k < had.getBody().size(); k++)
                {
                    if (i == had.getBody()[k].second && j == had.getBody()[k].first)
                    {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }
                if (!printed)
                    cout << " ";
            }

            if (j == sirka - 1) {
                //leva hranice hranice pole
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < sirka + 2; i++)
        //spodni hranice
     cout << "#";
    cout << endl;
}

int main()
{

    char smer = 'd';

    Snake had(sirka, vyska);
    Fruit ovoce(sirka, vyska);
    draw(had, ovoce, sirka, vyska);

    while (true)
    {
        if (_kbhit())
        {
            char input = _getch();
            switch (input)
            {
            case 'w':
                if (smer != 's')
                    smer = 'w';
                break;
            case 'a':
                if (smer != 'd')
                    smer = 'a';
                break;
            case 's':
                if (smer != 'w')
                    smer = 's';
                break;
            case 'd':
                if (smer != 'a')
                    smer = 'd';
                break;
            case 'x':
                exit(0);
            }
        }
        // pohne se do specifickeho smeru daneho uzivatele / pokud uzivatel nezadal zadny smer tak had jede furt stejnym smerem
        had.pohyb(smer);

        // kontrola jestli had narazil do své části nebo do hrany hracího pole
        if (had.getX() == 0 || had.getX() == sirka - 1 || had.getY() == 0 || had.getY() == vyska - 1)
        {
            cout << "Konec hry GIT GUD" << endl;
            exit(0);
        }

        for (int i = 1; i < had.getBody().size(); i++)
        {
            if (had.getX() == had.getBody()[i].first && had.getY() == had.getBody()[i].second)
            {
                cout << "Konec hry GIT GUD" << endl;
                exit(0);
            }
        }

        // kontrola jestli had snedl ovoce
        if (had.getX() == ovoce.getX() && had.getY() == ovoce.getY())
        {
            //zvetsi hada
            had.grow();

            // generuj nove ovoce
            ovoce.vytvor();
        }

        draw(had, ovoce, sirka, vyska);

        //pockej 50 sekund a potom spust znovu hra se vzdy updatuje po 50ms 
        Sleep(50);
    }

    return 0;
}
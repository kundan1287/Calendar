#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int getkey();
void display(int, int, int, int[]);
void calendar(int, int);

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

const char* month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const char* week[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

int main() {
    int nmonth, nyr, ch;
enteryear:
    while (1) {
        cout << "Enter year and month(number): ";
        cin >> nyr >> nmonth;
        if (nyr < 1945) {
            cout << "\n\tPlease enter year above 1945\n";
            continue;
        } else {
            calendar(nyr, nmonth);
        }
        while (1) {
            gotoxy(20, 20); cout << "(*) Use LEFT, RIGHT, UP and DOWN arrow.";
            gotoxy(20, 22); cout << "(*) Press P to go to particular year and month.";
            gotoxy(20, 24); cout << "(*) Press ESC to Exit.";
            ch = getkey();
            switch (ch) {
                case 80: // DOWN ARROW
                    if (nmonth == 12) {
                        nmonth = 1;
                        nyr++;
                    } else {
                        nmonth++;
                    }
                    calendar(nyr, nmonth);
                    break;
                case 77: // RIGHT ARROW
                    nyr++;
                    calendar(nyr, nmonth);
                    break;
                case 72: // UP ARROW
                    if (nmonth == 1) {
                        nyr--;
                        nmonth = 12;
                    } else
                        nmonth--;
                    calendar(nyr, nmonth);
                    break;
                case 75: // LEFT ARROW
                    if (nyr == 1945) {
                        gotoxy(15, 2); cout << "Year below 1945 not available";
                    } else {
                        nyr--;
                        calendar(nyr, nmonth);
                    }
                    break;
                case 27: // ESC KEY
                    system("cls");
                    gotoxy(50, 14); cout << "Exiting program.\n\n\n\n\n";
                    exit(0);
                case 112: // P KEY
                    system("cls");
                    goto enteryear;
            }
        }
        break;
    }
    getch();
    return 0;
}

void display(int nyr, int nmonth, int tdays, int days[]) {
    int i, j, pos;
    SetColor(12);
    gotoxy(56, 6); cout << month[nmonth - 1] << " " << nyr;
    for (i = 0, pos = 30; i < 7; i++, pos += 10) {
        if (i == 6)
            SetColor(9);
        else
            SetColor(10);
        gotoxy(pos, 8); cout << week[i];
    }

    SetColor(15);

    tdays++;
    if (tdays == 0 || tdays == 7)
        pos = 91;
    if (tdays == 1)
        pos = 31;
    if (tdays == 2)
        pos = 41;
    if (tdays == 3)
        pos = 51;
    if (tdays == 4)
        pos = 61;
    if (tdays == 5)
        pos = 71;
    if (tdays == 6)
        pos = 81;

    for (i = 0, j = 10, pos; i < days[nmonth - 1]; i++, pos += 10) {
        if (pos == 91)
            SetColor(8);
        else
            SetColor(7);
        gotoxy(pos, j); cout << i + 1;
        if (pos == 91) {
            pos = 21;
            j++;
        }
    }

    SetColor(5);

    for (i = 22; i < 102; i++) {
        gotoxy(i, 4); cout << char(196);
        gotoxy(i, 17); cout << char(196);
    }

    gotoxy(21, 4); cout << char(218);
    gotoxy(102, 4); cout << char(191);
    gotoxy(21, 17); cout << char(192);
    gotoxy(102, 17); cout << char(217);

    for (i = 5; i < 17; i++) {
        gotoxy(21, i); cout << char(179);
        gotoxy(102, i); cout << char(179);
    }

    SetColor(11);

    gotoxy(24, 11); cout << char(174);
    gotoxy(98, 11); cout << char(175);
}

int getkey() {
    int ch;
    ch = getch();
    if (ch == 0) {
        cout << "zero";
        ch = getch();
        return ch;
    }
    return ch;
}

void calendar(int nyr, int nmonth) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int tdays = 0, k, myear;
    system("cls");
    myear = nyr - 1;
    if (myear >= 1945) {
        for (k = 1945; k <= myear; k++) {
            if (k % 4 == 0)
                tdays = tdays + 366;
            else
                tdays = tdays + 365;
        }
    }

    if (nyr % 4 == 0)
        days[1] = 29;
    else
        days[1] = 28;

    for (k = 0; k < (nmonth - 1); k++) {
        tdays = tdays + days[k];
    }

    tdays = tdays % 7;
    display(nyr, nmonth, tdays, days);
}
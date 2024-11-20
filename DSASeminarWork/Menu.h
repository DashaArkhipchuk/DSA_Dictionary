#pragma once

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;


class Menu {
private:
    const char** menuItems;
    size_t menuSize;
    int backgroundColor;
    int foregroundColor;
    int highlightColor;
    int cursorRow;
    int cursorColumn;

    void SetColor(unsigned short backColor, unsigned short foreColor) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD color = (backColor << 4) + foreColor;
        SetConsoleTextAttribute(h, color);
    }

    void SetCursor(unsigned short row, unsigned short column) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord{ column, row };
        SetConsoleCursorPosition(h, coord);
    }

    void DisplayMenu(size_t selected) {
        SetColor(backgroundColor, foregroundColor);
        system("cls");
        SetCursor(cursorRow, cursorColumn);
        std::cout << "_________________________Menu________________________________\n";

        for (size_t i = 0; i < menuSize; i++) {
            SetCursor(cursorRow + i + 1, cursorColumn);
            if (i == selected) {
                SetColor(backgroundColor, highlightColor);
                std::cout << "=> ";
            }
            else {
                std::cout << "   ";
            }
            SetColor(backgroundColor, foregroundColor);
            std::cout << menuItems[i] << std::endl;
        }
        SetColor(backgroundColor, foregroundColor);
    }

public:
    Menu(const char** items, size_t size, int bg = 1, int fg = 15, int hl = 4, int row = 5, int col = 20)
        : menuItems(items), menuSize(size), backgroundColor(bg), foregroundColor(fg),
        highlightColor(hl), cursorRow(row), cursorColumn(col) {}

    size_t Show(size_t initialSelection = 0) {
        size_t selection = initialSelection;
        unsigned char c;
        do {
            DisplayMenu(selection);
            c = _getch();
            switch (c) {
            case 72: // Up arrow
                selection = (selection == 0) ? menuSize - 1 : selection - 1;
                break;
            case 80: // Down arrow
                selection = (selection + 1) % menuSize;
                break;
            case 13: // Enter key
                return selection;
            }
        } while (true);
    }

    void SetColors(int bg, int fg, int hl) {
        backgroundColor = bg;
        foregroundColor = fg;
        highlightColor = hl;
    }

    void SetPosition(int row, int col) {
        cursorRow = row;
        cursorColumn = col;
    }
};

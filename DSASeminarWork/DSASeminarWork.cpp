#include <iostream>
#include <string>
#include "LinkedList.h"
#include "MultimapAVL.h"
#include "Menu.h"
using namespace std;

void InsertData(MultimapAVL& mmap) {
    std::string key, value;
    std::cout << "Enter the word: ";
    std::getline(std::cin >> std::ws, key);
    std::cout << "Enter the translation: ";
    std::getline(std::cin, value);
    mmap.insert(key, value);
    std::cout << "Inserted (" << key << ", " << value << ") into the dictionary.\n";
}


// Example usage
int main() {

    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    const char* textMenu[] = {
        "Exit",
        "Import data",
        "Export data",
        "Print the dictionary",
        "Insert new word with a translation",
        "Insert new translation to a word",
        "Find translations of a word",
        "Remove a word",
        "Remove a translation for the word",
        "Edit a word",
        "Edit word's translation",
        "Sort the translations"
    };

    const char* textMenu2[] = {
        "Return to previous menu",
        "Sort translations ascending",
        "Sort translations descending"
    };

    Menu mainMenu(textMenu, sizeof(textMenu) / sizeof(*textMenu));
    Menu sortMenu(textMenu2, sizeof(textMenu2) / sizeof(*textMenu2));

    MultimapAVL map;

    size_t select = 0;
    while (true) {
        select = mainMenu.Show();
        switch (select) {
        case 0:
            return 0;
        case 1:
            // Implement functionality for "Import data"
            std::cout << "Import data selected.\n";
            break;
        case 2:
            // Implement functionality for "Export data"
            std::cout << "Export data selected.\n";
            break;
        case 3:
            map.inorder();
            break;
        case 4:
            InsertData(map);
            break;
        case 11:
        {
            size_t sortSelection = sortMenu.Show();
            switch (sortSelection) {
            case 0:
                std::cout << "Returning to previous menu.\n";
                break;
            case 1:
                std::cout << "Sorting translations ascending.\n";
                break;
            case 2:
                std::cout << "Sorting translations descending.\n";
                break;
            }
        }
            break;
        default:
            std::cout << "Option not implemented yet.\n";
        }
        system("pause");
    }

    return 0;

    //MultimapAVL mmap;

    //// Inserting key-value pairs
    //mmap.insert("String 1", "Value 1-1");
    //mmap.insert("String 2", "Value 2-1");
    //mmap.insert("String 3", "Value 3-1");
    //mmap.insert("String 1", "Value 1-2");
    //mmap.insert("String 2", "Value 2-2");
    //mmap.insert("String 4", "Value 4-1");
    //mmap.insert("String 5", "Value 5-1");
    //mmap.insert("String 4", "Value 4-2");

    //cout << "Multimap contents (in-order traversal):\n";
    //mmap.inorder();

    //// Searching for values
    //string searchKey = "String 1";
    //LinkedList<string> values = mmap.find(searchKey);
    //if (!values.isEmpty()) {
    //    cout << "\nValues for key " << searchKey << ": ";
    //    values.printList();
    //}
    //else {
    //    cout << "\nKey " << searchKey << " not found.\n";
    //}

    //searchKey = "String 6";
    //values = mmap.find(searchKey);
    //if (!values.isEmpty()) {
    //    cout << "\nValues for key " << searchKey << ": ";
    //    values.printList();
    //}
    //else {
    //    cout << "\nKey " << searchKey << " not found.\n";
    //}

    //return 0;

}
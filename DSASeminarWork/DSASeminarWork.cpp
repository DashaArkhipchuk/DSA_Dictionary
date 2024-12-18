#include <iostream>
#include <string>
#include "LinkedList.h"
#include "MultimapAVL.h"
#include "Menu.h"
using namespace std;

void InsertData(MultimapAVL& mmap) {
    string key, value;
    cout << "Enter the word: ";
    getline(std::cin >> std::ws, key); // std::ws ignoring whitespaces
    cout << "Enter the translation: ";
    getline(std::cin, value);
    mmap.insert(key, value);
    cout << "Inserted (" << key << ", " << value << ") into the dictionary.\n";
}

void FindTranslations(MultimapAVL& mmap, string searchKey) {

    LinkedList<string> values = mmap.find(searchKey);
    if (!values.isEmpty()) {
        cout << "\nValues for key " << searchKey << ": ";
        values.printList();
    }
    else {
        cout << "\nKey " << searchKey << " not found.\n";
    }
}


// Helper function to export data to a file
void ExportData(MultimapAVL& map) {
    cout << "Enter the file name to export data: ";
    string filename;
    cin >> filename;
    try {
        map.exportToFile(filename);
        cout << "Data exported successfully to " << filename << ".\n";
    }
    catch (const exception& e) {
        cout << "Error exporting data: " << e.what() << "\n";
    }
}
void ImportData(MultimapAVL& map) {
    cout << "Enter the file name to import data: ";
    string filename;
    cin >> filename;
    try {
        map.importFromFile(filename);
        cout << "Data imported successfully from " << filename << ".\n";
    }
    catch (const exception& e) {
        cout << "Error importing data: " << e.what() << "\n";
    }
}

void RemoveKey(MultimapAVL& mmap, string searchKey) {
    mmap.remove(searchKey);

}

void RemoveValue(MultimapAVL& mmap) {
    string key, value;
    cout << "Enter the word: ";
    getline(std::cin >> std::ws, key); // std::ws ignoring whitespaces
    cout << "Enter the translation: ";
    getline(std::cin, value);
    mmap.removeValue(key, value);
}

void EditTranslation(MultimapAVL& mmap) {
    string key, value, newvalue;
    cout << "Enter the word: ";
    getline(std::cin >> std::ws, key); // std::ws ignoring whitespaces
    cout << "Enter old translation: ";
    getline(std::cin, value);
    cout << "Enter new translation: ";
    getline(std::cin, newvalue);
    mmap.editValue(key, value, newvalue);
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
        "Insert a word with a translation",
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
            ImportData(map);
            break;
        case 2:
            ExportData(map);
            break;
        case 3:
            map.inorder();
            break;
        case 4:
            InsertData(map);
            break;
        case 5:
        {
            string searchKey;
            cout << "Enter the word: ";
            getline(std::cin >> std::ws, searchKey);
            FindTranslations(map, searchKey);
        }
        break;
        case 6:
        {
            string searchKey;
            cout << "Enter the word: ";
            getline(std::cin >> std::ws, searchKey);
            RemoveKey(map, searchKey);
        }
            break;
        case 7:
            RemoveValue(map);
            break;
        case 8:
            break;
        case 9:
            EditTranslation(map);
            break;
        case 10:
        {
            size_t sortSelection = sortMenu.Show();
            switch (sortSelection) {
            case 0:
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
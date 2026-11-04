#include <iostream>
#include <limits>
#include <string>
#include "CircularLinkedList/CircularLinkedList.h"

using namespace std;

int main() {
    CircularList collection;
    int choice = 0;
    int id, index, index1, index2;
    string name;

    do {
        cout << "\\n===== CIRCULAR MUSIC PLAYLIST MANAGER =====\\n";
        cout << "1. Display All Songs\\n";
        cout << "2. Insert Song at Head\\n";
        cout << "3. Remove Song from Head\\n";
        cout << "4. Insert Song at Index\\n";
        cout << "5. Remove Song at Index\\n";
        cout << "6. Swap Songs\\n";
        cout << "7. Sort Songs by ID\\n";
        cout << "8. Reverse Collection\\n";
        cout << "9. Move to Next Song\\n";
        cout << "10. Check Collection Status\\n";
        cout << "11. Exit\\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\\n";
            continue;
        }

        switch (choice) {
        case 1:
            collection.Print("song");
            break;
        case 2:
            cout << "Enter song ID: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\\n";
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter song title/name: ";
            getline(cin, name);
            collection.Insert(CreateItem(id, name));
            cout << "Song inserted at head.\\n";
            break;
        case 3: {
            ItemNode* removed = collection.Remove();
            if (removed != nullptr) {
                cout << "Removed: " << removed->id << " - " << removed->name << '\n';
                delete removed;
            } else {
                cout << "Collection is empty.\\n";
            }
            break;
        }
        case 4:
            cout << "Enter song ID: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\\n";
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter song title/name: ";
            getline(cin, name);
            cout << "Enter index (starting from 0): ";
            if (!(cin >> index)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index.\\n";
                break;
            }
            collection.InsertAt(CreateItem(id, name), index);
            cout << "Song inserted.\\n";
            break;
        case 5:
            cout << "Enter index (starting from 0): ";
            if (!(cin >> index)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index.\\n";
                break;
            }
            {
                ItemNode* removed = collection.RemoveAt(index);
                if (removed != nullptr) {
                    cout << "Removed: " << removed->name << '\n';
                    delete removed;
                } else {
                    cout << "Collection is empty.\\n";
                }
            }
            break;
        case 6:
            cout << "Enter first index: ";
            if (!(cin >> index1)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index.\\n";
                break;
            }
            cout << "Enter second index: ";
            if (!(cin >> index2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid index.\\n";
                break;
            }
            if (collection.Swap(index1, index2))
                cout << "Songs swapped.\\n";
            else
                cout << "Collection is empty.\\n";
            break;
        case 7:
            collection.Sort();
            cout << "Songs sorted by ID.\\n";
            break;
        case 8:
            collection.Reverse();
            cout << "Collection reversed.\\n";
            break;
        case 9: {
            ItemNode* item = collection.MoveToNext();
            if (item != nullptr)
                cout << "Now displaying: " << item->id << " - " << item->name << '\n';
            else
                cout << "Collection is empty.\\n";
            break;
        }
        case 10:
            cout << (collection.IsEmpty() ? "Collection is empty.\\n"
                                         : "Collection is not empty.\\n");
            cout << "Total songs: " << collection.Size() << '\n';
            break;
        case 11:
            cout << "Exiting program.\\n";
            break;
        default:
            cout << "Invalid choice. Try again.\\n";
        }
    } while (choice != 11);

    return 0;
}

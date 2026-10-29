#include <iostream>
#include "CircularLibraryList.h"

int main() {
    CircularLibraryList library;

    // Add initial books
    library.InsertAt(library.CreateBook(103, "Operating Systems"), 0);
    library.InsertAt(library.CreateBook(101, "Data Structures"), 1);
    library.InsertAt(library.CreateBook(105, "Computer Networks"), 2);
    library.InsertAt(library.CreateBook(102, "Database Systems"), 3);
    library.InsertAt(library.CreateBook(104, "Software Engineering"), 4);

    std::cout << "INITIAL CIRCULAR BOOK COLLECTION";
    library.Print();

    // Insert at index 2
    library.InsertAt(library.CreateBook(106, "Artificial Intelligence"), 2);
    std::cout << "\nAFTER INSERTING AT INDEX 2";
    library.Print();

    // Remove at index 1
    BookNode* removed = library.RemoveAt(1);
    if (removed != nullptr) {
        std::cout << "\nRemoved: " << removed->title << "\n";
        delete removed;
    }
    std::cout << "\nAFTER REMOVING INDEX 1";
    library.Print();

    // Swap indexes 0 and 2
    library.Swap(0, 2);
    std::cout << "\nAFTER SWAPPING INDEX 0 AND 2";
    library.Print();

    // Sort by book ID
    library.Sort();
    std::cout << "\nAFTER SORTING BY BOOK ID";
    library.Print();

    // Reverse the circular list
    library.Reverse();
    std::cout << "\nAFTER REVERSING";
    library.Print();

    // Insert at the node next to head (front)
    library.Insert(library.CreateBook(100, "Programming Fundamentals"));
    std::cout << "\nAFTER INSERT AT HEAD'S NEXT NODE";
    library.Print();

    // Remove from the node next to head
    removed = library.Remove();
    if (removed != nullptr) {
        std::cout << "\nRemoved from head's next: " << removed->title << "\n";
        delete removed;
    }
    std::cout << "\nFINAL CIRCULAR BOOK COLLECTION";
    library.Print();

    return 0;
}
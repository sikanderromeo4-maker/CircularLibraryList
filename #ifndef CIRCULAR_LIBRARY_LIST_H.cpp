#ifndef CIRCULAR_LIBRARY_LIST_H
#define CIRCULAR_LIBRARY_LIST_H

#include "BookNode.h"
#include <iostream>

class CircularLibraryList {
private:
    BookNode* head; // Points to the LAST node (pivot)
    int count;

    // Helper to normalize indexes (including negatives)
    int NormalizeIndex(int index);
    // Helper to get a node at a specific logical index
    BookNode* GetNodeAt(int index);
    // Helper to swap data
    void SwapData(BookNode* a, BookNode* b);

public:
    CircularLibraryList();
    ~CircularLibraryList();
    
    // Copy Constructor and Assignment Operator (Rule of Three)
    CircularLibraryList(const CircularLibraryList& other);
    CircularLibraryList& operator=(const CircularLibraryList& other);

    bool IsEmpty();
    bool IsNotEmpty();

    // Core operations
    void Insert(BookNode* book);       // Insert at front (next to head)
    BookNode* Remove();                // Remove from front (next to head)
    void InsertAt(BookNode* book, int index);
    BookNode* RemoveAt(int index);
    
    // Additional required functions
    void Swap(int index1, int index2);
    void Sort();
    void Reverse();
    void Print();
    
    // Create node utility
    BookNode* CreateBook(int id, std::string title);
};

#endif
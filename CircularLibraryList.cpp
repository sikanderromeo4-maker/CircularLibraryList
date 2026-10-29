#include "CircularLibraryList.h"
#include <algorithm>
#include <utility>

CircularLibraryList::CircularLibraryList() {
    head = nullptr;
    count = 0;
}

CircularLibraryList::~CircularLibraryList() {
    while (IsNotEmpty()) {
        delete Remove();
    }
}

bool CircularLibraryList::IsEmpty() { return count == 0; }
bool CircularLibraryList::IsNotEmpty() { return count > 0; }

int CircularLibraryList::NormalizeIndex(int index) {
    return ((index % count) + count) % count;
}

BookNode* CircularLibraryList::GetNodeAt(int index) {
    if (head == nullptr) return nullptr;
    BookNode* current = head->next; // Start at the first logical node
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

BookNode* CircularLibraryList::CreateBook(int id, std::string title) {
    BookNode* book = new BookNode;
    book->bookID = id;
    book->title = title;
    book->next = nullptr;
    return book;
}

void CircularLibraryList::Insert(BookNode* book) {
    if (book == nullptr) return;
    if (head == nullptr) {
        head = book;
        book->next = book;
    } else {
        book->next = head->next;
        head->next = book;
    }
    count++;
}

BookNode* CircularLibraryList::Remove() {
    if (IsEmpty()) return nullptr;
    BookNode* first = head->next;
    if (first == head) {
        head = nullptr;
    } else {
        head->next = first->next;
    }
    first->next = nullptr;
    count--;
    return first;
}

void CircularLibraryList::InsertAt(BookNode* book, int index) {
    if (book == nullptr) return;
    if (count == 0) {
        head = book;
        book->next = book;
        count++;
        return;
    }
    if (index < 0) index = NormalizeIndex(index);
    if (index > count) index %= count;

    if (index == 0) {
        Insert(book);
        return;
    }
    if (index == count) {
        book->next = head->next;
        head->next = book;
        head = book; // Update pivot to new last node
        count++;
        return;
    }

    BookNode* prev = GetNodeAt(index - 1);
    book->next = prev->next;
    prev->next = book;
    count++;
}

BookNode* CircularLibraryList::RemoveAt(int index) {
    if (IsEmpty()) return nullptr;
    if (index < 0) index = NormalizeIndex(index);
    if (index >= count) index %= count;

    if (index == 0) return Remove();

    BookNode* prev = GetNodeAt(index - 1);
    BookNode* toRemove = prev->next;
    prev->next = toRemove->next;
    
    // If we are removing the last node (head pivot)
    if (toRemove == head) {
        head = prev; 
    }
    
    toRemove->next = nullptr;
    count--;
    return toRemove;
}

void CircularLibraryList::Print() {
    if (IsEmpty()) {
        std::cout << "No books in the collection.\n";
        return;
    }
    BookNode* current = head->next;
    std::cout << "\nIndex\tBook ID\tTitle\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < count; i++) {
        std::cout << i << "\t" << current->bookID << "\t" << current->title << "\n";
        current = current->next;
    }
    std::cout << "Total books: " << count << "\n";
}

// --- Previously Implemented Lab 5 Features added to Circle ---

void CircularLibraryList::SwapData(BookNode* a, BookNode* b) {
    std::swap(a->bookID, b->bookID);
    std::swap(a->title, b->title);
}

void CircularLibraryList::Swap(int index1, int index2) {
    if (IsEmpty()) return;
    index1 = NormalizeIndex(index1);
    index2 = NormalizeIndex(index2);
    BookNode* node1 = GetNodeAt(index1);
    BookNode* node2 = GetNodeAt(index2);
    SwapData(node1, node2);
}

void CircularLibraryList::Sort() {
    if (count < 2) return;
    // Bubble sort on circular list
    for (int i = 0; i < count - 1; i++) {
        BookNode* current = head->next;
        for (int j = 0; j < count - i - 1; j++) {
            if (current->bookID > current->next->bookID) {
                SwapData(current, current->next);
            }
            current = current->next;
        }
    }
}

void CircularLibraryList::Reverse() {
    if (count < 2) return;
    
    BookNode* prev = head;
    BookNode* current = head->next;
    BookNode* nextNode = nullptr;
    BookNode* first = head->next;

    // Traverse and reverse links
    for (int i = 0; i < count; i++) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    
    head = first; // The old first becomes the new last (pivot)
}

// Rule of Three implementations
CircularLibraryList::CircularLibraryList(const CircularLibraryList& other) {
    head = nullptr; count = 0;
    if (other.head == nullptr) return;
    BookNode* current = other.head->next;
    for (int i = 0; i < other.count; i++) {
        InsertAt(CreateBook(current->bookID, current->title), count);
        current = current->next;
    }
}

CircularLibraryList& CircularLibraryList::operator=(const CircularLibraryList& other) {
    if (this == &other) return *this;
    while (IsNotEmpty()) delete Remove();
    if (other.head == nullptr) return *this;
    BookNode* current = other.head->next;
    for (int i = 0; i < other.count; i++) {
        InsertAt(CreateBook(current->bookID, current->title), count);
        current = current->next;
    }
    return *this;
}
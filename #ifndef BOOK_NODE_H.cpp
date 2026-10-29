#ifndef BOOK_NODE_H
#define BOOK_NODE_H

#include <string>

// Self-referential structure for the book node
struct BookNode {
    int bookID;
    std::string title;
    BookNode* next;
};

#endif
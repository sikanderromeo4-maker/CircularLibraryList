#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <string>

struct ItemNode {
    int id;
    std::string name;
    ItemNode* next;
};

class CircularList {
private:
    ItemNode* head;
    ItemNode* currentItem;
    int count;

    ItemNode* GetNodeAt(int index);
    int NormalizeIndex(int index) const;
    void SwapData(ItemNode* first, ItemNode* second);

public:
    CircularList();
    CircularList(const CircularList&) = delete;
    CircularList& operator=(const CircularList&) = delete;
    ~CircularList();

    bool IsEmpty() const;
    bool IsNotEmpty() const;
    int Size() const;
    void Insert(ItemNode* item);
    ItemNode* Remove();
    void InsertAt(ItemNode* item, int index);
    ItemNode* RemoveAt(int index);
    bool Swap(int index1, int index2);
    void Sort();
    void Reverse();
    void Print(const std::string& itemLabel) const;
    ItemNode* MoveToNext();
};

ItemNode* CreateItem(int id, const std::string& name);

#endif

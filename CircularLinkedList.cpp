#include "CircularLinkedList.h"
#include <iostream>
#include <utility>

CircularList::CircularList() : head(nullptr), currentItem(nullptr), count(0) {}

ItemNode* CircularList::GetNodeAt(int index) {
    if (head == nullptr)
        return nullptr;
    ItemNode* current = head->next;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}

int CircularList::NormalizeIndex(int index) const {
    return ((index % count) + count) % count;
}

void CircularList::SwapData(ItemNode* first, ItemNode* second) {
    std::swap(first->id, second->id);
    std::swap(first->name, second->name);
}

bool CircularList::IsEmpty() const { return count == 0; }
bool CircularList::IsNotEmpty() const { return count > 0; }
int CircularList::Size() const { return count; }

void CircularList::Insert(ItemNode* item) {
    if (item == nullptr)
        return;
    if (head == nullptr) {
        head = item;
        item->next = item;
    } else {
        item->next = head->next;
        head->next = item;
    }
    if (currentItem == nullptr)
        currentItem = item;
    count++;
}

ItemNode* CircularList::Remove() {
    if (IsEmpty())
        return nullptr;
    ItemNode* first = head->next;
    if (first == head) {
        head = nullptr;
        currentItem = nullptr;
    } else {
        head->next = first->next;
        if (currentItem == first)
            currentItem = first->next;
    }
    first->next = nullptr;
    count--;
    return first;
}

void CircularList::InsertAt(ItemNode* item, int index) {
    if (item == nullptr)
        return;
    if (count == 0) {
        head = item;
        item->next = item;
        currentItem = item;
        count++;
        return;
    }
    if (index == count) {
        item->next = head->next;
        head->next = item;
        head = item;
        count++;
        return;
    }
    if (index < 0 || index >= count)
        index = NormalizeIndex(index);
    if (index == 0) {
        Insert(item);
        return;
    }
    ItemNode* previous = GetNodeAt(index - 1);
    item->next = previous->next;
    previous->next = item;
    count++;
}

ItemNode* CircularList::RemoveAt(int index) {
    if (IsEmpty())
        return nullptr;
    index = NormalizeIndex(index);
    if (index == 0)
        return Remove();
    ItemNode* previous = GetNodeAt(index - 1);
    ItemNode* target = previous->next;
    previous->next = target->next;
    if (target == head)
        head = previous;
    if (currentItem == target)
        currentItem = target->next;
    target->next = nullptr;
    count--;
    return target;
}

bool CircularList::Swap(int index1, int index2) {
    if (IsEmpty())
        return false;
    index1 = NormalizeIndex(index1);
    index2 = NormalizeIndex(index2);
    if (index1 != index2)
        SwapData(GetNodeAt(index1), GetNodeAt(index2));
    return true;
}

void CircularList::Sort() {
    if (count < 2)
        return;
    ItemNode* current = head->next;
    for (int i = 0; i < count - 1; i++) {
        ItemNode* nextNode = current->next;
        for (int j = i + 1; j < count; j++) {
            if (current->id > nextNode->id)
                SwapData(current, nextNode);
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

void CircularList::Reverse() {
    if (count < 2)
        return;
    ItemNode* oldTail = head;
    ItemNode* oldFirst = head->next;
    ItemNode* previous = oldTail;
    ItemNode* current = oldFirst;
    while (current != oldTail) {
        ItemNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }
    oldTail->next = previous;
    head = oldFirst;
    currentItem = head->next;
}

void CircularList::Print(const std::string& itemLabel) const {
    if (IsEmpty()) {
        std::cout << "No " << itemLabel << "s in the collection.\n";
        return;
    }
    ItemNode* current = head->next;
    std::cout << "\nIndex\tID\t" << itemLabel << "\n";
    for (int i = 0; i < count; i++) {
        std::cout << i << '\t' << current->id << '\t' << current->name << '\n';
        current = current->next;
    }
    std::cout << "Total " << itemLabel << "s: " << count << '\n';
}

ItemNode* CircularList::MoveToNext() {
    if (IsEmpty())
        return nullptr;
    if (currentItem == nullptr)
        currentItem = head->next;
    else
        currentItem = currentItem->next;
    return currentItem;
}

CircularList::~CircularList() {
    while (!IsEmpty())
        delete Remove();
}

ItemNode* CreateItem(int id, const std::string& name) {
    ItemNode* item = new ItemNode;
    item->id = id;
    item->name = name;
    item->next = nullptr;
    return item;
}

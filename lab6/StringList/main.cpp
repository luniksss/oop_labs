#include <iostream>
#include "include/CStringList.h"

int main() {
    CStringList list;
    list.PushBack("World");
    list.PushFront("Hello");

    for (auto& s : list) {
        std::cout << s << " ";
    }

    auto it = list.begin();
    ++it;
    list.Insert(it, "C++");

    list.Erase(list.begin());

    for (auto& s : list)
    {
        std::cout << s << " ";
    }
}

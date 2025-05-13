#ifndef CSTRINGLIST_H
#define CSTRINGLIST_H
#include <cassert>
#include <iostream>
#include <string>
#include "CStringNode.h"
#include "CStringIterator.h"
#include <memory>

class CStringList
{
public:
    using Iterator = CStringIterator;

    CStringList() = default;
    ~CStringList();

    void PushFront(const std::string& data);
    void PushBack(const std::string& data);
    Iterator Insert(Iterator pos, const std::string& data);
    Iterator Erase(Iterator pos);

    size_t Size() const noexcept { return m_size; }
    bool Empty() const noexcept { return m_size == 0; }

    Iterator begin() noexcept { return Iterator{m_head.get()}; }
    Iterator end() noexcept { return Iterator{nullptr}; }

private:
    std::unique_ptr<CStringNode> m_head;
    CStringNode* m_tail = nullptr;
    size_t m_size = 0;
};

#endif //CSTRINGLIST_H

#ifndef CSTRINGLIST_H
#define CSTRINGLIST_H
#include <cassert>
#include <iostream>
#include <string>
#include "CStringNode.h"
#include "CStringIterator.h"
#include "CStringConstIterator.h"
#include <memory>

class CStringList
{
public:
    using Iterator = CStringIterator;
    using ConstIterator = CStringConstIterator;

    CStringList() = default;
    CStringList(const CStringList& other);
    CStringList(CStringList &&other) noexcept;
    ~CStringList();

    void PushFront(const std::string& data);
    void PushBack(const std::string& data);
    Iterator Insert(Iterator pos, const std::string& data);
    Iterator Erase(Iterator pos);
    void Clear() noexcept;

    CStringList &operator=(const CStringList &other);
    CStringList &operator=(CStringList &&other) noexcept;

    size_t Size() const noexcept { return m_size; }
    bool Empty() const noexcept { return m_size == 0; }

    Iterator begin() noexcept { return Iterator{m_head.get()}; }
    Iterator end() noexcept { return Iterator{nullptr}; }

    ConstIterator begin() const noexcept { return ConstIterator{m_head.get()}; }
    ConstIterator end() const noexcept { return ConstIterator{nullptr}; }

    ConstIterator cbegin() const noexcept { return begin(); }
    ConstIterator cend() const noexcept { return end(); }

private:
    std::unique_ptr<CStringNode> m_head;
    CStringNode* m_tail = nullptr;
    size_t m_size = 0;
};

#endif //CSTRINGLIST_H
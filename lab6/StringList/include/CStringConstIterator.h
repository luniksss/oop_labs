#ifndef CSTRINGCONSTITERATOR_H
#define CSTRINGCONSTITERATOR_H
#pragma once
#include "CStringNode.h"
#include <iterator>

class CStringConstIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const std::string;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    explicit CStringConstIterator(const CStringNode* node);
    CStringConstIterator(const class CStringIterator& it);

    reference operator*() const;
    pointer operator->() const;

    CStringConstIterator& operator++();
    CStringConstIterator operator++(int);
    CStringConstIterator& operator--();
    CStringConstIterator operator--(int);

    bool operator==(const CStringConstIterator& other) const;
    bool operator!=(const CStringConstIterator& other) const;

    const CStringNode* GetNode() const { return m_node; }

private:
    const CStringNode* m_node;
};
#endif //CSTRINGCONSTITERATOR_H
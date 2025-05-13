#ifndef CSTRINGITERATOR_H
#define CSTRINGITERATOR_H
#include "CStringNode.h"
#include <iterator>

class CStringIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::string;
    using pointer = value_type*;
    using reference = value_type&;

    explicit CStringIterator(CStringNode* node = nullptr);

    reference operator*() const;
    pointer operator->() const;

    CStringIterator& operator++();
    CStringIterator operator++(int);
    CStringIterator& operator--();
    CStringIterator operator--(int);

    bool operator==(const CStringIterator& other) const;
    bool operator!=(const CStringIterator& other) const;

    [[nodiscard]] CStringNode *GetNode() const;

protected:
    CStringNode* m_node;
};
#endif //CSTRINGITERATOR_H

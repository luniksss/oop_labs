#include "../include/CStringConstIterator.h"
#include "../include/CStringIterator.h"
#include <stdexcept>

CStringConstIterator::CStringConstIterator(const CStringNode* node)
    : m_node(node)
{}

CStringConstIterator::CStringConstIterator(const CStringIterator& it)
    : m_node(it.GetNode())
{}

auto CStringConstIterator::operator*() const -> reference
{
    if (!m_node) throw std::runtime_error("Dereferencing invalid iterator");
    return m_node->data;
}

auto CStringConstIterator::operator->() const -> pointer
{
    return &operator*();
}

CStringConstIterator& CStringConstIterator::operator++()
{
    if (m_node) m_node = m_node->GetNext().get();
    return *this;
}

CStringConstIterator CStringConstIterator::operator++(int)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

CStringConstIterator& CStringConstIterator::operator--()
{
    if (m_node) m_node = m_node->GetPrev();
    return *this;
}

CStringConstIterator CStringConstIterator::operator--(int)
{
    auto tmp = *this;
    --(*this);
    return tmp;
}

bool CStringConstIterator::operator==(const CStringConstIterator& other) const
{
    return m_node == other.m_node;
}

bool CStringConstIterator::operator!=(const CStringConstIterator& other) const
{
    return !(*this == other);
}
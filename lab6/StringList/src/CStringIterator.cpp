#include "../include/CStringIterator.h"
#include <stdexcept>

CStringIterator::CStringIterator(CStringNode* node) : m_node(node) {}

std::string& CStringIterator::operator*() const
{
    if (!m_node) throw std::runtime_error("Dereferencing invalid iterator");
    return m_node->data;
}

std::string* CStringIterator::operator->() const
{
    return &operator*();
}

CStringIterator& CStringIterator::operator++()
{
    if (m_node) m_node = m_node->m_next.get();
    return *this;
}

CStringIterator CStringIterator::operator++(int)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

CStringIterator& CStringIterator::operator--()
{
    if (m_node) m_node = m_node->m_prev;
    return *this;
}

CStringIterator CStringIterator::operator--(int)
{
    auto tmp = *this;
    --(*this);
    return tmp;
}

bool CStringIterator::operator==(const CStringIterator& other) const
{
    return m_node == other.m_node;
}

bool CStringIterator::operator!=(const CStringIterator& other) const
{
    return !(*this == other);
}

CStringNode *CStringIterator::GetNode() const
{
    return m_node;
}
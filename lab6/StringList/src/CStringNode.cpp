// CStringNode.cpp
#include "../include/CStringNode.h"

CStringNode::CStringNode(std::string data)
    : data(std::move(data)) {}

CStringNode::CStringNode(std::string data, CStringNode* prev, std::unique_ptr<CStringNode>&& next)
    : data(std::move(data)), m_prev(prev), m_next(std::move(next)) {}

CStringNode* CStringNode::GetPrev() const
{
    return m_prev;
}

std::unique_ptr<CStringNode>& CStringNode::GetNext()
{
    return m_next;
}

void CStringNode::SetPrev(CStringNode* prev)
{
    m_prev = prev;
}

void CStringNode::SetNext(std::unique_ptr<CStringNode>&& next)
{
    m_next = std::move(next);
}
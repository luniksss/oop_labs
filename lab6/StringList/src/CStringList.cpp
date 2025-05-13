#include "../include/CStringList.h"

CStringList::CStringList(const CStringList& other)
{
    for (const auto & it : other)
    {
        PushBack(it);
    }
}

CStringList::CStringList(CStringList&& other) noexcept
{
    m_head = std::move(other.m_head);
    m_tail = other.m_tail;
    m_size = other.m_size;
    other.m_tail = nullptr;
    other.m_size = 0;
}

CStringList::~CStringList()
{
    while (m_head)
    {
        m_head = std::move(m_head->m_next);
    }
}

void CStringList::PushFront(const std::string& data)
{
    auto newNode = std::make_unique<CStringNode>(data, nullptr, std::move(m_head));
    if (newNode->m_next)
    {
        newNode->m_next->m_prev = newNode.get();
    }
    else
    {
        m_tail = newNode.get();
    }
    m_head = std::move(newNode);
    ++m_size;
}

void CStringList::PushBack(const std::string& data)
{
    auto newNode = std::make_unique<CStringNode>(data, m_tail, nullptr);
    if (m_tail)
    {
        m_tail->m_next = std::move(newNode);
        m_tail = m_tail->m_next.get();
    }
    else
    {
        m_head = std::move(newNode);
        m_tail = m_head.get();
    }
    ++m_size;
}

CStringIterator CStringList::Insert(CStringIterator pos, const std::string& data)
{
    if (!pos.GetNode())
    {
        PushBack(data);
        return CStringIterator(m_tail);
    }

    auto newNode = std::make_unique<CStringNode>(data);
    CStringNode* current = pos.GetNode();
    CStringNode* prev = current->m_prev;

    newNode->m_next = std::move(prev ? prev->m_next : m_head);
    newNode->m_prev = prev;
    current->m_prev = newNode.get();

    if (prev)
    {
        prev->m_next = std::move(newNode);
    } else
    {
        m_head = std::move(newNode);
    }

    ++m_size;
    return CStringIterator(current->m_prev);
}

CStringIterator CStringList::Erase(CStringIterator pos)
{
    if (!pos.GetNode()) return end();

    CStringNode* current = pos.GetNode();
    CStringNode* next = current->m_next.get();
    CStringNode* prev = current->m_prev;

    if (prev)
    {
        prev->m_next = std::move(current->m_next);
    }
    else
    {
        m_head = std::move(current->m_next);
    }

    if (next)
    {
        next->m_prev = prev;
    }
    else
    {
        m_tail = prev;
    }

    --m_size;
    return CStringIterator(next);
}

void CStringList::Clear() noexcept
{
    m_head.reset();
    m_tail = nullptr;
    m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& other)
{
    if (this != &other)
    {
        Clear();
        for (const auto & it : other)
        {
            PushBack(it);
        }
    }
    return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        m_head = std::move(other.m_head);
        m_tail = other.m_tail;
        m_size = other.m_size;
        other.m_tail = nullptr;
        other.m_size = 0;
    }
    return *this;
}

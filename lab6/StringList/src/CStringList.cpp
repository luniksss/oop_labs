#include "../include/CStringList.h"

CStringList::~CStringList()
{
    while (m_head) {
        m_head = std::move(m_head->m_next);
    }
}

void CStringList::PushFront(const std::string& data) {
    auto newNode = std::make_unique<CStringNode>(data, nullptr, std::move(m_head));
    if (newNode->m_next) {
        newNode->m_next->m_prev = newNode.get();
    }
    else {
        m_tail = newNode.get();
    }
    m_head = std::move(newNode);
    ++m_size;
}

void CStringList::PushBack(const std::string& data) {
    auto newNode = std::make_unique<CStringNode>(data, m_tail, nullptr);
    if (m_tail) {
        m_tail->m_next = std::move(newNode);
        m_tail = m_tail->m_next.get();
    }
    else {
        m_head = std::move(newNode);
        m_tail = m_head.get();
    }
    ++m_size;
}

CStringList::Iterator CStringList::Insert(Iterator pos, const std::string& data) {
    if (!pos.GetNode())
    {
        PushBack(data);
        return Iterator{m_tail};
    }

    CStringNode* currentNode = pos.GetNode();
    CStringNode* prevNode = currentNode->GetPrev();

    auto newNode = std::make_unique<CStringNode>(data, prevNode, nullptr);
    newNode->SetNext(std::move(prevNode ? prevNode->GetNext() : m_head));

    currentNode->SetPrev(newNode.get());
    newNode->SetPrev(prevNode);

    if (newNode->GetPrev()) {
        newNode->GetPrev()->SetNext(std::move(newNode));
    } else {
        m_head = std::move(newNode);
    }

    ++m_size;
    return Iterator{currentNode->GetPrev()};
}

CStringList::Iterator CStringList::Erase(Iterator pos) {
    CStringNode* currentNode = pos.GetNode();
    if (!currentNode) return end();

    std::unique_ptr<CStringNode> nextNode = std::move(currentNode->GetNext());
    CStringNode* prevNode = currentNode->GetPrev();

    if (prevNode) {
        prevNode->SetNext(std::move(nextNode));
    } else {
        m_head = std::move(nextNode);
    }

    if (m_head) {
        m_head->SetPrev(nullptr);
    } else {
        m_tail = nullptr;
    }

    --m_size;
    return Iterator{m_head.get()};
}
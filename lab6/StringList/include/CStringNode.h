#ifndef CSTRINGNODE_H
#define CSTRINGNODE_H
#include <memory>
#include <string>

class CStringNode
{
public:
    std::string data;
    CStringNode* m_prev = nullptr;
    std::unique_ptr<CStringNode> m_next = nullptr;

    explicit CStringNode(std::string data);
    CStringNode(std::string data, CStringNode* m_prev, std::unique_ptr<CStringNode>&& m_next);

    [[nodiscard]] CStringNode* GetPrev() const;
    [[nodiscard]] const std::unique_ptr<CStringNode>& GetNext() const;
    std::unique_ptr<CStringNode>& GetNext();
    void SetPrev(CStringNode* prev);
    void SetNext(std::unique_ptr<CStringNode>&& next);
};

#endif //CSTRINGNODE_H

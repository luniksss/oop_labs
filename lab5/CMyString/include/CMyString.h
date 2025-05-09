#ifndef CMYSTRING_H
#define CMYSTRING_H
#include <string>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    CMyString(std::string const& stlString);

    ~CMyString();

    size_t GetLength() const;
    const char* GetStringData() const;
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
    void Clear();
    size_t GetCapacity() const;

    CMyString& operator=(const CMyString& str);
    CMyString& operator=(CMyString&& str) noexcept;

    CMyString operator+(const CMyString& str) const;
    friend CMyString operator+(const std::string& stlString, const CMyString& str);
    friend CMyString operator+(const char* chars, const CMyString& str);
    CMyString& operator+=(const CMyString& str);

    bool operator==(const CMyString& str) const;
    bool operator!=(const CMyString& str) const;
    std::strong_ordering operator<=>(const CMyString& str) const;

    const char& operator[](size_t index) const;
    char& operator[](size_t index);

    friend std::ostream& operator<<(std::ostream& strm, CMyString const& str);
    friend std::istream& operator>>(std::istream& strm, CMyString& str);
private:
    explicit CMyString(size_t length);
    int Compare(const CMyString& str) const;
    static const char STRING_END = '\0';
    static const char LINE_END = '\n';

    size_t m_length;
    size_t m_capacity;
    char* m_chars;

};

#endif //CMYSTRING_H
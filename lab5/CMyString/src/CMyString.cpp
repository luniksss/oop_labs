#include <cassert>
#include <iostream>
#include "../include/CMyString.h"
#include <String.h>
//https://isocpp.org/wiki/faq/ctors#static-init-order

CMyString::CMyString()
	: m_length(0),
	  m_capacity(1),
	  m_chars(nullptr)
{}

CMyString::CMyString(const char* pString)
{
	if (pString == nullptr)
	{
		throw std::invalid_argument("string is NULL");
	}

	m_length = strlen(pString);
	m_capacity = m_length + 1;
	m_chars = new char[m_capacity];
	strcpy(m_chars, pString);
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr && length > 0)
	{
		throw std::invalid_argument("string is NULL");
	}

	m_length = length;
	m_capacity = length + 1;
	m_chars = new char[m_capacity];

	if (length > 0)
	{
		strncpy(m_chars, pString, length);
	}
	m_chars[length] = STRING_END;
}

CMyString::CMyString(const CMyString& other)
	: m_length(other.m_length),
	  m_capacity(other.m_capacity),
	  m_chars(new char[other.m_capacity])
{
	memcpy(m_chars, other.m_chars, m_length + 1);
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_length(other.m_length),
	  m_capacity(other.m_capacity),
	  m_chars(other.m_chars)
{
	other.m_chars = nullptr;
	other.m_length = 0;
	other.m_capacity = 1;
}

CMyString::CMyString(std::string const& stlString)
	: m_length(stlString.size()),
	  m_capacity(stlString.size() + 1),
	  m_chars(new char[m_capacity])
{
	memcpy(m_chars, stlString.c_str(), m_length + 1);
}

CMyString::~CMyString()
{
	delete[] m_chars;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_chars ? m_chars : "";
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	//проверка для release
	if (m_chars == nullptr || start >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	//проверка для debug
	assert(start < m_length && "index out of range");

	if ((start + length > m_length) || (length == SIZE_MAX))
	{
		length = m_length - start;
	}

	return CMyString(&m_chars[start], length);
}

void CMyString::Clear()
{
	delete[] m_chars;
	m_chars = nullptr;
	m_length = 0;
	m_capacity = 1;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

CMyString& CMyString::operator=(const CMyString& str)
{
	if (this != &str)
	{
		CMyString tmp(str);
		std::swap(m_chars, tmp.m_chars);
		std::swap(m_length, tmp.m_length);
		std::swap(m_capacity, tmp.m_capacity);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& str) noexcept
{
	if (this != &str)
	{
		delete[] m_chars;
		m_chars = str.m_chars;
		m_length = str.m_length;
		m_capacity = str.m_capacity;

		str.m_chars = nullptr;
		str.m_length = 0;
		str.m_capacity = 1;
	}

	return *this;
}

CMyString CMyString::operator+(const CMyString& str) const
{
	CMyString resultStr;
	resultStr.m_length = m_length + str.m_length;
	resultStr.m_capacity = resultStr.m_length + 1;
	resultStr.m_chars = new char[resultStr.m_capacity];

	memcpy(resultStr.m_chars, GetStringData(), m_length);
	memcpy(resultStr.m_chars + m_length, str.GetStringData(), str.m_length + 1);
	resultStr.m_chars[resultStr.m_length] = STRING_END;

	return resultStr;
}

CMyString operator+(const std::string& stlString, const CMyString& str)
{
	return CMyString(stlString) + str;
}

CMyString operator+(const char* chars, const CMyString& str)
{
	return CMyString(chars) + str;
}

CMyString& CMyString::operator+=(const CMyString& str)
{
	if (str.m_chars != nullptr)
	{
		*this = *this + str;
	}

	return *this;
}

int CMyString::Compare(const CMyString& str) const
{
	auto cmpLength = std::min(m_length, str.m_length);
	auto cmp = memcmp(GetStringData(), str.GetStringData(), cmpLength);

	if (!cmp && m_length != str.m_length)
	{
		cmp = m_length < str.m_length ? -1 : 1;
	}

	return cmp;
}

bool CMyString::operator==(const CMyString& str) const
{
	if (this->m_length != str.m_length)
	{
		return false;
	}
	return Compare(str) == 0;
}

bool CMyString::operator!=(const CMyString& str) const
{
	return !(*this == str);
}

std::strong_ordering CMyString::operator<=>(const CMyString& str) const
{
	return Compare(str) <=> 0;
}

const char& CMyString::operator[](size_t index) const
{
	//проверка для release
	if (m_chars == nullptr || index >= m_length)
	{
		throw std::out_of_range("index out of range");
	}

	//проверка для debug
	assert(index < m_length && "index out of range");

	return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
	//проверка для release
	if (m_chars == nullptr || index >= m_length)
	{
		throw std::out_of_range("index out of range");
	}

	//проверка для debug
	assert(index < m_length && "index out of range");

	return m_chars[index];
}

std::ostream& operator<<(std::ostream& strm, CMyString const& str)
{
	strm << str.GetStringData();

	return strm;
}

std::istream& operator>>(std::istream& strm, CMyString& str)
{
	std::string tmp;
	strm >> tmp;
	str = tmp;

	return strm;
}
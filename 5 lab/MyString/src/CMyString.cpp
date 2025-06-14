#include "../include/CMyString.h"

#include <istream>


CMyString& CMyString::operator=(const CMyString &other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_size && m_chars != s_emptyString)
		{
			std::destroy_n(m_chars, m_size + 1);
			std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
			m_size = other.m_size;
		}
		else
		{
			CMyString copy{ other };
			std::swap(m_size, copy.m_size);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_chars, copy.m_chars);
		}

	}
	return *this;
}

CMyString operator+(const CMyString& left, const CMyString& right)
{
	CMyString result = left;
	result += right;
	return result;
}

bool operator==(const CMyString &left, const CMyString &right)
{
	if (left.m_size != right.m_size)
	{
		return false;
	}
	for (size_t i = 0; i < std::min(left.m_size, right.m_size); ++i)
	{
		if (left.m_chars[i] != right.m_chars[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const CMyString &left, const CMyString &right)
{
	return !(left == right);
}

bool operator<(const CMyString &left, const CMyString &right)
{
	for (size_t i = 0; i < std::min(left.m_size, right.m_size); ++i)
	{
		if (left.m_chars[i] < right.m_chars[i])
		{
			return true;
		}
	}
	return left.m_size < right.m_size;
}

bool operator>(const CMyString &left, const CMyString &right)
{
	return right < left;
}

bool operator<=(const CMyString &left, const CMyString &right)
{
	return !(right < left);
}

bool operator>=(const CMyString &left, const CMyString &right)
{
	return !(left < right);
}

std::ostream& operator<<(std::ostream &os, const CMyString &right)
{
	return os << right.m_chars;
}

std::istream& operator>>(std::istream &is, CMyString &right)
{
	right.Clear();

	char ch;
	while (is.get(ch) && std::isspace(ch)) {}
	if (is.fail() || is.eof())
	{
		return is;
	}
	is.unget();

	right.m_capacity = 1;
	right.m_chars = {right.Allocate(right.m_capacity + 1)};

	while (is.get(ch) && !std::isspace(static_cast<unsigned char>(ch)))
	{
		if (right.m_size + 1 >= right.m_capacity)
		{
			size_t newCap = right.m_capacity * 2;
			char* newBuffer = {right.Allocate(newCap + 1)};
			std::uninitialized_copy_n(right.m_chars, right.m_size + 1, newBuffer);
			right.Deallocate(right.m_chars);
			right.m_chars = newBuffer;
			right.m_capacity = newCap;
		}
		right.m_chars[right.m_size++] = ch;
		right.m_chars[right.m_size]   = '\0';
	}

	if (is && std::isspace(ch))
	{
		is.unget();
	}

	return is;
}

CMyString& CMyString::operator+=(const CMyString &right)
{
	if (m_capacity == 0 && right.m_size != 0)
	{
		++m_capacity;
	}
	while (m_capacity < right.m_size + m_size)
	{
		m_capacity *= 2;
	}
	char* newBuffer = {Allocate(m_size + right.m_size + 1)};
	std::uninitialized_copy_n(m_chars, m_size, newBuffer);
	std::uninitialized_copy_n(right.m_chars, right.m_size + 1, newBuffer + m_size);
	Deallocate(m_chars);
	m_size += right.m_size;
	m_chars = newBuffer;

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
	return m_chars[index];
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char * CMyString::GetStringData() const
{
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_size)
	{
		return CMyString{ "" };
	}
	length = std::min(length, m_size - start);
	return {m_chars + start, length};
}

void CMyString::Clear()
{
	if (m_chars && m_chars != s_emptyString)
	{
		Deallocate(m_chars);
	}

	m_size = 0;
	m_capacity = 0;
	m_chars = s_emptyString;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

char * CMyString::Allocate(size_t size)
{
	return static_cast<char*>(operator new(size));
}

void CMyString::Deallocate(char *buffer) noexcept
{
	operator delete(buffer);
}

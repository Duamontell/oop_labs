#ifndef CMYSTRING_H
#define CMYSTRING_H
#include <memory>
#include <cstring>
#include <string>
#include <utility>

class CMyString final
{
public:
	CMyString() : m_chars(s_emptyString) {}

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char * pString) :
		m_size{std::strlen(pString)},
		m_capacity(m_size),
		m_chars{Allocate(m_capacity + 1)}
	{
		std::uninitialized_copy_n(pString, m_size + 1, m_chars);
	}

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	CMyString(const char * pString, size_t length) :
		m_size{length},
		m_capacity(m_size),
		m_chars{Allocate(m_capacity + 1)}
	{
		std::uninitialized_copy_n(pString, m_size, m_chars);
		m_chars[m_size] = '\0';
	}

	// конструктор копирования
	CMyString(CMyString const& other) :
		m_size{other.m_size},
		m_capacity{other.m_size},
		m_chars{Allocate(m_capacity + 1)}
	{
		std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
	}

	// перемещающий конструктор
	//  реализуется совместно с перемещающим оператором присваивания
	CMyString(CMyString && other) noexcept :
		m_size{std::exchange(other.m_size, 0)},
		m_capacity{std::exchange(other.m_capacity, 0)},
		m_chars{std::exchange(other.m_chars, s_emptyString)} {}

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	CMyString(std::string const& stlString) :
		m_size{std::strlen(stlString.c_str())},
		m_capacity{m_size},
		m_chars{Allocate(m_capacity + 1)}
	{
		std::uninitialized_copy_n(stlString.c_str(), m_size + 1, m_chars);
	}

	~CMyString()
	{
		if (m_chars != s_emptyString)
		{
			std::destroy_n(m_chars, m_size + 1);
			Deallocate(m_chars);
		}
	}

	CMyString& operator=(const CMyString& other);
	friend CMyString operator+(const CMyString& left, const CMyString& right);
	CMyString& operator+=(const CMyString& right);
	friend bool operator==(const CMyString &left, const CMyString &right);
	friend bool operator!=(const CMyString &left, const CMyString &right);
	friend bool operator<(const CMyString &left, const CMyString &right);
	friend bool operator>(const CMyString &left, const CMyString &right);
	friend bool operator<=(const CMyString &left, const CMyString &right);
	friend bool operator>=(const CMyString &left, const CMyString &right);
	friend std::ostream& operator<<(std::ostream& os, const CMyString& right);
	friend std::istream& operator>>(std::istream& is, CMyString& right);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	size_t GetCapacity() const;


private:
	static char* Allocate(size_t size);
	static void Deallocate(char* buffer) noexcept;
	inline static char s_emptyString[] = {'\0'};
	size_t m_size = 0;
	size_t m_capacity = 0;
	char* m_chars;
};


#endif //CMYSTRING_H

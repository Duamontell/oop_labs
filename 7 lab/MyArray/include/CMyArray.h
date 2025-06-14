#ifndef CMYARRAY_H
#define CMYARRAY_H
#include <memory>

template <typename T>
class CMyArray
{
	class CIterator
	{
		friend class CMyArray;
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;

		CIterator(T* item) : m_item(item) {}
		CIterator() = default;

		reference operator*() { return *m_item; }
		pointer operator->() { return m_item; }
		CIterator& operator++()
		{
			++m_item;
			return *this;
		}
		CIterator operator++(int)
		{
			auto tmp = *this;
			++m_item;
			return tmp;
		}
		CIterator& operator--()
		{
			--m_item;
			return *this;
		}
		CIterator operator--(int)
		{
			auto tmp = *this;
			--m_item;
			return tmp;
		}
		CIterator operator+=(difference_type n)
		{
			m_item += n;
			return *this;
		}
		CIterator operator+(difference_type n) const
		{
			auto tmp = *this;
			tmp += n;
			return tmp;
		}
		CIterator operator-=(difference_type n)
		{
			m_item -= n;
			return *this;
		}
		CIterator operator-(difference_type n) const
		{
			auto tmp = *this;
			tmp -= n;
			return tmp;
		}
		bool operator==(const CIterator& other) const
		{
			return m_item == other.m_item;
		}
		bool operator!=(const CIterator& other) const
		{
			return !(*this == other);
		}

	private:
		T* m_item = nullptr;
	};

	using CReverseIterator = std::reverse_iterator<CIterator>;

public:
	CMyArray() = default;

	// Брать вместимость у other
	CMyArray(const CMyArray &other) :
		m_size(other.m_size),
		m_capacity(m_size),
		m_data(Allocate(m_capacity))
	{
		// Сделать строгу гарантию безопасности
		std::uninitialized_copy_n(other.m_data, m_size, m_data);
	}

	CMyArray(CMyArray &&other) noexcept :
		m_size(std::exchange(other.m_size, 0)),
		m_capacity(std::exchange(other.m_capacity, 0)),
		m_data(std::exchange(other.m_data, nullptr)) {}

	~CMyArray() noexcept
	{
		Clear();
	}

	// Операторы
	// Использовать копирующий конструктор
	CMyArray &operator=(const CMyArray &other)
	{
		if (this != &other)
		{
			Clear();
			m_size = other.m_size;
			// Брать вместимость у other
			m_capacity = m_size;
			m_data = Allocate(m_capacity);
			// Сделать строгу гарантию безопасности
			std::uninitialized_copy_n(other.m_data, m_size, m_data);
		}
		return *this;
	}

	// Использовать перемещающий конструктор
	CMyArray &operator=(CMyArray &&other) noexcept
	{
		if (this != &other)
		{
			Clear();
			m_size = std::exchange(other.m_size, 0);
			m_capacity = std::exchange(other.m_capacity, 0);
			m_data = std::exchange(other.m_data, nullptr);
		}
		return *this;
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index is out of range");
		}
		return m_data[index];
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index is out of range");
		}
		return m_data[index];
	}

	CIterator begin()
	{
		return {m_data};
	}
	CIterator end()
	{
		return {m_data + m_size};
	}
	CReverseIterator rbegin()
	{
		return CReverseIterator(end());
	}
	CReverseIterator rend()
	{
		return CReverseIterator(begin());
	}

	// Методы
	void PushBack(const T& value)
	{
		// Выделить в отдельную функцию
		if (m_capacity == 0)
		{
			++m_capacity;
		}
		while (m_capacity < m_size + 1)
		{
			m_capacity *= 2;
		}
		// Исправить утечну памяти
		T* newData = Allocate(m_capacity);
		std::uninitialized_copy_n(m_data, m_size, newData);
		std::uninitialized_copy_n(&value, 1, newData + m_size);
		std::destroy_n(m_data, m_size);
		Deallocate(m_data);
		++m_size;
		m_data = newData;
	}

	void Resize(size_t size)
	{
		if (size > m_capacity)
		{
			T* newData = Allocate(size);
			// Исправить утечну памяти
			std::uninitialized_copy_n(m_data, m_size, newData);
			Deallocate(m_data);
			m_data = newData;
			m_capacity = size;
		}

		if (size > m_size)
		{
			std::uninitialized_fill_n(m_data + m_size, size - m_size, T{});
		}
		else if (size < m_size)
		{
			std::destroy_n(m_data + size, m_size - size);
		}
		m_size = size;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	size_t GetCapacity() const
	{
		return m_capacity;
	}

	void Clear()
	{
		if (m_data != nullptr)
		{
			std::destroy_n(m_data, m_size);
			Deallocate(m_data);
			m_data = nullptr;
			m_capacity = 0;
			m_size = 0;
		}
	}

private:
	static T* Allocate(const size_t size)
	{
		return static_cast<T*>(operator new(size * sizeof(T)));
	}
	static void Deallocate(T* buffer) noexcept
	{
		operator delete(buffer);
	}

	size_t m_size = 0;
	size_t m_capacity = 0;
	T* m_data = nullptr;
};



#endif //CMYARRAY_H

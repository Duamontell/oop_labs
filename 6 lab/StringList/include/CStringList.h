#ifndef CSTRINGLIST_H
#define CSTRINGLIST_H
#include <memory>
#include <string>
#include <iterator>

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};

	class CIterator
	{
		friend class CStringList;
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = std::string;
		using pointer = std::string*;
		using reference = std::string&;
		using iterator_category = std::bidirectional_iterator_tag;

		CIterator(Node* node) : m_node(node) {}
		CIterator() = default;

		std::string& operator*();
		std::string* operator->();
		CIterator& operator++() noexcept;
		CIterator operator++(int) noexcept;
		CIterator& operator--() noexcept;
		CIterator operator--(int) noexcept;
		bool operator==(const CIterator& other) const noexcept;
		bool operator!=(const CIterator& other) const noexcept;

	private:
		Node* m_node = nullptr;
	};

	class CConstIterator
	{
		friend class CStringList;
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = std::string;
		using pointer = std::string*;
		using reference = std::string&;
		using iterator_category = std::bidirectional_iterator_tag;

		CConstIterator(const Node* node) : m_node(node) {}
		CConstIterator() = default;

		const std::string& operator*() const;
		const std::string* operator->() const;
		CConstIterator& operator++() noexcept;
		CConstIterator operator++(int) noexcept;
		CConstIterator& operator--() noexcept;
		CConstIterator operator--(int) noexcept;
		bool operator==(const CConstIterator& other) const noexcept;
		bool operator!=(const CConstIterator& other) const noexcept;

	private:
		const Node* m_node = nullptr;
	};

	class CReverseIterator
	{
		friend class CStringList;
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = std::string;
		using pointer = std::string*;
		using reference = std::string&;
		using iterator_category = std::bidirectional_iterator_tag;

		CReverseIterator(Node* node) : m_node(node) {}
		CReverseIterator() = default;

		std::string& operator*();
		std::string* operator->();
		CReverseIterator& operator++() noexcept;
		CReverseIterator operator++(int) noexcept;
		CReverseIterator& operator--() noexcept;
		CReverseIterator operator--(int) noexcept;
		bool operator==(const CReverseIterator& other) const noexcept;
		bool operator!=(const CReverseIterator& other) const noexcept;
	private:
		Node* m_node = nullptr;

	};

	class CConstReverseIterator
	{
		friend class CStringList;
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = std::string;
		using pointer = std::string*;
		using reference = std::string&;
		using iterator_category = std::bidirectional_iterator_tag;

		CConstReverseIterator(const Node* node) : m_node(node) {}
		CConstReverseIterator() = default;

		const std::string& operator*() const;
		const std::string* operator->() const;
		CConstReverseIterator& operator++() noexcept;
		CConstReverseIterator operator++(int) noexcept;
		CConstReverseIterator& operator--() noexcept;
		CConstReverseIterator operator--(int) noexcept;
		bool operator==(const CConstReverseIterator& other) const noexcept;
		bool operator!=(const CConstReverseIterator& other) const noexcept;
	private:
		const Node* m_node = nullptr;
	};

public:
	CStringList() : m_firstNode(nullptr) {}

	CStringList(const CStringList& other);
	CStringList(CStringList && other) noexcept;
	~CStringList() noexcept;

	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList && other) noexcept;

	CIterator Insert(const CIterator& pos, const std::string& str);
	CIterator Erase(const CIterator& pos);

	CIterator begin();
	CIterator end();
	CConstIterator begin() const;
	CConstIterator end() const;
	CConstIterator cbegin() const;
	CConstIterator cend() const;
	CReverseIterator rbegin();
	CReverseIterator rend();
	CConstReverseIterator rbegin() const;
	CConstReverseIterator rend() const;
	CConstReverseIterator crbegin() const;
	CConstReverseIterator crend() const;

	void PushFront(const std::string& data);
	void PushBack(const std::string& data);
	size_t GetSize() const;
	bool IsEmpty() const;
	void Clear();
	const std::string& GetFrontElement() const;
	std::string& GetFrontElement();
	const std::string& GetBackElement() const;
	std::string& GetBackElement();

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};



#endif //CSTRINGLIST_H

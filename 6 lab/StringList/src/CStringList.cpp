#include "../include/CStringList.h"

#include <utility>

std::string & CStringList::CIterator::operator*()
{
	return m_node->data;
}

std::string * CStringList::CIterator::operator->()
{
	return &m_node->data;
}

CStringList::CIterator & CStringList::CIterator::operator++() noexcept
{
	if (m_node)
	{
		m_node = m_node->next.get();
	}
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

CStringList::CIterator & CStringList::CIterator::operator--() noexcept
{
	if (m_node)
	{
		m_node = m_node->prev;
	}
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator--(int) noexcept
{
	auto tmp = *this;
	--*this;
	return tmp;
}

bool CStringList::CIterator::operator==(const CIterator &other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::CIterator::operator!=(const CIterator &other) const noexcept
{
	return !(*this == other);
}

const std::string & CStringList::CConstIterator::operator*() const
{
	return m_node->data;
}

const std::string * CStringList::CConstIterator::operator->() const
{
	return &m_node->data;
}

CStringList::CConstIterator & CStringList::CConstIterator::operator++() noexcept
{
	if (m_node)
	{
		m_node = m_node->next.get();
	}
	return *this;
}

CStringList::CConstIterator CStringList::CConstIterator::operator++(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

CStringList::CConstIterator & CStringList::CConstIterator::operator--() noexcept
{
	if (m_node)
	{
		m_node = m_node->prev;
	}
	return *this;
}

CStringList::CConstIterator CStringList::CConstIterator::operator--(int) noexcept
{
	auto tmp = *this;
	--*this;
	return tmp;
}

bool CStringList::CConstIterator::operator==(const CConstIterator &other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::CConstIterator::operator!=(const CConstIterator &other) const noexcept
{
	return !(*this == other);
}

std::string & CStringList::CReverseIterator::operator*()
{
	return m_node->data;
}

std::string * CStringList::CReverseIterator::operator->()
{
	return &m_node->data;
}

CStringList::CReverseIterator & CStringList::CReverseIterator::operator++() noexcept
{
	if (m_node)
	{
		m_node = m_node->prev;
	}
	return *this;
}

CStringList::CReverseIterator CStringList::CReverseIterator::operator++(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

CStringList::CReverseIterator & CStringList::CReverseIterator::operator--() noexcept
{
	if (m_node)
	{
		m_node = m_node->next.get();
	}
	return *this;
}

CStringList::CReverseIterator CStringList::CReverseIterator::operator--(int) noexcept
{
	auto tmp = *this;
	--*this;
	return tmp;
}

bool CStringList::CReverseIterator::operator==(const CReverseIterator &other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::CReverseIterator::operator!=(const CReverseIterator &other) const noexcept
{
	return !(*this == other);
}

const std::string & CStringList::CConstReverseIterator::operator*() const
{
	return m_node->data;
}

const std::string * CStringList::CConstReverseIterator::operator->() const
{
	return &m_node->data;
}

CStringList::CConstReverseIterator & CStringList::CConstReverseIterator::operator++() noexcept
{
	if (m_node)
	{
		m_node = m_node->prev;
	}
	return *this;
}

CStringList::CConstReverseIterator CStringList::CConstReverseIterator::operator++(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

CStringList::CConstReverseIterator & CStringList::CConstReverseIterator::operator--() noexcept
{
	if (m_node)
	{
		m_node = m_node->next.get();
	}
	return *this;
}

CStringList::CConstReverseIterator CStringList::CConstReverseIterator::operator--(int) noexcept
{
	auto tmp = *this;
	--*this;
	return tmp;
}

bool CStringList::CConstReverseIterator::operator==(const CConstReverseIterator &other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::CConstReverseIterator::operator!=(const CConstReverseIterator &other) const noexcept
{
	return !(*this == other);
}

CStringList::CStringList(const CStringList &other) :
	m_size(other.m_size)
{
	if (other.m_firstNode)
	{
		m_firstNode = std::make_unique<Node>(other.m_firstNode->data, nullptr, nullptr);
		Node *prev = m_firstNode.get();
		Node *current = other.m_firstNode.get();
		while (current->next)
		{
			current = current->next.get();
			prev->next = std::make_unique<Node>(current->data, prev, nullptr);
			prev = prev->next.get();
		}
		m_lastNode = prev;
	}
	else
	{
		m_firstNode = nullptr;
	}
}

CStringList::CStringList(CStringList &&other) noexcept :
	m_size(std::exchange(other.m_size, 0)),
	m_firstNode(std::exchange(other.m_firstNode, nullptr)),
	m_lastNode(std::exchange(other.m_lastNode, nullptr)) {}

CStringList::~CStringList() noexcept
{
	Clear();
}

CStringList & CStringList::operator=(const CStringList &other)
{
	if (this != &other)
	{
		Clear();
		m_size = other.m_size;
		if (other.m_firstNode)
		{
			m_firstNode = std::make_unique<Node>(other.m_firstNode->data, nullptr, nullptr);
			Node *prev = m_firstNode.get();
			Node *current = other.m_firstNode.get();
			while (current->next)
			{
				current = current->next.get();
				prev->next = std::make_unique<Node>(current->data, prev, nullptr);
				prev = prev->next.get();
			}
			m_lastNode = prev;
		}
		else
		{
			m_firstNode = nullptr;
		}
	}
	return *this;
}

CStringList & CStringList::operator=(CStringList &&other) noexcept
{
	if (this != &other)
	{
		Clear();
		m_size = std::exchange(other.m_size, 0);
		m_firstNode = std::move(other.m_firstNode);
		m_lastNode = std::exchange(other.m_lastNode, nullptr);
	}
	return *this;
}

CStringList::CIterator CStringList::Insert(const CIterator &pos, const std::string &str)
{
	auto ptr = pos.m_node;
	if (!ptr)
	{
		PushBack(str);
		return {m_lastNode};
	}
	auto newNode = std::make_unique<Node>(str, ptr->prev, nullptr);
	Node *prev = newNode.get();
	prev->next = std::move(ptr->prev ? ptr->prev->next : m_firstNode);
	if (ptr->prev)
	{
		ptr->prev->next = std::move(newNode);
	}
	else
	{
		m_firstNode = std::move(newNode);
	}
	ptr->prev = prev;
	++m_size;
	return {prev};
}

CStringList::CIterator CStringList::Erase(const CIterator &pos)
{
	auto ptr = pos.m_node;
	if (!ptr)
	{
		return {nullptr};
	}
	auto nextNode = ptr->next.get();
	if (ptr->prev)
	{
		ptr->prev->next = std::move(ptr->next);
	}
	else
	{
		m_firstNode = std::move(ptr->next);
	}
	if (nextNode)
	{
		nextNode->prev = ptr->prev;
	}
	else
	{
		m_lastNode = ptr->prev;
	}
	--m_size;
	return {nextNode};
}

CStringList::CIterator CStringList::begin()
{
	return {m_firstNode.get()};
}

CStringList::CIterator CStringList::end()
{
	return {nullptr};
}

CStringList::CConstIterator CStringList::begin() const
{
	return {m_firstNode.get()};
}

CStringList::CConstIterator CStringList::end() const
{
	return {m_lastNode};
}

CStringList::CConstIterator CStringList::cbegin() const
{
	return begin();
}

CStringList::CConstIterator CStringList::cend() const
{
	return end();
}

CStringList::CReverseIterator CStringList::rbegin()
{
	return {m_lastNode};
}

CStringList::CReverseIterator CStringList::rend()
{
	return {nullptr};
}

CStringList::CConstReverseIterator CStringList::rbegin() const
{
	return {m_lastNode};
}

CStringList::CConstReverseIterator CStringList::rend() const
{
	return {nullptr};
}

CStringList::CConstReverseIterator CStringList::crbegin() const
{
	return rbegin();
}

CStringList::CConstReverseIterator CStringList::crend() const
{
	return rend();
}

void CStringList::PushFront(const std::string &data)
{
	auto node = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	if (node->next)
	{
		node->next->prev = node.get();
	}
	else
	{
		m_lastNode = node.get();
	}
	m_firstNode = std::move(node);
	++m_size;
}

void CStringList::PushBack(const std::string &data)
{
	auto node = std::make_unique<Node>(data, m_lastNode, nullptr);
	if (m_lastNode)
	{
		m_lastNode->next = std::move(node);
		m_lastNode = m_lastNode->next.get();
	}
	else
	{
		m_firstNode = std::move(node);
		m_lastNode = m_firstNode.get();
	}
	++m_size;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::Clear()
{
	while (m_firstNode)
	{
		m_firstNode = std::move(m_firstNode->next);
	}
	m_lastNode = nullptr;
	m_size = 0;
}

const std::string & CStringList::GetFrontElement() const
{
	return m_firstNode->data;
}

std::string & CStringList::GetFrontElement()
{
	return m_firstNode->data;
}

const std::string & CStringList::GetBackElement() const
{
	return m_lastNode->data;
}

std::string & CStringList::GetBackElement()
{
	return m_lastNode->data;
}

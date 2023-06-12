#include "MagicalContainer.hpp"
namespace ariel
{

	void Iterator::checkType(const Iterator &other) const
	{
		if (typeid(*this) != typeid(other)) // if the types are different
		{
			throw std::runtime_error("Error -Cant compare or assign iterators of different types");
		}
	}

	bool Iterator::operator==(const Iterator &other) const
	{
		checkType(other);
		return m_current == other.m_current;
	}

	bool Iterator::operator!=(const Iterator &other) const
	{
		checkType(other);
		return m_current != other.m_current;
	}

	bool Iterator::operator<(const Iterator &other) const
	{
		checkType(other);
		if (typeid(*this) == typeid(MagicalContainer::SideCrossIterator))
		{
			return m_current->m_index < other.m_current->m_index;
		}

		if (other.m_current == nullptr)
		{
			return false;
		}
		return m_current->m_data < other.m_current->m_data;
	}

	bool Iterator::operator>(const Iterator &other) const
	{
		checkType(other);

		if (typeid(*this) == typeid(MagicalContainer::SideCrossIterator))
		{
			return m_current->m_index > other.m_current->m_index;
		}

		if (other.m_current == nullptr)
		{
			return false;
		}

		return m_current->m_data > other.m_current->m_data;
	}

	Iterator &Iterator::operator=(const Iterator &other)
	{
		checkType(other);
		if (&this->getContainer() != &other.getContainer())
		{
			throw std::runtime_error("Container is different");
		}

		m_container = other.m_container;
		m_current = other.m_current;

		return *this;
	}

	MagicalContainer &Iterator::getContainer() const
	{
		return this->m_container;
	}

}

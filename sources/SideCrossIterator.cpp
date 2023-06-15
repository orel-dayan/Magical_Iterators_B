#include "MagicalContainer.hpp"

namespace ariel
{

	MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
	{
		return MagicalContainer::SideCrossIterator(m_container);
	}

	MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
	{
		return m_container.size() == 0 ? MagicalContainer::SideCrossIterator(m_container)
									   : MagicalContainer::SideCrossIterator(m_container, m_container.m_list.getTail());
	}

	int MagicalContainer::SideCrossIterator::operator*()
	{
		if (m_container.size() == 0)
			throw std::runtime_error("Error - Out of range");

		if (*this == this->end()) // if the iterator is at the end
			throw std::runtime_error("Error - Out of range");

		if (m_current == nullptr)
			m_current = m_container.m_list.getHead();

		int ret = m_current->m_data;
		return ret;
	}

	MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
	{
		if (m_container.size() == 0 || *this == this->end())
			throw std::runtime_error("Error - Out of range");

		m_current = m_current->m_nextSideCrossIter;
		return *this;
	}

}

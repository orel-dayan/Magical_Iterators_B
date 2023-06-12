#include "MagicalContainer.hpp"

namespace ariel
{

	MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
	{
		return MagicalContainer::AscendingIterator(m_container);
	}

	MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
	{

		return m_container.size() == 0 ? MagicalContainer::AscendingIterator(m_container)
									   : MagicalContainer::AscendingIterator(m_container, m_container.m_list.getTail());
	}

	int MagicalContainer::AscendingIterator::operator*()
	{
		if (m_container.size() == 0)
			throw std::runtime_error("Error - Out of range");

		if (*this == this->end())
			throw std::runtime_error("Error - Out of range");

		if (m_current == nullptr && m_container.size() != 0)
			m_current = m_container.m_list.getHead();

		int ret = m_current->m_data;
		return ret;
	}

	MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
	{
		if (m_container.m_list.getTail() == m_current || m_container.size() == 0)
			throw std::runtime_error("Error - Out of range");
		if (m_current == nullptr)
			m_current = m_container.m_list.getHead();
		else
			m_current = m_current->m_nextAccendingIter;

		return *this;
	}

}

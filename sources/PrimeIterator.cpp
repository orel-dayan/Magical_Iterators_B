#include "MagicalContainer.hpp"

namespace ariel
{

	MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
	{
		return MagicalContainer::PrimeIterator(m_container); // return iterator to the first prime number
	}

	MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() // return iterator to the last prime number
	{
		return m_container.size() == 0 ? MagicalContainer::PrimeIterator(m_container)
									   : MagicalContainer::PrimeIterator(m_container, m_container.m_list.getTail());
	}

	int MagicalContainer::PrimeIterator::operator*()
	{
		if (m_container.m_list.getTail() == m_current || m_container.m_list.getPhead() == nullptr)
			throw std::runtime_error("Error - Out of range");

		if (m_current == nullptr) // if the iterator is at the end
			m_current = m_container.m_list.getPhead();

		int ret = m_current->m_data;
		return ret;
	}

	MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
	{
		if (m_container.m_list.getTail() == m_current)
		{
			throw std::runtime_error("Error - Out of range");
		}
		if (m_current == nullptr && m_container.m_list.getPhead() != m_container.m_list.getTail())
		{
			m_current = m_container.m_list.getPhead();
		}
		else if (m_container.m_list.getPhead() == m_container.m_list.getTail()) // if the list is empty
		{
			throw std::runtime_error("Error - Out of range");
		}
		else
		{
			m_current = m_current->m_nextPrimeIter;
		}
		return *this;
	}

}

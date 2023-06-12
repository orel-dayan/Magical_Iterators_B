#include "MagicalContainer.hpp"


namespace ariel
{

	bool MagicalContainer::isPrime(int &num)
	{
		if (num < 2)
		{
			return false;
		}
		for (int i = 2; i <= sqrt(num); i++)
		{
			if (num % i == 0)
			{
				return false;
			}
		}
		return true;
	}

	void MagicalContainer::addElement(int element)
	{
		if (isPrime(element))
		{

			m_list.addPrime(element);
		}
		else
		{
			m_list.addToList(element);
		}
	}

	void MagicalContainer::removeElement(int num)
	{
		m_list.removeNum(num);
	}

	int MagicalContainer::size() const
	{
		return m_list.getSize();
	}

}

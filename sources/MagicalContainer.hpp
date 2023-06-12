#pragma once
#include "LinkedList.hpp"
#include <cmath>
#include <stdexcept>

namespace ariel
{

	/**
	 * A container class that stores in a sorted manner and provides
	 * iterators for accessing elements in ascending order, side-cross order,
	 * and prime numbers only.
	 */

	class MagicalContainer
	{
	private:
		LinkedList m_list;

	public:
		MagicalContainer(){}; // default constructor

		// Checks if a given number is prime
		static bool isPrime(int &num);

		// Adds a given number to the container
		void addElement(int element);

		// Removes a given number from the container
		void removeElement(int element);

		// Returns the size of the container
		int size() const;

		// Forward declaration of iterator classes
		class AscendingIterator;

		class SideCrossIterator;

		class PrimeIterator;
	};
	/**
	 * Base iterator class for the MagicalContainer.
	 */

	class Iterator
	{
	protected:
		MagicalContainer &m_container;
		Node *m_current;

	protected:
		Iterator(MagicalContainer &container, Node *node) : m_container(container), m_current(node){};

	public:
		virtual ~Iterator() = default; // destructor

		Iterator &operator=(const Iterator &other); // assignment operator

		MagicalContainer &getContainer() const; // returns the container

		bool operator==(const Iterator &other) const; // equality operator

		bool operator!=(const Iterator &other) const; // inequality operator

		bool operator<(const Iterator &other) const; // less than operator

		bool operator>(const Iterator &other) const; // greater than operator

		void checkType(const Iterator &other) const; // checks if two iterators are of the same type
	};

	/**
	 * Iterator for accessing prime numbers in the MagicalContainer.
	 */

	class MagicalContainer::PrimeIterator : public Iterator
	{
	private:
		PrimeIterator(MagicalContainer &container, Node *node) : Iterator(container, node){};

	public:
		PrimeIterator(MagicalContainer &container) : Iterator(container, container.m_list.getPhead()){};

		PrimeIterator(const PrimeIterator &other) : Iterator(other.m_container, other.m_current){};

		int operator*();

		PrimeIterator &operator++();

		PrimeIterator begin();

		PrimeIterator end();
	};

	/**
	 * Iterator for accessing elements in side-cross order in the MagicalContainer.
	 */

	class MagicalContainer::SideCrossIterator : public Iterator
	{
	private:
		SideCrossIterator(MagicalContainer &container, Node *node) : Iterator(container, node){};

	public:
		SideCrossIterator(MagicalContainer &container) : Iterator(container, container.m_list.getHead()){}; // default constructor

		SideCrossIterator(const SideCrossIterator &other) : Iterator(other.m_container, other.m_current){}; // copy constructor

		int operator*();

		SideCrossIterator &operator++();

		SideCrossIterator begin();

		SideCrossIterator end();
	};

	/**
	 * Iterator for accessing elements in ascending order in the MagicalContainer.
	 */

	class MagicalContainer::AscendingIterator : public Iterator
	{
	private:
		AscendingIterator(MagicalContainer &container, Node *node) : Iterator(container,
																			  node){};

	public:
		AscendingIterator(MagicalContainer &container) : Iterator(container, container.m_list.getHead()){};

		AscendingIterator(const AscendingIterator &other) : Iterator(other.m_container, other.m_current){};

		int operator*();

		AscendingIterator &operator++();

		AscendingIterator begin();

		AscendingIterator end();
	};

}

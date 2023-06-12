#pragma once
#include <memory>
#include <limits.h>
#include <stdexcept>
namespace ariel
{
	class Node
	{
	public:
		int m_data;
		bool m_isPrime;
		int m_index;

		Node *m_nextAccendingIter; // iterator for the accending order
		Node *m_nextPrimeIter; // iterator for the prime numbers
		Node *m_nextSideCrossIter; // iterator for the side cross order
		Node *m_prevPrimeIter; // iterator for the prime numbers
		Node *m_prev; // iterator for the accending order

		Node(int number, bool isPrime, Node *nacceding, Node *nprime, Node *ncross, Node *prev,
			 Node *prevprime)
			: m_data(number), m_isPrime(isPrime), m_index(0), m_nextAccendingIter(nacceding), m_nextPrimeIter(nprime),
			  m_nextSideCrossIter(ncross),
			  m_prev(prev), m_prevPrimeIter(prevprime){};
	};

	class LinkedList
	{
	private:
		Node *m_head; // head
		Node *m_Phead; // Prime head
		Node *m_tail; // tail
		int m_size; // size of the list

	public:
		LinkedList() : m_head(nullptr), m_Phead(nullptr),
					   m_tail(new Node(INT_MAX, true, nullptr, nullptr, nullptr, nullptr, nullptr)), m_size(0){};

		void addToList(Node *node); // add a number to the list

		void addPrime(int number); // add a prime number to the list

		void addToList(int number); // add a number to the list

		void removeNum(int number); // remove a number from the list

		void removePrimesNumbers(Node *node); // remove a prime number from the list

		Node *getPhead() const
		{
			return m_Phead;
		}

		Node *getHead() const
		{
			return m_head;
		}

		Node *getTail() const
		{
			return m_tail;
		}

		int getSize() const
		{
			return m_size;
		}

	private:
		void UpdateSideCross(); // update the side cross iterator
	};
}

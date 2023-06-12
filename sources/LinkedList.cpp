
#include "LinkedList.hpp"
namespace ariel
{

	void LinkedList::addToList(const int num)
	{
		Node *newNode = new Node(num, false, nullptr, nullptr, nullptr, nullptr, nullptr); // create new node with the given number and default values
		addToList(newNode);																   // add the node to the list
	}

	void LinkedList::addToList(Node *node)
	{
		if (m_head == nullptr)
		{
			m_head = node; // if the list is empty, the new node is the head
			m_head->m_nextAccendingIter = m_tail;
			m_head->m_nextSideCrossIter = m_tail;
			m_tail->m_prev = node; // the tail's previous node is the new node
			if (m_Phead == nullptr)
			{
				m_Phead = m_tail;
			}
			m_size++;
		}
		else
		{
			Node *current = m_head;
			Node *previous = nullptr;

			while (current != m_tail && current->m_data <= node->m_data)
			{
				if (current->m_data == node->m_data)
				{
					delete node;
					return;
				}
				previous = current;
				current = current->m_nextAccendingIter;
			}

			node->m_nextAccendingIter = current;
			node->m_prev = previous;

			if (previous != nullptr)
			{
				previous->m_nextAccendingIter = node;
			}
			else
			{
				m_head = node;
			}

			current->m_prev = node;

			if (node->m_nextAccendingIter == m_tail)
			{
				m_tail->m_prev = node;
			}

			UpdateSideCross();
			m_size++;
		}
	}

	void LinkedList::removeNum(int num)
	{
		Node *current = m_head;
		while (current != nullptr && current != m_tail && current->m_data != num)
		{ // find the node with the given number
			current = current->m_nextAccendingIter;
		}

		if (current == m_tail)
		{ // if the node is the tail, the number does not exist
			throw std::runtime_error("Error - The number does not exist");
		}

		if (current->m_isPrime)
		{ // if the node is prime, remove it from the prime list
			 removePrimesNumbers(current);
		}

		if (current == m_head)
		{ // if the node is the head, update the head
			m_head = current->m_nextAccendingIter;
		}

		if (current->m_prev)
		{ // update the previous node
			current->m_prev->m_nextAccendingIter = current->m_nextAccendingIter;
		}

		if (current->m_nextAccendingIter)
		{ // update the next node
			current->m_nextAccendingIter->m_prev = current->m_prev;
		}

		delete current;
		m_size--;
	}

	void LinkedList::removePrimesNumbers(Node *node)
	{
		if (m_Phead == node) // if the node is the prime head, update the prime head
		{
			m_Phead = node->m_nextPrimeIter;
			if (node->m_nextPrimeIter != nullptr)
				node->m_nextPrimeIter->m_prevPrimeIter = nullptr;

			return;
		}

		node->m_prev->m_nextPrimeIter = node->m_nextPrimeIter;
		if (node->m_nextPrimeIter != nullptr) // update the next node
			node->m_nextPrimeIter->m_prevPrimeIter = node->m_prevPrimeIter;
	}

	void LinkedList::UpdateSideCross()
	{
		Node *l = m_head;		  // left node
		Node *r = m_tail->m_prev; // right node
		int indx = 0;
		Node *node = nullptr;

		while (l->m_data < r->m_data)
		{
			l->m_index = indx++;
			l->m_nextSideCrossIter = r;
			r->m_index = indx++;
			r->m_nextSideCrossIter = l->m_nextAccendingIter;

			if (node != nullptr)
				node->m_nextSideCrossIter = l;

			node = r;
			r = r->m_prev;
			l = l->m_nextAccendingIter;
		}

		l->m_nextSideCrossIter = m_tail;
		l->m_index = indx;
	}

	void LinkedList::addPrime(int num)
	{
		Node *node = new Node(num, true, nullptr, nullptr, nullptr, nullptr, nullptr);

		if (m_head == nullptr || m_Phead == nullptr)
		{
			m_Phead = node;
			m_Phead->m_nextPrimeIter = m_tail;
			addToList(node);
			return;
		}

		if (m_Phead->m_data > num)
		{
			node->m_nextPrimeIter = m_Phead;
			m_Phead->m_prev = node;
			m_Phead = node;
			addToList(node);
			return;
		}

		Node *temp = m_Phead;
		while (temp->m_nextPrimeIter != m_tail && temp->m_nextPrimeIter->m_data <= num)
		{
			temp = temp->m_nextPrimeIter;
		}

		if (temp->m_data == num)
		{
			delete node;
			return;
		}

		node->m_nextPrimeIter = temp->m_nextPrimeIter;
		node->m_prev = temp;
		if (temp->m_nextPrimeIter != m_tail)
		{
			temp->m_nextPrimeIter->m_prev = node;
		}
		temp->m_nextPrimeIter = node;

		addToList(node);
	}

}

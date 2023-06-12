#pragma once
#include <memory>
#include <limits.h>
#include <stdexcept>
namespace ariel {
    class Node {
    public:
        int m_data;
        bool m_isPrime;
        int m_index;
        Node *m_nextAccendingIter;
        Node *m_nextPrimeIter;
        Node *m_nextSideCrossIter;
        Node *m_prevPrimeIter;
        Node *m_prev;

        Node(int number, bool isPrime, Node *nextAsc, Node *nextPrime, Node *nextCross, Node *previous,
             Node *previousPrime)
                : m_data(number), m_isPrime(isPrime), m_index(0), m_nextAccendingIter(nextAsc), m_nextPrimeIter(nextPrime),
                  m_nextSideCrossIter(nextCross),
                  m_prev(previous), m_prevPrimeIter(previousPrime) {};

    };

    class LinkedList {
    private:
        Node *m_head;
        Node *m_Phead; // Prime head
        Node *m_tail;
        int m_size;

     
    public:
        LinkedList() : m_head(nullptr), m_Phead(nullptr),
                              m_tail(new Node(INT_MAX, true, nullptr, nullptr, nullptr, nullptr, nullptr)), m_size(0) {};

        void addToList(Node *node); // add a number to the list

        void addPrime(int number); // add a prime number to the list

        void addToList(int number); // add a number to the list

        void removeNum(int number); // remove a number from the list

        void removePrimesNumbers(Node *node); // remove a prime number from the list

        int getSize() const {
            return m_size;
        }

        Node *getPhead() const {
            return m_Phead;
        }

        Node *getHead() const {
            return m_head;
        }

        Node *getTail() const {
            return m_tail;
        }

    private:
        void UpdateSideCross();


    };
}




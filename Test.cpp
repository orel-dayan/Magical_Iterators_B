
#include <iostream>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"
using namespace doctest;
using namespace ariel;

typedef MagicalContainer::AscendingIterator AscendingIterator;
typedef MagicalContainer::SideCrossIterator SideCrossIterator;
typedef MagicalContainer::PrimeIterator PrimeIterator;

TEST_CASE("Build MagicalContainer")
{
	MagicalContainer container;
	CHECK_EQ(container.size(), 0);
}

TEST_CASE("Add Elements to MagicalContainer")
{

	MagicalContainer container;

	container.addElement(9);
	container.addElement(26);
	container.addElement(32);
	container.addElement(11);
	container.addElement(41);
	container.addElement(64);
	container.addElement(7);
	container.addElement(8);
	container.addElement(1);
	container.addElement(2);

	CHECK_EQ(container.size(), 10);
}

TEST_CASE("Remove Elements from MagicalContainer")
{
	MagicalContainer container;

	container.addElement(4);
	container.addElement(9);
	container.addElement(1);
	CHECK_EQ(container.size(), 3);
	container.removeElement(9);
	container.removeElement(4);
	CHECK_EQ(container.size(), 1);
	container.addElement(89);
	container.addElement(1); // duplicate
	container.addElement(5);
	container.addElement(3);
	CHECK_EQ(container.size(), 4); // 4 elements because 1 is duplicate
	container.removeElement(1);

	CHECK_EQ(container.size(), 3);
}

TEST_SUITE("Ascending Iterator Test")
{
	TEST_CASE("Create Accending Iterator")
	{
		MagicalContainer container;
		AscendingIterator it1(container);
		CHECK(it1.begin() == it1.end());

		container.addElement(8);
		container.addElement(9);
		container.addElement(10);
		container.addElement(11);
		AscendingIterator it2 = it1.begin();						  // it2 is now pointing to the first element in the container
		AscendingIterator it3 = AscendingIterator(container).begin(); // it3 is now pointing to the first element in the container
		AscendingIterator it4 = it3;								  // copy constructor
		CHECK(it1.begin() != it1.end());							  // it1 is not pointing to the end of the container
		CHECK(it2 == it1.begin());									  // it2 and it1 are pointing to the same element
		CHECK(it2.begin() == it3.begin());							  // it2 and it3 are pointing to the same element
		CHECK(it3 == it1.begin());
		CHECK(it4 == it3.begin()); // it4 and it3 are pointing to the same element
	}
	TEST_CASE("Compare < > == !=")
	{
		MagicalContainer container;
		container.addElement(1);
		container.addElement(4);
		container.addElement(2);
		container.addElement(3);

		AscendingIterator it1(container);
		PrimeIterator it2(container);
		try
		{
			if (it1 == it2)
			{
				CHECK(false);
			}
			else
			{
				CHECK(true);
			}
		}
		catch (const std::exception &e)
		{
			CHECK_THROWS_MESSAGE(it1 == it2, "Error -Cant compare or assign iterators of different types");
		}

		AscendingIterator it3(container);

		CHECK(it1 == it3);
		CHECK(++it1 == ++it3);

		++it1;

		CHECK(it1 > it3);
		CHECK(it3 < it1);
		CHECK(!(it1 < it3));
		CHECK(!(it3 > it1));

		++it1;

		CHECK(it1 > it3);
		CHECK(it3 < it1);
		CHECK(!(it3 > it1));
	}

	TEST_CASE("Check values of elements")
	{
		MagicalContainer container;
		container.addElement(11);
		container.addElement(15);
		container.addElement(2);
		container.addElement(19);

		AscendingIterator it(container);
		CHECK_EQ(*it, 2);

		++it;
		CHECK_EQ(*it, 11);
		++it;
		CHECK_EQ(*it, 15);
		CHECK_EQ(*(++it), 19);
		++it;
		CHECK_THROWS(*it);
		CHECK_THROWS(++it); // Out of range
	}
}

TEST_SUITE("SideCross Iterator Test")
{

	TEST_CASE("Create SideCross Iterator")
	{
		MagicalContainer container;
		SideCrossIterator it1(container);
		CHECK(it1.begin() == it1.end());
		container.addElement(8);
		container.addElement(9);
		container.addElement(10);
		container.addElement(11);

		SideCrossIterator it2 = it1.begin();
		SideCrossIterator it3 = SideCrossIterator(container).begin();
		CHECK(it1.begin() != it1.end());   // it1 is not pointing to the end of the container
		CHECK(it2 == it1.begin());		   // it2 and it1 are pointing to the same element
		CHECK(it2.begin() == it3.begin()); // it2 and it3 are pointing to the same element
		CHECK(it3 == it1.begin());
	}
	TEST_CASE("Compere < > == !=")
	{
		MagicalContainer container;
		container.addElement(1);
		container.addElement(14);
		container.addElement(2);
		container.addElement(4);
		container.addElement(5);
		SideCrossIterator it1(container);
		SideCrossIterator it2(container);
		CHECK(it1 == it2);
		CHECK(++it1 == ++it2);
		++it1;
		CHECK((it2 > it1)); // it2 is bigger than it1
		AscendingIterator t3(container);
		try
		{
			if (t3 == it2) // t3 and it2 are from different types
			{
				CHECK(false);
			}
			else
			{
				CHECK(true);
			}
		}
		catch (const std::exception &e)
		{
			CHECK_THROWS_MESSAGE(t3 == it2, "Error -Cant compare or assign iterators of different types");
		}
	}

	TEST_CASE("check values after one inserting")
	{
		MagicalContainer container;
		container.addElement(2);
		container.addElement(4);
		container.addElement(1);
		container.addElement(3);

		SideCrossIterator it(container);
		CHECK_EQ(*it, 1);
		++it;
		CHECK_EQ(*it, 4);
		++it;
		CHECK_EQ(*it, 2);
		CHECK_EQ(*(++it), 3);
		++it;
		CHECK_THROWS_AS_MESSAGE(*it, std::runtime_error, "Error - Out of range");
		CHECK_THROWS_MESSAGE(++it, "Error - Out of range");
	}

	TEST_CASE("check value after inserting")
	{
		MagicalContainer container;
		container.addElement(2);
		container.addElement(3);
		container.addElement(4);

		SideCrossIterator it(container);

		CHECK_EQ(*it, 2);
		++it;
		CHECK_EQ(*it, 4);
		++it;
		CHECK_EQ(*it, 3);
		++it;
		CHECK_EQ(it, it.end());
		CHECK_THROWS(*it);
	}
}

TEST_SUITE("Prime Iterator")
{
	TEST_CASE("Prime Iterator")
	{
		MagicalContainer container;
		container.addElement(145);
		container.addElement(5974);
		container.addElement(2456);

		PrimeIterator it1(container);
		PrimeIterator it2 = it1.begin();
		PrimeIterator it3 = PrimeIterator(container).begin();

		CHECK(it2 == it1.begin());		   // it2 and it1 are pointing to the same element
		CHECK(it2.begin() == it3.begin()); // it2 and it3 are pointing to the same element
		CHECK(it3 == it1.begin());
	}

	TEST_CASE("Compere < > == !=")
	{
		MagicalContainer container;
		container.addElement(1);
		container.addElement(4);
		container.addElement(2);
		container.addElement(3);
		container.addElement(5);
		container.addElement(7);

		PrimeIterator it1(container);
		PrimeIterator it2(container);

		CHECK(it1 == it2);
		CHECK(++it1 == ++it2);
		++it1;

		CHECK(it1 > it2);
		CHECK(it2 < it1);
		CHECK(!(it1 < it2));

		++it2;
		CHECK(it1 == it2);
		++it1;
		++it2;
		CHECK(it1 == it2);
		CHECK(!(it1 != it2));
	}

	TEST_CASE("check value after one inserting")
	{
		MagicalContainer container;
		container.addElement(1);
		container.addElement(4);
		container.addElement(2);
		container.addElement(3);

		PrimeIterator it(container);

		CHECK_EQ(*it, 2);
		CHECK_EQ(*it, 2);
		++it;
		CHECK_EQ(*it, 3);
		++it;

		CHECK_THROWS(*it);
		CHECK_THROWS(++it);
	}

	TEST_CASE("check values after adding elements")
	{
		MagicalContainer container;
		container.addElement(2);
		container.addElement(5);
		container.addElement(19);
		container.addElement(21);

		PrimeIterator it(container);
		CHECK_EQ(*it, 2);
		++it;
		CHECK_EQ(*it, 5);
		container.addElement(3);
		CHECK_EQ(*it, 5);
		++it;
		CHECK_EQ(*it, 19);

		container.addElement(4);
		container.addElement(7);
		container.addElement(6);
		container.addElement(8);

		CHECK_EQ(*it, 19);
	}
}

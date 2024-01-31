#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	KeyType k;
	ValueType v;

	Map m1;
	assert(m1.size() == 0); // test size
	assert(m1.empty()); // test empty
	assert(!m1.contains("a")); // doesn't contain "a"
	assert(!m1.erase("hello")); // nothing to erase
	assert(!m1.update("a", 1)); // nothing to update
	assert(m1.size() == 0); // test size after operations
	cout << "test 1 passed (empty map)" << endl;

	Map m2;
	assert(m2.insert("a", 1)); // test insert
	assert(m2.size() == 1); // size should increase
	assert(!m2.empty()); // should not be empty
	assert(m2.contains("a")); // should contain "a"
	assert(m2.erase("a")); // test erase
	assert(m2.size() == 0); // size should go back to 0
	assert(m2.empty()); // should now be empty
	cout << "test 2 passed (insert and erase)" << endl;

	Map m3;
	m3.insert("a", 1);
	m3.insert("b", 2);
	m3.insert("c", 3);
	assert(m3.size() == 3);
	v = 100;
	// "d" doesn't exist and v should be unchanged
	assert(!m3.get("d", v) && v == 100);
	assert(m3.get("b", v) && v == 2);
	k = "ToT";
	v = 22;
	// invalid indices and k and v unchanged
	assert(!m3.get(-1, k, v) && k == "ToT" && v == 22);
	assert(!m3.get(3, k, v) && k == "ToT" && v == 22);
	// valid indices
	assert(m3.get(0, k, v) && k == "a" && v == 1);
	assert(m3.get(1, k, v) && k == "b" && v == 2);
	assert(m3.get(2, k, v) && k == "c" && v == 3);
	// erase works
	assert(m3.erase("b") && !m3.contains("b") && m3.size() == 2);
	// new index
	assert(m3.get(1, k, v) && k == "c" && v == 3);
	cout << "test 3 passed (insert, erase, and get)" << endl;

	Map m4;
	m4.insert("a", 1);
	m4.insert("b", 2);
	m4.insert("c", 3);
	m4.insert("d", 4);
	// test update
	assert(m4.update("d", 5));
	assert(m4.size() == 4 && m4.get("d", v) && v == 5);
	assert(m4.get(3, k, v) && k == "d" && v == 5);
	// insertOrUpdate replaces "c"
	assert(m4.insertOrUpdate("c", 4) && m4.get("c", v) && v == 4);
	// insertOrUpdate inserts "e"
	assert(m4.insertOrUpdate("e", 6) && m4.get("e", v) && v == 6);
	// test size after insertOrUpdate
	assert(m4.size() == 5 && m4.get(4, k, v) && k == "e" && v == 6);
	assert(m4.contains("c") && m4.contains("d") && m4.contains("e"));
	cout << "test 4 passed (insert, update, and insertOrUpdate)" << endl;

	Map m5;
	m5.insert("a", 1);
	m5.insert("b", 2);
	m5.insert("c", 3);
	m5.insert("d", 4);
	Map m6;
	m6.insert("e", 5);
	m6.insert("f", 6);
	m6.swap(m5);
	assert(m5.contains("f") && m6.contains("a"));
	assert(m5.size() == 2 && m6.size() == 4);
	assert(m6.get(2, k, v) && k == "c" && v == 3);
	assert(m5.get(0, k, v) && k == "e" && v == 5);
	assert(!m5.get(2, k, v));
	m5 = m6;
	assert(m5.size() == 4 && m5.get(2, k, v) && k == "c" && v == 3);
	Map m7(m5);
	assert(m7.size() == 4 && m7.get(3, k, v) && k == "d" && v == 4);
	cout << "test 5 passed (swap, assignment, and copy constructor)" << endl;

	Map m8;
	m8.insert("a", 1);
	m8.insert("b", 2);
	m8.insert("c", 3);
	m8.insert("d", 4);
	if (true) {
		Map m9(m8);
		assert(m9.get(3, k, v) && k == "d" && v == 4);
	} //m9 goes out of scope
	// test that m8 still works
	assert(m8.get(2, k, v) && k == "c" && v == 3);
	if (true) {
		Map m9;
		m9 = m8;
		assert(m9.get(3, k, v) && k == "d" && v == 4);
	} // m9 goes out of scope
	// test that m8 still works
	assert(m8.get(2, k, v) && k == "c" && v == 3);
	cout << "test 6 passed (copy and assignment memory leak)" << endl;

	Map m9;
	m9.insert("Fred", 123);
	m9.insert("Ethel", 456);
	m9.insert("Lucy", 789);
	Map m10;
	m10.insert("Lucy", 789);
	m10.insert("Ricky", 321);
	Map result;
	result.insert("Ethan", 1);
	assert(merge(m9, m10, result));
	assert(result.size() == 4 && result.get("Lucy", v) && v == 789);
	assert(merge(m9, m10, m10));
	assert(m10.size() == 4 && m10.get("Lucy", v) && v == 789);
	assert(merge(m10, m10, m10));
	assert(m10.size() == 4 && m10.get("Fred", v) && v == 123);
	Map m11;
	m11.insert("Fred", 123);
	m11.insert("Ethel", 456);
	m11.insert("Lucy", 789);
	Map m12;
	m12.insert("Lucy", 654);
	m12.insert("Ricky", 321);
	merge(m11, m12, result);
	assert(result.size() == 3 && !result.contains("Lucy"));
	assert(result.contains("Fred") && result.contains("Ethel") && result.contains("Ricky"));
	cout << "test 7 passed (merge and aliasing)" << endl;

	Map m13;
	m13.insert("a", 1);
	m13.insert("b", 2);
	m13 = m13;
	assert(m13.size() == 2 && m13.get("a", v) && v == 1);
	assert(m13.get("b", v) && v == 2);
	cout << "test 8 passed (reassign aliasing)" << endl;

	Map m14;
	m14.insert("a", 1);
	m14.insert("b", 2);
	m14.insert("c", 3);
	reassign(m14, result);
	assert(result.size() == 3 && result.get("a", v) && v == 2);
	assert(result.get("b", v) && v == 3);
	assert(result.get("c", v) && v == 1);
	reassign(m14, m14); // test aliasing for reassign function
	assert(m14.size() == 3 && m14.get("a", v) && v == 2);
	assert(m14.get("b", v) && v == 3);
	assert(m14.get("c", v) && v == 1);
	Map m15;
	reassign(m15, result); // test on empty map
	assert(result.size() == 0);
	m15.insert("a", 1);
	reassign(m15, result); // test on map with size 1
	assert(result.size() == 1 && result.get("a", v) && v == 1);
	cout << "test 9 passed (reassign function and aliasing)" << endl;
}

// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests

#include "mini_test.h"
#include "bst.h"

template<typename T>
string to_s(const T& m) {
 	ostringstream os;
	os << m;
	return os.str();
 }

void check_add_node(){
	BinarySearchTree<int> bst;

	bst.add(1);

	ASSERT_EQ(to_s(bst), "[1]");

	bst.add(2);

	ASSERT_EQ(to_s(bst), "[1, 2]");

	bst.add(-3);

	ASSERT_EQ(to_s(bst), "[-3, 1, 2]");

	bst.add(-2);

	ASSERT_EQ(to_s(bst), "[-3, -2, 1, 2]");

	bst.add(-2);

	ASSERT_EQ(to_s(bst), "[-3, -2, 1, 2]");
}

void check_has_node(){
	BinarySearchTree<int> bst;

	bst.add(1);
	bst.add(42);
	bst.add(-3);

	ASSERT_EQ(bst.hasValue(-3), true);

	ASSERT_EQ(bst.hasValue(13), false);

	bst.add(13);

	ASSERT_EQ(bst.hasValue(13), true);
}

void check_height(){
	BinarySearchTree<int> bst;

	ASSERT_EQ(bst.getHeight(), 0);

	bst.add(1);

	ASSERT_EQ(bst.getHeight(), 1);

	bst.add(2);
	bst.add(3);

	ASSERT_EQ(bst.getHeight(), 3);

	bst.add(0);

	ASSERT_EQ(bst.getHeight(), 3);
}

void check_is_empty(){
	BinarySearchTree<int> bst;

	ASSERT_EQ(bst.isEmpty(), true);

	bst.add(42);

	ASSERT_EQ(bst.isEmpty(), false);
}

void check_remove(){
	BinarySearchTree<int> bst;

	bst.add(1);

	bst.remove(1);

	ASSERT_EQ(to_s(bst), "[]");

	bst.add(1);
	bst.add(2);

	bst.remove(2);

	ASSERT_EQ(to_s(bst), "[1]");

	bst.add(2);
	bst.add(3);
	bst.add(13);

	bst.remove(3);

	ASSERT_EQ(to_s(bst), "[1, 2, 13]");

	bst.add(6);
	bst.add(5);
	bst.add(7);
	bst.add(15);

	bst.remove(13);


	ASSERT_EQ(to_s(bst), "[1, 2, 5, 7, 15]");
}

int main() {
	RUN_TEST(check_add_node);
	RUN_TEST(check_has_node);
	RUN_TEST(check_height);
	RUN_TEST(check_is_empty);
	RUN_TEST(check_remove);
	return 0;
}

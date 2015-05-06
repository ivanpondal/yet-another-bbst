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


	ASSERT_EQ(to_s(bst), "[1, 2, 5, 6, 7, 15]");
}

void check_equal(){
	BinarySearchTree<int> bst;
	BinarySearchTree<int> otherBst;

	bst.add(1);
	bst.add(7);
	bst.add(6);

	ASSERT_EQ(bst == otherBst, false);

	otherBst.add(1);
	otherBst.add(7);
	otherBst.add(6);

	ASSERT_EQ(bst == otherBst, true);

	otherBst.remove(1);
	otherBst.remove(7);
	otherBst.remove(6);

	otherBst.add(7);
	otherBst.add(6);
	otherBst.add(1);

	ASSERT_EQ(bst == otherBst, false);

	otherBst.remove(1);
	otherBst.remove(7);
	otherBst.remove(6);

	otherBst.add(1);
	otherBst.add(7);
	otherBst.add(5);

	ASSERT_EQ(bst == otherBst, false);

	otherBst.remove(5);
	otherBst.add(6);

	ASSERT_EQ(bst == otherBst, true);
}

void check_copy(){
	BinarySearchTree<int> bst;

	bst.add(-24);
	bst.add(3);
	bst.add(5);
	bst.add(200);

	BinarySearchTree<int> copyBst = BinarySearchTree<int>(bst);

	ASSERT_EQ(to_s(copyBst), "[-24, 3, 5, 200]");
}

int main() {
	RUN_TEST(check_add_node);
	RUN_TEST(check_has_node);
	RUN_TEST(check_height);
	RUN_TEST(check_is_empty);
	RUN_TEST(check_remove);
	RUN_TEST(check_equal);
	RUN_TEST(check_copy);
	return 0;
}

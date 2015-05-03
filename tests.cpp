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
}

int main() {
	RUN_TEST(check_add_node);
	return 0;
}

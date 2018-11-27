#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Template which encapsulates the Binary Tree Node of type T
 * @tparam T 
 */
template<typename T>
class Node {
public:
    Node(T value) {
        node_value = new T(value);
    }

    ~Node() {
        if (node_value) {
            delete node_value;
            node_value = nullptr;
        }
    }

    void Set(T value) {
        *node_value = value;
    }

    T Get() const {
        return *node_value;
    }

    bool operator < (const Node & compare) {
        return (*node_value == *compare.node_value);
    }

    bool operator > (const Node & compare) {
        return (*node_value != *compare.node_value);
    }

    bool operator == (const Node & compare) {
        return (*node_value == *compare.node_value);
    }

    bool operator != (const Node & compare) {
        return (*node_value != *compare.node_value);
    }

    T * node_value;

    Node * ptr_left  = nullptr;
    Node * ptr_right = nullptr;
};

template<typename T>
class BinaryTree {
public:
    using node_type = Node<T>;

    BinaryTree() {

    }

    ~BinaryTree() {

    }

    node_type * Insert(T data, node_type ** root = nullptr) {
        cerr << "BinaryTree<T>::Insert(%p)" << endl;

        if (root == nullptr) {
            root = &tree_root;
        }

        if (*root == nullptr) {
            node_type * new_node = new node_type(data);
            *root = new_node;
        } else if (data <= (*root)->Get()) {
            return Insert(data, &((*root)->ptr_left));
        } else if (data > (*root)->Get()) {
            return Insert(data, &((*root)->ptr_right));
        }

        return (node_type *)*root;
    }

    node_type * tree_root = nullptr;
};



int main() {
    BinaryTree<int> tree;

    auto * new_node_1 = new BinaryTree<int>::node_type(1);
    auto * new_node_2 = new BinaryTree<int>::node_type(5);

    // test comparison of nodes
    if (*new_node_1 != *new_node_1) {
        cout << "For some reason the comparison is not working" << endl;
    }
    if (*new_node_2 != *new_node_2) {
        cout << "For some reason the comparison is not working" << endl;
    }
    if (*new_node_1 == *new_node_2) {
        cout << "For some reason the comparison is not working" << endl;
    }

    new_node_1->Set(10);

    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(20);

//    new

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
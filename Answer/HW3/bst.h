#ifndef BST_H
#define BST_H

#include <iostream>
#include <iomanip>
#include <cstddef>
#include <functional>
#include <queue>
#include <initializer_list>

class BST
{
public:
    BST(){}
    BST(const BST &other);
    BST(BST &&other):root(other.root){ other.root = nullptr;}
    BST(std::initializer_list<int> list);
    ~BST();
    
    class Node
    {
    public:
        Node(int value, Node* left = nullptr, Node* right = nullptr):value(value), 
            left(left), right(right){}
        Node():value(0), left(nullptr), right(nullptr){}
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;
        
        friend std::ostream& operator<<(std::ostream &out, const Node &node);
        friend bool operator>(const BST::Node &a, const BST::Node &b);
        friend bool operator>=(const BST::Node &a, const BST::Node &b);
        friend bool operator<(const BST::Node &a, const BST::Node &b);
        friend bool operator<=(const BST::Node &a, const BST::Node &b);
        friend bool operator==(const BST::Node &a, const BST::Node &b);
    };

    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(const int value);
    bool delete_node(const int value);
    Node*& get_root();
    Node** find_node(const int value);
    Node** find_parent(const int value);
    Node** find_successor(const int value); // Find the predecessor node

    friend std::ostream& operator<<(std::ostream &out, BST &bst);
    BST& operator++(); // Pre-version，即 ++i 形式
    BST operator++(int dummy); //Post-version，即 i++ 形式
    BST& operator=(BST &other);
    BST& operator=(BST &&other);

private:
    Node* root = nullptr;
};

#endif //BST_H
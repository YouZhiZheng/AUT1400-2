#include "bst.h"

BST::Node::Node(const Node& node)
{
    value = node.value;
    left = node.left;
    right = node.right;
}

// Overload the output symbol of the Node class
std::ostream& operator<<(std::ostream &out, const BST::Node &node)
{
    out << "node's address: " << &node << "\tnode's value: " << node.value << std::endl;

    if (node.left != nullptr)
    {
        out << "node's left address: " << node.left << "\n";
    }
    else
    {
        out << "node's left address: nullptr\n";
    }

    if (node.right != nullptr)
    {
        out << "node's right address: " << node.right << "\n";
    }
    else
    {
        out << "node's right address: nullptr\n";
    }
    
    return out;
}

bool operator>(const BST::Node &a, const BST::Node &b)
{
    return a.value > b.value;
}

bool operator>=(const BST::Node &a, const BST::Node &b)
{
    return a.value >= b.value;
}

bool operator<(const BST::Node &a, const BST::Node &b) 
{
    return a.value < b.value;
}

bool operator<=(const BST::Node &a, const BST::Node &b) 
{
    return a.value <= b.value;
}

bool operator==(const BST::Node &a, const BST::Node &b) 
{
    return a.value == b.value;
}

// 采用递归的方式来复制节点
BST::Node* copy_node(const BST::Node* node)
{
    if (node == nullptr) return nullptr;

    // 创建新的节点，递归地拷贝左右子树
    BST::Node* new_node = new BST::Node(node->value, nullptr, nullptr);
    new_node->left = copy_node(node->left);
    new_node->right = copy_node(node->right);

    return new_node;
}

BST::BST(const BST &other)
{
    if(this != &other) // 判断是否是同一个对象，避免浪费资源
    {
        if(other.root == nullptr) root = nullptr;
        else
        {
            // 这里采用调用一个递归函数来复制树
            // 也可以直接使用栈来实现，但难度较大
            root = copy_node(other.root);
        }
    }
}

BST::BST(std::initializer_list<int> list)
{
    // 这里虽然可以调用 add_node() 来简化实现，但是不推荐这样做
    // 因为构造函数是用来初始化对象的，现在调用成员函数可能会出现
    // 意想不到的错误
    for(auto &value: list)
    {
        if(root == nullptr)
        {
            root = new Node(value, nullptr, nullptr);
        }
        else
        {
            Node *p_current, *current = root;
            while(current)
            {
                if(current->value == value)
                {
                    std::cout << "The " << value  << " already exists and cannot be added." << std::endl;
                    break;
                }
                else
                {
                    p_current = current;
                    if(current->value > value) current = current->left;
                    else current = current->right;
                }
            }

            if(current == nullptr) // 判断该值是否需要插入
            {
                current = new Node(value, nullptr, nullptr);
                if(p_current->value > value) p_current->left = current;
                else p_current->right = current;
            }
        }
    }
}

 BST::~BST()
 {
 	std::vector<Node*> nodes;
    // Use lambda expressions to add each node to nodes
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto &node: nodes)
 		delete node;
 }

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    if(root == nullptr) return;

    std::queue<BST::Node*> sq;
    sq.push(root);
    BST::Node *current;
    
    while(!sq.empty())
    {
        current = sq.front();
        sq.pop();

        func(current);
        
        if(current->left != nullptr) sq.push(current->left);
        if(current->right != nullptr) sq.push(current->right);
    }
}

size_t BST::length()
{
    size_t num = 0;
    bfs([&num](Node*& node){ ++num; }); // use Lambda
    return num;
}

bool BST::add_node(const int value)
{
    if(root == nullptr)
    {
        root = new Node(value, nullptr, nullptr);
        return true;
    }

    Node *p_current, *current = root;
    while(current)
    {
        if(current->value == value)
        {
            std::cout << "The value already exists and cannot be added." << std::endl;
            return false;
        }
        else
        {
            p_current = current;
            if(current->value > value) current = current->left;
            else current = current->right;
        }
    }

    current = new Node(value, nullptr, nullptr);
    if(p_current->value > value) p_current->left = current;
    else p_current->right = current;
    
    return true;
}

BST::Node** BST::find_node(const int value)
{
    Node **current = &root;
    
    while(*current)
    {
        if((*current)->value == value) return current;
        else
        {
            if((*current)->value > value) current = &((*current)->left);
            else current = &((*current)->right);
        }
    }

    return nullptr;
}

BST::Node** BST::find_parent(const int value)
{
    Node **p_current = nullptr, **current = &root;
    
    while(*current)
    {
        if((*current)->value == value) return p_current;
        else
        {
            p_current = &(*current);
            if((*current)->value > value) current = &((*current)->left);
            else current = &((*current)->right);
        }
    }

    return nullptr;
}

// Find the predecessor node
BST::Node** BST::find_successor(const int value)
{
    Node **current = find_node(value);
    if(current == nullptr) return nullptr;
    
    // 二叉树中一个节点的前继节点为：
    // 该节点的左子树存在，则为其左子树中的最右节点
    // 该节点的左子树不存在，则为其父节点
    if((*current)->left)
    {
        // 左子树存在的情况
        Node **temp =  &((*current)->left);
        while((*temp)->right) temp = &((*temp)->right);

        return temp;
    }
    else
    {
        return find_parent(value);
    }
}

bool BST::delete_node(const int value)
{
    Node **c_pptr = find_node(value);
    if(c_pptr == nullptr)
    {
        std::cout << "The node to be deleted is not in the binary tree" << std::endl;
        return false;
    }
    
    Node **pc_pptr = find_parent(value);

    Node *c_ptr = *c_pptr; // 当前节点
    Node *pc_ptr = nullptr; // 当前节点的父节点
    Node *rc_ptr = nullptr; // 取代节点
    Node *prc_ptr = nullptr; // 取代节点的父节点

    if(pc_pptr != nullptr) pc_ptr = *pc_pptr; // 更新 pc_ptr 的值

    // NOTE: 删除当前节点的操作放在了最后，便于减少代码量
    // Case1: 删除节点是叶节点, 直接删除
    if(c_ptr->left == nullptr && c_ptr->right == nullptr)
    {
        if(c_ptr == root) root = nullptr;
        else
        {
            if(pc_ptr->left == c_ptr) pc_ptr->left = nullptr;
            else pc_ptr->right = nullptr;
        }
    }
    else
    {
        // Case2: 删除节点左右孩子均存在，选择前继节点来取代
        // NOTE: 选后继节点来取代过不了测试，因为测试样例选择的是前继节点
        if(c_ptr->left && c_ptr->right)
        {
            prc_ptr = c_ptr;
            rc_ptr = c_ptr->left;

            while(rc_ptr->right)
            {
                prc_ptr = rc_ptr;
                rc_ptr = rc_ptr->right;
            }

            if(c_ptr == root)
            {
                rc_ptr->right = root->right;
                
                if(prc_ptr == c_ptr)
                {
                    prc_ptr->left = rc_ptr->left;
                }
                else
                {
                    prc_ptr->right = rc_ptr->left;
                }

                rc_ptr->left = root->left;

                root = rc_ptr;
            }
            else
            {
                // 更新删除节点的父节点
                if(pc_ptr->left == c_ptr) pc_ptr->left = rc_ptr;
                else pc_ptr->right = rc_ptr;

                rc_ptr->right = c_ptr->right;

                if(prc_ptr == c_ptr)
                {
                    prc_ptr->left = rc_ptr->left;
                }
                else
                {
                    prc_ptr->right = rc_ptr->left;
                }

                rc_ptr->left = c_ptr->left;
            }
        }
        else
        {
            // Case3: 删除节点只存在一个孩子，直接用该孩子来取代
            prc_ptr = c_ptr;
            if(c_ptr->left) rc_ptr = c_ptr->left;
            else rc_ptr = c_ptr->right;

            if(c_ptr == root)
            {
                root = rc_ptr;
            }
            else
            {
                if(pc_ptr->left == c_ptr) pc_ptr->left = rc_ptr;
                else pc_ptr->right = rc_ptr;
            }
        }
    }

    delete c_ptr;

    return true;
}

std::ostream& operator<<(std::ostream &out, BST &bst)
{
    out << std::string(80, '*') << std::endl;
    bst.bfs([&out](BST::Node*& node){
        out << std::left << std::setw(17) << std::setfill(' ') << node;
        out << "=> value:" << std::setw(7) << std::setfill(' ') << node->value;

        if(node->left) 
        {
            out << std::left << "left:" << std::setw(16) << std::setfill(' ') << node->left;
        }
        else 
        {
            out << std::left << "left:" << std::setw(16) << std::setfill(' ') << 0;
        }

        if(node->right) 
        {
            out << std::left << "right:" << std::setw(16) << std::setfill(' ') << node->right << std::endl;
        }
        else 
        {
            out << std::left << "right:" << std::setw(16) << std::setfill(' ') << 0 << std::endl;
        }
    });
    out << "binary search tree size: " << bst.length() << std::endl;
    out << std::string(80, '*') << std::endl;
    return out;
}

BST& BST::operator++()
{
    bfs([](BST::Node*& node){ ++(node->value); });
    return *this;
}

BST BST::operator++(int dummy)
{
    BST new_bst(*this); 
    bfs([](BST::Node*& node){ ++(node->value); });
    return new_bst;
}

BST& BST::operator=(BST &other)
{
    if(this != &other)
    {
        // c_nodes 用于存储当前对象的节点，便于释放
        // o_nodes 用于存储other对象的节点
        std::vector<Node*> c_nodes, o_nodes;
 	    bfs([&c_nodes](BST::Node*& node){ c_nodes.push_back(node); });
        other.bfs([&o_nodes](BST::Node*& node){ o_nodes.push_back(node); });
 	    
        // 释放原来的节点
        for(auto &node: c_nodes)
        {
            delete node;
        }
        this->root = nullptr;

        for(auto &node: o_nodes)
        {
            this->add_node(node->value);
        }
    }

    return *this;
}

BST& BST::operator=(BST &&other)
{
    this->root = other.root;
    other.root = nullptr;
    return *this;
}
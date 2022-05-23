#include <iostream>
#include <queue>
using namespace std;


template <class type>
class Node
{
public:
    type value;
    Node *left, *right;
    Node(type _value = 0, Node *_left = NULL, Node *_right = NULL) : value(_value), left(_left), right(_right) {}
};

Node<int> *getnewNode(int element)
{
    Node<int> *newNode = new Node<int>();
    newNode->value = element;
    newNode->left = newNode->right = NULL;
    return newNode;
}

template <class type>
class binarySearchTree
{
private:
    Node<type> *root;

    Node<type> *_insert(Node<type> *root, type element)
    {
        if (root == NULL)
            return new Node<type>(element);
        else if (element <= root->value)
            root->left = _insert(root->left, element);
        else if (element > root->value)
            root->right = _insert(root->right, element);
        return root;
    }

    void __insert(Node<type> **root, type element)
    {
        if (*root == NULL)
            *root = new Node<type>(element);
        else if (element <= (**root).value)
            __insert(&((**root).left), element);
        else if (element > (**root).value)
            __insert(&((**root).right), element);
    }

    vector<type> _levelOrder(Node<type> *root)
    {
        if (root == NULL)
            return {};
        vector<type> elems;
        queue<Node<type> *> Q;
        Q.push(root);
        while (!Q.empty())
        {
            Node<type> *current = Q.front();
            Q.pop();
            elems.push_back(current->value);
            if (current->left != NULL)
                Q.push(current->left);
            if (current->right != NULL)
                Q.push(current->right);
        }
        return elems;
    }

    void _preOrder(Node<type> *root, vector<type> &elems)
    {
        if (root != NULL)
        {
            elems.push_back(root->value);
            _preOrder(root->left, elems);
            _preOrder(root->right, elems);
        }
    }

    void _inOrder(Node<type> *root, vector<type> &elems)
    {
        if (root != NULL)
        {
            _inOrder(root->left, elems);
            elems.push_back(root->value);
            _inOrder(root->right, elems);
        }
    }

    void _postOrder(Node<type> *root, vector<type> &elems)
    {
        if (root != NULL)
        {
            _postOrder(root->left, elems);
            _postOrder(root->right, elems);
            elems.push_back(root->value);
        }
    }

    bool _search(Node<type> *root, type element)
    {
        if (root == NULL)
            return false;
        else if (root->value == element)
            return true;
        else if (element < root->value)
            return _search(root->left, element);
        return _search(root->right, element);
    }

    type _maxElement(Node<type> *root)
    {
        if (isempty())
            return type();
        else if (root->right == NULL)
            return root->value;
        return _maxElement(root->right);
    }

    type _minElement(Node<type> *root)
    {
        if (isempty())
            return type();
        else if (root->left == NULL)
            return root->value;
        return _minElement(root->left);
    }

    int _height(Node<type> *root)
    {
        if (root == NULL)
            return -1;
        return 1 + max(_height(root->left), _height(root->right));
    }

    Node<type> *findMinElementPtr(Node<type> *root)
    {
        if (root->left == NULL)
            return root;
        return findMinElementPtr(root->left);
    }

    Node<type> *_remove(Node<type> *root, type element)
    {
        if (root == NULL)
            return root;
        else if (element < root->value)
            root->left = _remove(root->left, element);
        else if (element > root->value)
            root->right = _remove(root->right, element);
        else
        {
            // case 1: doesn't have children
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                root = NULL;
            }
            // case 2: has right child
            else if (root->left == NULL)
            {
                Node<type> *temp = root;
                root = root->right;
                delete temp;
            }
            // case 2: has left child
            else if (root->right == NULL)
            {
                Node<type> *temp = root;
                root = root->left;
                delete temp;
            }
            // case 3: has right and left children
            else
            {
                Node<type> *temp = findMinElementPtr(root->right);
                root->value = temp->value;
                root->right = _remove(root->right, temp->value);
            }
        }
        return root;
    }

    type _inorderSuccessor(Node<type> *root, type element)
    {
        if (root == NULL)
            return type();
        else if (element < root->value)
            return _inorderSuccessor(root->left, element);
        else if (element > root->value)
            return _inorderSuccessor(root->right, element);
        else
        {
            // case 1: has right subtree
            if (root->right != NULL)
            {
                return _minElement(root->right);
            }
            // case 2: doesn't have right subtree
            else
            {
                Node<type> *ancestor = this->root;
                Node<type> *successor = NULL;
                while (ancestor != root)
                {
                    if (element < ancestor->value)
                    {
                        successor = ancestor;
                        ancestor = ancestor->left;
                    }
                    else
                        ancestor = ancestor->right;
                }
                if (successor == NULL)
                    return type();
                else
                    return successor->value;
            }
        }
    }

    void _clear(Node<type> *root)
    {
        if (root != NULL)
        {
            _clear(root->left);
            _clear(root->right);
            delete root;
        }
    }

public:
    binarySearchTree() : root(NULL) {}

    ~binarySearchTree()
    {
        clear();
    }

    bool isempty()
    {
        return root == NULL;
    }

    void insert(type element)
    {
        root = _insert(root, element);
    }

    vector<type> levelOrder()
    {
        return _levelOrder(root);
    }

    vector<type> preOrder()
    {
        vector<type> elems;
        _preOrder(root, elems);
        return elems;
    }

    vector<type> inOrder()
    {
        vector<type> elems;
        _inOrder(root, elems);
        return elems;
    }

    vector<type> postOrder()
    {
        vector<type> elems;
        _postOrder(root, elems);
        return elems;
    }

    bool search(type element)
    {
        return _search(root, element);
    }

    type maxElement()
    {
        return _maxElement(root);
    }
    type minElement()
    {
        return _minElement(root);
    }

    int height()
    {
        return _height(root);
    }

    Node<type> *getRoot()
    {
        return root;
    }

    void remove(type element)
    {
        root = _remove(root, element);
    }

    type successor(type element)
    {
        return _inorderSuccessor(root, element);
    }

    void clear()
    {
        _clear(root);
        root = NULL;
    }
};

int main()
{
    return 0;
}

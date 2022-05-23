#include <iostream>
using namespace std;

template <class type>
class Node
{
public:
    type data;
    int balanceFactor, height;
    Node *left, *right;
    Node(type _data)
    {
        data = _data;
        left = right = NULL;
        balanceFactor = height = 0;
    }
};

template <class type>
class AVL
{
private:
    Node<type> *root;

    bool checkLeftBalancing(Node<type> *root, type elem)
    {
        if (root == NULL)
            return true;
        if (root->data < elem)
            return checkLeftBalancing(root->left, elem) && checkLeftBalancing(root->right, elem);
        else
            return false;
    }

    bool checkRightBalancing(Node<type> *root, type elem)
    {
        if (root == NULL)
            return true;
        if (root->data > elem)
            return checkRightBalancing(root->left, elem) && checkRightBalancing(root->right, elem);
        else
            return false;
    }

    bool _isBalanced(Node<type> *root)
    {
        if (root == NULL)
            return true;
        if (checkLeftBalancing(root->left, root->data) && checkRightBalancing(root->right, root->data))
            return _isBalanced(root->left) && _isBalanced(root->right);
        else
            return false;
    }

    bool _search(Node<type> *_root, type element)
    {
        if (_root == NULL)
            return false;
        else if (_root->data == element)
            return true;
        else if (element < _root->data)
            return _search(_root->left, element);
        else
            return _search(_root->right, element);
    }

    void update(Node<type> *root)
    {
        int leftHight = -1, rightHight = -1;

        if (root->left != NULL)
            leftHight = root->left->height;
        if (root->right != NULL)
            rightHight = root->right->height;

        root->height = max(leftHight, rightHight) + 1;

        root->balanceFactor = leftHight - rightHight;
    }

    Node<type> *rightRotation(Node<type> *root)
    {
        Node<type> *temp = root->left;
        root->left = temp->right;
        temp->right = root;

        update(root);
        update(temp);

        return temp;
    }

    Node<type> *leftRotation(Node<type> *root)
    {
        Node<type> *temp = root->right;
        root->right = temp->left;
        temp->left = root;

        update(root);
        update(temp);

        return temp;
    }

    Node<type> *balance(Node<type> *root)
    {
        // left case
        if (root->balanceFactor == 2)
        {
            if (root->left->balanceFactor == -1) // left right case
                root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        // right case
        if (root->balanceFactor == -2)
        {
            if (root->right->balanceFactor == 1) // right left case
                root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    Node<type> *_insert(Node<type> *root, type elem)
    {
        if (root == NULL)
            root = new Node<type>(elem);
        else if (elem < root->data)
            root->left = _insert(root->left, elem);
        else
            root->right = _insert(root->right, elem);

        update(root);

        return balance(root);
    }

    Node<type> *_FindMinimum(Node<type> *_root)
    {
        if (_root == NULL)
            return NULL;
        if (_root->left != NULL)
            return _FindMinimum(_root->left);
        else
            return _root;
    }

    Node<type> *_FindMinIterative(Node<type> *_root)
    {
        if (_root == NULL)
            return NULL;
        while (_root->left != NULL)
            _root = _root->left;
        return _root;
    }

    Node<type> *_FindMax(Node<type> *_root)
    {
        if (_root == NULL)
            return NULL;
        if (_root->right != NULL)
            return _FindMax(_root->right);
        else
            return _root;
    }

    Node<type> *_FindMaxIterative(Node<type> *_root)
    {
        if (_root == NULL)
            return NULL;
        while (_root->right != NULL)
            _root = _root->right;
        return _root;
    }

    Node<type> *_remove(Node<type> *root, type elem)
    {
        if (root == NULL)
            return NULL;
        else if (elem < root->data)
            root->left = _remove(root->left, elem);
        else if (elem > root->data)
            root->right = _remove(root->right, elem);
        else
        {
            // case 1
            if (root->right == NULL && root->left == NULL)
            {
                delete root;
                root = NULL;
            }
            // case 2;
            else if (root->left == NULL)
            {
                Node<type> *temp = root->right;
                delete root;
                root = temp;
            }
            else if (root->right == NULL)
            {
                Node<type> *temp = root->left;
                delete root;
                root = temp;
            }
            // case 3
            else
            {
                Node<type> *temp = _FindMinimum(root->right);
                root->data = temp->data;
                root->right = _remove(root->right, temp->data);
            }
        }

        update(root);
        return balance(root);
    }

public:
    AVL(Node<type> *_root = NULL) : root(_root) {}

    bool isBalanced()
    {
        return _isBalanced(root);
    }

    bool search(type elem)
    {
        return _search(root, elem);
    }

    bool insert(type elem)
    {
        if (_search(root, elem))
            return false;
        else
            root = _insert(root, elem);
        return true;
    }

    int Height()
    {
        return root->height;
    }

    void Remove(type elem)
    {
        root = _remove(root, elem);
    }
};
int main()
{
    return 0;
}
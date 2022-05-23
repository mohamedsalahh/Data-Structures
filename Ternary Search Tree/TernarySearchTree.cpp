#include <iostream>
using namespace std;

class Node
{
public:
    char val;
    bool isWord;
    Node *left, *right, *mid;
    Node(char _val, Node *_left, Node *_mid, Node *_right, bool _isWord) : val(_val), left(_left), mid(_mid), right(_right), isWord(_isWord) {}
};

class TST
{
private:
    Node *root;
    bool _search(Node *_root, string word, int idx = 0)
    {
        if (_root == NULL)
            return false;

        if (word[idx] > _root->val)
            return _search(_root->right, word, idx);
        else if (word[idx] < _root->val)
            return _search(_root->left, word, idx);
        else
        {
            if (idx == word.size() - 1)
                return _root->isWord;
            else
                return _search(_root->mid, word, idx + 1);
        }
    }
    Node *_insert(Node *_root, string word, int idx = 0)
    {
        if (_root == NULL)
            _root = new Node(word[idx], 0, 0, 0, 0);

        if (word[idx] > _root->val)
            _root->right = _insert(_root->right, word, idx);
        else if (word[idx] < _root->val)
            _root->left = _insert(_root->left, word, idx);
        else
        {
            if (idx == word.size() - 1)
                _root->isWord = true;
            else
                _root->mid = _insert(_root->mid, word, idx + 1);
        }

        return _root;
    }

public:
    TST() : root(NULL) {}

    TST(const TST &TST)
    {
        root = TST.root;
    }
    void insert(string word)
    {
        root = _insert(root, word);
    }
    bool search(string word)
    {
        return _search(root, word);
    }
};
int main()
{
    return 0;
}
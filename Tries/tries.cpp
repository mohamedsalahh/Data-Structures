#include <iostream>
#include <map>
#include <queue>
using namespace std;

class Node
{
public:
    bool isWord = false;
    int Count = 0;
    map<char, Node *> children;
};

class Trie
{
private:
    Node *root;

    void _insert(Node *_root, string word, int idx = 0)
    {
        if (_root->children[word[idx]] == NULL)
            _root->children[word[idx]] = new Node;

        _root->children[word[idx]]->Count += 1; // count prefix

        if (idx == word.size() - 1)
        {
            _root->children[word[idx]]->isWord = true;
            return;
        }

        _insert(_root->children[word[idx]], word, idx + 1);
    }

    bool _search(Node *_root, string word, int idx = 0)
    {
        if (_root->children[word[idx]] != NULL)
        {
            if (idx == word.size() - 1)
                return _root->children[word[idx]]->isWord;
            return _search(_root->children[word[idx]], word, idx + 1);
        }

        return false;
    }

    int _countPrefix(Node *_root, string word, int idx = 0)
    {
        if (_root->children[word[idx]] != NULL)
        {
            if (idx == word.size() - 1)
                return _root->children[word[idx]]->Count;
            return _countPrefix(_root->children[word[idx]], word, idx + 1);
        }

        return 0;
    }
    void _removeUsingPrefixCounting(Node *_root, string word, int idx = 0)
    {
        if (idx == word.size())
            return;
        if (idx == word.size() - 1)
            _root->children[word[idx]]->isWord = false;

        if (_root->children[word[idx]]->Count != 1)
            _root->children[word[idx]]->Count--;
        else
        {
            Node *next = _root->children[word[idx]];
            _root->children[word[idx]] = NULL;
            _root = next;
            idx++;
            while (idx < word.size())
            {
                Node *next = _root->children[word[idx]];
                delete _root;
                _root = next;
                idx++;
            }
            delete _root;
            return;
        }

        _removeUsingPrefixCounting(_root->children[word[idx]], word, idx + 1);
    }

    bool isEmpty(Node *_root)
    {
        for (auto child : _root->children)
        {
            if (child.second)
                return false;
        }
        return true;
    }

    Node *_remove(Node *_root, string word, int idx = 0)
    {
        if(_root == NULL) return NULL; 

        if (idx == word.size())
            _root->isWord = false;
        else
            _root->children[word[idx]] = _remove(_root->children[word[idx]], word, idx + 1);
        
        if (idx == 0)
            return _root;

        _root->Count -= 1;

        if (isEmpty(_root) && !_root->isWord)
        {
            delete _root;
            _root = NULL;
        }

        return _root;
    }

    Node *findRef(Node *_root, string word, int idx = 0)
    {
        if (_root->children[word[idx]] == NULL)
            return NULL;
        if (idx == word.size() - 1)
            return _root->children[word[idx]];
        return findRef(_root->children[word[idx]], word, idx + 1);
    }

    void _prefixMatch(Node *_root, string Prefix, queue<string> &Q)
    {
        if(_root == NULL) return;

        if (_root->isWord)
            Q.push(Prefix);
        for (auto child : _root->children)
        {
            Prefix.push_back(child.first);
            _prefixMatch(child.second, Prefix, Q);
            Prefix.pop_back();
        }
    }

public:
    Trie() : root(new Node) {}

    Trie(const Trie &trie)
    {
        root = trie.root;
    }

    void insert(string word)
    {
        _insert(root, word);
    }

    bool search(string word)
    {
        return _search(root, word);
    }

    int countPrefix(string word)
    {
        return _countPrefix(root, word);
    }

    void remove(string word)
    {
        //_removeUsingPrefixCounting(root, word);
        root = _remove(root, word);
    }

    queue<string> prefixMatch(string Prefix)
    {
        Node *curr = findRef(root, Prefix);
        if (!curr)
            return {};

        queue<string> Q;
        _prefixMatch(curr, Prefix, Q);
        return Q;
    }

    queue<string> words()
    {
        queue<string> Q;
        _prefixMatch(root, "", Q);
        return Q;
    }
};

int main()
{
    return 0;
}
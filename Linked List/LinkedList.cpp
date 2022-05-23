#include <iostream>
#include <cassert>
using namespace std;

template <class type>
class Node
{
public:
    type value;
    Node *next;
};

template <class type>
class linkedList
{
private:
    Node<type> *head;
    Node<type> *tail;
    int length;

public:
    linkedList() : head(NULL), tail(NULL), length(0) {}

    ~linkedList()
    {
        clear();
    }

    Node<type> *getHead()
    {
        return head;
    }

    Node<type> *getTail()
    {
        return tail;
    }

    void insertFront(type element)
    {
        Node<type> *newNode = new Node<type>();
        newNode->value = element;

        if (length == 0)
        {
            newNode->next = NULL;
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }

        length++;
    }

    void insertBack(type element)
    {
        Node<type> *newNode = new Node<type>;
        newNode->value = element;
        newNode->next = NULL;

        if (length == 0)
            tail = head = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        length++;
    }

    bool isempty()
    {
        return length == 0;
    }

    void insert(type element, int pos)
    {
        if (pos > length || pos < 0)
            pos = length;

        if (pos == length)
            insertBack(element);
        else if (pos == 0)
            insertFront(element);
        else
        {
            int idx = 0;
            Node<type> *temp = head;
            while (idx < pos - 1)
            {
                temp = temp->next;
                idx++;
            }

            Node<type> *newNode = new Node<type>();
            newNode->value = element;
            newNode->next = temp->next;
            temp->next = newNode;
            length++;
        }
    }

    void removeFront()
    {
        if (isempty())
            return;

        if (length == 1)
        {
            delete head;
            head = tail = NULL;
            length--;
        }
        else
        {
            Node<type> *temp = head;
            head = head->next;
            delete temp;
            length--;
        }
    }

    void removeBack()
    {
        if (isempty())
            return;

        if (length == 1)
        {
            delete head;
            head = tail = NULL;
            length--;
        }
        else
        {
            Node<type> *temp = head;
            while (temp->next != tail)
                temp = temp->next;
            delete tail;
            temp->next = NULL;
            tail = temp;
            length--;
        }
    }

    void remove(type element)
    {
        if (isempty())
            return;

        if (head->value == element)
            removeFront();
        else if (tail->value == element)
            removeBack();
        else
        {
            Node<type> *temp1 = head;
            while (temp1->next != NULL && temp1->next->value != element)
                temp1 = temp1->next;
            if (temp1->next == NULL)
                return;

            Node<type> *temp2 = temp1->next;
            temp1->next = temp2->next;
            delete temp2;
            length--;
        }
    }

    int Search(type element)
    {
        int pos = 0;
        Node<type> *temp = head;
        while (temp != NULL)
        {
            if (temp->value == element)
                return pos;
            temp = temp->next;
            pos++;
        }

        return -1;
    }

    void reverse()
    {
        if (length == 0 || length == 0)
            return;
        Node<type> *temp1 = NULL;
        Node<type> *temp2 = head;
        Node<type> *temp3 = head->next;
        while (temp3 != NULL)
        {
            temp2->next = temp1;
            temp1 = temp2;
            temp2 = temp3;
            temp3 = temp3->next;
        }
        temp2->next = temp1;
        tail = head;
        head = temp2;
    }

    int size()
    {
        return length;
    }

    void clear()
    {
        Node<type> *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;
        length = 0;
    }
};

int main()
{
    linkedList<int> l;
    return 0;
}

#include <iostream>
using namespace std;

template <class type>
class Node
{
public:
    type value;
    Node *next;
    Node *prev;
};

template <class type>
class doublyLinkedList
{
private:
    Node<type> *head;
    Node<type> *tail;
    int length;

public:
    doublyLinkedList() : head(NULL), tail(NULL), length(0) {}

    ~doublyLinkedList()
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

    bool isempty()
    {
        return length == 0;
    }

    void insertFront(type element)
    {
        Node<type> *newNode = new Node<type>();
        newNode->value = element;

        if (isempty())
        {
            newNode->next = newNode->prev = NULL;
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            newNode->prev = NULL;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    void insertBack(type element)
    {
        Node<type> *newNode = new Node<type>();
        newNode->value = element;
        if (isempty())
        {
            newNode->next = newNode->prev = NULL;
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void insert(type element, int pos)
    {
        if (pos > length || pos < 0)
            pos = length;

        if (pos == 0)
            insertFront(element);
        else if (pos == length)
            insertBack(element);
        else
        {
            Node<type> *temp = head;
            for (int i = 0; i < pos - 1; ++i)
                temp = temp->next;

            Node<type> *newNode = new Node<type>();
            newNode->value = element;

            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
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
            head->prev = NULL;
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
            Node<type> *temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
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
            Node<type> *temp = head;
            while (temp != NULL && temp->value != element)
                temp = temp->next;

            if (temp == NULL)
                return;
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                length--;
            }
        }
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

    int Sizeof()
    {
        return length;
    }
};

int main()
{
    return 0;
}

#include <iostream>
using namespace std;

template <class type>
class Node
{
public:
    type value;
    Node *next;
    Node(type _value = type(), Node *_next = NULL) : value(_value), next(_next) {}
};

template <class type>
class Stack
{
private:
    Node<type> *top;
    int lenght;

public:
    Stack() : top(0), lenght(0) {}

    Stack(const Stack &stack)
    {
        top = stack.top;
        lenght = stack.lenght;
    }

    ~Stack()
    {
        clear();
    }

    bool isEmpty()
    {
        return lenght == 0;
    }

    int size()
    {
        return lenght;
    }

    type getTop()
    {
        if (isEmpty())
            return type();
        return top->value;
    }

    void push(type element)
    {
        top = new Node<type>(element, top);
        lenght++;
    }

    type pop()
    {
        if (isEmpty())
            return type();

        Node<type> *temp = top;
        top = top->next;

        type value = temp->value;
        delete temp;

        lenght--;

        return value;
    }

    void clear()
    {
        while (top != NULL)
        {
            Node<type> *temp = top;
            top = top->next;

            delete temp;
        }
    }
};

int main()
{
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

class Heap
{
private:
    vector<int> items;
    int heapSize, heapCapacity;

    int leftChildIndex(int index) { return 2 * index + 1; }

    int rightChildIndex(int index) { return 2 * index + 2; }

    int parentIndex(int index) { return (index - 1) / 2; }

    bool hasLeftChild(int index) { return (2 * index + 1) < heapSize; }

    bool hasRightchild(int index) { return (2 * index + 2) < heapSize; }

    bool hasParent(int index) { return ((index - 1) / 2) >= 0; }

    void hasCapacity()
    {
        if (heapSize == heapCapacity)
        {
            heapCapacity *= 2;
            items.resize(heapCapacity);
        }
    }

    void Swap(int i, int j)
    {
        int temp = items[i];
        items[i] = items[j];
        items[j] = temp;
    }

    int contains(int item)
    {
        int index = 0;
        for (int i = 0; i < heapSize; ++i)
        {
            index = i;
            if (items[i] == item)
                break;
        }
        return index == heapSize ? -1 : index;
    }

    int swim(int index)
    {
        while (hasParent(index) && items[index] < items[parentIndex(index)])
        {
            Swap(index, parentIndex(index));
            index = parentIndex(index);
        }
        return index;
    }

    int sink(int index)
    {
        while (hasLeftChild(index))
        {
            int smallerIndex = leftChildIndex(index);
            if (hasRightchild(index) && items[smallerIndex] > items[rightChildIndex(index)])
                smallerIndex = rightChildIndex(index);
            if (items[index] < items[smallerIndex])
                break;
            Swap(index, smallerIndex);
            index = smallerIndex;
        }
        return index;
    }

public:
    Heap()
    {
        heapCapacity = 100;
        heapSize = 0;
        items = vector<int>(heapCapacity);
    }

    Heap(int _capacity)
    {
        heapCapacity = _capacity;
        heapSize = 0;
        items = vector<int>(heapCapacity);
    }

    Heap(const vector<int> &elems)
    {
        heapSize = elems.size();
        heapCapacity = elems.size() + 50;
        items = vector<int>(heapCapacity);

        for (int i = 0; i < heapSize; i++)
            items[i] = elems[i];

        for (int i = max(0, (heapSize / 2) - 1); i >= 0; i--)
            sink(i);
    }

    int size()
    {
        return heapSize;
    }

    bool isEmpty()
    {
        return heapSize == 0;
    }

    int peek()
    {
        if (isEmpty())
            return -1;
        return items[0];
    }

    void add(int item)
    {
        hasCapacity();
        items[heapSize] = item;
        heapSize++;
        swim(heapSize - 1);
    }

    int poll()
    {
        if (isEmpty())
            return -1;

        int item = items[0];
        Swap(0, heapSize - 1);
        heapSize--;
        sink(0);
        return item;
    }

    bool remove(int item)
    {
        if (isEmpty())
            return false;

        int index = contains(item);
        if (index == -1)
            return false;
        Swap(index, heapSize - 1);
        heapSize--;

        index = sink(index);
        index = swim(index);

        /*
        int data = items[index];
        sink(index);
        if(items[index] == data) 
            swim(index);
        */
        return true;
    }
};

int main()
{
    return 0;
}

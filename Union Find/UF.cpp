#include <iostream>
#include <vector>
using namespace std;

class UF_QuickFind
{
private:
    int Size;
    vector<int> id;

public:
    UF_QuickFind(int Size)
    {
        this->Size = Size;
        id = vector<int>(Size);
        for (int i = 0; i < Size; ++i)
        {
            id[i] = i;
        }
    }

    bool Connected(int x, int y)
    {
        return id[x] == id[y];
    }

    void Union(int x, int y)
    {
        int x_id = id[x];
        int y_id = id[y];
        for (int i = 0; i < Size; ++i)
        {
            if (id[i] == y_id)
                id[i] = x_id;
        }
    }
};

class UF_QuickUnion
{
private:
    int Size;
    vector<int> id;

public:
    UF_QuickUnion(int Size)
    {
        this->Size = Size;
        id = vector<int>(Size);
        for (int i = 0; i < Size; ++i)
        {
            id[i] = i;
        }
    }

    int Find(int x)
    {
        while (x != id[x])
            x = id[x];

        return x;
    }

    bool Connected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    void Union(int x, int y)
    {
        if (!Connected(x, y))
        {
            id[Find(y)] = Find(x);
        }
    }
};

class UF
{
private:
    vector<int> id, sz;
    int NoComponent, Size;

public:
    UF(int Size)
    {
        id = vector<int>(Size);
        sz = vector<int>(Size);
        this->Size = Size;
        NoComponent = Size;

        for (int i = 0; i < Size; ++i)
        {
            id[i] = i;
            sz[i] = 1;
        }
    }

    int Find(int x)
    {
        int root = x;

        while (root != id[root])
            root = id[root];
        while (x != root)
        {
            int next = id[x];
            id[x] = root;
            x = next;
        }

        return root;
    }

    bool Connected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int ComponentsNo()
    {
        return NoComponent;
    }

    void Union(int x, int y)
    {
        int i = Find(x);
        int j = Find(y);

        if (i == j)
            return;

        if (sz[i] > sz[j])
        {
            id[j] = i;
            sz[i] += sz[j];
        }
        else
        {
            id[i] = j;
            sz[j] += sz[i];
        }
        NoComponent--;
    }
};

int main()
{
    return 0;
}

#include <iostream>

const int MAX_SIZE = 10009;

using namespace std;

template <typename T>
struct Stack
{
    struct Node
    {
        Node *next;
        T value;
    };

    typename Stack<T>::Node *_top;
    int _size;

    Stack()
    {
        this->_top = nullptr;
        this->_size = 0;
    }
    ~Stack()
    {
        while (this->_size)
            this->pop();
    }
    void push(T element)
    {
        typename Stack<T>::Node *temp = new Node;
        temp->value = element;

        if (!this->_top)
            temp->next = nullptr;
        else
            temp->next = this->_top;

        this->_top = temp;

        ++(this->_size);
    }
    T top()
    {
        return this->_top->value;
    }
    void pop()
    {
        if (this->_top)
        {
            typename Stack<T>::Node *nextNode = this->_top->next;
            delete this->_top;
            this->_top = nextNode;

            --(this->_size);
        }
    }
    int size()
    {
        return this->_size;
    }
};

struct struc
{
    int idx;
    int woman_idx;
    int man_idx;

    friend bool operator<(const struc &lhs, const struc &rhs)
    {
        return lhs.idx < rhs.idx;
    }

    friend bool operator>(const struc &lhs, const struc &rhs)
    {
        return lhs.idx > rhs.idx;
    }
};

template <typename T>
void quickSort(T arr[], int low, int high)
{
    auto partition = [](T arr[], int low, int high)
    {
        T pivot = arr[low];
        int i = low, j = high;

        while (true)
        {
            while (arr[i] < pivot)
                ++i;
            while (arr[j] > pivot)
                --j;
            if (i >= j)
                return j;
            swap(arr[i], arr[j]);
        }
    };

    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot);
        quickSort(arr, pivot + 1, high);
    }
}

int exponentialSearch(struc arr[], int n, int x)
{
    for (int i = 0, j = n / 2; j > 0; i += j)
    {
        if (arr[i].idx == x)
            return i;
        while (i + j >= n || arr[i + j].idx > x)
            j /= 2;
    }

    return -1;
}

int getRoot(struc arr[], int n)
{
    bool found[n]{};

    for (int i = 0; i < n; ++i)
    {
        if (arr[i].woman_idx)
            found[exponentialSearch(arr, n, arr[i].woman_idx)] = true;
        if (arr[i].man_idx)
            found[exponentialSearch(arr, n, arr[i].man_idx)] = true;
    }

    for (int i = 0; i < n; ++i)
        if (!found[i])
            return i;

    return -1;
}

int getDepth(struc arr[], int n, int pos)
{
    if (arr[pos].woman_idx == 0 && arr[pos].man_idx == 0)
        return 1;

    int woman_depth = 0, man_depth = 0;
    if (arr[pos].woman_idx)
        woman_depth = 1 + getDepth(arr, n, exponentialSearch(arr, n, arr[pos].woman_idx));
    if (arr[pos].man_idx)
        man_depth = 1 + getDepth(arr, n, exponentialSearch(arr, n, arr[pos].man_idx));

    return (woman_depth > man_depth ? woman_depth : man_depth);
}

void fillLevels(struc arr[], Stack<int> ans[], int n, int lvl, int pos)
{
    ans[lvl].push(arr[pos].idx);

    if (arr[pos].man_idx)
        fillLevels(arr, ans, n, lvl + 1, exponentialSearch(arr, n, arr[pos].man_idx));
    if (arr[pos].woman_idx)
        fillLevels(arr, ans, n, lvl + 1, exponentialSearch(arr, n, arr[pos].woman_idx));
}

void solve()
{
    (void)!freopen("team.in", "r", stdin);
    (void)!freopen("team.out", "w", stdout);

    struc arr[MAX_SIZE];
    int size = 0;
    while (true)
    {
        int participant, woman, man;
        cin >> participant >> woman >> man;

        // cerr << participant << " " << woman << " " << man << endl;

        if (participant == 0)
            break;

        arr[size++] = {participant, woman, man};
    }

    quickSort(arr, 0, size - 1);

    int root = getRoot(arr, size);

    int depth = getDepth(arr, size, root);

    Stack<int> *ans = new Stack<int>[depth];
    fillLevels(arr, ans, size, 0, root);

    for (int i = depth - 1; i >= 0; --i)
    {
        cout << i << ": ";
        while (ans[i].size())
        {
            cout << ans[i].top() << " ";
            ans[i].pop();
        }
        cout << endl;
    }
}

int main()
{
    solve();
}
#include <iostream>

using namespace std;

template <typename T>
struct node
{
    node *next;
    T value;
};

template <typename T>
class stack
{
private:
    node<T> *_top;
    int _size;

public:
    stack()
    {
        this->_top = new node<T>{nullptr};
        this->_size = 0;
    }
    ~stack()
    {
        while (this->_size)
            (void)this->pop();

        delete this->_top;
    }
    void push(T element)
    {
        if (!(this->_size)++)
            this->_top->value = element;
        else
            this->_top = new node<T>{this->_top, element};
    }
    T pop()
    {
        if (!this->_size)
            return 0;

        --(this->_size);

        if (!this->_size)
            return this->_top->value;

        node<T> *nextNode = this->_top->next;
        T currValue = this->_top->value;

        delete this->_top;
        this->_top = nextNode;

        return currValue;
    }
    int size()
    {
        return this->_size;
    }
};

int main()
{
    (void)!freopen("post.in", "r", stdin);
    (void)!freopen("post.out", "w", stdout);

    stack<string> arr['z' - 'a' + 1];

    char ch;
    string temp = "";
    while (cin.get(ch))
    {

        if (ch != ' ' && ch != '\n')
        {
            temp.push_back(ch);
        }

        if (ch == ' ' || ch == '\n' || cin.peek() == EOF)
        {
            if (!temp.empty())
            {
                if (temp[0] >= 'a' && temp[0] <= 'z')
                    arr[temp[0] - 'a'].push(temp);
                else
                    arr[temp[0] - 'A'].push(temp);
            }

            temp = "";
        }
    }

    bool empty = true;
    for (int i = 0; i < 'z' - 'a' + 1; ++i)
    {
        while (arr[i].size())
        {
            empty = false;
            cout << arr[i].pop() << " ";
        }
    }

    if (empty)
        cout << "nothing";
}
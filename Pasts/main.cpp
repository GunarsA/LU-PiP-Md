#include <iostream>

#define MAX_LEN 256

using namespace std;

void strcpy(char from[], char to[])
{
    int i = -1;
    while (from[++i])
        to[i] = from[i];
    to[i] = '\0';
}

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
        this->_top = nullptr;
        this->_size = 0;
    }
    ~stack()
    {
        while (this->_size)
            this->pop();
    }
    void push(T element)
    {
        node<T> *temp = new node<T>;
        strcpy(element, temp->value);

        if (!this->_top)
        {
            temp->next = nullptr;
            this->_top = temp;
        }
        else
        {
            temp->next = this->_top;
            this->_top = temp;
        }

        ++(this->_size);
    }
    void top(T element)
    {
        if (this->_top)
            strcpy(this->_top->value, element);
    }
    void pop()
    {
        if (this->_top)
        {
            --(this->_size);

            node<T> *nextNode = this->_top->next;
            delete this->_top;
            this->_top = nextNode;
        }
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

    stack<char[MAX_LEN + 1]> arr['z' - 'a' + 1];

    char ch;
    char temp[MAX_LEN + 1];
    int currLen = 0;
    while (cin.get(ch))
    {

        if (ch != ' ' && ch != '\n')
        {
            temp[currLen++] = ch;
        }

        if (ch == ' ' || ch == '\n' || cin.peek() == EOF)
        {
            if (currLen)
            {
                temp[currLen] = '\0';

                if (temp[0] >= 'a' && temp[0] <= 'z')
                    arr[temp[0] - 'a'].push(temp);
                else
                    arr[temp[0] - 'A'].push(temp);
            }

            currLen = 0;
        }
    }

    bool empty = true;
    for (int i = 0; i < 'z' - 'a' + 1; ++i)
    {
        while (arr[i].size())
        {
            empty = false;

            arr[i].top(temp);
            arr[i].pop();
            
            cout << temp << " ";
        }
    }

    if (empty)
        cout << "nothing";
}
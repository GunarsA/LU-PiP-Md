#include <iostream>
#include <tuple>

using namespace std;

template <typename T>
class implicit_treap
{
private:
    struct node
    {
        T value;
        int prior, cnt;
        bool rev;
        node *l, *r;
        node(T value) : value(value), prior(rand()), cnt(1), rev(false), l(nullptr), r(nullptr) {}
    };

    node *root;

    int cnt(node *it) const
    {
        return it ? it->cnt : 0;
    }

    void upd_cnt(node *it) const
    {
        if (it)
            it->cnt = cnt(it->l) + cnt(it->r) + 1;
    }

    void push(node *it)
    {
        if (it && it->rev)
        {
            it->rev = false;
            swap(it->l, it->r);
            if (it->l)
                it->l->rev ^= true;
            if (it->r)
                it->r->rev ^= true;
        }
    }

    pair<node *, node *> split(node *const t, int key, int add = 0)
    {
        if (!t)
            return {nullptr, nullptr};
        push(t);
        int cur_key = add + cnt(t->l);
        node *l, *r;
        if (key <= cur_key)
            tie(l, t->l) = split(t->l, key, add), r = t;
        else
            tie(t->r, r) = split(t->r, key, add + 1 + cnt(t->l)), l = t;
        upd_cnt(t);

        return {l, r};
    }

    node *merge(node *l, node *r)
    {
        push(l);
        push(r);
        node *t;
        if (!l || !r)
            return l ? l : r;
        else if (l->prior > r->prior)
            l->r = merge(l->r, r), t = l;
        else
            r->l = merge(l, r->l), t = r;
        upd_cnt(t);

        return t;
    }

    void print(node *t)
    {
        if (!t)
            return;
        push(t);
        print(t->l);
        cout << t->value << " ";
        print(t->r);
    }

    void clear(node *t)
    {
        if (!t)
            return;
        clear(t->l);
        clear(t->r);
        delete t;
    }

public:
    implicit_treap() : root(nullptr) {}

    ~implicit_treap()
    {
        clear(root);
    }

    void push_back(T value)
    {
        root = merge(root, new node(value));
    }

    void insert(int pos, T value)
    {
        auto [a, b] = split(root, pos);
        root = merge(merge(a, new node(value)), b);
    }

    void erase(int pos)
    {
        auto [a, b] = split(root, pos);
        auto [c, d] = split(b, 1);
        delete c;
        root = merge(a, d);
    }

    T operator[](int pos) const
    {
        auto [a, b] = split(root, pos);
        auto [c, d] = split(b, 1);
        T res = c->value;
        root = merge(merge(a, c), d);
        return res;
    }

    T &operator[](int pos)
    {
        auto [a, b] = split(root, pos);
        auto [c, d] = split(b, 1);
        T &res = c->value;
        root = merge(merge(a, c), d);
        return res;
    }

    void reverse(int l, int r)
    {
        auto [a, b] = split(root, l);
        auto [c, d] = split(b, r - l + 1);
        c->rev ^= true;
        b = merge(c, d);
        root = merge(a, b);
    }

    int size() const
    {
        return cnt(root);
    }

    void print()
    {
        print(root);
        cout << endl;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }
};

main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    implicit_treap<int> treap1;
    for (int i = 0; i < 10; i++)
        treap1.push_back(arr[i]);

    treap1.print();
    treap1.reverse(2, 5);
    treap1.print();
    treap1.reverse(2, 5);
    treap1.print();
    treap1.erase(9);
    treap1.print();
    treap1.insert(0, 123);
    treap1.print();

    treap1[0] = 321;

    for (int i = 0; i < 10; i++)
        printf("%d ", treap1[i]);
    printf("\n");

    int n, q, m;
    cin >> n >> q >> m;

    implicit_treap<int> treap;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        treap.push_back(temp);
    }

    for (int i = 0; i < q; i++)
    {
        int opt, l, r;
        cin >> opt >> l >> r;
        --l, --r;

        if (opt == 1)
        {
            int temp = treap[r];
            treap.erase(r);
            treap.insert(l, temp);
        }
        else
            treap.reverse(l, r);
    }

    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        cout << treap[temp - 1] << " ";
    }
}
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
using ll = long long;

// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnd;

struct Node
{
    ll k, o;     // key and order
    ll sz;       // size of the subtree
    Node *l, *r; // left and right
    bool flip;
    Node(ll x)
    {
        k = x;
        o = rnd();
        sz = 1;
        l = r = nullptr;
        flip = false;
    }
};

ll size(Node *n)
{
    if (n)
        return n->sz;
    else
        return 0;
}

void push(Node *n)
{
    if (n == nullptr)
        return;
    if (n->flip)
    {
        if (n->l)
            n->l->flip = !n->l->flip;
        if (n->r)
            n->r->flip = !n->r->flip;
        swap(n->l, n->r);
        n->flip = 0;
    }
}

// x belongs to [1;n]
pair<Node *, Node *> split(Node *t, ll x)
{
    if (t == nullptr)
        return {nullptr, nullptr};
    push(t);
    ll szl = size(t->l), szr = size(t->r);
    if (szl >= x)
    {
        auto [a, b] = split(t->l, x);
        t->l = b;
        t->sz = size(t->l) + size(t->r) + 1;
        return {a, t};
    }
    else
    {
        auto [a, b] = split(t->r, x - szl - 1);
        t->r = a;
        t->sz = size(t->l) + size(t->r) + 1;
        return {t, b};
    }
}

Node *merge(Node *a, Node *b)
{
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;
    push(a);
    push(b);
    if ((a->o) > (b->o))
    {
        a->r = merge(a->r, b);
        a->sz = size(a->l) + size(a->r) + 1;
        return a;
    }
    else
    {
        b->l = merge(a, b->l);
        b->sz = size(b->l) + size(b->r) + 1;
        return b;
    }
}

void reverse(Node *t)
{
    if (t == nullptr)
        return;
    t->flip = !t->flip;
}

void getVector(Node *t, vector<ll> &vec)
{
    push(t);
    if (t->l)
        getVector(t->l, vec);
    vec.push_back(t->k);
    if (t->r)
        getVector(t->r, vec);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, q, m;
    cin >> n >> q >> m;
    ll a[n];
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    Node *treap = new Node(a[0]);
    for (ll i = 1; i < n; i++)
        treap = merge(treap, new Node(a[i]));
    for (ll i = 0; i < q; i++)
    {
        ll t, l, r;
        cin >> t >> l >> r;
        // t=1 -> cyclic shift to the right
        // t=2 -> reverse the segment [l,r]
        if (t == 1)
        {
            auto [a, b] = split(treap, l - 1);
            auto [c, d] = split(b, r - l);
            auto [e, f] = split(d, 1);
            treap = merge(a, e);
            treap = merge(treap, c);
            treap = merge(treap, f);
        }
        else
        {
            auto [a, b] = split(treap, l - 1);
            auto [c, d] = split(b, r - l + 1);
            reverse(c);
            treap = merge(a, c);
            treap = merge(treap, d);
        }
        // cout<<treap<<"\n";
    }
    ll b[m];
    for (ll i = 0; i < m; i++)
        cin >> b[i];
    vector<ll> res;
    getVector(treap, res);
    for (ll i = 0; i < m; i++)
    {
        cout << res[b[i] - 1] << " ";
    }
}
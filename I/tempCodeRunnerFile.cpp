int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    implicit_treap<int> treap;
    for (int i = 0; i < 10; i++)
        treap.push_back(arr[i]);

    treap.output();
    treap.reverse(2, 5);
    treap.output();
    treap.reverse(2, 5);
    treap.output();
    treap.erase(9);
    treap.output();
    treap.insert(0, 123);
    treap.output();
#include <iostream>
#include <stdio.h>

using namespace std;

template<typename T>
struct Stack {
    struct Node {
        T value;
        Node* prev;
        Node(T val) {
            value = val;
            prev = nullptr;
        }
    };
    Node* top;
    Stack() {
        top = nullptr;
    }
    ~Stack() {
        while(top!=nullptr){
            Node* prev = top->prev;
            delete top;
            top = prev;
        }
    }
    void push(T val){
        Node* node = new Node(val);
        node->prev = top;
        top = node;
    }
    void pop() {
        if(top==nullptr) return;
        Node* prev = top->prev;
        delete top;
        top = prev;
    }
    bool empty() {
        return top==nullptr;
    }
};

int main () {
    freopen("post.in","r",stdin);
    freopen("post.out","w",stdout);

    Stack<string> stacks[100];
    string str;
    while(cin>>str){
        stacks[str[0]-'a'].push(str);
    }
    bool found = false;
    for(int i=0;i<100;i++){
        while(!stacks[i].empty()){
            cout<<stacks[i].top->value<<" ";
            stacks[i].pop();
            found = true;
        }
    }
    if(!found) cout<<"nothing";
}
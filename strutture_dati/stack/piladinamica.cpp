#include <iostream>

using namespace std;

class Nodo{
    public:

    Nodo* succ;
    int valore;
};

class Stack{

    Nodo* top;

    public:
    Stack(){
        top=nullptr;
    }
    ~Stack(){
        while(top!=nullptr){
            Nodo*tmp=top;
            top=top->succ;
            delete tmp;
        }
    }
    void push(int valore){
            Nodo*nuovo=new Nodo;
            nuovo->valore=valore;
            nuovo->succ=top;
            top=nuovo;
    }
    int  pop(){
        if(top==nullptr) throw out_of_range("lista vuota");
        Nodo*tmp=top;
        int val=top->valore;
        top=top->succ;
        delete tmp;
        return val;
    }
    int peek(){
        return top->valore;
    }
    friend
    ostream&operator<<(ostream&os,const Stack&s){
        Nodo*current=s.top;
        while(current!=nullptr){
            os << current->valore << endl << "-" << endl;
            current=current->succ;
        }
        return os;
    }

};

int main(){

    Stack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << stack.pop();
    cout << endl;

    cout << stack;
}
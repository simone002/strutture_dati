#include <iostream>
using namespace std;

class Nodo{
public:
    int valore;
    Nodo* succ;

    Nodo(int value):valore(value),succ(nullptr){}
};

class Coda{
    Nodo*inizio;
    Nodo*fine;
    public:
    Coda(){inizio=fine=nullptr;}

    void enqueue(int value){
        Nodo*nuovo= new Nodo(value);
        if(isEmpty()){
            inizio=fine=nuovo;
        }
        else{
            fine->succ=nuovo;
            fine=nuovo;
        }
    }

    int dequeue(){
        if(isEmpty()){
            throw out_of_range("there're no elements");
        }
        else{
            Nodo*tmp=inizio;
            int val=tmp->valore;
            inizio=inizio->succ;
            
            if(isEmpty()){
                fine=nullptr;
            }
            delete tmp;
            return val;
        }
    }
    bool isEmpty()const { return inizio ==nullptr;}

    friend
    ostream& operator<<(ostream& out, const Coda q){
        Nodo*iter;
        out << endl << "Visualizzazione coda:" << endl;
        if(q.isEmpty())
            out << "Coda vuota"<< endl;
        else{
            out << "<--";
            for(iter=q.inizio; iter!=nullptr; iter=iter->succ)
                out << "|" << iter->valore;
        out << "|<--" << endl;
        }

        out << endl;
        return out;
    }

};

int main(){

    Coda c;

    c.enqueue(3);

    c.enqueue(4);

    cout << c;
}
#include <iostream>

//listadoppiamente linkata
using namespace std;

template<typename T>
class Nodo
{
    public:
    Nodo<T>*succ;
    Nodo<T>*prec;
    T val;
    Nodo(T valore):succ(nullptr),prec(nullptr),val(valore){}
};
template<typename T>
class List
{

    Nodo<T>* testa;

    Nodo<T>*ricerca(int val)
    {
        Nodo<T>*iter=testa;
        while(iter!=nullptr)
        {
            if(iter->val==val)
                return iter;
            iter=iter->succ;
        }
        return nullptr;
    }
    public:

    List(){testa=nullptr;}
    ~List(){clear();}
    void clear()
    {
        Nodo<T>*iter=testa;
        while(iter!=nullptr){
            Nodo<T>*tmp=iter->succ;
            delete iter;
            iter=tmp;
        }
        testa=nullptr;
    }

    void ins(int val)
    { //inserimento in testa;
        Nodo<T>*nuovo=new Nodo<T>(val);
        if(testa==nullptr)
        testa=nuovo;
        else {nuovo->succ=testa;
        testa->prec=nuovo;
        testa=nuovo;
        }
    }

    void orderList()
    {
        Nodo<T>*iter=testa;
        bool change=true;
        while(change){
            change=false;
            while(iter->succ!=nullptr)
            {
                if(iter->val>iter->succ->val)
                {
                int tmp=iter->val;
                iter->val=iter->succ->val;
                iter->succ->val=tmp;
                change=true;
                }
                iter=iter->succ;
            }
        }
    }
    void insC(int val)
    { //inserimento in coda
        Nodo<T>*nuovo=new Nodo<T>(val);
        if(testa==nullptr)
        {
            testa=nuovo;
        }
        else
        {
            Nodo<T>*iter=testa;
            while(iter->succ!=nullptr)
            {
                iter=iter->succ;
            }
            iter->succ=nuovo;
            nuovo->prec=iter;
        }
    }
    void ins(int val1,T val2)
    {
        Nodo<T>*nuovo=new Nodo<T>(val1);
        if(ricerca(val2)==nullptr)
        {
            throw out_of_range("error element not present in list");
        }
        else
        {
            nuovo->succ=ricerca(val2)->succ;
            ricerca(val2)->succ->prec=nuovo;
            ricerca(val2)->succ=nuovo;
            nuovo->prec=ricerca(val2);
        }
    }


    void canc(T val)
    { // cancellare un nodo specifico
        if(ricerca(val)==nullptr) throw out_of_range("element not present in list");
        Nodo<T>*iter=testa;
        if(iter==ricerca(val))
        {
            Nodo<T>*tmp=iter->succ;
            iter->succ->prec=nullptr;
            delete iter;
            testa=tmp;
            return;
        }
        while(iter->succ!=ricerca(val))
        {
            iter=iter->succ;
        }
        Nodo<T>*tmp=iter->succ;
        iter->succ->succ->prec=iter;
        iter->succ=iter->succ->succ;
        delete tmp;
    }

    template<typename U>
    friend ostream&operator<<(ostream&os,List<U>&l)
    {
        Nodo<U>*iter=l.testa;
        while(iter!=nullptr)
        {
            os <<  iter->val << " <-- ";
            iter=iter->succ;
        }
        os << "NULL";
        return os;
    }

    //Nodo<T>* getTesta(){return testa;}

    void succ_prec_node(T val)
    {
        if(ricerca(val)->prec!=nullptr)
        {
            cout<< ricerca(val)->prec->val<< " <-- ";
        }
        else
        {
            cout << " NULL <-- ";
        }
        cout << ricerca(val)->val << " <-- ";
        if(ricerca(val)->succ!=nullptr)
        {
            cout << ricerca(val)->succ->val;
        }
        else
        {
            cout << " NULL";
        }

    }

    void reverse()
    {
        Nodo<T>* temp = NULL;
        Nodo<T>* current =testa;
 
    /* swap next and prev for all nodes of
      doubly linked list */
        while (current != NULL) {
            temp = current->prec;
            current->prec = current->succ;
            current->succ = temp;
            current = current->prec;
        }
 
    /* Before changing head, check for the cases like empty
       list and list with only one node */
        if (temp != NULL)
            testa = temp->prec;
    }


};

int main()
{

    List<int> l;
    l.ins(23);
    l.ins(25);
    l.ins(1);
    l.insC(30);
    l.ins(29,23);
    l.ins(19,23);
    l.canc(23);
    l.canc(25);
    l.canc(19);
    l.canc(1);



    cout<<endl;
    l.succ_prec_node(30);
    l.orderList();
    cout <<endl;
    l.reverse();
    cout << l;
    cout<< endl;
    l.succ_prec_node(30);
    cout<<endl;

}
    
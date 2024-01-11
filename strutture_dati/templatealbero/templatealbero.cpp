#include <iostream>

using namespace std;

template<typename T>
class Nodo{

    public:
    Nodo<T>*parent;
    Nodo<T>*dx;
    Nodo<T>*sx;
    T value;

    Nodo(T val):parent(nullptr),sx(nullptr),dx(nullptr),value(val){}
};

template<typename T>
class BST{

    Nodo<T>*root;

    Nodo<T>*ricerca(Nodo<T>*p,T value){ // O(1)caso migliore, O(logn)

        if(p==nullptr || p->value==value) return p;
        if(p->value>value)ricerca(p->sx,value);
        else ricerca(p->dx,value);
        return p;
    }



    Nodo<T>*massimo(Nodo<T>*p){
        while(p!=nullptr) p=p->dx;
        return p;
    }

    Nodo<T>* minimo(Nodo<T>*x){
        Nodo<T>*nMin=x;
        while(nMin->sx!=nullptr){
            nMin=nMin->sx;
        }
        return nMin;
    }

    void cancella(Nodo<T> *z){
        Nodo<T>*y;
        if(z->sx==nullptr){
            trapianta(z,z->dx);
        }
        else if(z->dx==nullptr){
            trapianta(z,z->sx);
        }
        else{
        //caso generale
            y=minimo(z->dx);
            if(y->parent!=z){
                trapianta(y,y->dx);
                y->dx=z->dx;
                y->dx->parent=y;
            }
        trapianta(z,y);
        y->sx=z->sx;
        y->sx->parent=y;
        }
        delete z;
    }

    void trapianta(Nodo<T>* u, Nodo<T>* v){
        if(u->parent==nullptr){
            root=v;  //u è la radice
        }
        else if(u==u->parent->sx){
            u->parent->sx=v;
        }
        else 
        u->parent->dx=v;
        if(v!=nullptr){
            v->parent=u->parent;
        }
    }

    public:

    
    BST(){root=nullptr;}
    ~BST(){postorderDistructor(root);
            cout << "distruttore";}

    int deepness(Nodo<T>*p){
        if(p==nullptr)return 0;
        
        int lh=deepness(p->sx);
        int rh=deepness(p->dx);
        if(lh>rh)return (lh+1);
        else return(rh+1);
    }

    void insert(T value){// caso pessimo O(n),caso medio O(logn) H=logn

        Nodo<T>*x=root;
        Nodo<T>*y=nullptr;
        while(x!=nullptr){
            y=x;
            if(x->value>value) x=x->sx;
            else if(x->value<value) x=x->dx;
        }
        Nodo<T>*nuovo=new Nodo<T>(value);
        nuovo->parent=y;
        if(y==nullptr) root=nuovo;
        else if(nuovo->value<y->value) y->sx=nuovo;
        else y->dx=nuovo;
    }

    void preorder(Nodo<T>*p){ //radice sinistra destra O(n) tutti e tre
        if(p!=nullptr){
            cout << p->value << " "; 
            preorder(p->sx);
            preorder(p->dx);
        }
    }

    void inorder(Nodo<T>*p){//sinistra radice, destra
        if(p!=nullptr){
            inorder(p->sx);
            cout << p->value << " ";
            inorder(p->dx);
        }
    }

    void postorder(Nodo<T>*p){
        if(p!=nullptr){
            postorder(p->sx);
            postorder(p->dx);
            cout << p->value << " ";
        }
    }

    void postorderDistructor(Nodo<T>*p){
        if(p!=nullptr){
            postorderDistructor(p->dx);
            postorderDistructor(p->sx);
            delete p;
        }
        root=nullptr;
    }

    
    T&operator[](T val){
       return ricerca(root,val)->value;
    }

    Nodo<T>*getradice(){
        return root;
    }

    int min(Nodo<T>*x){
        return minimo(x)->val;
    } 

    bool cancella(T x){ //caso pessimo O(n),caso medio O(logn)

        Nodo<T>*iter=root;
        while((iter!=nullptr) && (iter->value!=x)){
            if(x<iter->value){
                iter=iter->sx;
            }
            else{
                iter=iter->dx;
            }
        }
        if(iter==nullptr) return false;
        cancella(iter);
        return true;
    }

    Nodo<T>*getNode(T value){
        return ricerca(root,value);
    }

    int distanceBetweenTwoNodes(Nodo<T>*node,T n1,T n2){
        if(node==nullptr){
            return -1;
        }
        Nodo<T>*lca =findLowestAncestor(node,n1,n2);
        if(lca==nullptr){
            return -1;
        }

        int d1= distanceFromParentToNode(lca,n1,0);
        int d2= distanceFromParentToNode(lca,n2,0);

        return d1+d2;
    }

    int distanceFromParentToNode(Nodo<T>*node,T val,int distance){
        if(node==nullptr) return -1;

        if(node->value==val) return distance;

        int d=distanceFromParentToNode(node->sx,val,distance+1);
        if(d!=-1) return d;
        d=distanceFromParentToNode(node->dx,val,distance+1);
        return d;
    }

    bool ifN1Present=false;
    bool ifN2Present=false;

    Nodo<T>* findLowestAncestor(Nodo<T>* node,T n1,T n2){
        Nodo<T>* lca=findLowestAncestorUtil(node,n1,n2);
        if(ifN1Present || ifN2Present)return lca;
        else  return nullptr;
    }

    Nodo<T>* findLowestAncestorUtil(Nodo<T>* node,T n1,T n2){
        if(node ==nullptr){
            return nullptr;
        }

        if(node->value==n1){
            ifN1Present=true;
            return node;
        }

        if(node->value==n2){
            ifN2Present=true;
            return node;
        }

        Nodo<T>* leftLCA= findLowestAncestorUtil(node->sx,n1,n2);
        Nodo<T>* rightLCA=findLowestAncestorUtil(node->dx,n1,n2);

        if(leftLCA!=nullptr && rightLCA != nullptr){
            return node;
        }

        return leftLCA !=nullptr ? leftLCA : rightLCA;

    }

};


int main(){


    BST<int> b;

    b.insert(13);
    b.insert(9);
    
    b.insert(15);
    b.insert(4);
    b.insert(2);
    b.insert(7);
    b.insert(19);

    //b.preorder(b.getradice());
    cout << endl;
   // b.inorder(b.getradice());
    cout << endl;
    b.postorder(b.getradice());
    cout << endl;

    //b.cancella(23);

    cout << endl;

    //b.preorder(b.getradice());

    //cout<<b.deepness(b.getradice());
    //cout<<b.distanceBetweenTwoNodes(b.getradice(),23,60);
    //cout << endl;



    
}
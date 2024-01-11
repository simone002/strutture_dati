#include <iostream>
#include <fstream>
using namespace std;

template<typename T>
class Heap{

    T* vett;
    int heapsize;
    int vettsize;
    int callheapify;

    int left(int i){return i << 1;}
    int right(int i){return (i << 1) | 1;}
    int parent(int i){return i>>1;}

    public:

    int chiamate(){return callheapify;}

    Heap(int n):vettsize(n){
        vett=new T[n];
        heapsize=0;
        callheapify=0;
    }


    void heapify(int i){
        if(heapsize>1){
            callheapify++;
        }
        int l=left(i);
        int r=right(i);
        int max=i;
        if(l<=heapsize && vett[max]<vett[l]){
            max=l;
        }
        if(r<=heapsize && vett[max]<vett[r]){
            max=r;
        }
        if(max!=i){
            swap(vett[i],vett[max]);
            heapify(max);
        }
    }

    void extract(){
        swap(vett[1],vett[heapsize]);
        heapsize--;
        heapify(1);
    }

    void enque(T x){
        heapsize++;
        vett[heapsize]=x;

        int i=heapsize;
        while(i>1 && vett[parent(i)]<vett[i]){
            swap(vett[i],vett[parent(i)])
            i=parent(i);
        }
    }

    void print(ofstream &os){
        for(int i=0;i<=heapsize;i++){
            os << vett[i] << " ";
        }
        os << endl;
    }


};


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");
    
    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;

        if(type == "int"){
            Heap<int>* t = new Heap<int>(n*2);

            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;
               
                if(tmp == "extract")
                    t->extract();
                
                else{
                    string _val = tmp.substr(2, tmp.length());
                    int val = stoi(_val);
                    t->enque(val);
                }
            }
            out << t->chiamate() << " ";
            t->print(out);
            delete t;
        }

        if(type == "bool"){
            Heap<bool>* t = new Heap<bool>(n*2);

            for(int j = 0; j < n; j++){
                string tmp; in >> tmp;

                if(tmp == "extract")
                    t->extract();
                else{
                    string _val = tmp.substr(2, tmp.length());
                    bool val = stoi(_val);
                    t->enque(val);
                }
            }
            out << t->chiamate() << " ";
            t->print(out);
            delete t;
        }
    }
}


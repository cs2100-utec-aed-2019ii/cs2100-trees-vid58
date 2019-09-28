#include <iostream>
#include <math.h>
#include "./Arbolito.cpp"

using namespace std;

class Tree : public Node{
public:
    Node *arbol = NULL;

    Node *crearNodo(int dato,Node *padre){
        Node *nuevo_nodo = new Node();
        nuevo_nodo->dato = dato;
        nuevo_nodo->der = NULL;
        nuevo_nodo->izq = NULL;

        nuevo_nodo->padre = padre;

        return nuevo_nodo;
    }

    void insertar(Node *&arbol,int n,Node *padre){
        if(arbol==NULL){
            Node *nuevo_nodo = crearNodo(n,padre);
            arbol = nuevo_nodo;
        }
        else{
            int valorRaiz = arbol->dato;

            if(n < valorRaiz){
                insertar(arbol->izq,n,arbol);
            }
            else{
                insertar(arbol->der,n,arbol);
            }
        }
    }

    void mostrar(Node *arbol,int contador){
        if(arbol==NULL){
            return;
        }
        else{
            mostrar(arbol->der,contador+1);
            for(int i=0;i<contador;i++){
                cout<<"---";
            }
            cout<<arbol->dato<<endl;
            mostrar(arbol->izq,contador+1);
        }
    }

    bool busqueda(Node *arbol,int n){
        if(arbol == NULL){
            return false;
        }
        else if(arbol->dato == n){
            return true;
        }
        else if(n < arbol->dato){
            return busqueda(arbol->izq,n);
        }
        else{
            return busqueda(arbol->der,n);
        }
    }

    void preOrden(Node *arbol){
        if(arbol == NULL){
            return;
        }
        else{
            cout<<arbol->dato<<" - ";

            preOrden(arbol->izq);
            preOrden(arbol->der);
        }
    }

    void inOrden(Node *arbol){
        if(arbol == NULL){
            return;
        }
        else{
            inOrden(arbol->izq);
            cout<<arbol->dato<<" - ";
            inOrden(arbol->der);

        }
    }

    void postOrden(Node *arbol){
        if(arbol == NULL){
            return;
        }
        else{
            postOrden(arbol->izq);
            postOrden(arbol->der);
            cout<<arbol->dato<<" - ";

        }
    }

    void eliminar(Node *arbol,int n){
        if(arbol == NULL){
            return;
        }
        else if(n < arbol->dato){
            eliminar(arbol->izq,n);
        }
        else if(n > arbol->dato){
            eliminar(arbol->der,n);
        }
        else{
            eliminarNodo(arbol);
        }
    }
    Node *minimo(Node *arbol){
        if(arbol == NULL){
            return NULL;
        }
        if(arbol->izq){
            return minimo(arbol->izq);
        }
        else{
            return arbol;
        }
    }
    void reemplazar(Node *arbol,Node *nuevoNodo){
        if(arbol->padre){
            if(arbol->dato == arbol->padre->izq->dato){
                arbol->padre->izq =nuevoNodo;
            }
            else if(arbol->dato == arbol->padre->der->dato){
                arbol->padre->der = nuevoNodo;
            }
        }
        if(nuevoNodo){
            nuevoNodo->padre = arbol->padre;
        }
    }
    void destruir(Node *nodo){
        nodo->izq = NULL;
        nodo->der = NULL;
        delete nodo;
    }
    void eliminarNodo(Node *nodoEliminar){
        if(nodoEliminar->izq && nodoEliminar->der){//si el nodo tiene dos hijos
            Node *menor = minimo(nodoEliminar->der);
            nodoEliminar->dato = menor->dato;
            eliminarNodo(menor);
        }
        else if(nodoEliminar->izq){//si el nodo tiene un hijo izquierdo
            reemplazar(nodoEliminar,nodoEliminar->izq);
            destruir(nodoEliminar);
        }
        else if(nodoEliminar->der){//si el nodo tiene un hijo derecho
            reemplazar(nodoEliminar,nodoEliminar->der);
            destruir(nodoEliminar);
        }
        else{//no tiene hijos
            reemplazar(nodoEliminar,NULL);
            destruir(nodoEliminar);
        }
    }

    int max(int altura_izq,int altura_der){
        if( altura_izq > altura_der){
            return altura_izq;
        }else{
            return altura_der;
        }
    }

    int altura(Node *arbol){
        if(arbol == NULL){
            return 0;
        }
        else{
            return(1+max(altura(arbol->izq),altura(arbol->der)));
        }
    }

    Node *raiz(Node *arbol){
        if(arbol==NULL){
            return NULL;
        }
        else{
            return arbol;
        }

    }

    void eliminarNodos(Node *nododelete){

        if(nododelete->izq && nododelete->der){//si el nodo tiene dos hijos
            Node *menor = minimo(nododelete->der);
            nododelete->dato = menor->dato;
            eliminarNodos(menor);
            eliminarNodos(raiz(nododelete));

        }

        else if(nododelete->izq){//si el nodo tiene un hijo izquierdo
            reemplazar(nododelete,nododelete->izq);
            destruir(nododelete);
            eliminarNodos(raiz(nododelete));
        }

        else if(nododelete->der){//si el nodo tiene un hijo derecho
            reemplazar(nododelete,nododelete->der);
            destruir(nododelete);
            eliminarNodos(raiz(nododelete));
        }

        else{//no tiene hijos
            reemplazar(raiz(nododelete),NULL);
            destruir(raiz(nododelete));
        }

    }

    void BorrarTodo(Node *arbol){

        if (arbol == NULL) {
            return;
        }
        else {
            eliminarNodo(arbol);
        }

    }

    int tamano(Node *arbol) { //cantidad de nodos que posee el arbol
        int n = altura(arbol);
        int t=0;
        for(int i=0;i<n;i++){
            t=t+pow(2,i);
        }
        return t;

    }

    void arreglin(Node *arbol,int a[]){//intento de meterlos dentro de un arreglo
        if(arbol == NULL){
            return;
        }
        else{
            int i=0;
                 a[i]=arbol->dato ;

            i=i+1;

                arreglin(arbol->izq,a);
                arreglin(arbol->der,a);

        }
    }


    int antepasado(Node *arbol){
        return arbol->padre->dato;
    }


};
int iguales(Node *a, Node *b){
    if(a == NULL && b ==NULL){
        return 0;
    } else {
        if(a == NULL || b == NULL){
            return 1;
        } else {
            if(a->dato == b->dato){
                iguales(a->izq, b->izq);
                iguales(a->der, b->der);
            } else if(a->dato !=b->dato){
                return 1;
            }
        }
    }
}

int main(){
    int contador =0;
    int tamano1,tamano2;

    Tree *arbol1;
    Node *nodin;
    cout<<"\n";
    arbol1->insertar(nodin,8,NULL);
    arbol1->insertar(nodin,10,NULL);
    arbol1->insertar(nodin,14,NULL);
    arbol1->insertar(nodin,13,NULL);
    arbol1->insertar(nodin,3,NULL);
    arbol1->insertar(nodin,1,NULL);
    arbol1->insertar(nodin,6,NULL);
    arbol1->insertar(nodin,4,NULL);
    arbol1->insertar(nodin,7,NULL);
    arbol1->mostrar(nodin,contador);
    cout<<"Altura: "<<arbol1->altura(nodin)<<endl;

    arbol1->preOrden(nodin);cout<<endl;
    arbol1->inOrden(nodin);cout<<endl;
    arbol1->postOrden(nodin);cout<<endl;

    cout<<"antepasado: "<<arbol1->antepasado(nodin->izq->izq);
    cout<<"\n///////////////////////\n\n";

    Tree *arbol2;
    Node *nodel;
    /*arbol2->insertar(nodel,4,NULL);
    arbol2->insertar(nodel,2,NULL);
    arbol2->insertar(nodel,5,NULL);
    arbol2->insertar(nodel,1,NULL);
    arbol2->insertar(nodel,3,NULL);
    arbol2->insertar(nodel,7,NULL);
    arbol2->insertar(nodel,6,NULL);*/
    arbol2->insertar(nodel,8,NULL);
    arbol2->insertar(nodel,10,NULL);
    arbol2->insertar(nodel,14,NULL);
    arbol2->insertar(nodel,13,NULL);
    arbol2->insertar(nodel,3,NULL);
    arbol2->insertar(nodel,1,NULL);
    arbol2->insertar(nodel,6,NULL);
    arbol2->insertar(nodel,4,NULL);
    arbol2->insertar(nodel,7,NULL);
    arbol2->mostrar(nodel,contador);
    cout<<"Altura: "<<arbol2->altura(nodel)<<endl;

    arbol2->preOrden(nodel);cout<<endl;
    arbol2->inOrden(nodel);cout<<endl;
    arbol2->postOrden(nodel);cout<<endl;

    cout<<"antepasado: "<<arbol2->antepasado(nodel->der->der);

    cout<<"\n///////////////////////\n\n";

    //Retorna 0 si son iguales, si son diferentes retornara 1
    cout<<iguales(arbol1,arbol2)<<endl;

    //int i=0;
    int a[tamano1];
    int b[tamano2];



    tamano1 = arbol1->tamano(nodin);
    cout<<"Capacidad maxima del arbol 1: "<<tamano1<<endl;
    tamano2 = arbol2->tamano(nodin);
    cout<<"Capacidad maxima del arbol 2: "<<tamano2<<endl;
/*
    arbol1->arreglin(nodin,a);

    for(int i=0;i<tamano1;i++){
        cout<<a[i]<<endl;
    }



    tamano2 = arbol2->tamano(nodin);
    arbol2->arreglin(nodel,b);

    cout<<endl<<endl<<"OwO"<<endl;

    for(int i=0;i<tamano2;i++){
        cout<<b[i]<<endl;
    }
*/
   /* for(int i=0;i<tamano1;i++){
        for(int j=0;j<tamano2;j++){
            if(a[i] != b[j]){
                return false;
            }
            else{

            }
        }
    }*/

}

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node {
    private:
        T val;
        Node* next;
        Node* prev;
    public:
        Node(T newVal){
            val = newVal;
        }
        void setNext(Node* newNext){
            next = newNext;
        }
        Node* getNext() {
            return next;
        }
        void setPrev(Node* newPrev){
            prev = newPrev;
        }
        Node* getPrev() {
            return prev;
        }
        T getVal(){
            return val;
        }


};

template <typename T>
class LinkedList {
    private:
        Node<T> *ptr;
        int size;
        Node<T> *head;
        Node<T> *tail;
        bool movePtr(int index){
            //moves pointer to specific index using shortest path
            if (index >= size || index<0){
                throw out_of_range("Index out of range");
                return false;
            }
            if (index < size/2){
                ptr=head;
                for (int i=0;i<index;i++)
                    ptr = (*ptr).getNext();
            }
            else {
                ptr=tail;
                for (int i=1;i<(size-index);i++)
                    ptr = (*ptr).getPrev();
            }

            return true;
        }
    public: 
        LinkedList(){
            size = 0;
            T placeholder;
            Node<T> *head = new Node<T>(placeholder);
            Node<T> *tail = new Node<T>(placeholder);
            ptr = head;
        }
        bool isEmpty(){
            if (size==0) return true;
            else return false;
        }
        
        bool add(T val) {
            Node<T> *newNode = new Node<T>(val);
            if (isEmpty()){
                head = newNode;
                tail = newNode;
            }
            else{
                (*tail).setNext(newNode);
                (*newNode).setPrev(tail);
                tail = newNode;
            }
            size++;
            return true;
        }
        bool remove(int index){
            movePtr(index);
            if (index==0){
                head = (*ptr).getNext();
                (*head).setPrev(nullptr);
            }
            else if (index==size-1){
                tail = (*ptr).getPrev();
                (*tail).setNext(nullptr);
            }
            else {
                //previous's next now points to current's next
                (*(*ptr).getPrev()).setNext((*ptr).getNext());

                //next's previous now points to current's previous
                (*(*ptr).getNext()).setPrev((*ptr).getPrev());
            }
            //delete current node from memory
            delete ptr;
            size--;
            return true;
        }
        T get(int index){
            movePtr(index);
            return (*ptr).getVal();
        }

        bool contains(T element){
            ptr=head;
            for (int i=0;i<size-1;i++){
                if ((*ptr).getVal() == element)
                    return true;
                ptr = (*ptr).getNext();
            }
            if ((*ptr).getVal() == element)
                    return true;

            return false;
        }

        string display(){
            string out = "[";
            ptr = head;
            if (size <20){
                for (int i=0;i<size-1;i++){
                    out.append(to_string((*ptr).getVal()));
                    out.append(", ");
                    ptr = (*ptr).getNext();
                }
                out.append(to_string((*ptr).getVal()));
            }
            else {
                for (int i=0;i<9;i++){
                    out.append(to_string((*ptr).getVal()));
                    out.append(", ");
                    ptr = (*ptr).getNext();
                }
                out.append(to_string((*ptr).getVal()));
                out.append("  ...  ");
                for (int i=size-9;i<size-1;i++){
                    out.append(to_string((*ptr).getVal()));
                    out.append(", ");
                    ptr = (*ptr).getNext();
                }
                out.append(to_string((*ptr).getVal()));
            }

            return out + "]";
        }

        T* toArray() {
            //returns array on heap
            //remember to delete[] it when finished
            T *out = new T[size];
            ptr = head;
            for (int i=0; i<size-1;i++){
                out[i] = (*ptr).getVal();
                ptr = (*ptr).getNext();
            }
            out[size-1] = (*ptr).getVal();

            return out;
        }

        int getSize(){
            return size;
        }
};

int main() {

    LinkedList<int> myLinkedList;
    myLinkedList.add(5);
    myLinkedList.add(4);
    myLinkedList.add(3);
    myLinkedList.add(2);
    myLinkedList.add(1);
    myLinkedList.add(2);
    myLinkedList.add(1);
    cout<<myLinkedList.get(5)<<endl;;
    myLinkedList.remove(4);
    cout<<myLinkedList.get(4)<<endl;;
    cout<<myLinkedList.contains(100)<<endl;
    cout<<myLinkedList.display()<<endl;
    int* arr = myLinkedList.toArray();
    for (int* i = arr;i<arr+myLinkedList.getSize();i++)
        cout<<*i;
    cout<<endl;
    delete[] arr;
    return 0;
}
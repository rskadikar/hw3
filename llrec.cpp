#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    if (head == nullptr) {
        // once it reaches end of list, sets initial larger and smaller values to nullptr in case of garbage
        larger = nullptr; 
        smaller = nullptr;
        return;
    }
    Node* temp = head -> next;
    llpivot(temp, smaller, larger, pivot); // implementing head recursion
    if (head -> val > pivot) {
        head -> next = larger;
        larger = head;
        head = nullptr;
    } 
    else {
        head -> next = smaller;
        smaller = head;
        head = nullptr;
    }
}

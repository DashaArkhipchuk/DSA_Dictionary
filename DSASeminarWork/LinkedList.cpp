#include "LinkedList.h"
using namespace std;

// Insert a node at the beginning
Node* LinkedList::insertBegin(Node* head, int data) {

    // Create a new node
    Node* new_node = new Node(data);

    // Make next of it as head
    new_node->next = head;

    // Set previous of head as new node
    if (head != NULL) {
        head->prev = new_node;
    }

    // Return new node as new head
    return new_node;
}

Node* LinkedList::insertEnd(Node* head, int new_data) {

    // Create a new node
    Node* new_node = new Node(new_data);

    // If the linked list is empty, set the new 
    //node as the head of linked list
    if (head == NULL) {
        head = new_node;
    }
    else {
        Node* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        // Set the next of last node to new node
        curr->next = new_node;

        // Set prev of new node to last node
        new_node->prev = curr;
    }

    // Return the head of the doubly linked list
    return head;
}
// Function to insert a new node at a given position
Node* LinkedList::insertAtPosition(Node* head, int pos, int new_data) {

    // Create a new node
    Node* new_node = new Node(new_data);

    // Insertion at the beginning
    if (pos == 1) {
        new_node->next = head;

        // If the linked list is not empty, set the prev
        //of head to new node
        if (head != NULL)
            head->prev = new_node;

        // Set the new node as the head of linked list
        head = new_node;
        return head;
    }

    Node* curr = head;
    // Traverse the list to find the node before the
    // insertion point
    for (int i = 1; i < pos - 1 && curr != NULL; ++i) {
        curr = curr->next;
    }

    // If the position is out of bounds
    if (curr == NULL) {
        //THROW SOME EXCEPTION
        //std::cout << "Position is out of bounds." << endl;
        delete new_node;
        return head;
    }

    // Set the prev of new node to curr
    new_node->prev = curr;

    // Set the new of new node to next of curr
    new_node->next = curr->next;

    // Update the next of current node to new node
    curr->next = new_node;

    // If the new node is not the last node, update prev
     //of next node to new node
    if (new_node->next != NULL)
        new_node->next->prev = new_node;

    // Return the head of the doubly linked list
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        //COUT
        //cout << curr->data << " ";
        curr = curr->next;
    }
    //cout << "\n";
}
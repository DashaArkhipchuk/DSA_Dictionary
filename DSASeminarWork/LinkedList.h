#pragma once
#include <cstddef>
using namespace std;

struct Node {

    // To store the Value or data.
    int data;

    // Pointer to point the Previous Element
    Node* prev;

    // Pointer to point the Next Element
    Node* next;

    // Constructor
    Node(int d) {
        data = d;
        prev = next = nullptr;
    }
};

class LinkedList
{
    // Insert a node at the beginning
    Node* insertBegin(Node* head, int data);

    Node* insertEnd(Node* head, int new_data);
    // Function to insert a new node at a given position
    Node* insertAtPosition(Node* head, int pos, int new_data);

    void printList(Node* head);
};


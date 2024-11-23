
#pragma once


template <typename T> struct Node {

    // To store the Value or data.
    T data;

    // Pointer to point the Previous Element
    Node<T>* prev;

    // Pointer to point the Next Element
    Node<T>* next;

    // Constructor
    Node(T d) {
        data = d;
        prev = next = nullptr;
    }
};

template <typename T> class LinkedList
{
    Node<T>* head;

public :
    LinkedList();
    // Insert a node at the beginning
    Node<T>* insertBegin(T data);

    Node<T>* insertEnd(T new_data);

    // Function to insert a new node at a given position
    Node<T>* insertAtPosition(int pos, T new_data);

    void printList();
    bool isEmpty();
    Node<T>* getHead() const;
    bool remove(const T& value);
    void sort(bool ascending = true);


private:
    Node<T>* split(Node<T>* head);
    Node<T>* merge(Node<T>* first, Node<T>* second, bool ascending);
    Node<T>* MergeSort(Node<T>* head, bool ascending = true);



};

template <typename T> Node<T>* LinkedList<T>::getHead() const{
    return head;
}

template <typename T> LinkedList<T>::LinkedList() {
    this->head = nullptr;
}

// Insert a node at the beginning
template <typename T> Node<T>* LinkedList<T>::insertBegin(T data) {

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

template <typename T> Node<T>* LinkedList<T>::insertEnd(T new_data) {

    // Create a new node
    Node<T>* new_node = new Node<T>(new_data);

    // If the linked list is empty, set the new 
    //node as the head of linked list
    if (head == NULL) {
        head = new_node;
    }
    else {
        Node<T>* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        // Set the next of last node to new node
        curr->next = new_node;

        // Set prev of new node to last node
        new_node->prev = curr;
    }
    return head;
}
// Function to insert a new node at a given position
template <typename T> Node<T>* LinkedList<T>::insertAtPosition(int pos, T new_data) {

    // Create a new node
    Node<T>* new_node = new Node<T>(new_data);

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

    Node<T>* curr = head;
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

template <typename T> void LinkedList<T>::printList() {
    Node<T>* curr = head;
    while (curr != NULL) {
        //COUT
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << "\n";
}

template <typename T> bool LinkedList<T>::isEmpty()
{
    return head == NULL;
}

template <typename T> bool LinkedList<T>::remove(const T& value) {
    // Case 1: If the list is empty
    if (head == nullptr) {
        return false;  // No node to remove
    }

    Node<T>* curr = head;

    // Case 2: If the node to be removed is the head node
    if (curr->data == value) {
        head = curr->next;  // Move head to the next node

        // If there is a node after the head, update its prev pointer
        if (head != nullptr) {
            head->prev = nullptr;
        }

        delete curr;  // Delete the old head
        return true;   // Successfully removed
    }

    // Case 3: Traverse the list to find the node to remove
    while (curr != nullptr) {
        if (curr->data == value) {
            // Case 3a: Remove the node in the middle or end
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            }

            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }

            delete curr;  // Delete the node
            return true;   // Successfully removed
        }
        curr = curr->next;
    }

    // Case 4: If the value was not found in the list
    return false;
}

// Function to split the doubly linked list into two halves
template <typename T> Node<T>* LinkedList<T>::split(Node<T>* head) {
    Node<T>* fast = head;
    Node<T>* slow = head;

    // Move fast pointer two steps and slow pointer
    // one step until fast reaches the end
    while (fast != NULL && fast->next != NULL
        && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Split the list into two halves
    Node<T>* temp = slow->next;
    slow->next = NULL;
    if (temp != NULL) {
        temp->prev = NULL;
    }
    return temp;
}

template <typename T>
Node<T>* LinkedList<T>::merge(Node<T>* first, Node<T>* second, bool ascending) {
    // If either list is empty, return the other list
    if (first == NULL) return second;
    if (second == NULL) return first;

    // Choose the order based on the 'ascending' flag
    if ((ascending && first->data < second->data) || (!ascending && first->data > second->data)) {
        // Recursively merge the rest of the lists
        first->next = merge(first->next, second, ascending);
        if (first->next != NULL) {
            first->next->prev = first;
        }
        first->prev = NULL;
        return first;
    }
    else {
        // Recursively merge the rest of the lists
        second->next = merge(first, second->next, ascending);
        if (second->next != NULL) {
            second->next->prev = second;
        }
        second->prev = NULL;
        return second;
    }
}

// Function to perform merge sort on a doubly linked list
template <typename T> Node<T>* LinkedList<T>::MergeSort(Node<T>* head, bool ascending) {
    // Base case: if the list is empty or has only one node, it's already sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves
    Node<T>* second = split(head);

    // Recursively sort each half
    head = MergeSort(head, ascending);
    second = MergeSort(second, ascending);

    // Merge the two sorted halves
    return merge(head, second, ascending);
}

template <typename T> void LinkedList<T>::sort(bool ascending) {
    head = MergeSort(head, ascending);
}
#include <iostream>

#include <iostream>
#include <vector>
using namespace std;

// Node structure for AVL Tree
struct Node {
    string key;
    vector<string> values;
    int height;
    Node* left;
    Node* right;

    Node(string k, string value)
        : key(k), values{ value }, height(1), left(nullptr), right(nullptr) {}
};

// AVL Tree-based Multimap
class MultimapAVL {
private:
    Node* root;

    // Get height of a node
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Get balance factor of a node
    int getBalance(Node* node) {
        if (!node)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Right rotate subtree rooted with y
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        // Return new root
        return x;
    }

    // Left rotate subtree rooted with x
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        // Return new root
        return y;
    }

    // Insert a key-value pair into the subtree rooted with node
    Node* insert(Node* node, string key, string value) {
        // 1. Perform the normal BST insertion
        if (!node)
            return new Node(key, value);

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else {
            // Key already exists, append the value
            node->values.push_back(value);
            return node;
        }

        // 2. Update height of this ancestor node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 3. Get the balance factor to check whether this node became unbalanced
        int balance = getBalance(node);

        // 4. If node is unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // 5. Return the (unchanged) node pointer
        return node;
    }

    // Search for a key in the subtree rooted with node
    Node* search(Node* node, string key) const {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    // In-order traversal to print the tree
    void inorderHelper(Node* node) const {
        if (node) {
            inorderHelper(node->left);
            cout << node->key << ": ";
            for (string val : node->values)
                cout << val << " ";
            cout << endl;
            inorderHelper(node->right);
        }
    }

    // Utility to delete all nodes (Destructor helper)
    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    // Constructor
    MultimapAVL() : root(nullptr) {}

    // Destructor
    ~MultimapAVL() {
        deleteTree(root);
    }

    // Insert a key-value pair
    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    // Find all values for a given key
    vector<string> find(string key) const {
        Node* node = search(root, key);
        if (node)
            return node->values;
        return {}; // Key not found
    }

    // In-order traversal of the tree
    void inorder() const {
        inorderHelper(root);
    }
};

// Example usage
int main() {
    MultimapAVL mmap;

    // Inserting key-value pairs
    mmap.insert("String 1", "Value 1-1");
    mmap.insert("String 2", "Value 2-1");
    mmap.insert("String 3", "Value 3-1");
    mmap.insert("String 1", "Value 1-2");
    mmap.insert("String 2", "Value 2-2");
    mmap.insert("String 4", "Value 4-1");
    mmap.insert("String 5", "Value 5-1");
    mmap.insert("String 4", "Value 4-2");

    cout << "Multimap contents (in-order traversal):\n";
    mmap.inorder();

    // Searching for values
    string searchKey = "String 1";
    vector<string> values = mmap.find(searchKey);
    if (!values.empty()) {
        cout << "\nValues for key " << searchKey << ": ";
        for (string val : values)
            cout << val << " ";
        cout << endl;
    }
    else {
        cout << "\nKey " << searchKey << " not found.\n";
    }

    searchKey = "String 6";
    values = mmap.find(searchKey);
    if (!values.empty()) {
        cout << "\nValues for key " << searchKey << ": ";
        for (string val : values)
            cout << val << " ";
        cout << endl;
    }
    else {
        cout << "\nKey " << searchKey << " not found.\n";
    }

    return 0;
}
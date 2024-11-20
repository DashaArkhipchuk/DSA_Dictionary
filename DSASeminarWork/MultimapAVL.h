#pragma once
#include <iostream>
#include "LinkedList.h"
using namespace std;

class TreeNode {
public:
    string key;
    LinkedList<string> values;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string k, string value)
        : key(k), height(1), left(nullptr), right(nullptr) {
        values.insertEnd(value);
    }
};

// AVL Tree-based Multimap
class MultimapAVL {
private:
    TreeNode* root;

    // Get height of a node
    int getHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    // Get balance factor of a node
    int getBalance(TreeNode* node) {
        if (!node)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Right rotate subtree rooted with y
    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

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
    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

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
    TreeNode* insert(TreeNode* node, string key, string value) {
        // 1. Perform the normal BST insertion
        if (!node)
            return new TreeNode(key, value);

        if (key.compare(node->key) < 0) //key < node->key
            node->left = insert(node->left, key, value);
        else if (key.compare(node->key) > 0) //key > node->key
            node->right = insert(node->right, key, value);
        else {
            // Key already exists, append the value
            node->values.insertEnd(value);
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
    TreeNode* search(TreeNode* node, string key) const {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    // In-order traversal to print the tree
    void inorderHelper(TreeNode* node) const {
        if (node) {
            inorderHelper(node->left);
            cout << node->key << ": ";
            node->values.printList();
            inorderHelper(node->right);
        }
    }

    // Utility to delete all nodes (Destructor helper)
    void deleteTree(TreeNode* node) {
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
    LinkedList<string> find(string key) const {
        TreeNode* node = search(root, key);
        if (node)
            return node->values;
        return {}; // Key not found
    }

    // In-order traversal of the tree
    void inorder() const {
        inorderHelper(root);
    }
};

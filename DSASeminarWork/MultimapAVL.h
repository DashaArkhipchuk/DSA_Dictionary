#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
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

    void exportHelper(TreeNode* node, ofstream& outFile) const {
        if (node) {
            exportHelper(node->left, outFile); // Traverse the left subtree
            outFile << node->key << ": ";

            // Traverse the linked list to write all translations
            Node<string>* current = node->values.getHead();
            while (current) {
                outFile << current->data;
                if (current->next) // Add a comma only if there's another translation
                    outFile << ", ";
                current = current->next;
            }

            outFile << endl;
            exportHelper(node->right, outFile); // Traverse the right subtree
        }
    }

    void processLine(const string& line) {
        size_t colonPos = line.find(":");
        if (colonPos == string::npos) {
            throw runtime_error("Invalid file format. Missing colon (:).");
        }

        string key = line.substr(0, colonPos); // Extract the word (key)
        string translations = line.substr(colonPos + 1); // Extract the translations part

        stringstream ss(translations);
        string translation;

        while (getline(ss, translation, ',')) {
            // Trim leading and trailing spaces (if necessary)
            size_t start = translation.find_first_not_of(" ");
            size_t end = translation.find_last_not_of(" ");
            if (start != string::npos && end != string::npos) {
                translation = translation.substr(start, end - start + 1);
            }

            insert(key, translation); // Insert the word and translation
        }
    }

    // Remove a key from the tree
    TreeNode* remove(TreeNode* node, const string& key, bool& found) {
        if (!node) {
            found = false;
            return node; // Node not found
        }

        // 1. Perform the normal BST delete
        if (key < node->key) {
            node->left = remove(node->left, key, found);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key, found);
        }
        else {
            // Node found, perform deletion
            found = true;

            // Node with only one child or no child
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: get the inorder successor
            TreeNode* temp = getMinNode(node->right);

            // Copy the inorder successor's content to this node
            node->key = temp->key;
            node->values = temp->values;

            // Delete the inorder successor
            node->right = remove(node->right, temp->key, found);
        }

        // 2. Update the height of the current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 3. Check the balance factor and balance the node
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }


    // Helper function to get the minimum node in the tree (used for finding in-order successor)
    TreeNode* getMinNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    bool removeValueFromNode(TreeNode* node, const string& translation) {
        return node->values.remove(translation);  // Try to remove the translation
    }


    void SortTranslations(TreeNode* node, bool ascending) {
        if (!node) return;

        // In-order traversal: left subtree, node, right subtree
        SortTranslations(node->left, ascending);

        node->values.sort(ascending);

        SortTranslations(node->right, ascending);
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

    void exportToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }
        exportHelper(root, outFile);
        outFile.close();
    }

    void importFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error opening file for reading: " << filename << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            processLine(line);
        }

        inFile.close();
    }

    void remove(string key) {
        bool found = false;
        root = remove(root, key, found);
        if (found) {
            cout << "Key '" << key << "' removed successfully!" << endl;
        }
        else {
            cout << "Key '" << key << "' not found!" << endl;
        }
    }

    void removeValue(string key, string translation) {
        TreeNode* node = search(root, key);  // Find the node by key
        if (!node) {
            cout << "Key '" << key << "' not found!" << endl;
            return;
        }

        bool removed = removeValueFromNode(node, translation);  // Try to remove the translation
        if (removed) {
            cout << "Translation '" << translation << "' removed from key '" << key << "'." << endl;
        }
        else {
            cout << "Translation '" << translation << "' not found for key '" << key << "'!" << endl;
        }
    }

    void editValue(string key, string oldTranslation, string newTranslation) {
        // Find the node associated with the key
        TreeNode* node = search(root, key);

        // If the node doesn't exist, the word is not found
        if (!node) {
            cout << "Word '" << key << "' not found!" << endl;
            return;
        }

        // Try to remove the old translation and get its position
        Node<string>* oldNode = node->values.getHead();
        int position = 1;  // Position in the linked list

        // Traverse the linked list to find the old translation
        while (oldNode != nullptr) {
            if (oldNode->data == oldTranslation) {
                // Old translation found, remove it
                node->values.remove(oldTranslation);

                // Insert the new translation at the same position
                node->values.insertAtPosition(position, newTranslation);

                cout << "Translation '" << oldTranslation << "' replaced with '" << newTranslation << "' at position " << position << " for word '" << key << "'." << endl;
                return;
            }
            oldNode = oldNode->next;
            position++;
        }

        // If the old translation was not found
        cout << "Translation '" << oldTranslation << "' not found for word '" << key << "'!" << endl;
    }

    void EditKey(string oldKey, string newKey) {
        // Find the node associated with the old key
        TreeNode* node = search(root, oldKey);

        // If the node doesn't exist, the key is not found
        if (!node) {
            cout << "Word '" << oldKey << "' not found!" << endl;
            return;
        }

        // Store the translations of the old key
        LinkedList<string> translations = node->values;

        // Remove the old key
        bool found = false;
        root = remove(root, oldKey, found);

        if (!found) {
            cout << "Failed to remove the old key '" << oldKey << "'!" << endl;
            return;
        }

        // Insert the new key with the existing translations
        Node<string>* current = translations.getHead();
        while (current != nullptr) {
            insert(newKey, current->data);
            current = current->next;
        }

        cout << "Key '" << oldKey << "' successfully changed to '" << newKey << "'." << endl;
    }

    void sortTranslations(bool ascending) {
        SortTranslations(root, ascending);
    }

};

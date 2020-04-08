#include <iostream>
#include <queue>
#include <string>

using std::string;
using std::cout;
using std::endl;

class BST;
class Node {
private:
    Node* left_child;
    Node* right_child;
    Node* parent;
    int key;
    string data;
public:
    Node(): left_child(NULL), right_child(NULL), parent(NULL), key(0), data(""){};
    Node(int x, string y): left_child(NULL), right_child(NULL), parent(NULL), key(x), data(y){};
    int GetKey() {
        return key;
    }
    string GetData() {
        return data;
    }

    friend class BST;
};

class BST {
private:
    Node* root;
    Node* Leftmost(Node* current);
    Node* Succesor(Node* current);
public:
    BST(): root(NULL){};
    Node* Search(int key);
    void Insert(int key, string data);
    void InorderPrint();
    void Inorder(Node* current);
    void Levelorder();
};
// InOrderTraversal
void BST::Inorder(Node* current) {
    if (current) {                           // if current != NULL
        Inorder(current->left_child);        // L
        cout << current->data << "(" << current->key << ")" << " ";   // V
        Inorder(current->right_child);       // R
    }
}
void BST::InorderPrint() {
    Inorder(this->root);
}
// Search
Node* BST::Search(int key) {
    Node* current = this->root;
    while(current != NULL && key != current->key) {
        if(key > current->key)
            current = current->right_child;
        else
            current = current->left_child;
    }
    return current;
}

// Insert
void BST::Insert(int key, string data) {
    Node* x = this->root;
    Node* y = NULL;
    Node* insert_node = new Node(key, data);
    // true: right, false: left
    bool direction;

    while(x != NULL) {
        y = x;
        if(key > x->key) {
            x = x->right_child;
            direction = true;
        }
        else {
            x = x->left_child;
            direction = false;
        }
    }

    insert_node->parent = y;

    if(y == NULL) {
        this->root = insert_node;
    }
    else if(direction == true) {
        y->right_child = insert_node;
    }
    else if(direction == false) {
        y->left_child = insert_node;
    }
    
}

int main() {
    BST B;
    B.Insert(100, "A");
    B.Insert(200, "B");
    B.Insert(50, "C");
    B.Insert(1000, "D");

    B.InorderPrint(); cout << endl;

    Node* node;
    int search_key;
    search_key = 1000;
    node = B.Search(search_key);
    if(node != NULL)
        cout << "Found " << search_key << " data: " << node->GetData() << endl;
    else
        cout << "Can not find " << search_key << endl;
    
    search_key = 500;
    node = B.Search(search_key);
    if(node != NULL)
        cout << "Found " << search_key << " " << node->GetData() << endl;
    else
        cout << "Can not find " << search_key << endl;
    
    return 0;
}
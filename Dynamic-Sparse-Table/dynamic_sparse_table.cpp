#include <iostream>
#include <stdio.h>
using namespace std;

struct Node {
    int key;
    Node** children;
};

Node* create_node() {
    Node* node = new Node;
    node->key = -1;
    node->children = nullptr;
    return node;
}

void allocate_children(Node* node, const int k) {
    if (node->children==nullptr) {
        node->children = new Node*[k];
        for (int i=0;i<k;++i) {
            node->children[i] = nullptr;
        }
    }
}

void delete_node(Node* node, int n, int k, bool is_root) {
    if (node==nullptr) return;

    int index=is_root ? n : k;

    if (node->children!=nullptr) {
        for (int i=0;i<index;++i) {
            if (node->children[i]!=nullptr) {
                delete_node(node->children[i], n, k, false);
            }
        }
        delete[] node->children;
    }
    delete node;
}

bool insert(Node* root, int x, int n, int k) {
    Node* current=root;
    int temp_x=x;

    if (current->key!=-1 && current->key==x) {
        printf("%d exist\n", x);
        return false;
    }

    if (current->key==-1) {
        current->key=x;
        return true;
    }

    if (root->children==nullptr)
        allocate_children(root, n);

    int mod=temp_x % n;
    temp_x/=n;

    if (current->children[mod]==nullptr) {
        Node* new_node = create_node();
        new_node->key=x;
        current->children[mod]=new_node;
        return true;
    }

    current=current->children[mod];

    while (true) {
        if (current->key!=-1 && current->key==x) {
            printf("%d exist\n", x);
            return false;
        }

        if (current->key==-1) {
            current->key=x;
            return true;
        }

        if (current->children==nullptr)
            allocate_children(current, k);

        mod = temp_x % k;
        temp_x /= k;

        if (current->children[mod]==nullptr) {
            Node* new_node = create_node();
            new_node->key=x;
            current->children[mod]=new_node;
            return true;
        }

        current=current->children[mod];
    }
}

bool find(Node* root, int x, int n, int k) {
    Node* current=root;
    int temp_x=x;

    if (current->key!=-1 && current->key==x) {
        printf("%d exist\n", x);
        return true;
    }

    if (root->children==nullptr) {
        printf("%d not exist\n", x);
        return false;
    }

    int mod=temp_x % n;
    temp_x/=n;

    if (current->children[mod]==nullptr ) {
        printf("%d not exist\n", x);
        return false;
    }

    current=current->children[mod];

    while (current!=nullptr) {
        if (current->key!=-1&&current->key==x) {
            printf("%d exist\n", x);
            return true;
        }

        if (current->children==nullptr) {
            printf("%d not exist\n", x);
            return false;
        }

        mod=temp_x%k;
        temp_x/=k;

        if (current->children[mod]==nullptr) {
            printf("%d not exist\n", x);
            return false;
        }

        current=current->children[mod];
    }

    printf("%d not exist\n", x);
    return false;
}

Node* find_node_with_key(Node* root, int x, int n, int k) {
    Node* current=root;
    int temp_x=x;

    if (current->key !=-1 && current->key==x) {
        return current;
    }

    if (current->children==nullptr) return nullptr;

    int mod=temp_x % n;
    temp_x/=n;

    if (current->children[mod]==nullptr) return nullptr;

    current=current->children[mod];

    while (current!=nullptr) {
        if (current->key!=-1&&current->key==x) {
            return current;
        }

        if (current->children==nullptr) {
            return nullptr;
        }

        mod=temp_x%k;
        temp_x/=k;

        if (current->children[mod]==nullptr) {
            return nullptr;
        }

        current=current->children[mod];
    }
    return nullptr;
}

bool is_leaf(Node* node, int branch_factor) {
    if (node->children==nullptr) return true;
    for (int i=0;i<branch_factor;++i) {
        if (node->children[i]!=nullptr && node->children[i]->key!=-1) return false;
    }
    return true;
}

Node* find_leftmost_leaf_with_key(Node* node, int n, int k, bool is_root) {
    if (node==nullptr) return nullptr;

    int branch_factor = is_root?n:k;

    if (is_leaf(node, branch_factor) && node->key!=-1) {
        return node;
    }

    for (int i = 0; i < branch_factor; ++i) {
        if (node->children != nullptr && node->children[i] != nullptr && node->children[i]->key!=-1) {
            Node* result = find_leftmost_leaf_with_key(node->children[i], n, k, false);
            if (result != nullptr) return result;
        }
    }

    return nullptr;
}

bool remove(Node* root, int x, int n, int k) {
    Node* p=find_node_with_key(root, x, n, k);
    if (p==nullptr) {
        printf("%d not exist\n", x);
        return false;
    }

    int branch_factor=(p==root)?n:k;

    Node* q = find_leftmost_leaf_with_key(p, n, k, p==root);

    if (q==nullptr) {
        p->key=-1;
        return true;
    }
    if (p==q) {
        p->key=-1;
        return true;
    }

    p->key = q->key;
    q->key=-1;
    return true;
}


void inorder(Node* node, int branch_factor) {
    if (node==nullptr) return;

    if (node->key!=-1) {
        printf("%d ", node->key);
    }
    if (node->children!=nullptr) {
        for (int i=0;i<branch_factor;++i) {
            inorder(node->children[i], branch_factor);
        }
    }
}

void inorder_root(Node* root, int n, int k) {
    if (root==nullptr) return;

    if (root->key!=-1) {
        printf("%d ", root->key);
    }
    if (root->children!=nullptr) {
        for (int i=0;i<n;i++) {
            if (root->children[i]!=nullptr) {
                inorder(root->children[i], k);
            }
        }
    }
}


int main() {
    int test_cases;
    scanf("%d", &test_cases);

    int min_value, max_value;
    scanf("%d %d", &min_value, &max_value);
    int n, k;
    scanf("%d %d", &n, &k);
    //cin.ignore();
    Node* root = create_node();
    for (int i=0;i<test_cases;++i) {
        char command;
        scanf(" %c", &command);
        int x;
        switch (command) {
            case 'I':
                scanf("%d", &x);
                insert(root,x,n,k);
                break;
            case 'L':
                scanf("%d", &x);
                find(root, x, n, k);
                break;
            case 'D':
                scanf("%d", &x);
                remove(root, x, n, k);
                break;
            case 'P':
                inorder_root(root, n,k);
                printf("\n");
                break;
            default:
                break;
        }
    }
    delete_node(root, n, k, true);
    return 0;
}
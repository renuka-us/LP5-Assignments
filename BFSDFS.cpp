#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
#include <chrono>
using namespace std;

class node {
public:
    node *left, *right;
    int data;
    node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to insert a node into the binary tree
node* insert(node* root, int data) {
    if (!root)
        return new node(data);

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp->left == nullptr) {
            temp->left = new node(data);
            cout<< "Parent" << temp->data << "left" << temp->left->data;
            return root;
        } else if (temp->right == nullptr) {
            temp->right = new node(data);
            cout<< "Parent" << temp->data << "right" << temp->right->data;
            return root;
        } else {
            q.push(temp->left);
            q.push(temp->right);
        }
    }
    return root;
}


// Function to perform breadth-first search traversal of the binary tree
void bfs(node* root) {
    if (!root)
        return;

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        int qSize = q.size();

        for (int i = 0; i < qSize; i++) {
            node* currNode;

            currNode = q.front();
            q.pop();
            cout << "\t" << currNode->data;

            if (currNode->left)
                q.push(currNode->left);
            if (currNode->right)
                q.push(currNode->right);
        }
    }
}
// Function to perform breadth-first search traversal of the binary tree
void parallel_bfs(node* root) {
    if (!root)
        return;

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        int qSize = q.size();

#pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            node* currNode;
#pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }

            if (currNode->left)
                q.push(currNode->left);
            if (currNode->right)
                q.push(currNode->right);
        }
    }
}

void dfs(node* root) {
    if (root == nullptr)
        return;

    stack<node*> stk;
    stk.push(root);

    {
        while (!stk.empty()) {
            node* node = nullptr;

            {
                if (!stk.empty()) {
                    node = stk.top();
                    stk.pop();
                }
            }

            if (node != nullptr) {
                cout << node->data << "\t";
          
                    if (node->right != nullptr)
                        stk.push(node->right);
               
                    if (node->left != nullptr)
                        stk.push(node->left);
 
            }
        }
    }
}
void parallel_dfs(node* root) {
    if (root == nullptr)
        return;

    stack<node*> stk;
    stk.push(root);

    #pragma omp parallel
    {
        while (!stk.empty()) {
            node* node = nullptr;

            #pragma omp critical
            {
                if (!stk.empty()) {
                    node = stk.top();
                    stk.pop();
                }
            }

            if (node != nullptr) {
                cout << node->data << "\t";
                #pragma omp task shared(stk)
                {
                    if (node->right != nullptr)
                        stk.push(node->right);
                }

                #pragma omp task shared(stk)
                {
                    if (node->left != nullptr)
                        stk.push(node->left);
                }

                #pragma omp taskwait
            }
        }
    }
}

int main() {
    node* root = nullptr;
    int data;
    char ans;
    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = insert(root, data);
        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "Sequential BFS traversal:";
    auto start = chrono::high_resolution_clock::now();
    bfs(root);
    auto end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    chrono::duration<double> duration = end - start;

    // Print the duration
    cout << "Time taken by Sequential BFS traversal:  " << duration.count() << " seconds" << endl;


    cout << "Parallel BFS traversal:";
    start = chrono::high_resolution_clock::now();
    parallel_bfs(root);
    end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    duration = end - start;

    // Print the duration
    cout << "Time taken by Parallel BFS: " << duration.count() << " seconds" << endl;

    cout << "Sequential DFS traversal:";
    start = chrono::high_resolution_clock::now();
    dfs(root);
    end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    duration = end - start;

    // Print the duration
    cout << "Time taken by Sequential DFS traversal: " << duration.count() << " seconds" << endl;
    cout << endl;

    cout << "Parallel DFS traversal:";
    start = chrono::high_resolution_clock::now();
    parallel_dfs(root);
    end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    duration = end - start;

    // Print the duration
    cout << "Time taken by Parallel DFS: " << duration.count() << " seconds" << endl;
    cout << endl;

    return 0;
}



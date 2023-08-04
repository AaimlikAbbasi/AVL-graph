#include<iostream>
#include<iomanip>
//#include <SDL.h>
//#include <SDL_mixer.h>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<fstream>
//#include"MST.h"
const int V = 400;
using namespace std;
// An AVL tree node
class Node
{
public:
    int id;
    int rewardscore;
    Node* left;
    Node* right;
    int height;
};

// A utility function to get the
// height of the tree
int height(Node* N)
{
    if (N == nullptr)
        return 0;
    return N->height;
}

// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(int key, int score)
{
    Node* node = new Node();
    node->id = key;
    node->rewardscore = score;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
        height(x->right)) + 1;
    y->height = max(height(y->left),
        height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node* N)
{
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, int key, int score)
{
    /* 1. Perform the normal BST insertion */
    if (node == nullptr)
        return(newNode(key, score));

    if (key < node->id)
        node->left = insert(node->left, key, score);
    else if (key > node->id)
        node->right = insert(node->right, key, score);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
        height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->id)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->id)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->id)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}
Node* search_by_score(Node* node, int score) {                //searches the nodes and makes it's score zero
    Node* first_match = nullptr;

    while (node != nullptr) {
        if (node->rewardscore == score) {
            // Found a node with the same score
            first_match = node;
            node = node->left;  // Continue search in the left subtree
        }
        else if (score < node->rewardscore) {
            node = node->left;  // Search in the left subtree
        }
        else {
            node = node->right;  // Search in the right subtree
        }
    }
    if (first_match != nullptr) {
        first_match->rewardscore = 0;
        return first_match;
    }

}


int sum_rewards(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int sum = 0;
    sum = sum_rewards(node->left) + node->rewardscore + sum_rewards(node->right);

    return sum;
}








struct node
{
    int id;
    char data;
    int rewardstore;
    int count;
    node* next;
    node* down;
    node()
    {
        id = 0;
        rewardstore = 0;
        count = 0;
        next = NULL;
        down = NULL;
    }
    node(int d)
    {
        next = NULL;
        down = NULL;
        data = d;
    }
};
class menu
{
public:

    menu() {}


    char** gamemap();
    void display(char** arr);
    node** convertTo2dLL(char** array, int row, int col);
    char** moveplayer(char** arr, int row, int col); // Add this line
    int** floydsalgorithm(char** arr);
    //void floyd_warshall_algo(int** arr, int x, int y);
    int** dijistraalgorithm(int** matrix, int loc);

};

const int INF = 9999;
void printPath(int** path_matrix, int i, int j)
{
    if (i == j)
    {
        cout << i << " ";
    }
    else if (path_matrix[i][j] == -1)
    {
        cout << "No path exists" << endl;
    }
    else
    {
        printPath(path_matrix, i, path_matrix[i][j]);
        cout << j << " ";
    }
}

int** menu::floydsalgorithm(char** arr)
{

    int** weight = new int* [20];
    for (int j = 0; j < 20; j++)
    {
        weight[j] = new int[20];

    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
            weight[i][j] = 0;
    }

    int** matrix = new int* [20];
    for (int j = 0; j < 20; j++)
    {
        matrix[j] = new int[20];
    }
    int count = 1;
    for (int i = 0; i < 20; i++)
    {
        // assign the weights
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = count;
            count++;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        // assign the weights
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == 'c')
                weight[i][j] = 6;
            else if (arr[i][j] == 'p')
                weight[i][j] = 2;
            else if (arr[i][j] == 'w')
                weight[i][j] = 4;
            else if (arr[i][j] == 'j')
                weight[i][j] = 3;

            else if (arr[i][j] == '%') // dead point
                weight[i][j] = INF;
            else if (arr[i][j] == '#') // obstacle
                weight[i][j] = INF;
            else if (arr[i][j] == '&') // dragon
                weight[i][j] = 100;
            else if (arr[i][j] == '$') // goblin
                weight[i][j] = 150;
            else if (arr[i][j] == '@') // werewolf
                weight[i][j] = 50;
            else
                weight[i][j] = INF;
        }
    }

    int num_nodes = 400;

    cout << endl;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << setw(5) << weight[i][j];
        }
        cout << endl;
    }

    int** adj_matrix = new int* [num_nodes];
    for (int i = 0; i < num_nodes; i++)
    {
        adj_matrix[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++)
        {
            if (i == j)
                adj_matrix[i][j] = 0;
            else
                adj_matrix[i][j] = INF;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int node1 = matrix[i][j];
            if (i > 0)
            {
                int node2 = matrix[i - 1][j];
                if (weight[i][j] != INF && weight[i - 1][j] != INF)
                {
                    adj_matrix[node1 - 1][node2 - 1] = weight[i][j];
                    adj_matrix[node2 - 1][node1 - 1] = weight[i][j];
                }
            }
            if (j > 0)
            {
                int node2 = matrix[i][j - 1];
                if (weight[i][j] != INF && weight[i][j - 1] != INF)
                {
                    adj_matrix[node1 - 1][node2 - 1] = weight[i][j];
                    adj_matrix[node2 - 1][node1 - 1] = weight[i][j];
                }
            }
            if (i < 4)
            {
                int node2 = matrix[i + 1][j];
                if (weight[i][j] != INF && weight[i + 1][j] != INF)
                {
                    adj_matrix[node1 - 1][node2 - 1] = weight[i][j];
                    adj_matrix[node2 - 1][node1 - 1] = weight[i][j];
                }
            }
            if (j < 4)
            {
                int node2 = matrix[i][j + 1];
                if (weight[i][j] != INF && weight[i][j + 1] != INF)
                {
                    adj_matrix[node1 - 1][node2 - 1] = weight[i][j];
                    adj_matrix[node2 - 1][node1 - 1] = weight[i][j];
                }
            }
        }
    }
    cout << "ADJANCENCY MATRIX FOR FLOYD'S ALGORITHM'" << endl;
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j < 400; j++)
            if (adj_matrix[i][j] == 9999)
                cout << setw(4) << "INF";
            else
                cout << setw(4) << adj_matrix[i][j];
        cout << endl;
    }

    cout << "FLOYD'S ALGORITHM'" << endl;
    int** dist_matrix = new int* [num_nodes];
    for (int i = 0; i < num_nodes; i++)
    {
        dist_matrix[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++)
        {
            dist_matrix[i][j] = adj_matrix[i][j];

        }
    }
    int** path_matrix = new int* [num_nodes];
    for (int i = 0; i < num_nodes; i++)
    {
        path_matrix[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++)
        {
            if (i == j || dist_matrix[i][j] == INF)
                path_matrix[i][j] = -1;
            else
                path_matrix[i][j] = i;
        }
    }

    // Floyd's algorithm
    for (int k = 0; k < num_nodes; k++)
    {
        for (int i = 0; i < num_nodes; i++)
        {
            for (int j = 0; j < num_nodes; j++)
            {
                if (dist_matrix[i][k] + dist_matrix[k][j] < dist_matrix[i][j])
                {
                    dist_matrix[i][j] = dist_matrix[i][k] + dist_matrix[k][j];
                    path_matrix[i][j] = path_matrix[k][j];
                }
            }
        }
    }

    // Print the shortest path distances
    cout << "Shortest Path Distances: " << endl;
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 0; j < num_nodes; j++)
        {
            if (dist_matrix[i][j] == INF)
            {
                cout << setw(5) << "INF ";
            }
            else
            {
                cout << setw(5) << dist_matrix[i][j];
            }
        }
        cout << endl;
    }

    // Print the shortest path between any two nodes
    cout << "Shortest Path: " << endl;
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 0; j < num_nodes; j++)
        {
            cout << "Path from " << i + 1 << " to " << j + 1 << ": ";
            printPath(path_matrix, i, j);
            cout << endl;
        }
    }
    int start = 0;
    cout << "DEAFAULT SHORTST PATH" << endl;
    cout << "starting location";
    cin >> start;
    int end = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == '*')
            {
                end = matrix[i][j];
            }
        }
    }

    cout << "Path from " << start << " to " << end << ": ";
    printPath(path_matrix, start - 1, end - 1);
    return dist_matrix;


}

class Graph {
private:
    int** adjMatrix;
    int numVertices;

public:
    // Initialize the matrix to zero
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjMatrix = new int* [numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }
    }

    // Add edges
    void addEdge(int weight, int i, int j) {
        adjMatrix[i][j] = weight;
        adjMatrix[j][i] = weight;
    }

    // Remove edges
    void removeEdge(int i, int j) {
        adjMatrix[i][j] = false;
        adjMatrix[j][i] = false;
    }

    // Print the martix
    int** toString() {
        return adjMatrix;
        /* for (int i = 0; i < numVertices; i++) {

           for (int j = 0; j < numVertices; j++)
             cout << adjMatrix[i][j] << " ";
           cout << "\n";
         }*/
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
};
int minDistance(int dist[], bool flag[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (flag[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void display1(int dist[]) {
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}
int** menu::dijistraalgorithm(int** adj_matrix, int src)
{
    int* dist = new int[V];
    bool flag[V];

    for (int i = 0; i < V; i++)
        dist[i] = INF, flag[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, flag);

        flag[u] = true;

        for (int v = 0; v < V; v++) {
            if (!flag[v] && adj_matrix[u][v] && dist[u] != INF
                && dist[u] + adj_matrix[u][v] < dist[v])
                dist[v] = dist[u] + adj_matrix[u][v];
        }
    }

    display1(dist);
}
void dijistra(char** arr)
{
    int** weight = new int* [20];
    for (int j = 0; j < 20; j++)
    {
        weight[j] = new int[20];

    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
            weight[i][j] = 0;
    }

    int** matrix = new int* [20];
    for (int j = 0; j < 20; j++)
    {
        matrix[j] = new int[20];
    }
    int count = 1;
    for (int i = 0; i < 20; i++)
    {
        // assign the weights
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = count;
            count++;
        }
    }
    Graph g(400);
    int num_nodes = 400;
    for (int i = 0; i < 20; i++)
    {
        // assign the weights
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == 'c')
                weight[i][j] = 6;
            else if (arr[i][j] == 'p')
                weight[i][j] = 2;
            else if (arr[i][j] == 'w')
                weight[i][j] = 4;
            else if (arr[i][j] == 'j')
                weight[i][j] = 3;

            else if (arr[i][j] == '%') // dead point
                weight[i][j] = INF;
            else if (arr[i][j] == '#') // obstacle
                weight[i][j] = INF;
            else if (arr[i][j] == '&') // dragon
                weight[i][j] = 100;
            else if (arr[i][j] == '$') // goblin
                weight[i][j] = 150;
            else if (arr[i][j] == '@') // werewolf
                weight[i][j] = 50;
            else
                weight[i][j] = INF;
        }
    }

    num_nodes = 400;

    cout << endl;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << setw(5) << weight[i][j];
        }
        cout << endl;
    }
    int** adj_matrix = new int* [num_nodes];
    for (int i = 0; i < num_nodes; i++)
    {
        adj_matrix[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++)
        {
            adj_matrix[i][j] = 0;
        }
    }
    int value = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int node1 = matrix[i][j];
            if (i > 0)
            {
                int node2 = matrix[i - 1][j];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);


            }
            if (j > 0)
            {
                int node2 = matrix[i][j - 1];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);



            }
            if (i < 4)
            {
                int node2 = matrix[i + 1][j];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);

            }
            if (j < 4)
            {
                int node2 = matrix[i][j + 1];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);

            }
        }
    }
    menu obj;
    adj_matrix = g.toString();
    cout << "Adjency Matrix" << endl;
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j < 400; j++)
            cout << setw(4) << adj_matrix[i][j];
        cout << endl;
    }
    for (int i = 0; i < 400; i++)
    {
        cout << "next coloumn" << endl;
        obj.dijistraalgorithm(adj_matrix, i);
    }
}
int** adjacency_matric(char** arr) {


    Graph g(400);
    int count = 1;
    int** matrix = new int* [20];
    for (int j = 0; j < 20; j++)
        matrix[j] = new int[20];

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            matrix[i][j] = count;
            count++;
        }
    }


    int** weight = new int* [20];
    for (int j = 0; j < 20; j++)
        weight[j] = new int[20];

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            weight[i][j] = 0;

        }
    }

    int num_edges = 0;
    for (int i = 0; i < 20; i++)
    {
        // assign the weights
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == 'c')
                weight[i][j] = 6;
            else if (arr[i][j] == 'p')
                weight[i][j] = 2;
            else if (arr[i][j] == 'w')
                weight[i][j] = 4;
            else if (arr[i][j] == 'j')
                weight[i][j] = 3;

            else if (arr[i][j] == '%') // dead point
                weight[i][j] = INF;
            else if (arr[i][j] == '#') // obstacle
                weight[i][j] = INF;
            else if (arr[i][j] == '&') // dragon
                weight[i][j] = 100;
            else if (arr[i][j] == '$') // goblin
                weight[i][j] = 150;
            else if (arr[i][j] == '@') // werewolf
                weight[i][j] = 50;
            else
                weight[i][j] = 500;
        }
    }

    int num_nodes = 400;


    cout << endl;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << setw(4) << weight[i][j];
        }
        cout << endl;
    }

    int** adj_matrix = new int* [num_nodes];
    for (int i = 0; i < num_nodes; i++)
    {
        adj_matrix[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++)
        {
            adj_matrix[i][j] = 0;
        }
    }
    int value = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int node1 = matrix[i][j];
            if (i > 0)
            {
                int node2 = matrix[i - 1][j];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);


            }
            if (j > 0)
            {
                int node2 = matrix[i][j - 1];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);



            }
            if (i < 4)
            {
                int node2 = matrix[i + 1][j];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);

            }
            if (j < 4)
            {
                int node2 = matrix[i][j + 1];

                value = weight[i][j];
                g.addEdge(value, node1 - 1, node2 - 1);
                value = weight[i][j];
                g.addEdge(value, node2 - 1, node1 - 1);

            }
        }
    }

    adj_matrix = g.toString();
    char choice;
    cout << "DO YOU WANT TO PRINT ADJANCY MATRIX Y/N";
    cin >> choice;

    // print the adjacency matrix
    if (choice == 'y')
    {
        for (int i = 0; i < 400; i++) {
            for (int j = 0; j < 400; j++) {
                cout << setw(4) << adj_matrix[i][j];
            }
            cout << endl;
        }
    }

    return adj_matrix;
}

char** menu::moveplayer(char** arr, int row, int col)
{
    row = 0;
    col = 0;
    char key = ' ';
    bool flag = false;
    char previous = 0;
    char player = '+';
    Node* root = nullptr;
    root = insert(root, 100, 0);
    while (flag != true)
    {
        cout << "MOVE" << endl;
        cin >> key;


        if (key == 't') // Move up
        {
            arr[row][col] = previous;
            if (row > 0 && previous != '#')
            {

                previous = arr[row - 1][col];
                arr[row - 1][col] = '+';
                row--;

                if (previous == 'p') {
                    int x = rand() % 200;
                    root = insert(root, x, 70);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'j') {
                    int x = rand() % 200;
                    root = insert(root, x, 50);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'w') {
                    int x = rand() % 200;
                    root = insert(root, x, 30);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '&') {

                    root = search_by_score(root, 50);     //will search the first jewel colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '$') {

                    root = search_by_score(root, 70);     //will search the first potion colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '@') {

                    root = search_by_score(root, 30);     //will search the first weopen colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '%') {

                    cout << "Game over this was a dead end play again";
                    system("pause");
                    system("cls");

                }
                else if (previous == '*') {

                    cout << "YOU FOUND THE CRYSTEL YOU WON ";
                    system("pause");
                    system("cls");
                    cout << "THE TOTAL SCORE IS " << sum_rewards(root);

                }
                else {
                    cout << "the path was clear" << endl;
                }
                display(arr);
            }
            else
            {
                cout << "Cannot move up." << endl;
            }
        }
        else if (key == 'g') // Move down
        {
            arr[row][col] = previous;
            if (row < 19 && previous != '#')
            {

                previous = arr[row + 1][col];
                arr[row + 1][col] = '+';
                row++;
                if (previous == 'p') {
                    int x = rand() % 200;
                    root = insert(root, x, 70);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'j') {
                    int x = rand() % 200;
                    root = insert(root, x, 50);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'w') {
                    int x = rand() % 200;
                    root = insert(root, x, 30);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '&') {

                    root = search_by_score(root, 50);     //will search the first jewel colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '$') {

                    root = search_by_score(root, 70);     //will search the first potion colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '@') {

                    root = search_by_score(root, 30);     //will search the first weopen colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '%') {

                    cout << "Game over this was a dead end play again";
                    system("pause");
                    system("cls");

                }
                else if (previous == '*') {

                    cout << "YOU FOUND THE CRYSTEL YOU WON ";
                    system("pause");
                    system("cls");
                    cout << "THE TOTAL SCORE IS " << sum_rewards(root);

                }
                else {
                    cout << "the path was clear" << endl;
                }
                display(arr);
            }
            else
            {
                cout << "Cannot move down." << endl;
            }
        }
        else if (key == 'h') // Move right
        {
            arr[row][col] = previous;
            if (col < 19 && previous != '#')
            {

                previous = arr[row][col + 1];
                arr[row][col + 1] = '+';
                col++;
                if (previous == 'p') {
                    int x = rand() % 200;
                    root = insert(root, x, 70);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'j') {
                    int x = rand() % 200;
                    root = insert(root, x, 50);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'w') {
                    int x = rand() % 200;
                    root = insert(root, x, 30);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '&') {

                    root = search_by_score(root, 50);     //will search the first jewel colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '$') {

                    root = search_by_score(root, 70);     //will search the first potion colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '@') {

                    root = search_by_score(root, 30);     //will search the first weopen colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '%') {

                    cout << "Game over this was a dead end play again";
                    system("pause");
                    system("cls");

                }
                else if (previous == '*') {

                    cout << "YOU FOUND THE CRYSTEL YOU WON ";
                    system("pause");
                    system("cls");
                    cout << "THE TOTAL SCORE IS " << sum_rewards(root);

                }
                else {
                    cout << "the path was clear" << endl;
                }
                display(arr);
            }
            else
            {
                cout << "Cannot move right." << endl;
            }
        }
        else if (key == 'f') // Move left
        {
            arr[row][col] = previous;
            if (col > 0 && previous != '#')
            {

                previous = arr[row][col - 1];
                arr[row][col = 1] = '+';
                col--;

                if (previous == 'P') {
                    int x = rand() % 200;
                    root = insert(root, x, 70);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'j') {
                    int x = rand() % 200;
                    root = insert(root, x, 50);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == 'w') {
                    int x = rand() % 200;
                    root = insert(root, x, 30);
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '&') {

                    root = search_by_score(root, 50);     //will search the first jewel colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '$') {

                    root = search_by_score(root, 70);     //will search the first potion colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '@') {

                    root = search_by_score(root, 30);     //will search the first weopen colleced and make it's score 0
                    cout << "THE TOTAL SCORE UPTILL NOW " << sum_rewards(root) << endl;
                }
                else if (previous == '%') {

                    cout << "Game over this was a dead end play again";
                    system("pause");
                    system("cls");

                }
                else if (previous == '*') {

                    cout << "YOU FOUND THE CRYSTEL YOU WON ";
                    system("pause");
                    system("cls");
                    cout << "THE TOTAL SCORE IS " << sum_rewards(root) << endl;

                }
                else {
                    cout << "the path was clear" << endl;
                }
                display(arr);
            }
            else
            {
                cout << "Cannot move left." << endl;
            }
        }

    }



    return arr;
}

node** menu::convertTo2dLL(char** array, int row, int col)
{

    ///first we create the head node pointer  array and allocate memory to the memory of rows
    node** head = new node * [row];  // Use a dynamic array of node pointers

    // Create head nodes for each row
    for (int i = 0; i < row; i++) {
        head[i] = NULL; //initialized head node of each row into null
    }
    int row_count = 0;
    // Convert 2D array into 2D linked list
    while (row_count < row)
    {
        node* moveright = NULL;  // Initialize moveright for each row to null,it will traverse the link list in right way

        int col_count = 0;  // Reset col_count for each row
        while (col_count < col)
        {
            node* newnode = new node(array[row_count][col_count]);
            //create new node that stores the element of current index
            if (head[row_count] == NULL)


            {
                head[row_count] = newnode;
            }
            else
            {//if head is not null ,then traverse the list while assigning it some value
                moveright->next = newnode;
            }
            //move right pointer to new node
            moveright = newnode;

            col_count++;
        }
        row_count++;
    }
    row_count = 0;
    // Link the down pointers
    while (row_count < row - 1)
    {
        node* p = head[row_count];
        node* q = head[row_count + 1];

        while (p != NULL && q != NULL)
        {
            p->down = q;
            p = p->next;
            q = q->next;
        }
        row_count++;
    }
    cout << endl;

    for (int i = 0; i < row; i++) {
        node* current = head[i];
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }


    system("pause");
    system("cls");
    return head;
}




void menu::display(char** arr)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
    system("cls");
}
char** menu::gamemap()
{
    char c = 'c';
    char j = 'j';       // 50 points
    char potion = 'P';  // 70 points
    char w = 'w';       // 30 points
    char deathpoint = '%';
    char obstacle = '#';   // #
    char dragon = '&';      // you will lose the jewel
    char globin = '$';      // you will lose the potion
    char warewolf = '@';    // you will lose the weapon
    char crystals = '*';    // goal point

    char** arr = new char* [20];
    for (int j = 0; j < 20; j++)
    {
        arr[j] = new char[20];
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            arr[i][j] = c;
        }
    }

    srand(time(NULL));

    int row = 0;
    int col = 0;
    int count = 0;
    while (count < 25)
    {
        row = rand() % 20;
        col = rand() % 20;
        if (arr[row][col] == c)
        {

            arr[row][col] = potion;
            count++;
        }
    }


    count = 0;

    while (count < 20)
    {
        row = rand() % 20;
        col = rand() % 20;
        if (arr[row][col] == c)
        {

            arr[row][col] = j;
            count++;
        }
    }
    count = 0;
    while (count < 40)
    {
        row = rand() % 20;
        col = rand() % 20;
        if (arr[row][col] == c)
        {

            arr[row][col] = obstacle;
            count++;
        }
    }

    count = 0;
    while (count < 20)
    {
        row = rand() % 20;
        col = rand() % 20;
        if (arr[row][col] == c)
        {

            arr[row][col] = dragon;
            count++;
        }
    }


    count = 0;
    while (count < 20)
    {
        row = rand() % 20;
        col = rand() % 20;
        if (arr[row][col] == c)
        {

            arr[row][col] = globin;
            count++;
        }
    }

    count = 0;
    while (count < 20)
    {
        row = rand() % 20;
        col = rand() % 20;
        if (arr[row][col] == c)
        {

            arr[row][col] = warewolf;
            count++;
        }
    }




    //this will ensure that there is no two consrction p portion
    arr[17][9] = crystals;



    return arr;


}
void instruction()
{


    cout << "\t\t" << " _____________________________________" << endl;
    cout << "\t\t" << "|1: if you want to move up press t    |" << endl;
    cout << "\t\t" << "|2: if you want to move down press g  |" << endl;
    cout << "\t\t" << "|3: if you want to move right press h |" << endl;
    cout << "\t\t" << "|4: if you want to move left press f  |" << endl;
    cout << "\t\t" << "|_____________________________________|" << endl;
    system("pause");
    system("cls");

}
int main()
{
    cout << "\033[48;5;197m";
    cout << "\033[37m";
    cout << "\t\t\t\t" << " __________________________________" << endl;
    cout << "\t\t\t\t" << "|   THE QUEST OF CRYSTAL KINGDOM   |" << endl;
    cout << "\t\t\t\t" << "|__________________________________|" << endl;

    menu obj;
    char** arr = new char* [20];
    for (int j = 0; j < 20; j++)
    {
        arr[j] = new char[20];
    }
    arr = obj.gamemap();
    int choice = 0;
    bool flag = false;
    int x = 0;
    int y = 0;
    do {
        cout << "\t\t\t\t" << " _____________________________________________" << endl;
        cout << "\t\t\t\t" << "|                MENU                         |" << endl;
        cout << "\t\t\t\t" << "|_____________________________________________|" << endl;
        cout << "\t\t\t\t" << " _____________________________________________" << endl;
        cout << "\t\t\t\t" << "|  1:PRESS 1 ;for  instruction                |" << endl;
        cout << "\t\t\t\t" << "|  2:PRESS 2 ;for  display in 2D              |" << endl;
        cout << "\t\t\t\t" << "|  3:PRESS 3 ;for  display in link list       |" << endl;
        cout << "\t\t\t\t" << "|  4:PRESS 4 ;for  PLAY GAME                  |" << endl;
        cout << "\t\t\t\t" << "|  5:PRESS 5 ;for  EXIT                       |" << endl;
        cout << "\t\t\t\t" << "|  6:PRESS 6 ;for  DISPLAY ADJANCY MATRIX     |" << endl;
        cout << "\t\t\t\t" << "|  7:PRESS 7 ;for  DISPLAY FlOYD's ALGORITHM  |" << endl;
        cout << "\t\t\t\t" << "|  8:PRESS 8 ;for  DISPLAY PRIMS ALGORITHM    |" << endl;
        cout << "\t\t\t\t" << "|  9:PRESS 9 ;for  DISPLAY KRUSHKAL ALGORITHM |" << endl;
        cout << "\t\t\t\t" << "| 10:PRESS 10;for  DISPLAY DIJISTRA ALGORITHM|" << endl;
        cout << "\t\t\t\t" << "|_____________________________________________|" << endl;
        cin >> choice;

        switch (choice)
        {

        case 1:
            instruction();
            break;
        case 2:
            system("color  40");
            cout << "DISPLAY THROUGH 2D ARRAY" << endl;
            obj.display(arr);
            break;
        case 3:
            system("color  B0");
            cout << "DISPLAY THROUGH 2D LINKED LIST" << endl;
            obj.convertTo2dLL(arr, 20, 20);
            break;

        case 5:
            system("color  D0");
            flag = true;
            break;

        case 6:
            system("color  E0");
            cout << "DISPLAY ADJANCENCY MATRIC" << endl;
            adjacency_matric(arr);
            //obj.floyd_warshall_algo(arr, x, y);
            break;
        case 7:
            system("color  E0");
            obj.floydsalgorithm(arr);
            break;
        case 8:
            //prim
            system("color B0");
            break;
        case 9:
            //kruskal
            system("color B0");
            break;
        case 10:
            system("color  70");
            dijistra(arr);
        case 4:
            system("color  F0");
            cout << "PLUS INDICATES THE PLAYER" << endl;
            obj.moveplayer(arr, 20, 20);
            break;


        }
    } while (flag != true);
    char audio_[50];
    string audio_str;
    fstream fp;
    cout << "enter name of audio file .wav extension";
    cin >> audio_;

    fp.open(audio_, ios::in);
    if (fp != NULL)
    {
       string audio_str = audio_;
    }
    PlaySound(audio_str.c_str(), NULL, SND_SYNC);
    fp.close();
    return 0;
}


#include <iostream>
#include <string>
using namespace std;

class Flight
{
public:
    int flightNumber;
    string destination;
    int seatsAvailable;

    Flight(int n = 0, string dest = "", int s = 0)
    {
        flightNumber = n;
        destination = dest;
        seatsAvailable = s;
    }

    int getId() const
    {
        return flightNumber;
    }

    bool operator<(const Flight& obj) const
    {
        return flightNumber < obj.flightNumber;
    }

    bool operator>(const Flight& obj) const
    {
        return flightNumber > obj.flightNumber;
    }

    bool operator==(const Flight& obj) const
    {
        return flightNumber == obj.flightNumber;
    }
};

ostream& operator<<(ostream& os, const Flight& f)
{
    os << "ID: " << f.flightNumber << " | " << f.destination << " | Seats: " << f.seatsAvailable;
    return os;
}

template<class T>
class AvlTree
{
    class Node
    {
    public:
        T data;
        Node* left;
        Node* right;
        int height;

        Node(T d)
        {
            data = d;
            left = right = nullptr;
            height = 1;
        }
    };

    Node* root;
    int ll, rr, lr, rl;

    int getHeight(Node* node)
    {
        if (node == nullptr) return 0;

        return node->height;
    }

    int getBalanceFactor(Node* n)
    {
        if (n == nullptr) return 0;

        return getHeight(n->left) - getHeight(n->right);
    }

    void updateHeight(Node* node)
    {
        int l = getHeight(node->left);
        int r = getHeight(node->right);

        if (r > l) node->height = 1 + r;
        else node->height = 1 + l;
    }

    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* rebalance(Node* node)
    {
        updateHeight(node);
        int bf = getBalanceFactor(node);

        if (bf == 2)
        {
            if (getBalanceFactor(node->left) >= 0)
            {
                ll++;
                cout << "Imbalance at flight " << node->data.getId() << ": LL case, right rotation performed." << endl;
                return rotateRight(node);
            }
            lr++;
            cout << "Imbalance at flight " << node->data.getId() << ": LR case, left-right rotation performed." << endl;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (bf == -2)
        {
            if (getBalanceFactor(node->right) <= 0)
            {
                rr++;
                cout << "Imbalance at flight " << node->data.getId() << ": RR case, left rotation performed." << endl;
                return rotateLeft(node);
            }
            rl++;
            cout << "Imbalance at flight " << node->data.getId() << ": RL case, right-left rotation performed." << endl;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(Node* d)
    {
        if (d == nullptr) return;

        inorder(d->left);
        cout << d->data << endl;
        inorder(d->right);
    }

    void preorder(Node* d)
    {
        if (d == nullptr) return;

        cout << d->data << endl;
        preorder(d->left);
        preorder(d->right);
    }

    void postorder(Node* d)
    {
        if (d == nullptr) return;

        postorder(d->left);
        postorder(d->right);
        cout << d->data << endl;
    }

    void printTree(Node* d, int depth)
    {
        if (d == nullptr) return;

        printTree(d->right, depth + 1);
        cout << string(depth * 4, ' ') << d->data.getId() << " (bf=" << getBalanceFactor(d) << ")" << endl;
        printTree(d->left, depth + 1);
    }

    int countLeafNodes(Node* d)
    {
        if (d == nullptr) return 0;

        if (d->left == nullptr && d->right == nullptr) return 1;

        return countLeafNodes(d->left) + countLeafNodes(d->right);
    }

    int countNodes(Node* d)
    {
        if (d == nullptr) return 0;

        return 1 + countNodes(d->left) + countNodes(d->right);
    }

    bool isBalance(Node* d)
    {
        if (d == nullptr) return true;

        int BF = getBalanceFactor(d);
        if (BF > 1 || BF < -1) return false;

        return isBalance(d->left) && isBalance(d->right);
    }

    Node* findMin(Node* d)
    {
        if (d == nullptr || d->left == nullptr) return d;

        return findMin(d->left);
    }

    Node* findMax(Node* d)
    {
        if (d == nullptr || d->right == nullptr) return d;

        return findMax(d->right);
    }

    T* search(Node* d, T key)
    {
        if (d == nullptr) return nullptr;

        if (key < d->data) return search(d->left, key);
        if (key > d->data) return search(d->right, key);

        return &(d->data);
    }

    Node* insert(Node* node, T d, bool& inserted)
    {
        if (node == nullptr)
        {
            inserted = true;

            node = new Node(d);

            return node;
        }

        if (d < node->data)
            node->left = insert(node->left, d, inserted);
        else if (d > node->data)
            node->right = insert(node->right, d, inserted);
        else
        {
            inserted = false;
            return node;
        }

        return rebalance(node);
    }

    Node* remove(Node* node, T d, bool& removed)
    {
        if (node == nullptr)
        {
            removed = false;
            return nullptr;
        }

        if (d < node->data)
            node->left = remove(node->left, d, removed);
        else if (d > node->data)
            node->right = remove(node->right, d, removed);
        else
        {
            removed = true;

            if (node->left == nullptr || node->right == nullptr)
            {
                Node* child = node->left;
                if (child == nullptr) child = node->right;

                delete node;
                return child;
            }

            Node* next = findMin(node->right);
            node->data = next->data;

            bool temp = false;
            node->right = remove(node->right, next->data, temp);
        }

        return rebalance(node);
    }

    Node* clone(Node* d)
    {
        if (d == nullptr) return nullptr;

        Node* copy = new Node(d->data);
        copy->height = d->height;
        copy->left = clone(d->left);
        copy->right = clone(d->right);

        return copy;
    }

    void clear(Node* d)
    {
        if (d == nullptr) return;

        clear(d->left);
        clear(d->right);
        delete d;
    }

public:

    AvlTree()
    {
        root = nullptr;
        ll = rr = lr = rl = 0;
    }

    AvlTree(const AvlTree& other)
    {
        root = clone(other.root);
        ll = rr = lr = rl = 0;
    }

    AvlTree& operator=(const AvlTree& other)
    {
        if (this != &other)
        {
            clear();
            root = clone(other.root);
        }
        return *this;
    }

    ~AvlTree()
    {
        clear();
    }

    bool isEmpty()
    {
        return root == nullptr;
    }

    void inorder()
    {
        inorder(root);
    }

    void preorder()
    {
        preorder(root);
    }

    void postorder()
    {
        postorder(root);
    }

    void printTree()
    {
        printTree(root, 0);
    }

    int getHeight()
    {
        return getHeight(root);
    }

    int countLeafNodes()
    {
        return countLeafNodes(root);
    }

    int countNodes()
    {
        return countNodes(root);
    }

    bool isBalance()
    {
        return isBalance(root);
    }

    T* findMin()
    {
        Node* n = findMin(root);
        if (n == nullptr) return nullptr;

        return &(n->data);
    }

    T* findMax()
    {
        Node* n = findMax(root);
        if (n == nullptr) return nullptr;

        return &(n->data);
    }

    T* search(T d)
    {
        return search(root, d);
    }

    bool insert(T d)
    {
        bool inserted = false;
        root = insert(root, d, inserted);
        return inserted;
    }

    bool remove(T d)
    {
        bool removed = false;
        root = remove(root, d, removed);
        return removed;
    }

    void printRotationStats()
    {
        cout << "LL rotations: " << ll << endl;
        cout << "RR rotations: " << rr << endl;
        cout << "LR rotations: " << lr << endl;
        cout << "RL rotations: " << rl << endl;
    }

    AvlTree clone()
    {
        return AvlTree(*this);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
        ll = rr = lr = rl = 0;
    }
};

void showMenu()
{
    cout << endl;
    cout << "========= FLIGHT BOARD MANAGEMENT =========" << endl;
    cout << "1. Add flight                9. Total Flight Count" << endl;
    cout << "2. Cancel flight             10. Find Highest / Lowest" << endl;
    cout << "3. Search flight             11. Balance Check" << endl;
    cout << "4. Display InOrder           12. Count Leaf Flights" << endl;
    cout << "5. Display PreOrder          13. Rotation Statistics" << endl;
    cout << "6. Display PostOrder         14. Copy Board" << endl;
    cout << "7. Display Tree Structure    15. Clear Board" << endl;
    cout << "8. Board Height              16. Display Saved Copy" << endl;
    cout << "0. Exit" << endl;
}

void showBoard(AvlTree<Flight>& board)
{
    if (board.isEmpty())
        cout << "The board is empty." << endl;
    else
        board.inorder();
}

int main()
{
    AvlTree<Flight> board;
    AvlTree<Flight> savedCopy;
    int choice = -1;

    while (choice != 0)
    {
        showMenu();
        cout << endl << "Enter choice: ";
        cin >> choice;

        if (cin.eof()) break;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice, enter a number from the menu." << endl;
            choice = -1;
            continue;
        }

        if (choice == 1)
        {
            int num, seats;
            string dest;

            cout << "Enter Flight Number: ";
            cin >> num;
            cin.ignore();
            cout << "Enter Destination: ";
            getline(cin, dest);
            cout << "Enter Seats Available: ";
            cin >> seats;

            if (cin.fail() || num <= 0 || seats < 0 || dest.empty())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Record not added." << endl;
                continue;
            }

            if (board.insert(Flight(num, dest, seats)))
                cout << "Flight added successfully." << endl;
            else
                cout << "Flight number already exists. Record rejected." << endl;
        }
        else if (choice == 2)
        {
            if (board.isEmpty())
            {
                cout << "The board is empty." << endl;
                continue;
            }

            int num;
            cout << "Enter Flight Number to cancel: ";
            cin >> num;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input." << endl;
                continue;
            }

            if (board.remove(Flight(num)))
                cout << "Flight cancelled successfully." << endl;
            else
                cout << "Flight " << num << " not found." << endl;
        }
        else if (choice == 3)
        {
            if (board.isEmpty())
            {
                cout << "The board is empty." << endl;
                continue;
            }

            int num;
            cout << "Enter Flight Number to search: ";
            cin >> num;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input." << endl;
                continue;
            }

            Flight* found = board.search(Flight(num));

            if (found != nullptr)
                cout << "Flight found: " << *found << endl;
            else
                cout << "Flight " << num << " not found." << endl;
        }
        else if (choice == 4)
        {
            showBoard(board);
        }
        else if (choice == 5)
        {
            if (board.isEmpty()) cout << "The board is empty." << endl;
            else board.preorder();
        }
        else if (choice == 6)
        {
            if (board.isEmpty()) cout << "The board is empty." << endl;
            else board.postorder();
        }
        else if (choice == 7)
        {
            if (board.isEmpty())
            {
                cout << "The board is empty." << endl;
            }
            else
            {
                cout << "Tree structure (right subtree on top):" << endl;
                board.printTree();
            }
        }
        else if (choice == 8)
        {
            cout << "Board height: " << board.getHeight() << endl;
        }
        else if (choice == 9)
        {
            cout << "Total flights on the board: " << board.countNodes() << endl;
        }
        else if (choice == 10)
        {
            if (board.isEmpty())
            {
                cout << "The board is empty." << endl;
            }
            else
            {
                cout << "Highest flight: " << *board.findMax() << endl;
                cout << "Lowest flight: " << *board.findMin() << endl;
            }
        }
        else if (choice == 11)
        {
            if (board.isBalance())
                cout << "The board is height-balanced." << endl;
            else
                cout << "The board is NOT height-balanced." << endl;
        }
        else if (choice == 12)
        {
            cout << "Number of leaf flights: " << board.countLeafNodes() << endl;
        }
        else if (choice == 13)
        {
            board.printRotationStats();
        }
        else if (choice == 14)
        {
            savedCopy = board.clone();
            cout << "Board copied. Contents of the copy:" << endl;
            showBoard(savedCopy);
        }
        else if (choice == 15)
        {
            board.clear();
            cout << "All flight records deleted." << endl;
        }
        else if (choice == 16)
        {
            cout << "Saved copy:" << endl;
            showBoard(savedCopy);
        }
        else if (choice == 0)
        {
            cout << "Goodbye." << endl;
        }
        else
        {
            cout << "Invalid choice, enter a number from the menu." << endl;
        }
    }

    return 0;
}
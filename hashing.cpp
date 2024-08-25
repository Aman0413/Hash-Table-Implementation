#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

public:
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }

    void display(Node *head)
    {

        if (head == NULL)
        {
            cout << "Empty list" << endl;
            return;
        }
        else
        {
            Node *temp = head;

            while (temp != NULL)
            {
                cout << temp->data << "->";
                temp = temp->next;
            }
            cout << "NULL" << endl;
            ;
        }
    }
};

class Hashing
{
public:
    vector<Node *> table;
    int size;
    int capacity;

public:
    float loadFactor()
    {
        return (float)size / capacity;
    }

    void rehash()
    {
        int oldCapacity = capacity;
        capacity *= 2; // Double the capacity

        // Create a new table with the updated capacity

        vector<Node *> oldTable = table; // Store the old table
        table.clear();                   // Clear the old table
        table.resize(capacity, NULL);

        size = 0;

        // Re-insert all nodes into the new table
        for (int i = 0; i < oldCapacity; i++)
        {
            Node *temp = oldTable[i];

            while (temp != NULL)
            {
                insert(temp->data);
                temp = temp->next;
            }
        }
    }
    Hashing(int initialCapacity) : capacity(initialCapacity), size(0)
    {
        table.resize(capacity, NULL);
    }

    void insert(int data)
    {

        int index = data % capacity;

        Node *newNode = new Node(data);

        if (table[index] == NULL)
        {
            table[index] = newNode;
        }
        else
        {
            Node *temp = table[index];

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }
        size++;

        // Rehash if the load factor exceeds 0.75
        if (loadFactor() > 0.75)
        {
            rehash();
        }
    }

    void remove(int data)
    {
        int index = data % capacity;
        Node *temp = table[index];
        Node *prev = NULL;

        while (temp != NULL)
        {
            if (temp->data == data)
            {
                // If the node is head
                if (prev == NULL)
                {
                    table[index] = temp->next; // Move the head pointer to the next node
                }
                else
                {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "Data not found in the table." << endl;
    }

    void display()
    {
        for (int i = 0; i < capacity; i++)
        {
            cout << "Index " << i << ": ";
            if (table[i] != NULL)
            {
                table[i]->display(table[i]);
            }
            else
            {
                cout << "Empty" << endl;
            }
        }
    }

    bool find(int data)
    {

        int index = data % capacity;
        Node *temp = table[index];

        while (temp != NULL)
        {
            if (temp->data == data)
                return true;
            temp = temp->next;
        }

        return false;
    }
};
int main()
{
    int initialCapacity;

    cout << "ENTER INITIAL CAPACITY OF THE HASH TABLE: ";
    cin >> initialCapacity;

    Hashing hs(initialCapacity);
    // insert data
    hs.insert(20);
    hs.insert(98);
    hs.insert(55);
    hs.insert(89);
    hs.insert(35);
    hs.insert(67);

    cout << "Hash Table Contents:" << endl;
    hs.display();

    cout << endl;
    int keyElement;

    cout << "ENTER ELEMENT TO FIND: ";
    cin >> keyElement;

    cout << "Finding element " << keyElement << ": "
         << (hs.find(keyElement) ? "Found" : "Not Found") << endl
         << endl;

    int removeElement;
    cout << "ENTER ELEMENT TO REMOVE: ";
    cin >> removeElement;

    hs.remove(removeElement);
    cout << "After removing element " << removeElement << ":" << endl
         << endl;
    hs.display();

    cout << endl;
    cout << "LOAD FACTOR: " << hs.loadFactor() << endl;

    return 0;
}
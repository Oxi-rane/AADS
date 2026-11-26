#include <iostream>
using namespace std;

class BTreeNode {
public:
    int *keys;
    int t;
    BTreeNode **child;
    int n;
    bool leaf;

    BTreeNode(int t, bool leaf) {
        this->t = t;
        this->leaf = leaf;

        keys = new int[2 * t - 1];
        child = new BTreeNode*[2 * t];

        n = 0;
    }

    void traverse() {
        int i;

        for (i = 0; i < n; i++) {
            if (!leaf)
                child[i]->traverse();

            cout << keys[i] << " ";
        }

        if (!leaf)
            child[i]->traverse();
    }

    BTreeNode* search(int k) {
        int i = 0;

        while (i < n && k > keys[i])
            i++;

        if (i < n && keys[i] == k)
            return this;

        if (leaf)
            return NULL;

        return child[i]->search(k);
    }

    void splitChild(int i, BTreeNode *y) {
        BTreeNode *z = new BTreeNode(t, y->leaf);

        z->n = t - 1;

        // Copy the last t-1 keys
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        // Copy the last t children
        if (!y->leaf) {
            for (int j = 0; j < t; j++)
                z->child[j] = y->child[j + t];
        }

        y->n = t - 1;

        // Shift children to make space
        for (int j = n; j >= i + 1; j--)
            child[j + 1] = child[j];

        child[i + 1] = z;

        // Shift keys
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        // Move median key to parent
        keys[i] = y->keys[t - 1];

        n++;
    }

    void insertNonFull(int k) {
        int i = n - 1;

        if (leaf) {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
            n++;
        }
        else {
            while (i >= 0 && keys[i] > k)
                i--;

            i++;

            if (child[i]->n == 2 * t - 1) {
                splitChild(i, child[i]);

                if (keys[i] < k)
                    i++;
            }

            child[i]->insertNonFull(k);
        }
    }

    int findKey(int k) {
        int idx = 0;

        while (idx < n && keys[idx] < k)
            idx++;

        return idx;
    }

    void remove(int k) {
        int idx = findKey(k);

        if (idx < n && keys[idx] == k) {
            if (leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        }
        else {
            if (leaf)
                return;

            bool flag = (idx == n);

            if (child[idx]->n < t)
                fill(idx);

            if (flag && idx > n)
                child[idx - 1]->remove(k);
            else
                child[idx]->remove(k);
        }
    }

    void removeFromLeaf(int idx) {
        for (int i = idx + 1; i < n; i++)
            keys[i - 1] = keys[i];

        n--;
    }

    void removeFromNonLeaf(int idx) {
        int k = keys[idx];

        if (child[idx]->n >= t) {
            int pred = getPred(idx);
            keys[idx] = pred;
            child[idx]->remove(pred);
        }
        else if (child[idx + 1]->n >= t) {
            int succ = getSucc(idx);
            keys[idx] = succ;
            child[idx + 1]->remove(succ);
        }
        else {
            merge(idx);
            child[idx]->remove(k);
        }
    }

    int getPred(int idx) {
        BTreeNode *cur = child[idx];

        while (!cur->leaf)
            cur = cur->child[cur->n];

        return cur->keys[cur->n - 1];
    }

    int getSucc(int idx) {
        BTreeNode *cur = child[idx + 1];

        while (!cur->leaf)
            cur = cur->child[0];

        return cur->keys[0];
    }

    void fill(int idx) {
        if (idx != 0 && child[idx - 1]->n >= t)
            borrowFromPrev(idx);

        else if (idx != n && child[idx + 1]->n >= t)
            borrowFromNext(idx);

        else {
            if (idx != n)
                merge(idx);
            else
                merge(idx - 1);
        }
    }

    void borrowFromPrev(int idx) {
        BTreeNode *c = child[idx];
        BTreeNode *s = child[idx - 1];

        for (int i = c->n - 1; i >= 0; i--)
            c->keys[i + 1] = c->keys[i];

        if (!c->leaf) {
            for (int i = c->n; i >= 0; i--)
                c->child[i + 1] = c->child[i];
        }

        c->keys[0] = keys[idx - 1];

        if (!c->leaf)
            c->child[0] = s->child[s->n];

        keys[idx - 1] = s->keys[s->n - 1];

        c->n++;
        s->n--;
    }

    void borrowFromNext(int idx) {
        BTreeNode *c = child[idx];
        BTreeNode *s = child[idx + 1];

        c->keys[c->n] = keys[idx];

        if (!c->leaf)
            c->child[c->n + 1] = s->child[0];

        keys[idx] = s->keys[0];

        for (int i = 1; i < s->n; i++)
            s->keys[i - 1] = s->keys[i];

        if (!s->leaf) {
            for (int i = 1; i <= s->n; i++)
                s->child[i - 1] = s->child[i];
        }

        c->n++;
        s->n--;
    }

    void merge(int idx) {
        BTreeNode *c = child[idx];
        BTreeNode *s = child[idx + 1];

        c->keys[t - 1] = keys[idx];

        for (int i = 0; i < s->n; i++)
            c->keys[i + t] = s->keys[i];

        if (!c->leaf) {
            for (int i = 0; i <= s->n; i++)
                c->child[i + t] = s->child[i];
        }

        for (int i = idx + 1; i < n; i++)
            keys[i - 1] = keys[i];

        for (int i = idx + 2; i <= n; i++)
            child[i - 1] = child[i];

        c->n += s->n + 1;
        n--;

        delete s;
    }
};

class BTree {
    BTreeNode *root;
    int t;

public:
    BTree(int t) {
        root = NULL;
        this->t = t;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();

        cout << endl;
    }

    void search(int k) {
        if (root != NULL && root->search(k) != NULL)
            cout << "Key found\n";
        else
            cout << "Key not found\n";
    }

    void insert(int k) {
        if (root == NULL) {
            root = new BTreeNode(t, true);
            root->keys[0] = k;
            root->n = 1;
            return;
        }

        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);

            s->child[0] = root;
            s->splitChild(0, root);

            int i = 0;

            if (s->keys[0] < k)
                i++;

            s->child[i]->insertNonFull(k);

            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }

    void remove(int k) {
        if (root == NULL)
            return;

        root->remove(k);

        if (root->n == 0) {
            BTreeNode *tmp = root;

            if (root->leaf)
                root = NULL;
            else
                root = root->child[0];

            delete tmp;
        }
    }
};

int main() {
    int t, choice, key;

    cout << "Enter minimum degree: ";
    cin >> t;

    BTree tree(t);

    do {
        cout << "\n1. Insert";
        cout << "\n2. Search";
        cout << "\n3. Delete";
        cout << "\n4. Display";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                tree.insert(key);
                break;

            case 2:
                cout << "Enter key: ";
                cin >> key;
                tree.search(key);
                break;

            case 3:
                cout << "Enter key: ";
                cin >> key;
                tree.remove(key);
                break;

            case 4:
                cout << "B-Tree: ";
                tree.traverse();
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 5);

    return 0;
}
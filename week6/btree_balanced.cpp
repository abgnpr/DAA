/*

 * BALANCED BINARY TREE

 * Insert

 * Find

 * Min

 * Max

 * Pred

 * Succ

 * Delete

 * Traversal

*/

#include <cstdlib>
#include <stdexcept>

struct BTree
{
    int value, height;
    BTree *parent, *left, *right;
};

inline BTree*
newNode(int val,
        int height,
        BTree* parent = NULL,
        BTree* left = NULL,
        BTree* right = NULL)
{
    BTree* node = (BTree*)malloc(sizeof(BTree));

    node->value = val;
    node->height = height;

    node->parent = parent;
    node->left = left;
    node->right = right;

    return node;
}

void
updateHeights(BTree*& t)
{
    if (t != NULL) {
        if (t->parent == NULL)
            t->height = 0;
        else
            t->height = t->parent->height + 1;
        updateHeights(t->left);
        updateHeights(t->right);
    }
}

inline int
slope(BTree* t)
{
    return t->left->height - t->right->height;
}

inline void
rotateLeft(BTree*& t)
{
    int y, z;
    BTree *TLL, *TLRL, *TLRR;

    
}

inline void
rotateRight(BTree*& t)
{
    int x, y;
    BTree *TLL, *TLR, *TR;

    x = t->value;
    y = t->left->value;
    TLL = t->left->left;
    TLR = t->left->right;
    TR = t->right;

    // rotate
    t->value = y;
    t->right = t->left;
    t->right->value = x;
    t->left = TLL;
    t->right->left = TLR;
    t->right->right = TR;
}

void
rebalance(BTree*& t)
{
    if (slope(t) == 2) {
        if (slope(t->left) == -1)
            rotateLeft(t->left);
        rotateRight(t);
    }

    if (slope(t) == -2) {
        if (slope(t->right) == 1)
            rotateRight(t->right);
        rotateLeft(t);
    }
}

void
insert(BTree*& t, int val)
{
    if (t == NULL) {
        t = newNode(val, 0);
        return;
    }

    if (val == t->value)
        return;

    if (val < t->value) {
        if (t->left == NULL) {
            t->left = newNode(val, t->height + 1);
            t->left->parent = t;
            return;
        } else {
            insert(t->left, val);
        }
    } else { // val > t->value
        if (t->right == NULL) {
            t->right = newNode(val, t->height + 1);
            t->right->parent = t;
            return;
        } else {
            insert(t->right, val);
        }
    }
}

BTree* /* returns NULL if `val` not found */
find(BTree* t, int val)
{
    if (t == NULL)
        return NULL;

    if (val == t->value)
        return t;

    if (val < t->value)
        return find(t->left, val);
    else
        return find(t->right, val);
}

int
minval(BTree* t)
{
    if (t == NULL)
        throw std::invalid_argument("Empty B-Tree");

    /* // recursive solution
    else if (t->left == NULL)
        return t->value;
    else
        return minval(t->left); */

    // iterative
    while (t->left != NULL)
        t = t->left;

    return t->value;
}

int
maxval(BTree* t)
{
    if (t == NULL)
        throw std::invalid_argument("Empty B-Tree");

    while (t->right != NULL)
        t = t->right;

    return t->value;
}

int
succ(BTree* t)
{
    if (t == NULL)
        throw std::invalid_argument("Empty B-Tree");

    if (t->right != NULL)
        return minval(t->right);

    else {
        BTree* y = t->parent;
        // find where it turned right
        while (y != NULL && t == y->right) {
            t = y;
            y = y->parent;
        }
        return y->value;
    }
}

int
pred(BTree* t)
{
    if (t == NULL)
        throw std::invalid_argument("Empty B-Tree");

    if (t->left != NULL)
        return maxval(t->left);

    else {
        BTree* y = t->parent;
        // find where it turned left
        while (y != NULL && t == y->left) {
            t = y;
            y = y->left;
        }
        return y->value;
    }
}

void
del(BTree*& t, int val)
{
    BTree* toBeFreed = t;

    if (t == NULL)
        return;

    //--- when t.value != val

    if (val < t->value) {
        if (t->left != NULL)
            del(t->left, val);
        return;
    }

    if (val > t->value) {
        if (t->right != NULL)
            del(t->right, val);
        return;
    }

    /* when t.value == val */

    if (t->left == NULL && t->right == NULL) {

        //--- delete root
        if (t->parent == NULL)
            t = NULL;

        //--- delete leaf
        else if (t == t->parent->left)
            t->parent->left = NULL;
        else
            t->parent->right = NULL;

        free(toBeFreed);
        return;
    }

    /* delete node with one child */

    //--- only left child
    if (t->left != NULL && t->right == NULL) {
        t->left->parent = t->parent;
        if (t->parent == NULL) {
            t = t->left;
        } else if (t == t->parent->left)
            t->parent->left = t->left;
        else
            t->parent->right = t->left;
        updateHeights(t);
        free(toBeFreed);
        return;
    }
    //--- only right child
    else if (t->left == NULL && t->right != NULL) {
        t->right->parent = t->parent;
        if (t->parent == NULL) {
            t = t->right;
        } else if (t == t->parent->left)
            t->parent->left = t->right;
        else
            t->parent->right = t->right;
        updateHeights(t);
        free(toBeFreed);
        return;
    }

    /* delete node with two children */

    //--- copy pred(val) into current node
    int pv = pred(t);
    t->value = pv;

    //--- delete pv from left subtree
    //    pv : it is either a leaf or
    //         it has a single child
    del(t->left, pv);
}

void
inOrderTrav(BTree* t)
{
    if (t != NULL) {
        inOrderTrav(t->left);
        printf("\nval: %4d\theight: %4d", t->value, t->height);
        inOrderTrav(t->right);
    }
}

int
main()
{
    BTree *t = NULL, *t2 = NULL;

    // insert
    insert(t, 25);
    insert(t, 56);
    insert(t, 2);
    insert(t, 99);
    insert(t, -100);

    // traversal
    printf("\n");
    inOrderTrav(t);
    printf("\n");

    // find
    find(t, 100) ? printf("\nFound\n") : printf("\nNot Found\n");

    // minval and maxval
    printf("\nMinimum value : %d", minval(t));
    printf("\nMaximum value : %d", maxval(t));

    // succ and pred
    printf("\nSucc : %d", succ(t));
    printf("\nPred : %d", pred(t));
    // succ of a number
    printf("\nSucc of %d is %d", 2, succ(find(t, 2)));

    // delete
    // del(t, -100);
    // del(t, 99);
    del(t, 56);
    del(t, 2);
    del(t, 25);
    insert(t, -200);
    insert(t, -300);
    insert(t, -400);
    insert(t, -500);
    insert(t, -250);
    insert(t, 0);

    /// traversal
    printf("\n");
    inOrderTrav(t);
    printf("\n");

    /*
    for (int i = 0; i <= 5; ++i)
        insert(t2, i);

    // traversal
    printf("\n");
    inOrderTrav(t2);
    printf("\n");

    for (int i = 0; i <= 5; i += 2)
        del(t2, i);

    // traversal
    printf("\n");
    inOrderTrav(t2);
    printf("\n");
    */

    printf("\n");
    printf("\n");
    return EXIT_SUCCESS;
}

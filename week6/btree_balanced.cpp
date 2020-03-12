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

inline void
updateHeight(BTree*& t)
{
    if (!t->left && !t->right)
        t->height = 0;
    else if (t->left && t->right)
        t->height = 1 + std::max(t->left->height, t->right->height);
    else if (t->left && !t->right)
        t->height = t->left->height + 1;
    else if (!t->left && t->right)
        t->height = t->right->height + 1;
}

void
updateTreeHeights(BTree*& t)
{
    if (t != NULL) {
        // post-order
        updateTreeHeights(t->left);
        updateTreeHeights(t->right);
        updateHeight(t);
    }
}

inline int
slope(BTree* t)
{
    if (t == NULL)
        return 0;

    if (!t->left && !t->right)
        return 0;

    else if (!t->left && t->right)
        return -1 * t->height;

    else if (t->left && !t->right)
        return t->height;

    return t->left->height - t->right->height;
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
    if (TLL)
        TLL->parent = t;

    t->right->left = TLR;

    t->right->right = TR;
    if (TR)
        TR->parent = t->right;
}

inline void
rotateLeft(BTree*& t)
{
    int y, z;
    BTree *TL, *TRL, *TRR;

    y = t->value;
    z = t->right->value;
    TL = t->left;
    TRL = t->right->left;
    TRR = t->right->right;

    t->value = z;

    t->left = t->right;
    t->left->value = y;

    t->left->left = TL;
    if (TL)
        TL->parent = t->left;

    t->left->right = TRL;

    t->right = TRR;
    if (TRR)
        TRR->parent = t;
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

    if (val == t->value) {
        return;
    }

    if (val < t->value) {
        if (t->left == NULL) {
            t->left = newNode(val, 0);
            t->left->parent = t;
            updateTreeHeights(t);
            return;
        } else {
            insert(t->left, val);
            updateTreeHeights(t);
            rebalance(t);
            updateTreeHeights(t);
        }
    } else { // val > t->value
        if (t->right == NULL) {
            t->right = newNode(val, 0);
            t->right->parent = t;
            updateTreeHeights(t);
            return;
        } else {
            insert(t->right, val);
            updateTreeHeights(t);
            rebalance(t);
            updateTreeHeights(t);
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
    BTree* t_ = t; // t'

    if (t == NULL)
        return;

    //--- when t.value != val

    if (val < t->value) {
        if (t->left != NULL) {
            del(t->left, val);
            updateTreeHeights(t);
            rebalance(t);
            updateTreeHeights(t);
        }
        return;
    }

    else if (val > t->value) {
        if (t->right != NULL) {
            del(t->right, val);
            updateTreeHeights(t);
            rebalance(t);
            updateTreeHeights(t);
        }
        return;
    }

    /* when t.value == val */

    if (t->left == NULL && t->right == NULL) {

        //--- delete root
        if (t->parent == NULL)
            t = NULL;

        //--- delete leaf
        else if (t == t->parent->left) {
            t->parent->left = NULL;
        } else {
            t->parent->right = NULL;
        }

        free(t_);
        return;
    }

    /* delete node with one child */

    //--- only left child
    else if (t->left != NULL && t->right == NULL) {
        t->left->parent = t->parent;

        if (t->parent == NULL)
            t = t->left;
        else if (t == t->parent->left)
            t->parent->left = t->left;
        else
            t->parent->right = t->left;

        free(t_);
        return;
    }

    //--- only right child
    else if (t->left == NULL && t->right != NULL) {
        t->right->parent = t->parent;

        if (t->parent == NULL)
            t = t->right;
        else if (t == t->parent->left)
            t->parent->left = t->right;
        else
            t->parent->right = t->right;

        free(t_);
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
    updateTreeHeights(t);
    rebalance(t);
    updateTreeHeights(t);
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
    BTree* t = NULL;

    /*
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

        // traversal
        printf("\n");
        inOrderTrav(t);
        printf("\n");
    */

    /*
        for (int i = 0; i <= 1000; ++i)
            if (i % 2)
                insert(t, i);
        for (int i = 0; i <= 1000; ++i)
            if (i % 2 == 0)
                insert(t, i);

        for (int i = 1000; i >= 0; i--)
            del(t, i);
    */

    printf("\n");
    printf("\n");
    return EXIT_SUCCESS;
}

/*

 * BINARY Tree

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
    int value;
    BTree *parent, *left, *right;
};

BTree*
newNode(int val, BTree* parent = NULL, BTree* left = NULL, BTree* right = NULL)
{
    BTree* node = (BTree*)malloc(sizeof(BTree));

    node->value = val;
    node->parent = parent;
    node->left = left;
    node->right = right;

    return node;
}

void
insert(BTree*& t, int val)
{
    if (t == NULL) {
        t = newNode(val);
        return;
    }

    if (val == t->value)
        return;

    if (val < t->value) {
        if (t->left == NULL) {
            t->left = newNode(val);
            t->left->parent = t;
            return;
        } else {
            insert(t->left, val);
        }
    } else { // val > t->value
        if (t->right == NULL) {
            t->right = newNode(val);
            t->right->parent = t;
            return;
        } else {
            insert(t->right, val);
        }
    }
}

BTree* /* is NULL if `val` not found */
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
        printf("%d ", t->value);
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
    del(t, -100);
    del(t, 99);
    del(t, 56);
    del(t, 2);
    del(t, 25);

    /// traversal
    printf("\n");
    inOrderTrav(t);
    printf("\n");

/*
    for (int i = 0; i <= 5; ++i)
        insert(t2, i);

    for (int i = 0; i <= 5; i += 2)
        del(t2, i);

    /// traversal
    printf("\n");
    inOrderTrav(t2);
    printf("\n");
*/
    
    printf("\n");
    printf("\n");
    return EXIT_SUCCESS;
}
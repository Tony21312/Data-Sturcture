// xtree internal header
#define Red 0
#define Black 1
#ifndef XTREE
#define XTREE

template< typename Ty >
struct TreeNode
{
    using NodePtr = TreeNode*;
    using value_type = Ty;

    NodePtr    left;   // left subtree, or smallest element if head
    NodePtr    parent; // parent, or root of tree if head
    NodePtr    right;  // right subtree, or largest element if head
    char       color;  // 0: Red, 1: Black; Black if head
    char       isNil;  // 1 only if head (also nil) node
    value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
    using NodePtr = TreeNode< Ty >*;

    using value_type = Ty;
    using size_type = size_t;

    TreeVal()
        : myHead(new TreeNode< value_type >),
        mySize(0)
    {
        myHead->left = myHead;
        myHead->parent = myHead;
        myHead->right = myHead;
        myHead->color = 1;
        myHead->isNil = 1;
    }

    ~TreeVal()
    {
        clear(myHead->parent);
        delete myHead;
    }
    // Removes all elements from the set object (which are destroyed)
    void clear(TreeNode< value_type >* node)
    {
        if (!node->isNil) // node is not an external node
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // rebalance for insertion; u points to the inserted node
    void reBalance(TreeNode< value_type >* u)
    {  // u->parent cannot be the root
        TreeNode< value_type >* pu = u->parent;
        TreeNode< value_type >* gu = pu->parent;
        TreeNode< value_type >* uncle; // uncle of u

        uncle = (gu->left == pu) ? gu->right : gu->left;

        // if uncle is red,we only change color of gu and pu
        if (uncle->color == 0)
        {
            // if gu is the root, gu will not change color
            if (gu == myHead->parent)
            {
                pu->color = 1;
                uncle->color = 1;
            }
            else
            {
                gu->color = 0;
                pu->color = 1;
                uncle->color = 1;
                if (gu->parent->color == 0)
                    reBalance(gu);
            }
        }
        // if uncle is black, we need to change color and rotate
        else
        {
            if (gu->left == pu)
            {
                if (pu->left == u) // LLb
                {
                    gu->color = 0;
                    pu->color = 1;
                    LLRotation(pu);
                }
                else // LRb
                {
                    gu->color = 0;
                    u->color = 1;
                    LRRotation(u);
                }
            }
            else
            {
                if (pu->left == u) // RLb
                {
                    gu->color = 0;
                    u->color = 1;
                    RLRotation(u);
                }
                else // RRb
                {
                    gu->color = 0;
                    pu->color = 1;
                    RRRotation(pu);
                }
            }
        }
    }

    // rotate right at gu, where pu = gu->left and u = pu->left
    void LLRotation(TreeNode< value_type >* pu)
    {
        TreeNode< value_type >* gu = pu->parent;

        // when gu is root
        if (gu->parent == myHead)
            myHead->parent = pu;
        else
        {
            if (gu->parent->left == gu)
                gu->parent->left = pu;
            else
                gu->parent->right = pu;
        }
        pu->parent = gu->parent;
        gu->left = pu->right;

        // avoid myHead(pu->right)->parent point to gu
        if (pu->right != myHead)
            pu->right->parent = gu;

        gu->parent = pu;
        pu->right = gu;
    }

    // LR rotation; pu = gu->left and u = pu->right
    void LRRotation(TreeNode< value_type >* u)
    {
          TreeNode< value_type > *pu = u->parent;
          TreeNode< value_type > *gu = pu->parent;

          if (gu->parent == myHead)
              myHead->parent = u;
          else
          {
              if (gu->parent->left == gu)
                  gu->parent->left = u;
              else if(gu->parent->right == gu)
                  gu->parent->right = u;
          }
          u->parent = gu->parent;

          pu->right = u->left;
          if (u->left != myHead)
              u->left->parent = pu;

          gu->left = u->right;
          if (u->right != myHead)
              u->right->parent = gu;

          u->left = pu;
          pu->parent = u;

          u->right = gu;
          gu->parent = u;
    }

    // RL rotation; pu = gu->right and u = pu->left
    void RLRotation(TreeNode< value_type >* u)
    {
        TreeNode< value_type >* pu = u->parent;
        TreeNode< value_type >* gu = pu->parent;

        if (gu->parent == myHead)
            myHead->parent = u;
        else
        {
            if (gu->parent->left == gu)
                gu->parent->left = u;
            else
                gu->parent->right = u;
        }
        u->parent = gu->parent;

        gu->right = u->left;
        if (u->left != myHead)
            u->left->parent = gu;

        pu->left = u->right;
        if (u->right != myHead)
            u->right->parent = pu;

        u->left = gu;
        gu->parent = u;

        u->right = pu;
        pu->parent = u;
    }

    // rotate left at gu, where pu = gu->right and u = pu->right
    void RRRotation(TreeNode< value_type >* pu)
    {
        TreeNode< value_type >* gu = pu->parent;

        if (gu->parent == myHead)
            myHead->parent = pu;
        else
        {
            if (gu->parent->left == gu)
                gu->parent->left = pu;
            else
                gu->parent->right = pu;
        }
        pu->parent = gu->parent;

        gu->right = pu->left;
        // avoid myHead(pu->left)->parent point to gu
        if (pu->left != myHead)
            pu->left->parent = gu;

        gu->parent = pu;
        pu->left = gu;
    }

    // erase p provided that the degree of p is at most one
    // p points to the node to be deleted
    // p == M in "Ch 10 Sec 3.pptx"
    void eraseDegreeOne(TreeNode< value_type >* p)
    {
        TreeNode< value_type >* child;
        if (p->left != myHead)
            child = p->left;
        else if (p->right != myHead)
            child = p->right;
        else
            child = myHead;

        if (p == myHead->parent) // p points to the root; Case 3 in "Ch 10 Sec 3.pptx"
        {
            // set child to be the new root
            child->color = 1;
            myHead->parent = child;
            child->parent = myHead;
            if (myHead->left == p) myHead->left = child;
            if (myHead->right == p) myHead->right = child;
        }
        else // deal with Case 1¡B2¡B4
        {
            TreeNode< value_type >* pp = p->parent;

            if (pp->left == p)
                pp->left = child;
            else
                pp->right = child;

            if (child != myHead)
                child->parent = pp;

            if (myHead->left == p)
                myHead->left = child;
            if (myHead->right == p)
                myHead->right = child;

            if (p->color == 1)
                if (child->color == 0) // Case 2 in "Ch 10 Sec 3.pptx"
                    child->color = 1;
                else                   // Case 4 in "Ch 10 Sec 3.pptx"
                    fixUp(child, p->parent);
        }

        delete p;
        mySize--;
    }

    // rebalance for deletion; Case 4 in "Ch 10 Sec 3.pptx"
    void fixUp(TreeNode< value_type >* N, TreeNode< value_type >* P)
    {
        TreeNode<value_type>* S = (P->left == N) ? P->right : P->left;

        if (S->color == 0)
        {       
             if (P->left == N) // Case 4.1.1
             {
                 char color = P->color;
                 P->color = S->color;
                 S->color = color;
                 RRRotation(S);
                 fixUp(N, P);
             }
             else // Case 4.1.2
             {
                 char color = P->color;
                 P->color = S->color;
                 S->color = color;
                 LLRotation(S);
                 fixUp(N, P);
             }
        }
        else
        { 
            if (S->right->color == 1 && S->left->color == 1) // Case 4.4 and 4.5
            {
                if (P->color == 0) // Case 4.4
                {
                    P->color = 1;
                    S->color = 0;
                }
                else // Case 4.5
                {
                    S->color = 0;
                    if (P->parent != myHead)
                        fixUp(P, P->parent);
                }
            }
            else if (S->right->color == 0 && N == P->left) // Case 4.2.1
            {
                char color = P->color;
                P->color = S->color;
                S->color = color;
                S->right->color = 1;
                RRRotation(S);
            }
            else if (S->left->color == 0 && N == P->right) // Case4.2.2
            {
                char color = P->color;
                P->color = S->color;
                S->color = color;
                S->left->color = 1;
                LLRotation(S);
            }
            else if (S->right->color == 1 && N == P->left && S->left->color == 0) // Case 4.3.1
            {
                char color = S->left->color;
                S->left->color = S->color;
                S->color = color;

                LLRotation(S->left);
                fixUp(N, P);
            }
            else if (S->left->color == 1 && N == P->right && S->right->color == 0) // Case 4.3.2
            {
                char color = S->right->color;
                S->right->color = S->color;
                S->color = color;

                RRRotation(S->right);
                fixUp(N, P);
            }

        }

    }

    NodePtr myHead;   // pointer to head node
    size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
    using value_type = typename Traits::value_type;

protected:
    using ScaryVal = TreeVal< value_type >;

public:
    using key_type = typename Traits::key_type;
    using key_compare = typename Traits::key_compare;

    using size_type = size_t;

    Tree(const key_compare& parg)
        : keyCompare(parg),
        scaryVal()
    {
    }

    ~Tree()
    {
    }



    // Extends the container by inserting a new element,
    // effectively increasing the container size by one.
    void insert(const value_type& val)
    {
        if (scaryVal.mySize == 0)
        {
            TreeNode< value_type >* root = new TreeNode< value_type >;
            root->myval = val;
            root->left = scaryVal.myHead;
            root->right = scaryVal.myHead;
            root->isNil = 0;
            root->parent = scaryVal.myHead;
            root->color = 1;
            scaryVal.myHead->left = root;
            scaryVal.myHead->parent = root;
            scaryVal.myHead->right = root;
            scaryVal.mySize = 1;
        }
        else
        {                           // scaryVal.myHead->parent points to the root
            TreeNode< value_type >* p = scaryVal.myHead->parent; // p points to the root
            TreeNode< value_type >* pp = nullptr;
            while (p != scaryVal.myHead)
            {
                pp = p;
                //              keyCompare.operator()( val, p->myval )
                if (keyCompare(val, p->myval)) // if( val < p->myval )
                    p = p->left;
                else if (keyCompare(p->myval, val)) // if( val > p->myval )
                    p = p->right;
                else
                    return;
            }

            // init temp as a new node
            TreeNode<value_type>* temp = new TreeNode<value_type>();
            temp->color = 0;
            temp->isNil = 0;
            temp->myval = val;
            temp->parent = pp;
            temp->left = scaryVal.myHead;
            temp->right = scaryVal.myHead;
            scaryVal.mySize++;

            if (keyCompare(val, pp->myval))
            {
                pp->left = temp;
                if (keyCompare(val, scaryVal.myHead->left->myval))
                    scaryVal.myHead->left = temp;
            }
            else
            {
                pp->right = temp;
                if (keyCompare(scaryVal.myHead->right->myval, val))
                    scaryVal.myHead->right = temp;
            }
            if (pp->color == 0)
                scaryVal.reBalance(temp);
        }
    }

    // Removes from the set container a single element whose value is val
    // This effectively reduces the container size by one, which are destroyed.
    // Returns the number of elements erased.
    size_type erase(const key_type& val)
    {
        TreeNode< key_type >* p = scaryVal.myHead->parent; // p points to the root
        while (p != scaryVal.myHead && val != p->myval)
        {
            //           keyCompare.operator()( val, p->myval )
            if (keyCompare(val, p->myval)) // if( val < p->myval )
                p = p->left;
            else
                p = p->right;
        }

        if (p == scaryVal.myHead) // not found
            return 0;
        else // found
        {  // deletes the node pointed by p

            TreeNode<value_type>* it1 = p;
            TreeNode<value_type>* it2 = p->right;

            while (it2 != scaryVal.myHead)
            {
                it1 = it2;
                it2 = it2->left;
            }
            p->myval = it1->myval;

            bool left = 0, right = 0;
            if (scaryVal.myHead->left == it1)
                left = 1;
            if (scaryVal.myHead->right == it1)
                right = 1;
            p->myval = it1->myval;

            scaryVal.eraseDegreeOne(it1);
            if (left)
            {
                TreeNode<value_type>* pu = scaryVal.myHead;
                TreeNode<value_type>* u = scaryVal.myHead->parent;
                while (u != scaryVal.myHead)
                {
                    pu = u;
                    u = u->left;
                }
                scaryVal.myHead->left = pu;
            }
            if (right)
            {
                TreeNode<value_type>* pu = scaryVal.myHead;
                TreeNode<value_type>* u = scaryVal.myHead->parent;
                while (u != scaryVal.myHead)
                {
                    pu = u;
                    u = u->right;
                }
                scaryVal.myHead->right = pu;
            }

            return 1;
        }

    }

private:
    key_compare keyCompare;
    ScaryVal scaryVal;
};

#endif // XTREE
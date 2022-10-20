// xtree internal header

#ifndef XTREE
#define XTREE

template< typename Ty >
struct TreeNode
{
   using NodePtr = TreeNode *;
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
   using NodePtr = TreeNode< Ty > *;

   using value_type = Ty;
   using size_type  = size_t;

   TreeVal()
      : myHead( new TreeNode< value_type > ),
        mySize( 0 )
   {
      myHead->left = myHead;
      myHead->parent = myHead;
      myHead->right = myHead;
      myHead->color = 1;
      myHead->isNil = 1;
   }

   ~TreeVal()
   {
      clear( myHead->parent );
      delete myHead;
   }

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< value_type > *node )
   {
      if( !node->isNil ) // node is not an external node
      {
         clear( node->left );
         clear( node->right );
         delete node;
      }
   }

   // rebalance for insertion; u points to the inserted node
   void reBalance( TreeNode< value_type > *u )
   {  // u->parent cannot be the root
      TreeNode< value_type > *pu = u->parent;
      TreeNode< value_type > *gu = pu->parent;
      TreeNode< value_type > *uncle; // uncle of u

      uncle = (gu->left == pu) ? gu->right : gu->left;
      if (uncle->color == 0)
      {
          if (gu != myHead->parent)
              gu->color = 0;
          pu->color = 1;
          uncle->color = 1;
          if (gu->parent->color == 0)
              reBalance(gu);
      }
      else
      {
          gu->color = 0;
          pu->color = 1;
          if (gu->left == pu && pu->left == u)
              LLRotation(pu);
          else if (gu->right == pu && pu->right == u)
              RRRotation(pu);
      }
   }

   // rotate right at gu, where pu = gu->left and u = pu->left
   void LLRotation( TreeNode< value_type > *pu )
   {
      TreeNode< value_type > *gu = pu->parent;

      if (gu->parent == myHead)
          myHead->parent = pu;
      else
          ((gu->parent->left == gu) ? gu->parent->left : gu->parent->right) = pu;
      pu->parent = gu->parent;

      gu->left = pu->right;
      if (pu->right != myHead)
          pu->right->parent = gu;
      pu->right = gu;
      gu->parent = pu;
   }

   // rotate left at gu, where pu = gu->right and u = pu->right
   void RRRotation( TreeNode< value_type > *pu )
   {
      TreeNode< value_type > *gu = pu->parent;

      if (gu->parent == myHead)
          myHead->parent = pu;
      else
          ((gu->parent->left == gu) ? gu->parent->left : gu->parent->right) = pu;
      pu->parent = gu->parent;

      gu->right = pu->left;
      if (pu->left != myHead)
          pu->left->parent = gu;
      pu->left = gu;
      gu->parent = pu;
   }

   // erase p provided that the degree of p is at most one
   // p points to the node to be deleted
   // p == M in "Ch 10 Sec 3.pptx"
   void eraseDegreeOne( TreeNode< value_type > *p )
   {
      TreeNode< value_type > *child;
      if( p->left != myHead )
         child = p->left;
      else if( p->right != myHead )
         child = p->right;
      else
         child = myHead;

      if( p == myHead->parent ) // p points to the root; Cases 2 & 3 in "Ch 10 Sec 3.pptx"
      {
         // set child to be the new root
          child->color = 1;
          myHead->parent = child;
          child->parent = myHead;
          myHead->right = child;
          myHead->left = child;
      }
      else
      {
         TreeNode< value_type > *pp = p->parent;

         ((pp->left == p) ? pp->left : pp->right) = child;
         if (child != myHead)
             child->parent = pp;

         if( p->color == 1 ) 
            if( child->color == 0 ) // Case 2 in "Ch 10 Sec 3.pptx"
               child->color = 1;
            else                   // Case 4 in "Ch 10 Sec 3.pptx"
               fixUp( child, p->parent );
      }

      delete p;
      mySize--;
   }

   // rebalance for deletion;  // Case 4 in "Ch 10 Sec 3.pptx"
   void fixUp(TreeNode< value_type >* N, TreeNode< value_type >* P)
   {
       TreeNode< value_type >* S = (P->left == N) ? P->right : P->left;
       if (S->color == 1)
       {
           if (N == P->left)
           {
               if (S->right->color == 0)
               {
                   char color = P->color;
                   P->color = S->color;
                   S->color = color;
                   S->right->color = 1;
                   RRRotation(S);
               }
               else if (S->left->color == 1 && S->right->color == 1 && P->color == 0)
               {
                   char color = P->color;
                   P->color = S->color;
                   S->color = color;
               }
           }
           else if(N == P->right)
           {
               if (S->left->color == 0)
               {
                   char color = P->color;
                   P->color = S->color;
                   S->color = color;
                   S->left->color = 1;
                   LLRotation(S);
               }
               else if (S->left->color == 1 && S->right->color == 1 && P->color == 0)
               {
                   char color = P->color;
                   P->color = S->color;
                   S->color = color;
               }
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
   using key_type      = typename Traits::key_type;
   using key_compare   = typename Traits::key_compare;

   using size_type       = size_t;

   Tree( const key_compare &parg )
      : keyCompare( parg ),
        scaryVal()
   {
   }

   ~Tree()
   {
   }

   // Extends the container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const value_type &val )
   {
      if( scaryVal.mySize == 0 )
      {
         TreeNode< value_type > *root = new TreeNode< value_type >;
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
         TreeNode< value_type > *p = scaryVal.myHead->parent; // p points to the root
         TreeNode< value_type > *pp = nullptr;
         while( p != scaryVal.myHead )
         {
            pp = p;
            if( keyCompare( val, p->myval ) ) // if( val < p->myval )
               p = p->left;
            else if( keyCompare( p->myval, val ) ) // if( val > p->myval )
               p = p->right;
            else
               return;
         }
         p = new TreeNode< value_type >();
         p->color = 0;
         p->isNil = 0;
         p->left = p->right = scaryVal.myHead;
         p->myval = val;
         p->parent = pp;
         scaryVal.mySize++;
         if (keyCompare(val, pp->myval))
         {
             pp->left = p;
             if (keyCompare(val, scaryVal.myHead->left->myval))
                 scaryVal.myHead->left = p;
         }    
         if(keyCompare(pp->myval, val))
         {
             pp->right = p;
             if (keyCompare(scaryVal.myHead->right->myval, val))
                 scaryVal.myHead->right = p;
         }

         if( pp->color == 0 ) // pp cannot be the root
            scaryVal.reBalance( p );
      }
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
      TreeNode< key_type > *p = scaryVal.myHead->parent; // p points to the root
      while( p != scaryVal.myHead && val != p->myval )
      {
         if( keyCompare( val, p->myval ) ) // if( val < p->myval )
            p = p->left;
         else
            p = p->right;
      }

      if( p == scaryVal.myHead ) // not found
         return 0;
      else // found
      {  // deletes the node pointed by p
          TreeNode< value_type >* it1 = p;
          TreeNode< value_type >* it2 = p->right;
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
          scaryVal.eraseDegreeOne(it1);

          if (left)
          {
              it1 = scaryVal.myHead;
              it2 = scaryVal.myHead->parent;
              while (it2 != scaryVal.myHead)
              {
                  it1 = it2;
                  it2 = it2->left;
              }
              scaryVal.myHead->left = it1;
          }
          if (right)
          {
              it1 = scaryVal.myHead;
              it2 = scaryVal.myHead->parent;
              while (it2 != scaryVal.myHead)
              {
                  it1 = it2;
                  it2 = it2->right;
              }
              scaryVal.myHead->right = it1;
          }
         return 1;
      }
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE
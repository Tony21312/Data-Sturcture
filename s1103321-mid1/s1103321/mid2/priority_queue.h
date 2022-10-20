// priority_queue class definition.

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "xstddef.h"
#include "algorithm - s1103321 - mid.h"
//#include "vector.h"

#include <vector>
using std::vector;

// CLASS TEMPLATE priority_queue
template< typename Ty,
          typename Container = vector< Ty >,
          typename Pr = less< typename Container::value_type > >
class priority_queue
{
public:
   using value_type = typename Container::value_type;
   using const_reference = typename Container::const_reference;
   using size_type = typename Container::size_type;

   // Explicitly defaulted default constructor
   priority_queue() = default;

   // Returns whether the priority_queue is empty: i.e. whether its size is zero.
   bool empty() const
   {
      return c.empty();
   }

   // Returns the number of elements in the priority_queue.
   size_type size() const
   {
      return c.size();
   }

   // Returns a constant reference to the top element in the priority_queue.
   // The top element is the element that compares higher in the priority_queue,
   // and the next that is removed from the container when priority_queue::pop is called.
   const_reference top() const
   {
      return c.front();
   }

   // Inserts a new element in the priority_queue.
   // The content of this new element is initialized to val.
   // This member function effectively calls the member function push_back
   // of the underlying container object,
   // and then reorders it to its location in the heap by calling the push_heap algorithm
   // on the range that includes all the elements of the container.
   void push( const value_type &val )
   {
      c.push_back( val );
      MyNamespace::push_heap( c.begin(), c.end(), comp );
   }

protected:
   Container c{};
   Pr comp{};
};

#endif
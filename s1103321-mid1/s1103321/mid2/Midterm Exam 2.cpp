// testing priority queues

#include <iostream>
using std::cout;
using std::endl;

//#include "deque.h"

#include <queue>
using std::deque;

#include "priority_queue.h"

template< typename T >
void testPriorityQueue();

template< typename T, typename T1, typename T2, typename T3 = less< T >,
                                             typename T4 = std::less< T > >
void testPush();

template< typename T1, typename T2 >
bool equal( T1 &v1, T2 &v2 );

int main()
{
   testPriorityQueue< char >();
   testPriorityQueue< short >();
   testPriorityQueue< long >();
   testPriorityQueue< long long >();

   system( "pause" );
}

template< typename T >
void testPriorityQueue()
{
   testPush< T, vector< T >, std::vector< T > >();
   testPush< T, vector< T >, std::vector< T >, greater< T >, std::greater< T > >();

   testPush< T, deque< T >, std::deque< T > >();
   testPush< T, deque< T >, std::deque< T >, greater< T >, std::greater< T > >();

   cout << endl;
}

template< typename T, typename T1, typename T2, typename T3, typename T4 >
void testPush()
{
   int num = 500;
   int numErrors = num;

   priority_queue< T, T1, T3 > pq1;
   std::priority_queue< T, T2, T4 > pq2;
   T1 v1;
   T2 v2;

   for( int i = 0; i < num; i++ )
   {
      T value = 1 + rand() % 99;
      pq1.push( value );
      pq2.push( value );

      v1 = *( reinterpret_cast< T1 * >( &pq1 ) );
      v2 = *( reinterpret_cast< T2 * >( &pq2 ) );

      if( equal( v1, v2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T1, typename T2 >
bool equal( T1 &v1, T2 &v2 )
{
   if( v1.size() != v2.size() )
      return false;

   for( unsigned int i = 0; i < v1.size(); i++ )
      if( v1[ i ] != v2[ i ] )
         return false;

   return true;
}
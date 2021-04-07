//---------------------------------------------------------------------------//
//!
//! \file   tstIteratorTypeTraits.cpp
//! \author Alex Robinson
//! \brief  Iterator type traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <type_traits>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

// FRENSIE Includes
#include "Utility_IteratorTypeTraits.hpp"

//---------------------------------------------------------------------------//
// Template Typedefs
//---------------------------------------------------------------------------//
typedef boost::mpl::list<bool,bool*,
                         char,char*,
                         signed char,signed char*,
                         unsigned char,unsigned char*,
                         short,short*,
                         unsigned short,
                         int,
                         unsigned,
                         long,
                         unsigned long,
                         long long,
                         unsigned long long,
                         float,
                         double,
                         std::string> TestTypes;

typedef boost::mpl::list<std::pair<bool,bool>,
                         std::pair<bool*,bool*>,
                         std::pair<char,char>,
                         std::pair<char*,char*>,
                         std::pair<signed char,signed char>,
                         std::pair<signed char*,signed char*>,
                         std::pair<unsigned char,unsigned char>,
                         std::pair<unsigned char*,unsigned char*>,
                         std::pair<short,short>,
                         std::pair<unsigned short,unsigned short>,
                         std::pair<int,int>,
                         std::pair<unsigned,unsigned>,
                         std::pair<long,long>,
                         std::pair<unsigned long,unsigned long>,
                         std::pair<long long,long long>,
                         std::pair<unsigned long long,unsigned long long>,
                         std::pair<float,float>,
                         std::pair<double,double>,
                         std::pair<std::string,std::string>,
                         std::pair<int,std::pair<int,double> > > TestTypePairs;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a std::string iterator is a const iterator
BOOST_AUTO_TEST_CASE( string_IsConstIterator )
{
  BOOST_CHECK( !Utility::IsConstIterator<std::string::iterator>::value );
  BOOST_CHECK( Utility::IsConstIterator<std::string::const_iterator>::value );
  BOOST_CHECK( !Utility::IsConstIterator<std::string::reverse_iterator>::value );
  BOOST_CHECK( Utility::IsConstIterator<std::string::const_reverse_iterator>::value );
}

//---------------------------------------------------------------------------//
// Check if std::string iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE( string_ConstIterator )
{
  BOOST_CHECK( (std::is_same<Utility::ConstIterator<std::string::iterator>::type,std::string::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<Utility::ConstIterator<std::string::const_iterator>::type,std::string::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<Utility::ConstIterator<std::string::reverse_iterator>::type,std::string::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<Utility::ConstIterator<std::string::const_reverse_iterator>::type,std::string::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::string const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE( string_NonConstIterator )
{
  BOOST_CHECK( (std::is_same<Utility::NonConstIterator<std::string::iterator>::type,std::string::iterator>::value) );
  BOOST_CHECK( (std::is_same<Utility::NonConstIterator<std::string::const_iterator>::type,std::string::iterator>::value) );
  BOOST_CHECK( (std::is_same<Utility::NonConstIterator<std::string::reverse_iterator>::type,std::string::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<Utility::NonConstIterator<std::string::const_reverse_iterator>::type,std::string::reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::array iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( array_IsConstIterator, T, TestTypes )
{
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::array<T,1>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::array<T,1>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::array<T,1>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::array<T,1>::const_reverse_iterator>::value) );

  BOOST_CHECK( !(Utility::IsConstIterator<typename std::array<T,10>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::array<T,10>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::array<T,10>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::array<T,10>::const_reverse_iterator>::value) );

  BOOST_CHECK( !(Utility::IsConstIterator<typename std::array<T,100>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::array<T,100>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::array<T,100>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::array<T,100>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::array iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( array_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::iterator>::type,typename std::array<T,1>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::const_iterator>::type,typename std::array<T,1>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::reverse_iterator>::type,typename std::array<T,1>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,1>::const_reverse_iterator>::type,typename std::array<T,1>::const_reverse_iterator>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::iterator>::type,typename std::array<T,10>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::const_iterator>::type,typename std::array<T,10>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::reverse_iterator>::type,typename std::array<T,10>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,10>::const_reverse_iterator>::type,typename std::array<T,10>::const_reverse_iterator>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::iterator>::type,typename std::array<T,100>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::const_iterator>::type,typename std::array<T,100>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::reverse_iterator>::type,typename std::array<T,100>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::array<T,100>::const_reverse_iterator>::type,typename std::array<T,100>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::array const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( array_NonConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::iterator>::type,typename std::array<T,1>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::const_iterator>::type,typename std::array<T,1>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::reverse_iterator>::type,typename std::array<T,1>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,1>::const_reverse_iterator>::type,typename std::array<T,1>::reverse_iterator>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::iterator>::type,typename std::array<T,10>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::const_iterator>::type,typename std::array<T,10>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::reverse_iterator>::type,typename std::array<T,10>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,10>::const_reverse_iterator>::type,typename std::array<T,10>::reverse_iterator>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::iterator>::type,typename std::array<T,100>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::const_iterator>::type,typename std::array<T,100>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::reverse_iterator>::type,typename std::array<T,100>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::array<T,100>::const_reverse_iterator>::type,typename std::array<T,100>::reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::vector iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( vector_IsConstIterator, T, TestTypes )
{

  BOOST_CHECK( !(Utility::IsConstIterator<typename std::vector<T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::vector<T>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::vector<T>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::vector<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::vector iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( vector_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::iterator>::type,typename std::vector<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::const_iterator>::type,typename std::vector<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::reverse_iterator>::type,typename std::vector<T>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::vector<T>::const_reverse_iterator>::type,typename std::vector<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::vector const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( vector_NonConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::iterator>::type,typename std::vector<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::const_iterator>::type,typename std::vector<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::reverse_iterator>::type,typename std::vector<T>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::vector<T>::const_reverse_iterator>::type,typename std::vector<T>::reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::list iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( list_IsConstIterator, T, TestTypes )
{

  BOOST_CHECK( !(Utility::IsConstIterator<typename std::list<T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::list<T>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::list<T>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::list<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::list iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( list_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::iterator>::type,typename std::list<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::const_iterator>::type,typename std::list<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::reverse_iterator>::type,typename std::list<T>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::list<T>::const_reverse_iterator>::type,typename std::list<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::list const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( list_NonConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::iterator>::type,typename std::list<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::const_iterator>::type,typename std::list<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::reverse_iterator>::type,typename std::list<T>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::list<T>::const_reverse_iterator>::type,typename std::list<T>::reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::forward_list iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( forward_list_IsConstIterator, T, TestTypes )
{
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::forward_list<T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::forward_list<T>::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::forward_list iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( forward_list_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::forward_list<T>::iterator>::type,typename std::forward_list<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::forward_list<T>::const_iterator>::type,typename std::forward_list<T>::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::forward_list const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( forward_list_NonConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::forward_list<T>::iterator>::type,typename std::forward_list<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::forward_list<T>::const_iterator>::type,typename std::forward_list<T>::iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::deque iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( deque_IsConstIterator, T, TestTypes )
{
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::deque<T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::deque<T>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::deque<T>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::deque<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::deque iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( deque_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::iterator>::type,typename std::deque<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::const_iterator>::type,typename std::deque<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::reverse_iterator>::type,typename std::deque<T>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::deque<T>::const_reverse_iterator>::type,typename std::deque<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::deque const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( deque_NonConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::iterator>::type,typename std::deque<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::const_iterator>::type,typename std::deque<T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::reverse_iterator>::type,typename std::deque<T>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::deque<T>::const_reverse_iterator>::type,typename std::deque<T>::reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::set iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( set_IsConstIterator, T, TestTypes )
{
  // std::set only provides a const iterator type
  BOOST_CHECK( (Utility::IsConstIterator<typename std::set<T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::set<T>::const_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::set<T>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::set<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::set iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( set_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::iterator>::type,typename std::set<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::const_iterator>::type,typename std::set<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::reverse_iterator>::type,typename std::set<T>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::set<T>::const_reverse_iterator>::type,typename std::set<T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::unordered_set iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( unordered_set_IsConstIterator, T, TestTypes )
{
  // std::unordered_set only provides a const iterator type
  BOOST_CHECK( (Utility::IsConstIterator<typename std::unordered_set<T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::unordered_set<T>::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::unordered_set iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( unordered_set_ConstIterator, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::unordered_set<T>::iterator>::type,typename std::unordered_set<T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::unordered_set<T>::const_iterator>::type,typename std::unordered_set<T>::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if a std::map iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( IteratorTypeTraits, KeyValuePair, TestTypePairs )
{
  typedef typename std::tuple_element<0,KeyValuePair>::type Key;
  typedef typename std::tuple_element<1,KeyValuePair>::type T;
  
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::map<Key,T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::map<Key,T>::const_iterator>::value) );
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::map<Key,T>::reverse_iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::map<Key,T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::map iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( map_ConstIterator, KeyValuePair, TestTypePairs )
{
  typedef typename std::tuple_element<0,KeyValuePair>::type Key;
  typedef typename std::tuple_element<1,KeyValuePair>::type T;
  
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::iterator>::type,typename std::map<Key,T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::const_iterator>::type,typename std::map<Key,T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::reverse_iterator>::type,typename std::map<Key,T>::const_reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::map<Key,T>::const_reverse_iterator>::type,typename std::map<Key,T>::const_reverse_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::map const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( map_NonConstIterator, KeyValuePair, TestTypePairs )
{
  typedef typename std::tuple_element<0,KeyValuePair>::type Key;
  typedef typename std::tuple_element<1,KeyValuePair>::type T;
  
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::iterator>::type,typename std::map<Key,T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::const_iterator>::type,typename std::map<Key,T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::reverse_iterator>::type,typename std::map<Key,T>::reverse_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::map<Key,T>::const_reverse_iterator>::type,typename std::map<Key,T>::reverse_iterator>::value) );
}


//---------------------------------------------------------------------------//
// Check if a std::unordered_map iterator is a const iterator
BOOST_AUTO_TEST_CASE_TEMPLATE( unordered_map_IsConstIterator, KeyValuePair, TestTypePairs )
{
  typedef typename std::tuple_element<0,KeyValuePair>::type Key;
  typedef typename std::tuple_element<1,KeyValuePair>::type T;
  
  BOOST_CHECK( !(Utility::IsConstIterator<typename std::unordered_map<Key,T>::iterator>::value) );
  BOOST_CHECK( (Utility::IsConstIterator<typename std::unordered_map<Key,T>::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::unordered_map iterator types can be converted to const iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( unordered_map_ConstIterator, KeyValuePair, TestTypePairs )
{
  typedef typename std::tuple_element<0,KeyValuePair>::type Key;
  typedef typename std::tuple_element<1,KeyValuePair>::type T;
  
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::unordered_map<Key,T>::iterator>::type,typename std::unordered_map<Key,T>::const_iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::ConstIterator<typename std::unordered_map<Key,T>::const_iterator>::type,typename std::unordered_map<Key,T>::const_iterator>::value) );
}

//---------------------------------------------------------------------------//
// Check if std::unordered_map const iterator types can be converted to non-const
// iterator types
BOOST_AUTO_TEST_CASE_TEMPLATE( unordered_map_NonConstIterator, KeyValuePair, TestTypePairs )
{
  typedef typename std::tuple_element<0,KeyValuePair>::type Key;
  typedef typename std::tuple_element<1,KeyValuePair>::type T;
  
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::unordered_map<Key,T>::iterator>::type,typename std::unordered_map<Key,T>::iterator>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::NonConstIterator<typename std::unordered_map<Key,T>::const_iterator>::type,typename std::unordered_map<Key,T>::iterator>::value) );
}

//---------------------------------------------------------------------------//
// end tstIteratorTypeTraits.cpp
//---------------------------------------------------------------------------//

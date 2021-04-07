//---------------------------------------------------------------------------//
//!
//! \file   tstArrayView.cpp
//! \author Alex Robinson
//! \brief  ArrayView unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <type_traits>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/insert_range.hpp>

// FRENSIE Includes
#include "Utility_ArrayView.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<char,signed char,unsigned char,short,unsigned short,int,unsigned int,long,unsigned long,long long,unsigned long long,float,double> TestTypes;

template<typename Policy>
struct TypeList
{
  typedef boost::mpl::list<std::tuple<Policy,char>,std::tuple<Policy,signed char>,std::tuple<Policy,unsigned char>,std::tuple<Policy,short>,std::tuple<Policy,unsigned short>,std::tuple<Policy,int>,std::tuple<Policy,unsigned int>,std::tuple<Policy,long>,std::tuple<Policy,unsigned long>,std::tuple<Policy,long long>,std::tuple<Policy,unsigned long long>,std::tuple<Policy,float>,std::tuple<Policy,double> > type;
};

template<typename... TypeLists>
struct MergeTypeLists
{ /* ... */ };

template<typename FrontList, typename... TypeLists>
struct MergeTypeLists<FrontList,TypeLists...>
{
private:
  typedef typename MergeTypeLists<TypeLists...>::type BackMergedListType;

public:
  typedef typename boost::mpl::insert_range<FrontList,typename boost::mpl::end<FrontList>::type,BackMergedListType>::type type;
};

template<typename FrontList>
struct MergeTypeLists<FrontList>
{ 
  typedef FrontList type;
};

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type, typename TypeList<Utility::CloseComparisonPolicy>::type, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type, typename TypeList<Utility::InequalityComparisonPolicy>::type>::type TestPolicyTypes;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an array view is a container with contiguous memory
BOOST_AUTO_TEST_CASE_TEMPLATE( IsSequenceContainerWithContiguousMemory, T, TestTypes )
{
  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<Utility::ArrayView<T> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::ArrayView<T>*>::value );
  
  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<Utility::ArrayView<const T> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<Utility::ArrayView<const T>*>::value );

  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<const Utility::ArrayView<T> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::ArrayView<T>*>::value );

  BOOST_CHECK( Utility::IsSequenceContainerWithContiguousMemory<const Utility::ArrayView<const T> >::value );
  BOOST_CHECK( !Utility::IsSequenceContainerWithContiguousMemory<const Utility::ArrayView<const T>*>::value );
}

//---------------------------------------------------------------------------//
// Check that an array view can be constructed
BOOST_AUTO_TEST_CASE_TEMPLATE( default_constructor, T, TestTypes )
{
  Utility::ArrayView<T> view;

  BOOST_CHECK_EQUAL( view.size(), 0 );
  BOOST_CHECK( view.empty() );

  Utility::ArrayView<const T> view_of_const;

  BOOST_CHECK_EQUAL( view_of_const.size(), 0 );
  BOOST_CHECK( view_of_const.empty() );
}

//---------------------------------------------------------------------------//
// Check that an array view can be constructed from iterators
BOOST_AUTO_TEST_CASE_TEMPLATE( iterator_constructor, T, TestTypes )
{
  std::vector<T> container( 10, T() );

  Utility::ArrayView<T> view( container.data(), container.data()+10 );

  BOOST_CHECK_EQUAL( view.size(), 10 );
  BOOST_CHECK( !view.empty() );

  {
    Utility::ArrayView<const T>
      view_of_const( container.data(), container.data()+10 );

    BOOST_CHECK_EQUAL( view_of_const.size(), 10 );
    BOOST_CHECK( !view_of_const.empty() );
  }

  {
    Utility::ArrayView<const T>
      view_of_const( (const T*)container.data(),
                     (const T*)(container.data()+10) );

    BOOST_CHECK_EQUAL( view_of_const.size(), 10 );
    BOOST_CHECK( !view_of_const.empty() );
  }
}

//---------------------------------------------------------------------------//
// Check that an array view can be constructed from a range
BOOST_AUTO_TEST_CASE_TEMPLATE( range_constructor, T, TestTypes )
{
  std::vector<T> container( 10, T() );

  Utility::ArrayView<T> view( container.data(), 10 );

  BOOST_CHECK_EQUAL( view.size(), 10 );
  BOOST_CHECK( !view.empty() );

  {
    Utility::ArrayView<const T>
      view_of_const( container.data(), 10 );

    BOOST_CHECK_EQUAL( view_of_const.size(), 10 );
    BOOST_CHECK( !view_of_const.empty() );
  }

  {
    Utility::ArrayView<const T>
      view_of_const( (const T*)container.data(), 10 );

    BOOST_CHECK_EQUAL( view_of_const.size(), 10 );
    BOOST_CHECK( !view_of_const.empty() );
  }
}

//---------------------------------------------------------------------------//
// Check that an array view can be constructed from containers
BOOST_AUTO_TEST_CASE_TEMPLATE( container_constructor, T, TestTypes )
{
  std::vector<T> vector( 10, T() );

  {
    Utility::ArrayView<T> view( vector );

    BOOST_CHECK_EQUAL( view.size(), 10 );
    BOOST_CHECK( !view.empty() );

    Utility::ArrayView<const T> view_of_const( vector );

    BOOST_CHECK_EQUAL( view_of_const.size(), 10 );
    BOOST_CHECK( !view_of_const.empty() );
  }

  std::array<T,10> array;

  {
    Utility::ArrayView<T> view( array );

    BOOST_CHECK_EQUAL( view.size(), 10 );
    BOOST_CHECK( !view.empty() );

    Utility::ArrayView<const T> view_of_const( array );

    BOOST_CHECK_EQUAL( view_of_const.size(), 10 );
    BOOST_CHECK( !view_of_const.empty() );
  }
}

//---------------------------------------------------------------------------//
// Check the copy constructor
BOOST_AUTO_TEST_CASE_TEMPLATE( copy_constructor, T, TestTypes )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  Utility::ArrayView<const T> view_of_const( container );

  {
    Utility::ArrayView<T> view_copy( view );

    BOOST_CHECK_EQUAL( view_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy( view );

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy( view_of_const );

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view_of_const.size() );
  }
}

//---------------------------------------------------------------------------//
// Check the assignment operator
BOOST_AUTO_TEST_CASE_TEMPLATE( assignment_operator, T, TestTypes )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  Utility::ArrayView<const T> view_of_const( container );

  {
    Utility::ArrayView<T> view_copy = view;

    BOOST_CHECK_EQUAL( view_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy = view;

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view.size() );
  }

  {
    Utility::ArrayView<const T> view_of_const_copy = view_of_const;

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view_of_const.size() );
  }
}

//---------------------------------------------------------------------------//
// Check that array view iterators can be acquired
BOOST_AUTO_TEST_CASE_TEMPLATE( iterator, T, TestTypes )
{
  std::array<T,10> container;

  Utility::ArrayView<T> view( container );

  BOOST_CHECK_EQUAL( view.begin(), container.begin() );
  BOOST_CHECK_EQUAL( std::distance( view.begin(), view.end() ), 10 );
  BOOST_CHECK_EQUAL( view.cbegin(), container.cbegin() );
  BOOST_CHECK_EQUAL( std::distance( view.cbegin(), view.cend() ), 10 );

  Utility::ArrayView<const T> view_of_const( container );

  BOOST_CHECK_EQUAL( view_of_const.begin(), container.cbegin() );
  BOOST_CHECK_EQUAL( std::distance( view_of_const.begin(), view_of_const.cend() ), 10 );
  BOOST_CHECK_EQUAL( view_of_const.cbegin(), container.cbegin() );
  BOOST_CHECK_EQUAL( std::distance( view_of_const.cbegin(), view_of_const.cend() ), 10 );
}

//---------------------------------------------------------------------------//
// Check that array view elements can be accessed
BOOST_AUTO_TEST_CASE_TEMPLATE( element_access, T, TestTypes )
{
  std::array<T,2> container( {0, 1} );

  Utility::ArrayView<T> view( container );

  BOOST_CHECK_EQUAL( view[0], 0 );
  BOOST_CHECK_EQUAL( view[1], 1 );
  BOOST_CHECK_EQUAL( view.at(0), 0 );
  BOOST_CHECK_EQUAL( view.at(1), 1 );
  BOOST_CHECK_EQUAL( view.front(), 0 );
  BOOST_CHECK_EQUAL( view.back(), 1 );

  view[0] = 1;
  view[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( view.at(0), 1 );
  BOOST_CHECK_EQUAL( view.at(1), 0 );
  BOOST_CHECK_EQUAL( view.front(), 1 );
  BOOST_CHECK_EQUAL( view.back(), 0 );

  Utility::ArrayView<T> partial_view = view( 1, 1 );

  BOOST_CHECK_EQUAL( partial_view[0], 0 );
  BOOST_CHECK_EQUAL( partial_view.at(0), 0 );
  BOOST_CHECK_EQUAL( partial_view.front(), 0 );
  BOOST_CHECK_EQUAL( partial_view.back(), 0 );

  partial_view[0] = 1;

  BOOST_CHECK_EQUAL( partial_view[0], 1 );
  BOOST_CHECK_EQUAL( partial_view.front(), 1 );
  BOOST_CHECK_EQUAL( partial_view.back(), 1 );
  BOOST_CHECK_EQUAL( view[1], 1 );

  partial_view = view | Utility::Slice( 0, 1 );

  partial_view[0] = 0;

  BOOST_CHECK_EQUAL( partial_view[0], 0 );
  BOOST_CHECK_EQUAL( partial_view.front(), 0 );
  BOOST_CHECK_EQUAL( partial_view.back(), 0 );
  BOOST_CHECK_EQUAL( view[0], 0 );

  container[0] = 1;
  container[1] = 0;

  BOOST_CHECK_EQUAL( view[0], 1 );
  BOOST_CHECK_EQUAL( view[1], 0 );
  BOOST_CHECK_EQUAL( partial_view[0], 1 );

  Utility::ArrayView<const T> view_of_const( container );

  BOOST_CHECK_EQUAL( view_of_const[0], 1 );
  BOOST_CHECK_EQUAL( view_of_const[1], 0 );
  BOOST_CHECK_EQUAL( view_of_const.at(0), 1 );
  BOOST_CHECK_EQUAL( view_of_const.at(1), 0 );
  BOOST_CHECK_EQUAL( view_of_const.front(), 1 );
  BOOST_CHECK_EQUAL( view_of_const.back(), 0 );
}

//---------------------------------------------------------------------------//
// Check if an array view can be converted to an array view-of-const
BOOST_AUTO_TEST_CASE_TEMPLATE( to_const, T, TestTypes )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  {
    auto view_of_const = view.toConst();

    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  {
    auto view_of_const = (Utility::ArrayView<const T>)view;

    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
}

//---------------------------------------------------------------------------//
// Check if an array view can be converted to a std::vector
BOOST_AUTO_TEST_CASE_TEMPLATE( to_vector, T, TestTypes )
{
  std::vector<T> container( {0, 1, 2, 3, 4, 5} );

  Utility::ArrayView<T> view( container );
  Utility::ArrayView<const T> view_of_const = view( 1, 4 );

  {
    std::vector<T> container_copy = view.toVector();

    BOOST_CHECK_EQUAL( container_copy.size(), 6 );
    BOOST_CHECK_EQUAL( container_copy.front(), 0 );
    BOOST_CHECK_EQUAL( container_copy.back(), 5 );
  }

  {
    std::vector<T> container_copy = (std::vector<T>)view;

    BOOST_CHECK_EQUAL( container_copy.size(), 6 );
    BOOST_CHECK_EQUAL( container_copy.front(), 0 );
    BOOST_CHECK_EQUAL( container_copy.back(), 5 );
  }

  {
    std::vector<T> container_copy( view );

    BOOST_CHECK_EQUAL( container_copy.size(), 6 );
    BOOST_CHECK_EQUAL( container_copy.front(), 0 );
    BOOST_CHECK_EQUAL( container_copy.back(), 5 );
  }

  {
    std::vector<T> container_copy = view_of_const.toVector();

    BOOST_CHECK_EQUAL( container_copy.size(), 4 );
    BOOST_CHECK_EQUAL( container_copy.front(), 1 );
    BOOST_CHECK_EQUAL( container_copy.back(), 4 );
  }

  {
    std::vector<T> container_copy = (std::vector<T>)view_of_const;

    BOOST_CHECK_EQUAL( container_copy.size(), 4 );
    BOOST_CHECK_EQUAL( container_copy.front(), 1 );
    BOOST_CHECK_EQUAL( container_copy.back(), 4 );
  }

  {
    std::vector<T> container_copy( view_of_const );

    BOOST_CHECK_EQUAL( container_copy.size(), 4 );
    BOOST_CHECK_EQUAL( container_copy.front(), 1 );
    BOOST_CHECK_EQUAL( container_copy.back(), 4 );
  }
}

//---------------------------------------------------------------------------//
// Check that a direct pointer to the memory array used internally can be
// acquired
BOOST_AUTO_TEST_CASE_TEMPLATE( data, T, TestTypes )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );

  BOOST_CHECK_EQUAL( view.data(), container.data() );

  const std::vector<T>& const_container = container;
  const Utility::ArrayView<T>& const_view = view;

  BOOST_CHECK_EQUAL( const_view.data(), const_container.data() );
}

//---------------------------------------------------------------------------//
// Check if an array view can be constructed using the arrayView helper
// function
BOOST_AUTO_TEST_CASE_TEMPLATE( array_view_construction_helper, T, TestTypes )
{
  std::vector<T> vector( 10 );

  {
    auto view = Utility::arrayView( vector );
    
    BOOST_CHECK_EQUAL( view.size(), vector.size() );
    BOOST_CHECK_EQUAL( view.front(), vector.front() );
    BOOST_CHECK_EQUAL( view.back(), vector.back() );
    BOOST_CHECK( !Utility::IsPointerToConst<typename decltype(view)::pointer>::value );
  }

  {
    auto view_of_const =
      Utility::arrayView( const_cast<const std::vector<T>&>(vector) );

    BOOST_CHECK_EQUAL( view_of_const.size(), vector.size() );
    BOOST_CHECK_EQUAL( view_of_const.front(), vector.front() );
    BOOST_CHECK_EQUAL( view_of_const.back(), vector.back() );
    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  {
    auto view_of_const = Utility::arrayViewOfConst( vector );

    BOOST_CHECK_EQUAL( view_of_const.size(), vector.size() );
    BOOST_CHECK_EQUAL( view_of_const.front(), vector.front() );
    BOOST_CHECK_EQUAL( view_of_const.back(), vector.back() );
    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  std::array<T,10> array({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

  {
    auto view = Utility::arrayView( array );
    
    BOOST_CHECK_EQUAL( view.size(), array.size() );
    BOOST_CHECK_EQUAL( view.front(), array.front() );
    BOOST_CHECK_EQUAL( view.back(), array.back() );
    BOOST_CHECK( !Utility::IsPointerToConst<typename decltype(view)::pointer>::value );
  }

  {
    auto view_of_const =
      Utility::arrayView( const_cast<const std::array<T,10>&>(array) );

    BOOST_CHECK_EQUAL( view_of_const.size(), array.size() );
    BOOST_CHECK_EQUAL( view_of_const.front(), array.front() );
    BOOST_CHECK_EQUAL( view_of_const.back(), array.back() );
    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }

  {
    auto view_of_const = Utility::arrayViewOfConst( array );

    BOOST_CHECK_EQUAL( view_of_const.size(), array.size() );
    BOOST_CHECK_EQUAL( view_of_const.front(), array.front() );
    BOOST_CHECK_EQUAL( view_of_const.back(), array.back() );
    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const)::pointer>::value );
  }
}

//---------------------------------------------------------------------------//
// Check that an array view can be cast to a array view-of-const and back
BOOST_AUTO_TEST_CASE_TEMPLATE( array_view_const_cast_helper, T, TestTypes )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );
  Utility::ArrayView<const T> view_of_const( container );

  {
    auto view_of_const_copy = Utility::av_const_cast<const T>( view );

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view_of_const.size() );
    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const_copy)::pointer>::value );
  }

  {
    auto view_of_const_copy = Utility::av_const_cast<const T>( view_of_const );

    BOOST_CHECK_EQUAL( view_of_const_copy.size(), view_of_const.size() );
    BOOST_CHECK( Utility::IsPointerToConst<typename decltype(view_of_const_copy)::pointer>::value );
  }

  {
    auto view_copy = Utility::av_const_cast<T>( view );

    BOOST_CHECK_EQUAL( view_copy.size(), view.size() );
    BOOST_CHECK( !Utility::IsPointerToConst<typename decltype(view_copy)::pointer>::value );
  }

  {
    auto view_copy = Utility::av_const_cast<T>( view_of_const );

    BOOST_CHECK_EQUAL( view_copy.size(), view.size() );
    BOOST_CHECK( !Utility::IsPointerToConst<typename decltype(view_copy)::pointer>::value );
  }
}

//---------------------------------------------------------------------------//
// Check the reinterpret cast array view helper function
BOOST_AUTO_TEST_CASE_TEMPLATE( array_view_reinterpret_cast_helper,
                               T,
                               TestTypes )
{
  std::vector<T> container( 10 );

  Utility::ArrayView<T> view( container );
  Utility::ArrayView<const T> view_of_const( container );

  {
    auto reinterpreted_view_copy = Utility::av_reinterpret_cast<char>( view );

    BOOST_CHECK_EQUAL( reinterpreted_view_copy.size(),
                       view.size()*sizeof(T) );
    BOOST_CHECK( (std::is_same<typename decltype(reinterpreted_view_copy)::value_type,char>::value) );
  }

  {
    auto reinterpreted_view_of_const_copy =
      Utility::av_reinterpret_cast<const char>( view );

    BOOST_CHECK_EQUAL( reinterpreted_view_of_const_copy.size(),
                       view.size()*sizeof(T) );
    BOOST_CHECK( (std::is_same<typename decltype(reinterpreted_view_of_const_copy)::value_type,char>::value) );
  }

  {
    auto reinterpreted_view_of_const_copy =
      Utility::av_reinterpret_cast<const char>( view_of_const );

    BOOST_CHECK_EQUAL( reinterpreted_view_of_const_copy.size(),
                       view_of_const.size()*sizeof(T) );
    BOOST_CHECK( (std::is_same<typename decltype(reinterpreted_view_of_const_copy)::value_type,char>::value) );
  }
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for array views
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef Utility::ArrayView<T> ArrayView;
  typedef Utility::ArrayView<const T> ArrayViewOfConst;

  BOOST_CHECK( Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ArrayView>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ArrayView>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<ArrayViewOfConst>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const ArrayViewOfConst>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for array views
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;
  
  typedef Utility::ArrayView<T> ArrayView;
  typedef Utility::ArrayView<const T> ArrayViewOfConst;

  std::vector<T> container({T(0),T(1),T(2)});

  // Construct views
  ArrayView left_view( container );
  ArrayViewOfConst left_view_of_const = left_view.toConst();

  ArrayView right_view( container );
  ArrayViewOfConst right_view_of_const = right_view.toConst();

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_view, "lhs",
                                                    right_view, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_view_of_const, "lhs",
                                               right_view_of_const, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_view, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_view, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_view_of_const, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_view_of_const, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_view, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_view, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_view_of_const, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_view_of_const, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_view, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               right_view, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_view.size(), "lhs", true,
                                                right_view.size(), "rhs", true,
                                                ".size()", local_oss, true );
    for( size_t i = 0; i < left_view.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view[i], "lhs", true,
                right_view[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_view_of_const, "lhs",
                                               right_view_of_const, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view_of_const, "lhs",
                                               right_view_of_const, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       left_view_of_const.size(), "lhs", true,
                                       right_view_of_const.size(), "rhs", true,
                                       ".size()", local_oss, true );
    for( size_t i = 0; i < left_view_of_const.size(); ++i )
    {
      Utility::ComparisonTraits<const T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", true,
                right_view_of_const[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_view.toConst(), "lhs",
                                               right_view_of_const, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view.toConst(), "lhs",
                                               right_view_of_const, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       left_view_of_const.size(), "lhs", false,
                                       right_view_of_const.size(), "rhs", true,
                                       ".size()", local_oss, true );
    for( size_t i = 0; i < left_view_of_const.size(); ++i )
    {
      Utility::ComparisonTraits<const T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", false,
                right_view_of_const[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_view_of_const, "lhs",
                                               right_view.toConst(), "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view_of_const, "lhs",
                                               right_view.toConst(), "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", true,
                                      right_view_of_const.size(), "rhs", false,
                                      ".size()", local_oss, true );
    for( size_t i = 0; i < left_view_of_const.size(); ++i )
    {
      Utility::ComparisonTraits<const T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", true,
                right_view_of_const[i], "rhs", false,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_view.toConst(), "lhs",
                                               right_view.toConst(), "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view.toConst(), "lhs",
                                               right_view.toConst(), "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", false,
                                      right_view_of_const.size(), "rhs", false,
                                      ".size()", local_oss, true );
    for( size_t i = 0; i < left_view_of_const.size(); ++i )
    {
      Utility::ComparisonTraits<const T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_view_of_const[i], "lhs", false,
                right_view_of_const[i], "rhs", false,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_view, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_view, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       0, "lhs", false,
                                       right_view.size(), "rhs", true,
                                       ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_view, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view, "lhs",
                                               {}, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view.size(), "lhs", true,
                                      0, "rhs", false,
                                      ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_view_of_const, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_view_of_const, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                       0, "lhs", false,
                                       right_view_of_const.size(), "rhs", true,
                                       ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_view_of_const, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_view_of_const, "lhs",
                                               {}, "rhs",
                                               tol );
  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                      left_view_of_const.size(), "lhs", true,
                                      0, "rhs", false,
                                      ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
}

//---------------------------------------------------------------------------//
// end tstArrayView.cpp
//---------------------------------------------------------------------------//

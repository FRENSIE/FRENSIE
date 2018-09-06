//---------------------------------------------------------------------------//
//!
//! \file   Utility_TemplateUnitTestWrapper_def.hpp
//! \author Alex Robinson
//! \brief  The template unit test wrapper class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_DEF_HPP
#define UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_DEF_HPP

// Std Lib Includes
#include <typeindex>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_TypeTraits.hpp"

namespace Utility{

namespace Details{
  
//! The template unit test instantiation helper
template<size_t I, typename TupleTypeWrapper, typename Enabled = void>
struct TemplateUnitTestInstantiationHelper
{
  //! Instantiate the template unit test template I
  template<template<typename...> class TemplateUnitTest,
           bool expand_inner_tuples>
  static inline void instantiateUnitTest(
                   std::vector<std::shared_ptr<Utility::UnitTest> >& test_list,
                   std::set<std::type_index>& test_ids )
  {
    typedef typename Utility::TupleElement<I,TupleTypeWrapper>::type IType;
    
    typedef typename std::conditional<Utility::IsTuple<IType>::value && !Utility::IsPair<IType>::value,TemplateUnitTest<std::integral_constant<bool,expand_inner_tuples>,IType>,TemplateUnitTest<IType> >::type TemplateUnitTestType;

    std::type_index test_id(typeid(TemplateUnitTestType));

    // Only instantiate the test if its id has not been registered
    if( !test_ids.count(test_id) )
    {
      test_list.push_back( std::shared_ptr<Utility::UnitTest>( new TemplateUnitTestType ) );
      test_ids.insert( test_id );
    }

    TemplateUnitTestInstantiationHelper<I+1,TupleTypeWrapper>::template instantiateUnitTest<TemplateUnitTest,expand_inner_tuples>( test_list, test_ids );
  }                   
};

/*! \brief Partial specialization of unit test instantiation helper 
 * (I == Utility::TupleSize, which is past the last element)
 */
template<size_t I, typename TupleTypeWrapper>
struct TemplateUnitTestInstantiationHelper<I,TupleTypeWrapper,typename std::enable_if<I==Utility::TupleSize<TupleTypeWrapper>::value>::type>
{
  //! Instantiate the template unit test type I
  template<template<typename...> class TemplateUnitTest,
           bool expand_inner_tuples>
  static inline void instantiateUnitTest(
                             std::vector<std::shared_ptr<Utility::UnitTest> >&,
                             std::set<std::type_index>& )
  { /* ... */ }
};

} // end Details namespace

// Constructor
template<template<typename...> class TemplateUnitTest,
         bool expand_inner_tuples,
         typename... Types>
TemplateUnitTestWrapper<TemplateUnitTest,expand_inner_tuples,Types...>::TemplateUnitTestWrapper()
  : d_instantiated_tests()
{
  // To avoid instantiated the same test multiple times we will keep track of
  // the type ids of the tests that are created and avoid instantiated a test
  // if its id has already been encountered
  std::set<std::type_index> instantiated_test_ids;
  
  Details::TemplateUnitTestInstantiationHelper<0,std::tuple<Types...> >::template instantiateUnitTest<TemplateUnitTest,expand_inner_tuples>( d_instantiated_tests, instantiated_test_ids );
}

// Destructor
template<template<typename...> class TemplateUnitTest,
         bool expand_inner_tuples,
         typename... Types>
TemplateUnitTestWrapper<TemplateUnitTest,expand_inner_tuples,Types...>::~TemplateUnitTestWrapper()
{ /* ... */ }

// Return the number of instantiated tests
template<template<typename...> class TemplateUnitTest,
         bool expand_inner_tuples,
         typename... Types>
size_t TemplateUnitTestWrapper<TemplateUnitTest,expand_inner_tuples,Types...>::getNumberOfTests() const
{
  return d_instantiated_tests.size();
}
  
} // end Utility namespace

#endif // end UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TemplateUnitTestWrapper_def.hpp
//---------------------------------------------------------------------------//


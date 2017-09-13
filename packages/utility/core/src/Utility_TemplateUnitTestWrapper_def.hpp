//---------------------------------------------------------------------------//
//!
//! \file   Utility_TemplateUnitTestWrapper_def.hpp
//! \author Alex Robinson
//! \brief  The template unit test wrapper class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_DEF_HPP
#define UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_DEF_HPP

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_ContractException.hpp"

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
                  std::vector<std::shared_ptr<Utility::UnitTest> >& test_list )
  {
    typedef typename Utility::TupleElement<I,TupleTypeWrapper>::type IType;

    if( Utility::IsTuple<IType>::value )
    {
      test_list[I].reset( new TemplateUnitTest<std::integral_constant<bool,expand_inner_tuples>,IType>() );
    }
    else
    {
      test_list[I].reset( new TemplateUnitTest<IType>() );
    }

    TemplateUnitTestInstantiationHelper<I+1,TupleTypeWrapper>::template instantiateUnitTest<TemplateUnitTest,expand_inner_tuples>( test_list );
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
                            std::vector<std::shared_ptr<Utility::UnitTest> >& )
  { /* ... */ }
};

} // end Details namespace

// Constructor
template<template<typename...> class TemplateUnitTest,
         bool expand_inner_tuples,
         typename... Types>
TemplateUnitTestWrapper<TemplateUnitTest,expand_inner_tuples,Types...>::TemplateUnitTestWrapper()
  : d_instantiated_tests( Utility::TupleSize<std::tuple<Types...> >::value )
{
  // Make sure that the number of types is a multiple of N
  Details::TemplateUnitTestInstantiationHelper<0,std::tuple<Types...> >::template instantiateUnitTest<TemplateUnitTest,expand_inner_tuples>( d_instantiated_tests );
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


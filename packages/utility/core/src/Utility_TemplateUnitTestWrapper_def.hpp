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
#include "Utility_ContractException.hpp"

namespace Utility{

namespace Details{
  
//! The template unit test instantiation helper
template<size_t I, size_t N, typename... Types, typename Enabled = void>
struct TemplateUnitTestInstantiationHelper
{
  //! Instantiate the template unit test template I
  template<template<typename,typename...> class TemplateUnitTest>
  static inline void instantiateUnitTest(
                  std::vector<std::shared_ptr<Utility::UnitTest> >& test_list )
  {
    typedef Utility::TupleSlice<I*N,N,std::tuple<Types...> >::type SliceType;
    
    test_list[I].reset( new TemplateUnitTest<SliceType>() );

    TemplateUnitTestInstantiationHelper<I+1,N,Types...>::instantiateUnitTest<TemplateUnitTest>( test_list, type_names );
  }                   
};

/*! \brief Partial specialization of unit test instantiation helper 
 * (I == Utility::TupleSize, which is for the last element)
 */
template<size_t I, typename TupleType>
struct TemplateUnitTestInstantiationHelper<I,TupleType,typename std::enable_if<I==Utility::TupleSize<TupleType>::value-1>::type>
{
  //! Instantiate the template unit test type I
  template<template<typename,typename...> class TemplateUnitTest>
  static inline void instantiateUnitTest(
                   std::vector<std::shared_ptr<Utility::UnitTest> >&,
                   const std::vector<std::string>& )
  { /* ... */ }
};

/*! \brief Partial specialization of unit test instantiation helper 
 * (I == Utility::TupleSize, which is past the last element)
 */
template<size_t I, typename TupleType>
struct TemplateUnitTestInstantiationHelper<I,TupleType,typename std::enable_if<I==Utility::TupleSize<TupleType>::value>::type>
{
  //! Instantiate the template unit test type I
  template<template<typename,typename...> class TemplateUnitTest>
  static inline void instantiateUnitTest(
                   std::vector<std::shared_ptr<Utility::UnitTest> >&,
                   const std::vector<std::string>& )
  { /* ... */ }
};

} // end Details namespace

// Constructor
template<template<typename,typename...> class TemplateUnitTest,
         size_t N,
         typename... Types>
TemplateUnitTestWrapper<TemplateUnitTest,Types...>::TemplateUnitTestWrapper()
  : d_instantiated_tests( Utility::TupleSize<std::tuple<Types...> >::value/N )
{
  // Make sure that the number of types is a multiple of N
  testStaticPrecondition( sizeof(Types...) % N == 0 );
  
  Details::TemplateUnitTestInstantiationHelper<0,N,Types...>::instantiate<TemplateUnitTest>( d_instantiated_tests );
}

// Destructor
template<template<typename,typename...> class TemplateUnitTest, typename Types>
TemplateUnitTestWrapper<TemplateUnitTest,Types>::~TemplateUnitTestWrapper()
{ /* ... */ }

// Return the number of instantiated tests
template<template<typename,typename...> class TemplateUnitTest, typename Types>
size_t TemplateUnitTestWrapper<TemplateUnitTest,Types>::getNumberOfTests() const
{
  return d_instantiated_tests.size();
}
  
} // end Utility namespace

#endif // end UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TemplateUnitTestWrapper_def.hpp
//---------------------------------------------------------------------------//


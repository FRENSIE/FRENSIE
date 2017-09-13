//---------------------------------------------------------------------------//
//!
//! \file   Utility_TemplateUnitTestWrapper.hpp
//! \author Alex Robinson
//! \brief  The template unit test wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_HPP
#define UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <vector>

// FRENSIE Includes
#include "Utility_UnitTest.hpp"

namespace Utility{

/*! The template unit test wrapper class
 * 
 * This class can be used to instantiate a template unit test with a set
 * of desired types. The wrapper will store the instantiated unit tests
 * to ensure persistance during testing.
 * \ingroup unit_test_framework
 */
template<template<typename...> class TemplateUnitTest,
         bool expand_inner_tuples,
         typename... Types>
class TemplateUnitTestWrapper
{

public:

  //! Constructor
  TemplateUnitTestWrapper();

  //! Destructor
  ~TemplateUnitTestWrapper();

  //! Return the number of instantiated tests
  size_t getNumberOfTests() const;

private:

  // The instantiated tests
  std::vector<std::shared_ptr<Utility::UnitTest> > d_instantiated_tests;
};

/*! The specialization of TemplateUnitTestWrapper for std::tuple
 * \ingroup unit_test_framework
 */
template<template<typename...> class TemplateUnitTest,
         bool expand_inner_tuples,
         typename... Types>
class TemplateUnitTestWrapper<TemplateUnitTest,expand_inner_tuples,std::tuple<Types...> > : public TemplateUnitTestWrapper<TemplateUnitTest,expand_inner_tuples,Types...>
{ /* ... */ };
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_TemplateUnitTestWrapper_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TEMPLATE_UNIT_TEST_WRAPPER_HPP

//---------------------------------------------------------------------------//
// end Utility_TemplateUnitTestWrapper.hpp
//---------------------------------------------------------------------------//

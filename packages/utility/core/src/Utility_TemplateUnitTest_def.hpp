//---------------------------------------------------------------------------//
//!
//! \file   Utility_TemplateUnitTest_def.hpp
//! \author Alex Robinson
//! \brief  The template unit test base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEMPLATE_UNIT_TEST_DEF_HPP
#define UTILITY_TEMPLATE_UNIT_TEST_DEF_HPP

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

// Constructor
template<typename... Types>
TemplateUnitTest<Types...>::TemplateUnitTest( const std::string& group_name,
                                              const std::string& test_name )
  : TemplateUnitTest<Types...>( group_name,
                                test_name,
                                Utility::typeName<Types...>() )
{ /* ... */ }

// Constructor with template parameter name
template<typename... Types>
TemplateUnitTest<Types...>::TemplateUnitTest(
                                  const std::string& group_name,
                                  const std::string& test_name,
                                  const std::string& template_param_pack_name )
  : UnitTest( group_name, test_name + "<" + template_param_pack_name + ">" )
{ /* ... */ }
  
} // end Utility namespace

#endif // end UTILITY_TEMPLATE_UNIT_TEST_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TemplateUnitTest_def.hpp
//---------------------------------------------------------------------------//

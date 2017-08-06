//---------------------------------------------------------------------------//
//!
//! \file   Utility_TemplateUnitTest.hpp
//! \author Alex Robinson
//! \brief  The template unit test base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEMPLATE_UNIT_TEST_HPP
#define UTILITY_TEMPLATE_UNIT_TEST_HPP

// FRENSIE Includes
#include "Utility_UnitTest.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The template unit test base class
 * \ingroup unit_test_framework
 */
template<typename... Types>
class TemplateUnitTest
{

public:

  //! Constructor
  TemplateUnitTest( const std::string& group_name,
                    const std::string& test_name,
                    const std::string& data_name = "" );

  //! Constructor with template parameter name
  TemplateUnitTest( const std::string& group_name,
                    const std::string& test_name,
                    const std::string& template_param_pack_name,
                    const std::string& data_name = "" );

  //! Destructor
  ~TemplateUnitTest()
  { /* ... */ }
  
  //! Get the Nth template parameter
  template<size_t N>
  struct _T
  {
    typedef typename Utility::TupleElement<N,std::tuple<Types...> >::type;
  };
};

/*! Partial specialization of TemplateUnitTest for std::tuple type
 * \ingroup unit_test_framework
 */
template<typename... Types>
class TemplateUnitTest<std::tuple<Types...> > : public TemplateUnitTest<Types...>
{ /* ... */ };

/*! Partial specialization of TemplateUnitTest for empty std::tuple type
 * \ingroup unit_test_framework
 */
template<>
class TemplateUnitTest<std::tuple<> >
{ /* ... */ };

  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Inclues.
//---------------------------------------------------------------------------//

#include "Utility_TemplateUnitTest_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TEMPLATE_UNIT_TEST_HPP

//---------------------------------------------------------------------------//
// end Utility_TemplateUnitTest.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   tstSetOperationFunctor.hpp
//! \author Alex Robinson
//! \brief  SetOperationFunctor unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <vector>

// FRENSIE Includes
#include "Utility_SetOperationFunctor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that IntersectionFunctor returns the correct value
FRENSIE_UNIT_TEST( IntersectionFunctor, operator )
{
  std::shared_ptr<Utility::SetOperationFunctor>
    functor( new Utility::IntersectionFunctor );

  bool functor_value = (*functor)( true, true );

  FRENSIE_CHECK( functor_value );

  functor_value = (*functor)( true, false );

  FRENSIE_CHECK( !functor_value );

  functor_value = (*functor)( false, true );

  FRENSIE_CHECK( !functor_value );

  functor_value = (*functor)( false, false );

  FRENSIE_CHECK( !functor_value );
}

//---------------------------------------------------------------------------//
// Check that the UnionFunctor returns the correct value
FRENSIE_UNIT_TEST( UnionFunctor, operator )
{
  std::shared_ptr<Utility::SetOperationFunctor>
    functor( new Utility::UnionFunctor );

  bool functor_value = (*functor)( true, true );

  FRENSIE_CHECK( functor_value );

  functor_value = (*functor)( true, false );

  FRENSIE_CHECK( functor_value );

  functor_value = (*functor)( false, true );

  FRENSIE_CHECK( functor_value );

  functor_value = (*functor)( false, false );

  FRENSIE_CHECK( !functor_value );
}

//---------------------------------------------------------------------------//
// Check that an array of SetOperationFunctors will return the correct value
FRENSIE_UNIT_TEST( SetOperationFunctor, array )
{
  std::vector<std::shared_ptr<Utility::SetOperationFunctor> > functor_array;

  std::shared_ptr<Utility::SetOperationFunctor>
    functor( new Utility::IntersectionFunctor );
  functor_array.push_back( functor );
  functor.reset( new Utility::UnionFunctor );
  functor_array.push_back( functor );

  bool functor_value = (*functor_array[0])( true, false );

  FRENSIE_CHECK( !functor_value );

  functor_value = (*functor_array[1])( true, false );

  FRENSIE_CHECK( functor_value );
}

//---------------------------------------------------------------------------//
// end tstSetOperationFunctor.hpp
//---------------------------------------------------------------------------//


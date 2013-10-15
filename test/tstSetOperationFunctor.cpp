//---------------------------------------------------------------------------//
//!
//! \file   tstSetOperationFunctor.hpp
//! \author Alex Robinson
//! \brief  SetOperationFunctor unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "SetOperationFunctor.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that IntersectionFunctor returns the correct value
TEUCHOS_UNIT_TEST( IntersectionFunctor, operator )
{
  Teuchos::RCP<FACEMC::SetOperationFunctor> 
    functor( new FACEMC::IntersectionFunctor );

  bool functor_value = (*functor)( true, true );
  
  TEST_ASSERT( functor_value );

  functor_value = (*functor)( true, false );

  TEST_ASSERT( !functor_value );

  functor_value = (*functor)( false, true );
  
  TEST_ASSERT( !functor_value );

  functor_value = (*functor)( false, false );

  TEST_ASSERT( !functor_value );
}

//---------------------------------------------------------------------------//
// Check that the UnionFunctor returns the correct value
TEUCHOS_UNIT_TEST( UnionFunctor, operator )
{
  Teuchos::RCP<FACEMC::SetOperationFunctor>
    functor( new FACEMC::UnionFunctor );

  bool functor_value = (*functor)( true, true );

  TEST_ASSERT( functor_value );

  functor_value = (*functor)( true, false );

  TEST_ASSERT( functor_value );

  functor_value = (*functor)( false, true );

  TEST_ASSERT( functor_value );
  
  functor_value = (*functor)( false, false );

  TEST_ASSERT( !functor_value );
}

//---------------------------------------------------------------------------//
// Check that an array of SetOperationFunctors will return the correct value
TEUCHOS_UNIT_TEST( SetOperationFunctor, array )
{
  Teuchos::Array<Teuchos::RCP<FACEMC::SetOperationFunctor> > functor_array;
  
  Teuchos::RCP<FACEMC::SetOperationFunctor> 
    functor( new FACEMC::IntersectionFunctor );
  functor_array.push_back( functor );
  functor.reset( new FACEMC::UnionFunctor );
  functor_array.push_back( functor );

  bool functor_value = (*functor_array[0])( true, false );

  TEST_ASSERT( !functor_value );

  functor_value = (*functor_array[1])( true, false );

  TEST_ASSERT( functor_value );
}

//---------------------------------------------------------------------------//
// end tstSetOperationFunctor.hpp
//---------------------------------------------------------------------------//


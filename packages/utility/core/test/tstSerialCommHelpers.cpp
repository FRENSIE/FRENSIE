//---------------------------------------------------------------------------//
//!
//! \file   tstSerialCommHelpers.cpp
//! \author Alex Robinson
//! \brief  Comm helper and extensions serial unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_DefaultSerialComm.hpp>

// FRENSIE Includes
#include "Utility_CommHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )   \
  typedef long long int64;            \
  typedef unsigned long long uint64;            \
  typedef unsigned long uint32;                 \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int64 )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint32 )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint64 )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_source_no_status,
                                   Ordinal )
{
  Teuchos::RCP<Teuchos::Comm<Ordinal> >
    comm( new Teuchos::SerialComm<Ordinal> );

  // No probing with serial comms
  TEST_THROW( Utility::iprobe( *comm, 0 ), std::logic_error );
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_source_no_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_source_status,
                                   Ordinal )
{
  Teuchos::RCP<Teuchos::Comm<Ordinal> >
    comm( new Teuchos::SerialComm<Ordinal> );

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;

  // No probing with serial comms
  TEST_THROW( Utility::iprobe( *comm, 0, status ), std::logic_error );
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_source_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_no_status,
                                   Ordinal )
{
  Teuchos::RCP<Teuchos::Comm<Ordinal> >
    comm( new Teuchos::SerialComm<Ordinal> );

  // No probing with serial comms
  TEST_THROW( Utility::iprobe( *comm ), std::logic_error );
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_no_status );

//---------------------------------------------------------------------------//
// Check that a serial iprobe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   iprobe_status,
                                   Ordinal )
{
  Teuchos::RCP<Teuchos::Comm<Ordinal> >
    comm( new Teuchos::SerialComm<Ordinal> );

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;

  // No probing with serial comms
  TEST_THROW( Utility::iprobe( *comm, status ), std::logic_error );
}

UNIT_TEST_INSTANTIATION( CommHelpers, iprobe_status );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   probe_source,
                                   Ordinal )
{
  Teuchos::RCP<Teuchos::Comm<Ordinal> >
    comm( new Teuchos::SerialComm<Ordinal> );

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;

  // No probing with serial comms
  TEST_THROW( Utility::probe( *comm, 0, status ), std::logic_error );
}

UNIT_TEST_INSTANTIATION( CommHelpers, probe_source );

//---------------------------------------------------------------------------//
// Check that a serial probe can be done
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CommHelpers,
                                   probe,
                                   Ordinal )
{
  Teuchos::RCP<Teuchos::Comm<Ordinal> >
    comm( new Teuchos::SerialComm<Ordinal> );

  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > status;

  // No probing with serial comms
  TEST_THROW( Utility::probe( *comm, status ), std::logic_error );
}

UNIT_TEST_INSTANTIATION( CommHelpers, probe );

//---------------------------------------------------------------------------//
// end tstSerialCommHelpers.cpp
//---------------------------------------------------------------------------//

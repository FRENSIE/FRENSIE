//---------------------------------------------------------------------------//
//!
//! \file   Utility_TeuchosUnitTestInitializer.cpp
//! \author Alex Robinson
//! \brief  The Teuchos unit test initializer class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_TeuchosUnitTestInitializer.hpp"

namespace Utility{

// Initialize the static member data
std::unique_ptr<TeuchosUnitTestInitializer>
TeuchosUnitTestInitializer::s_initializer;

// Initialize the unit tests
/*! \details This method will throw a  std::exception if the initialization
 * fails.
 */
void TeuchosUnitTestInitializer::initializeUnitTests( int argc,
                                                      char** argv,
                                                      std::ostream* os )
{
  // Get the initializer
  TeuchosUnitTestInitializer& initializer =
    TeuchosUnitTestInitializer::getInitializer();

  // Force the command line processor to throw exceptions
  initializer.clp().throwExceptions( true );

  // Set the command line processor options
  initializer.setCommandLineProcessorOptions();

  // Parse the command line
  initializer.clp().parse( argc, argv, os );

  // Initialize the unit test data
  initializer.initialize();
}

// Set the initializer
/*! \details This method will take ownership of the initializer pointer.
 */
void TeuchosUnitTestInitializer::setInitializer(
                                      TeuchosUnitTestInitializer* initializer )
{
  s_initializer.reset( initializer );
}

// Get the initializer
/*! \details Returns the singleton instance "just-in-time".
 */
TeuchosUnitTestInitializer& TeuchosUnitTestInitializer::getInitializer()
{
  if( !s_initializer.get() )
    s_initializer.reset( new TeuchosUnitTestInitializer );

  return *s_initializer;
}

// Shortcut for getting the command line processor
Teuchos::CommandLineProcessor& TeuchosUnitTestInitializer::clp() const
{
  return Teuchos::UnitTestRepository::getCLP();
}

// Set the command line processor options
/*! \details Derived classes can override this method if a unit test suite
 * needs additional command line options. Only modify the command line
 * processor returned from the TeuchosUnitTestInitializer::clp method. Note:
 * this method is non-const because of how it can be used by the
 * unit test harness extensions.
 */
void TeuchosUnitTestInitializer::setCommandLineProcessorOptions()
{ /* ... */ }

// Initialize method
/*! \details Derived classes can override this method if test data needs
 * to be initialized in a specific way.
 */
void TeuchosUnitTestInitializer::initialize() const
{ /* ... */ }

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TeuchosUnitTestInitializer.cpp
//---------------------------------------------------------------------------//

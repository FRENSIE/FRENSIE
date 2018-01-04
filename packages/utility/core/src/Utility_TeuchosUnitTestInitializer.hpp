//---------------------------------------------------------------------------//
//!
//! \file   Utility_TeuchosUnitTestInitializer.hpp
//! \author Alex Robinson
//! \brief  The Teuchos unit test initializer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEUCHOS_UNIT_TEST_INITIALIZER_HPP
#define UTILITY_TEUCHOS_UNIT_TEST_INITIALIZER_HPP

// Std Lib Includes
#include <memory>
#include <iostream>

// Trilinos Includes
#include <Teuchos_CommandLineProcessor.hpp>

namespace Utility{

//! The Teuchos unit test initializer
class TeuchosUnitTestInitializer
{

public:

  //! Initialize the unit tests
  static void initializeUnitTests( int argc, char** argv, std::ostream* os );

  //! Destructor
  virtual ~TeuchosUnitTestInitializer()
  { /* ... */ }

protected:

  //! Set the initializer
  static void setInitializer( TeuchosUnitTestInitializer* initializer );

  //! Get the initializer
  static TeuchosUnitTestInitializer& getInitializer();

  //! Constructor
  TeuchosUnitTestInitializer()
  { /* ... */ }

  //! Shortcut for getting the command line processor
  Teuchos::CommandLineProcessor& clp() const;

  //! Set the command line processor options
  virtual void setCommandLineProcessorOptions();

  //! Initialize method
  virtual void initialize() const;

private:

  // The initializer singleton instance
  static std::unique_ptr<TeuchosUnitTestInitializer> s_initializer;
};

} // end Utility namespace

#endif // end UTILITY_TEUCHOS_UNIT_TEST_INITIALIZER_HPP

//---------------------------------------------------------------------------//
// end Utility_TeuchosUnitTestInitializer.hpp
//---------------------------------------------------------------------------//

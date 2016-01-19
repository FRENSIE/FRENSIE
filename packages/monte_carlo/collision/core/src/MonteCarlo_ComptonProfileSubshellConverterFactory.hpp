//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_ComptonProfileSubshellConverterFactory.hpp
//! \author Alex Robinson
//! \brief  Compton profile subshell-to-index converter factory decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_FACTORY_HPP
#define MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"

namespace MonteCarlo{

//! The Compton profile subshell converter factory
class ComptonProfileSubshellConverterFactory
{
public:

  //! Create the converter
  template<template<typename> class SmartPointer>
  static void createConverter( 
		      SmartPointer<ComptonProfileSubshellConverter>& converter,
		      const unsigned atomic_number );

private:

  // Constructor
  ComptonProfileSubshellConverterFactory();
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ComptonProfileSubshellConverterFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileSubshellCOnverterFactory.hpp
//---------------------------------------------------------------------------//

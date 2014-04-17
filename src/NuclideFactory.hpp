//---------------------------------------------------------------------------//
//!
//! \file   NuclideFactory.hpp
//! \author Alex Robinson
//! \brief  The nuclide factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLIDE_FACTORY_HPP
#define NUCLIDE_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_set>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FACEMC Includes
#include "Nuclide.hpp"

namespace FACEMC{

//! The nuclide factory class
class NuclideFactory
{
public:

  //! Constructor
  NuclideFactory( const std::string& ace_table_directory,
		  const boost::unordered_set<std::string>& nuclides );

  //! Destructor
  ~NuclideFactory()
  { /* ... */ }

  //! Create the map of nuclides
  template<template<typename,typename,typename,typename> Map>
  create( Map<std::string,Teuchos::RCP<Nuclide> >& nuclide_map) const;

private:

  // The path to the ace table directory
  std::string d_ace_table_directory;

  // The nuclides that need to be loaded
  const boost::unordered_set<std::string>& d_nuclides;
  
   // The cross section table information
  Teuchos::ParameterList d_cross_section_table_info;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "NuclideFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end NUCLIDE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end NuclideFactory.hpp
//---------------------------------------------------------------------------//

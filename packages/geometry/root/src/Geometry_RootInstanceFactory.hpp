//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootInstanceFactory.hpp
//! \author Eli Moll
//! \brief  Root instance factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_INSTANCE_FACTORY_HPP
#define GEOMETRY_ROOT_INSTANCE_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Geometry_Exceptions.hpp"

namespace Geometry{

//! The Root instance factory
class RootInstanceFactory
{
  
public:
  
  //! Initialize Root (singleton geometry manager -> gGeoManager)
  static void initializeRoot( const Teuchos::ParameterList& geom_rep );

private:

  // Validate a geometry representation
  static void validateGeometryRep( const Teuchos::ParameterList& geom_rep );
};

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_INSTANCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootInstanceFactory.hpp
//---------------------------------------------------------------------------//

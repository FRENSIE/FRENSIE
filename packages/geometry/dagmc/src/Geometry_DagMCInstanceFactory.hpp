//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCInstanceFactory.hpp
//! \author Alex Robinson
//! \brief  DagMC instance factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_INSTANCE_FACTORY_HPP
#define GEOMETRY_DAGMC_INSTANCE_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Geometry_Exceptions.hpp"

namespace Geometry{

//! The DagMC instance factory
class DagMCInstanceFactory
{
  
public:
  
  //! Initialize DagMC 
  static void initializeDagMC( const Teuchos::ParameterList& geom_rep,
			       std::ostream& os_warn = std::cerr );

private:

  // Validate a geometry representation
  static void validateGeometryRep( const Teuchos::ParameterList& geom_rep );
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_INSTANCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCInstanceFactory.hpp
//---------------------------------------------------------------------------//

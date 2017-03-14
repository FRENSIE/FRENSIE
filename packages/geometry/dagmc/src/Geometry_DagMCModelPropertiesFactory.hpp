//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModelPropertiesFactory.hpp
//! \author Alex Robinson
//! \brief  DagMC model properties factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_MODEL_PROPERTIES_FACTORY_HPP
#define GEOMETRY_DAGMC_MODEL_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Geometry_DagMCModelProperties.hpp"

namespace Geometry{

//! The DagMC model properties factory
class DagMCModelPropertiesFactory
{

public:

  //! Load the DagMC model properties
  static std::shared_ptr<const DagMCModelProperties> createProperties(
                                    const Teuchos::ParameterList& properties );
};
  
} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_MODEL_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModelPropertiesFactory.hpp
//---------------------------------------------------------------------------//

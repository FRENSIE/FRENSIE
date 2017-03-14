//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModelPropertiesFactory.hpp
//! \author Alex Robinson
//! \brief  Root model properties factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_MODEL_PROPERTIES_FACTORY_HPP
#define GEOMETRY_ROOT_MODEL_PROPERTIES_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Geometry_RootModelProperties.hpp"

namespace Geometry{

//! The Root model properties factory
class RootModelPropertiesFactory
{

public:

  //! Load the Root model properties
  static std::shared_ptr<const RootModelProperties> createProperties(
                                    const Teuchos::ParameterList& properties );
};
  
} // end Geometry namespace

#endif // end GEOMETRY_ROOT_MODEL_PROPERTIES_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootModelPropertiesFactory.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModelFactory.hpp
//! \author Alex Robinson
//! \brief  The geometry model factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODEL_FACTORY_HPP
#define GEOMETRY_MODEL_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Geometry_Model.hpp"

namespace Geometry{

//! The model factory
class ModelFactory
{

public:

  //! Create the model from the data
  static std::shared_ptr<const Model> createModel(
                                    const Teuchos::ParameterList& model_data );
};
  
} // end Geometry namespace

#endif // end GEOMETRY_MODEL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_ModelFactory.hpp
//---------------------------------------------------------------------------//

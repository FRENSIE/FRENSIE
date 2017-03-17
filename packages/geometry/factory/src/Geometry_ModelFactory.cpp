//---------------------------------------------------------------------------//
//!
//! \file   Geometry_ModelFactory.cpp
//! \author Alex Robinson
//! \brief  The geometry model factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_ModelFactory.hpp"
#include "Geometry_Config.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCModelPropertiesFactory.hpp"
#include "Geometry_DagMCModel.hpp"
#endif

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_RootModelPropertiesFactory.hpp"
#include "Geometry_RootModel.hpp"
#endif

namespace Geometry{

// Create the model from the data
std::shared_ptr<const Model> ModelFactory::createModel(
                                     const Teuchos::ParameterList& model_data )
{
  // The handler property must be defined
  TEST_FOR_EXCEPTION( !model_data.isParameter( "Handler" ),
                      std::runtime_error,
                      "Unable to determine the geometry handler type!" );

  std::string handler = model_data.get<std::string>( "Handler" );

  if( handler == "DagMC" )
  {
#ifdef HAVE_FRENSIE_DAGMC
    std::shared_ptr<const DagMCModelProperties> model_properties =
      DagMCModelPropertiesFactory::createProperties( model_data );
    
    DagMCModel::getInstance()->initialize( *model_properties );

    return DagMCModel::getInstance();
#else // HAVE_FRENSIE_DAGMC
    THROW_EXCEPTION( std::runtime_error,
                     "A DagMC model cannot be created because the DagMC "
                     "geometry package has not been enabled!" );
#endif // end HAVE_FRENSIE_DAGMC
  }
  else if( handler == "ROOT" )
  {
#ifdef HAVE_FRENSIE_ROOT
    std::shared_ptr<const RootModelProperties> model_properties =
      RootModelPropertiesFactory::createProperties( model_data );
    
    RootModel::getInstance()->initialize( *model_properties );

    return RootModel::getInstance();
#else // HAVE_FRENSIE_ROOT
    THROW_EXCEPTION( std::runtime_error,
                     "A Root model cannot be created because the Root "
                     "geometry package has noot been enabled!" );
#endif // end HAVE_FRENSIE_ROOT
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Geometry handler " << handler << " is not supported!" );
  }
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModelFactory.cpp
//---------------------------------------------------------------------------//

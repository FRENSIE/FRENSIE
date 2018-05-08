//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledElectronGeometryModel.cpp
//! \author Alex Robinson
//! \brief  The filled electron geometry model class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FilledElectronGeometryModel.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"

namespace MonteCarlo{

// Load the scattering centers
void FilledElectronGeometryModel::loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const
{
  ElectroatomFactory electroatom_factory( database_path,
                                          unique_scattering_center_names,
                                          scattering_center_definitions,
                                          atomic_relaxation_model_factory,
                                          properties,
                                          verbose );

  electroatom_factory.createElectroatomMap( scattering_center_name_map );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledElectronGeometryModel.cpp
//---------------------------------------------------------------------------//

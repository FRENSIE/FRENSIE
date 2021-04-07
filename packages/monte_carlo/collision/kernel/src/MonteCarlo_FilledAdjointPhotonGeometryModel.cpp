//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledAdjointPhotonGeometryModel.cpp
//! \author Alex Robinson
//! \brief  The filled adjoint photon geometry model class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FilledAdjointPhotonGeometryModel.hpp"
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"

namespace MonteCarlo{

// Load the scattering centers
void FilledAdjointPhotonGeometryModel::loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const
{
  AdjointPhotoatomFactory adjoint_photoatom_factory( database_path,
                                                     unique_scattering_center_names,
                                                     scattering_center_definitions,
                                                     properties,
                                                     verbose );

  adjoint_photoatom_factory.createAdjointPhotoatomMap( scattering_center_name_map );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledAdjointPhotonGeometryModel.cpp
//---------------------------------------------------------------------------//

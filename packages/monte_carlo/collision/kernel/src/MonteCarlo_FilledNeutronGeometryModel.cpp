//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledNeutronGeometryModel.cpp
//! \author Alex Robinson
//! \brief  The filled neutron geometry model class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FilledNeutronGeometryModel.hpp"
#include "MonteCarlo_NuclideFactory.hpp"

namespace MonteCarlo{

// Load the scattering centers
void FilledNeutronGeometryModel::loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const
{
  // Load the nuclides of interest
  NuclideFactory nuclide_factory( database_path,
                                  unique_scattering_center_names,
                                  scattering_center_definitions,
                                  properties,
                                  verbose );

  nuclide_factory.createNuclideMap( scattering_center_name_map );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledNeutronGeometryModel.cpp
//---------------------------------------------------------------------------//

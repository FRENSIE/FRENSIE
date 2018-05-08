//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledAdjointElectronGeometryModel.cpp
//! \author Alex Robinson
//! \brief  The filled adjoint electron geometry model class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FilledAdjointElectronGeometryModel.hpp"
#include "MonteCarlo_AdjointElectroatomFactory.hpp"

namespace MonteCarlo{

// Load the scattering centers
void FilledAdjointElectronGeometryModel::loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const
{
  AdjointElectroatomFactory adjoint_electroatom_factory(
                                                database_path,
                                                unique_scattering_center_names,
                                                scattering_center_definitions,
                                                properties,
                                                verbose );

  adjoint_electroatom_factory.createAdjointElectroatomMap( scattering_center_name_map );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledAdjointElectronGeometryModel.cpp
//---------------------------------------------------------------------------//

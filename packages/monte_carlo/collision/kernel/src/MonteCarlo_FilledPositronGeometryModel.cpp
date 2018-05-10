//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledPositronGeometryModel.cpp
//! \author Alex Robinson
//! \brief  The filled positron geometry model class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_FilledPositronGeometryModel.hpp"
#include "MonteCarlo_PositronatomFactory.hpp"

namespace MonteCarlo{

// Load the scattering centers
void FilledPositronGeometryModel::loadScatteringCenters(
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
  PositronatomFactory positronatom_factory( database_path,
                                            unique_scattering_center_names,
                                            scattering_center_definitions,
                                            atomic_relaxation_model_factory,
                                            properties,
                                            verbose );

  positronatom_factory.createPositronatomMap( scattering_center_name_map );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledPositronGeometryModel.cpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledAdjointElectronGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The filled adjoint electron geometry model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FILLED_ADJOINT_ELECTRON_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_FILLED_ADJOINT_ELECTRON_GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardFilledAdjointParticleGeometryModel.hpp"
#include "MonteCarlo_AdjointElectronMaterial.hpp"

namespace MonteCarlo{

//! The filled adjoint electron geometry model class
class FilledAdjointElectronGeometryModel : public StandardFilledAdjointParticleGeometryModel<AdjointElectronMaterial>
{
  // Typedef for the base type
  typedef StandardFilledAdjointParticleGeometryModel<AdjointElectronMaterial> BaseType;

public:

  //! Typedef for the material type
  typedef BaseType::MaterialType MaterialType;

  //! Typedef for the scattering center name map
  typedef BaseType::ScatteringCenterNameMap ScatteringCenterNameMap;

  //! Typedef for the reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef BaseType::ParticleStateType ParticleStateType;

protected:

  //! Constructor
  using StandardFilledAdjointParticleGeometryModel<AdjointElectronMaterial>::StandardFilledAdjointParticleGeometryModel;

  //! Load the scattering centers
  void loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const final override;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FILLED_ADJOINT_ELECTRON_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledAdjointElectronGeometryModel.hpp
//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledAdjointPhotonGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The filled adjoint photon geometry model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FILLED_ADJOINT_PHOTON_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_FILLED_ADJOINT_PHOTON_GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardFilledAdjointParticleGeometryModel.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"

namespace MonteCarlo{

//! The filled adjoint photon geometry model class
class FilledAdjointPhotonGeometryModel : public StandardFilledAdjointParticleGeometryModel<AdjointPhotonMaterial>
{
  // Typedef for the base type
  typedef StandardFilledAdjointParticleGeometryModel<AdjointPhotonMaterial> BaseType;

public:

  //! Typedef for the material type
  typedef BaseType::MaterialType MaterialType;

  //! Typedef for the scattering center name map
  typedef BaseType::ScatteringCenterNameMap ScatteringCenterNameMap;

  //! Typedef for the reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! Destructor
  ~FilledAdjointPhotonGeometryModel()
  { /* ... */ }

protected:

  //! Constructor
  using StandardFilledAdjointParticleGeometryModel<AdjointPhotonMaterial>::StandardFilledAdjointParticleGeometryModel;

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

#endif // end MONTE_CARLO_FILLED_ADJOINT_PHOTON_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledAdjointPhotonGeometryModel.hpp
//---------------------------------------------------------------------------//


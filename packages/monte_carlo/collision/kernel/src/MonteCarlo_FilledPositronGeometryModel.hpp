//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledPositronGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The filled positron geometry model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FILLED_POSITRON_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_FILLED_POSITRON_GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardFilledParticleGeometryModel.hpp"
#include "MonteCarlo_PositronMaterial.hpp"

namespace MonteCarlo{

//! The filled positron geometry model class
class FilledPositronGeometryModel : public StandardFilledParticleGeometryModel<PositronMaterial>
{
  // Typedef for the base type
  typedef StandardFilledParticleGeometryModel<PositronMaterial> BaseType;

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
  ~FilledPositronGeometryModel()
  { /* ... */ }

protected:

  //! Constructor
  using StandardFilledParticleGeometryModel<PositronMaterial>::StandardFilledParticleGeometryModel;

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

#endif // end MONTE_CARLO_FILLED_POSITRON_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledPositronGeometryModel.hpp
//---------------------------------------------------------------------------//

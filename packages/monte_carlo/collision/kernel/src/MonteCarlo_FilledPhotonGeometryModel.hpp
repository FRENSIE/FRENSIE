//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledPhotonGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The filled photon geometry model class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FILLED_PHOTON_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_FILLED_PHOTON_GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardFilledParticleGeometryModel.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"

namespace MonteCarlo{

//! The filled photon geometry model class
class FilledPhotonGeometryModel : public StandardFilledParticleGeometryModel<PhotonMaterial>
{
  // Typedef for the base type
  typedef StandardFilledParticleGeometryModel<PhotonMaterial> BaseType;

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
  ~FilledPhotonGeometryModel()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                               const PhotonState& photon,
                               const PhotonuclearReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                         const Geometry::Model::EntityId cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                               const PhotonState& photon,
                               const PhotonuclearReactionType reaction ) const;

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                         const Geometry::Model::EntityId cell,
                         const double energy,
                         const PhotonuclearReactionType reaction ) const;

protected:

  //! Constructor
  using StandardFilledParticleGeometryModel<PhotonMaterial>::StandardFilledParticleGeometryModel;

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

#endif // end MONTE_CARLO_FILLED_PHOTON_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledPhotonGeometryModel.hpp
//---------------------------------------------------------------------------//

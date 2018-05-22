//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterialParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Photon material particle response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_PHOTON_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_MaterialParticleResponseFunction.hpp"

namespace MonteCarlo{

//! The photon material particle response function
class PhotonMaterialParticleResponseFunction : public MaterialParticleResponseFunction<PhotonMaterial>
{
  // Typedef for the base type
  typedef MaterialParticleResponseFunction<PhotonMaterial> BaseType;

public:

  //! Constructor (photoatomic reaction)
  PhotonMaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::InternalCellHandle cell,
                       const PhotoatomicReactionType reaction );

  //! Constructor (photonuclear reaction)
  PhotonMaterialParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::InternalCellHandle cell,
                       const PhotonuclearReactionType reaction );

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Get a description of the response function
  std::string description() const override;

private:

  // Use the photonuclear reaction type
  bool d_use_photonuclear_reaction_type;

  // The photonuclear reaction
  PhotonuclearReactionType d_photonuclear_reaction;

  // The evaluate method
  std::function<double(const ParticleState&)> d_evaluation_method;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_MATERIAL_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterialParticleResponseFunction.hpp
//---------------------------------------------------------------------------//

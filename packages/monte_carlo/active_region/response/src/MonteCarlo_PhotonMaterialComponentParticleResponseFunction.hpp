//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonMaterialComponentParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Photon material particle response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_PHOTON_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_MaterialComponentParticleResponseFunction.hpp"

namespace MonteCarlo{

//! The photon material component particle response function
class PhotonMaterialComponentParticleResponseFunction : public MaterialComponentParticleResponseFunction<PhotonMaterial>
{
  // Typedef for the base type
  typedef MaterialComponentParticleResponseFunction<PhotonMaterial> BaseType;
  
public:

  //! Constructor (photoatomic reaction)
  PhotonMaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const PhotoatomicReactionType reaction );

  //! Constructor (photonuclear reaction)
  PhotonMaterialComponentParticleResponseFunction(
                       const std::shared_ptr<const FilledGeometryModel>& model,
                       const Geometry::Model::EntityId cell,
                       const std::string& component_name,
                       const PhotonuclearReactionType reaction );

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const override;

  //! Get a description of the response function
  std::string description() const override;

private:
 
  // Default Constructor
  PhotonMaterialComponentParticleResponseFunction()
  { /* ... */ }

  // Evaluate the photonuclear reaction cross section
  double evaluatePhotonuclearReactionCrossSection( const ParticleState& particle ) const;

  // Set the evaluation method
  void setEvaluationMethod();

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Use the photonuclear reaction type
  bool d_use_photonuclear_reaction_type;

  // The photonuclear reaction
  PhotonuclearReactionType d_photonuclear_reaction;

  // The evaluate method
  std::function<double(const ParticleState&)> d_evaluation_method;
};

// Save the data to an archive
template<typename Archive>
void PhotonMaterialComponentParticleResponseFunction::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_use_photonuclear_reaction_type );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_reaction );
}

// Load the data from an archive
template<typename Archive>
void PhotonMaterialComponentParticleResponseFunction::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_use_photonuclear_reaction_type );
  ar & BOOST_SERIALIZATION_NVP( d_photonuclear_reaction );

  // Set the evaluation method
  this->setEvaluationMethod();
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( PhotonMaterialComponentParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PhotonMaterialComponentParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, PhotonMaterialComponentParticleResponseFunction );

#endif // end MONTE_CARLO_PHOTON_MATERIAL_COMPONENT_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonMaterialComponentParticleResponseFunction.hpp
//---------------------------------------------------------------------------//

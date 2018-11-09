//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightCutoffRoulette.cpp
//! \author Luke Kersting
//! \brief  Weight cutoff roulette class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_WeightCutoffRoulette.hpp"

namespace MonteCarlo{

//! The default weight cutoff roulette
class DefaultWeightCutoffRoulette : public WeightCutoffRoulette
{

public:

  //! Constructor
  DefaultWeightCutoffRoulette()
  { /* ... */ }

  //! Destructor
  ~DefaultWeightCutoffRoulette()
  { /* ... */ }

  //! Return the roulette cutoff weights for the specified particle type
  void getCutoffWeights( const ParticleType,
                         WeightType&,
                         WeightType& ) const final override
  { /* ... */ }

  //! Return the particle types that will have weight cutoff rouletting
  void getParticleTypes( std::set<ParticleType>& ) const final override
  { /* ... */ }

  //! Update the particle state and bank
  void rouletteParticleWeight( ParticleState& ) const final override
  { /* ... */ }

private:

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( WeightCutoffRoulette ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Get the default weight cutoff roulette
std::shared_ptr<const WeightCutoffRoulette> WeightCutoffRoulette::getDefault()
{
  return std::shared_ptr<const WeightCutoffRoulette>( new DefaultWeightCutoffRoulette );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::DefaultWeightCutoffRoulette, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DefaultWeightCutoffRoulette, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( DefaultWeightCutoffRoulette, MonteCarlo );

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::WeightCutoffRoulette );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultWeightCutoffRoulette );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightCutoffRoulette.cpp
//---------------------------------------------------------------------------//

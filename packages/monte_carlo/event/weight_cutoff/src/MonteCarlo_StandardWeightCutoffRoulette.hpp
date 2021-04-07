//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardWeightCutoffRoulette.hpp
//! \author Luke Kersting
//! \brief  Standard weight cutoff roulette class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_WEIGHT_CUTOFF_ROULETTE_HPP
#define MONTE_CARLO_STANDARD_WEIGHT_CUTOFF_ROULETTE_HPP

// FRENSIE Includes
#include "MonteCarlo_WeightCutoffRoulette.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The weight cutoff roulette class
class StandardWeightCutoffRoulette : public WeightCutoffRoulette
{

public:

  //! The entity id type
  typedef WeightCutoffRoulette::WeightType WeightType;


  //! Constructor
  StandardWeightCutoffRoulette();

  //! Destructor
  ~StandardWeightCutoffRoulette()
  { /* ... */ }

  //! Set the roulette cutoff weights for the specified particle type
  void setCutoffWeights( const ParticleType particle_type,
                         const WeightType& threshold_weight,
                         const WeightType& survival_weight );

  //! Return the roulette cutoff weights for the specified particle type
  void getCutoffWeights( const ParticleType particle_type,
                         WeightType& threshold_weight,
                         WeightType& survival_weight ) const final override;

  //! Return the particle types that will have weight cutoff rouletting
  void getParticleTypes( std::set<ParticleType>& particle_types ) const final override;

  //! Roulette the particle weight based on the threshold and survival weights
  void rouletteParticleWeight( ParticleState& particle ) const final override;

private:

  // Save the weight cutoff roulette data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the weight cutoff roulette data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The cutoff roulette weights
  typedef std::pair<double,double> RouletteCutoffWeightData;
  typedef std::map<ParticleType,RouletteCutoffWeightData> ParticleTypeWeightCutoffRouletteMap;
  ParticleTypeWeightCutoffRouletteMap d_roulette_cutoff_weights;
};

// Save the weight cutoff roulette data to an archive
template<typename Archive>
void StandardWeightCutoffRoulette::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( WeightCutoffRoulette );
  ar & BOOST_SERIALIZATION_NVP( d_roulette_cutoff_weights );
}

// Load the weight cutoff roulette data from an archive
template<typename Archive>
void StandardWeightCutoffRoulette::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( WeightCutoffRoulette );
  ar & BOOST_SERIALIZATION_NVP( d_roulette_cutoff_weights );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardWeightCutoffRoulette, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardWeightCutoffRoulette, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardWeightCutoffRoulette );

#endif // end MONTE_CARLO_STANDARD_WEIGHT_CUTOFF_ROULETTE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardWeightCutoffRoulette.hpp
//---------------------------------------------------------------------------//

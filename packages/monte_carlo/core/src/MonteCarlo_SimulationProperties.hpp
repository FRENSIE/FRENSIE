//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "MonteCarlo_ParticleType.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 *
 * This class has been designed as a mix-in class. It can be used as the
 * control point for all runtime configuration options used in a Monte Carlo
 * simulation.
 */
class SimulationProperties : public SimulationGeneralProperties,
                             public SimulationNeutronProperties,
                             public SimulationPhotonProperties,
                             public SimulationAdjointPhotonProperties,
                             public SimulationElectronProperties,
                             public SimulationAdjointElectronProperties
{

public:

  //! Constructor
  SimulationProperties()
  { /* ... */ }

  //! Destructor
  ~SimulationProperties()
  { /* ... */ }

  //! Return the min particle energy
  template<typename ParticleType>
  double getMinParticleEnergy() const;

  //! Return the max particle energy
  template<typename ParticleType>
  double getMaxParticleEnergy() const;

  //! Set atomic relaxation mode to off
  void setAtomicRelaxationModeOff( const ParticleType particle );

  //! Set atomic relaxation mode to on
  void setAtomicRelaxationModeOn( const ParticleType particle );

  //! Return if atomic relaxation mode is on
  bool isAtomicRelaxationModeOn( const ParticleType particle ) const;

  //! Return the cutoff roulette threshold weight
  template<typename ParticleType>
  double getRouletteThresholdWeight() const;

  //! Return the cutoff roulette survival weight
  template<typename ParticleType>
  double getRouletteSurvivalWeight() const;

private:

  // Save/load the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationProperties, "SimulationProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationProperties );

#endif // end !defined SWIG

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_SimulationProperties_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.hpp
//---------------------------------------------------------------------------//

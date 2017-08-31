//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_PROPERTIES_HPP

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
 * \details This class has been designed as a mix-in class
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
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_SimulationProperties_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.hpp
//---------------------------------------------------------------------------//

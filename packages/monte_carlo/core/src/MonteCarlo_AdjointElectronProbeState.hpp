//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronProbeState.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron probe state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_PROBE_STATE_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_PROBE_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"

namespace MonteCarlo{

/*! The adjoint electron probe state class
 * \details The probe state get killed when its energy changes (after being
 * activated).
 */
class AdjointElectronProbeState : public AdjointElectronState
{

public:

  // The adjoint electron probe tag
  struct AdjointElectronProbeTag{};

  // Typedef for the adjoint electron probe tag
  struct AdjointElectronProbeTag ParticleTag;

  //! Default constructor
  AdjointElectronProbeState();

  //! Constructor
  AdjointElectronProbeState( 
		       const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronProbeState( const ParticleState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronProbeState( const AdjointElectronProbeState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );


  //! Destructor
  ~AdjointElectronProbeState()
  { /* ... */ }

  //! Set the energy of the particle (MeV)
  void setEnergy( const energyType energy );

  //! Check if this is a probe
  bool isProbe() const;

  //! Activate the probe
  void activate();

  //! Returns if the probe is active
  bool isActive() const;

  //! Clone the particle state (do not use to generate new particles!)
  AdjointElectronProbeState* clone() const;

  //! Print the adjoint electron state
  void print( std::ostream& os ) const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AdjointElectronState);
    ar & BOOST_SERIALIZATION_NVP( d_active );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Flag that indicates if the probe is active
  bool d_active;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::AdjointElectronProbeState, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::AdjointElectronProbeState, 
			 "AdjointElectronProbeState" );

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_PROBE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronProbeState.hpp
//---------------------------------------------------------------------------//

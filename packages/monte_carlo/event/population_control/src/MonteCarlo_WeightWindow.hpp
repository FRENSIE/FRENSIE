//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindow.hpp
//! \author Alex Robinson
//! \brief  Weight window class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_WINDOW_HPP
#define MONTE_CARLO_WEIGHT_WINDOW_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PopulationControl.hpp"
#include "MonteCarlo_DiscretizableParticleHistoryObserver.hpp"

namespace MonteCarlo{

//! The weight window base class
class WeightWindow: public DiscretizableParticleHistoryObserver,
                    public PopulationControl
{

public:

  //! Constructor
  WeightWindow()
  { /* ... */ }

  //! Destructor
  virtual ~WeightWindow()
  { /* ... */ }

  virtual void checkParticleWithWeightWindow(ParticleState& particle,
                                             ParticleBank& bank) const;

  static std::shared_ptr<const WeightWindow> getDefault();

  
  /* The below methods are not used for weight windows but must be defined due to being pure virtual in the Particle History Observer
     class. At some point, this will need to be fixed and these methods removed */
  void enableThreadSupport( const unsigned num_threads ) final override;

  bool hasUncommittedHistoryContribution() const final override;

  void commitHistoryContribution();

  void takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                             const double time_since_last_snapshot ) final override;

  void resetData() final override;

  void reduceData( const Utility::Communicator& comm,
                           const int root_process ) final override;

  void printSummary( std::ostream& os ) const final override;

};
  

} // end MonteCarlo namespace


#endif // end MONTE_CARLO_WEIGHT_WINDOW_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindow.hpp
//---------------------------------------------------------------------------//

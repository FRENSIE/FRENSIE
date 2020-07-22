//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.cpp
//! \author Philip Britt
//! \brief  Weight window mesh class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_WeightWindow.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Update the particle state and bank
void WeightWindow::checkParticleWithWeightWindow( ParticleState& particle,
                                                  ParticleBank& bank ) const
{
  double weight = particle.getWeight();
}

//! The default weight window
class DefaultWeightWindow : public WeightWindow
{

public:

  //! Constructor
  DefaultWeightWindow()
  { /* ... */ }

  //! Destructor
  ~DefaultWeightWindow()
  { /* ... */ }

  //! Update the particle state and bank by passing through the weight window
  void checkParticleWithWeightWindow( ParticleState&, ParticleBank& ) const final override
  { /* ... */ }

};

// Return the default weight window - used when there are no weight windows applied
std::shared_ptr<const WeightWindow> WeightWindow::getDefault()
{
  return std::shared_ptr<const WeightWindow>( new DefaultWeightWindow );
}

/* The below functions should not be used */
void WeightWindow::enableThreadSupport( const unsigned num_threads )
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

bool WeightWindow::hasUncommittedHistoryContribution() const
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

void WeightWindow::commitHistoryContribution()
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

void WeightWindow::takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                            const double time_since_last_snapshot )
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

void WeightWindow::resetData()
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

void WeightWindow::reduceData( const Utility::Communicator& comm,
                          const int root_process )
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

void WeightWindow::printSummary( std::ostream& os ) const
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for weight windows")
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//
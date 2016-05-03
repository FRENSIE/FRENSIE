//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron hard elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution base class
class AtomicExcitationElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the atomic excitation distribution
  typedef Teuchos::RCP<const Utility::OneDDistribution> AtomicDistribution;

  //! Constructor
  AtomicExcitationElectronScatteringDistribution(
    const AtomicDistribution& energy_loss_distribution );

  //! Destructor 
  virtual ~AtomicExcitationElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const
  { /*...*/}

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const
  { /*...*/}

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const
  { /* ... */ }

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double precision) const
  { /*...*/}


  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
	                      ParticleBank& bank,
                        SubshellType& shell_of_interaction ) const;

private:

  // Atomic excitation energy loss table
  AtomicDistribution d_energy_loss_distribution;


};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

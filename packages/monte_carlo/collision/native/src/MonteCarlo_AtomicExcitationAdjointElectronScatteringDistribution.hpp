//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribuiton.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation adjoint electron scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The atomic excitation adjoint electron scattering distribution class
class AtomicExcitationAdjointElectronScatteringDistribution : public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the adjoint atomic excitation distribution
  typedef Teuchos::RCP<const Utility::OneDDistribution> AtomicDistribution;

  //! Constructor
  AtomicExcitationAdjointElectronScatteringDistribution(
	       const double max_energy,
	       const AtomicDistribution& energy_gain_distribution );

  //! Destructor
  virtual ~AtomicExcitationAdjointElectronScatteringDistribution()
  { /* ... */ }

 //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double precision) const;


  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& electron,
                               ParticleBank& bank,
                               SubshellType& shell_of_interaction ) const;
  
protected:

  //! Return the max energy
  double getMaxEnergy() const;

  
private:

  // adjoint atomic excitation energy gain tables
  AtomicDistribution d_energy_gain_distribution;
  
  // The maximum energy
  double d_max_energy;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

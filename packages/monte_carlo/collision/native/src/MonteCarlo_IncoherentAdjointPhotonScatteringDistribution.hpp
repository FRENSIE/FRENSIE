//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistribuiton.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The incoherent adjoint photon scattering distribution class
class IncoherentAdjointPhotonScatteringDistribution : public AdjointPhotonScatteringDistribution
{

protected:

  //! Typedef for ArrayRCP const iterator
  typedef Teuchos::ArrayRCP<const double>::const_iterator LineEnergyIterator;

public:

  //! Constructor
  IncoherentAdjointPhotonScatteringDistribution(
	       const double max_energy,
	       const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Destructor
  virtual ~IncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the pdf
  double evaluatePDF( const double incoming_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the pdf efficiently
  double evaluatePDFEfficient( const double incoming_energy,
			       const double scattering_angle_cosine,
			       const double integrated_cross_section ) const;

  //! Check if an energy is in the scattering window
  bool isEnergyInScatteringWindow( const double energy_of_interest,
				   const double initial_energy ) const;

  //! Check if an energy is below the scattering window
  virtual bool isEnergyBelowScatteringWindow( 
					   const double energy_of_interest,
					   const double initial_energy ) const;

  //! Check if an energy is above the scattering window
  virtual bool isEnergyAboveScatteringWindow( 
					   const double energy_of_interest,
					   const double initial_energy ) const;

  //! Create a probe particle
  virtual void createProbeParticle( const double energy_of_interest, 
				    const AdjointPhotonState& adjoint_photon,
				    ParticleBank& bank ) const = 0;

  //! Return the max energy
  double getMaxEnergy() const;
  
protected:

  //! Evaluate the adjoint Klein-Nishina distribution
  double evaluateAdjointKleinNishinaDist( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

  //! Basic sampling implementation
  void sampleAndRecordTrialsAdjointKleinNishina( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const;

  // Return only the critical line energies that can be scattered into
  void getCriticalLineEnergiesInScatteringWindow( 
					const double energy,
				        LineEnergyIterator& start_energy,
					LineEnergyIterator& end_energy ) const;

  //! Create the probe particles
  void createProbeParticles( const AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank ) const;
  
private:

  // The maximum energy
  double d_max_energy;

  // The critical line energies
  Teuchos::ArrayRCP<const double> d_critical_line_energies;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//

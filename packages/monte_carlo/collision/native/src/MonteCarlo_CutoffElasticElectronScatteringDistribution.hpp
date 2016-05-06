//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron cutoff elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The cutoff scattering distribution base class
class CutoffElasticElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the  elastic distribution
  typedef Teuchos::Array<Utility::Pair< double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Constructor
  CutoffElasticElectronScatteringDistribution(
        const ElasticDistribution& cutoff_elastic_scattering_distribution,
        const double upper_cutoff_angle_cosine = 0.999999 );

  //! Destructor 
  virtual ~CutoffElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the distribution
  double evaluate( const unsigned incoming_energy_bin,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const unsigned incoming_energy_bin,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the cross section ratio for the cutoff angle cosine
  double evaluateCutoffCrossSectionRatio( const double incoming_energy ) const;

  //! Return the energy at a given energy bin
  double getEnergy( const unsigned energy_bin ) const;

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
                        Data::SubshellType& shell_of_interaction ) const;
                    
protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

private:

  // The cutoff scattering angle cosine (mu) below which the cutoff distribution is used
  double d_upper_cutoff_angle_cosine;

  // The cutoff change in scattering angle cosine (delta mu) above which the cutoff distribution is used
  double d_lower_cutoff_delta_mu;

  // cutoff elastic scattering distribution (no screened Rutherford data)
  ElasticDistribution d_elastic_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CUTOFF_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

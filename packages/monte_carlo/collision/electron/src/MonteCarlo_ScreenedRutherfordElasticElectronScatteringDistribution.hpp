//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The screened Rutherford elastic electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronTraits.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class ScreenedRutherfordElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                                public PositronScatteringDistribution,
                                                                public AdjointElectronScatteringDistribution
{

public:

  //! The counter type
  typedef ElectronScatteringDistribution::Counter Counter;
  
  //! The elastic distribution type
  typedef std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
            ElasticDistribution;

  //! Typedef for the Elastic electron traits
  typedef MonteCarlo::ElasticElectronTraits ElasticTraits;

  //! Constructor
  ScreenedRutherfordElasticElectronScatteringDistribution(
    const int atomic_number,
    const bool seltzer_modification_on = true );

  //! Destructor
  virtual ~ScreenedRutherfordElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const override;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine,
                   const double eta ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine,
                      const double eta ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override;
  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine,
                      const double eta ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              Counter& trials ) const override;

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
                        ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the positron
  void scatterPositron( MonteCarlo::PositronState& positron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& adjoint_electron,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const override;

protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  Counter& trials ) const;

private:

  // Elastic electron traits
  std::shared_ptr<const ElasticTraits> d_elastic_traits;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

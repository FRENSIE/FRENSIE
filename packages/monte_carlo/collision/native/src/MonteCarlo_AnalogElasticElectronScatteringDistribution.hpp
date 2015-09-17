//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron analog elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

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
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class AnalogElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                    public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the  elastic distribution
  typedef Teuchos::Array<Utility::Pair< double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Constructor
  AnalogElasticElectronScatteringDistribution(
        const ElasticDistribution& elastic_scattering_distribution,
        const double lower_cutoff_angle = 1.0e-6,
        const bool angle_is_used_as_independent_variable = true );

  //! Destructor 
  virtual ~AnalogElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle ) const;

  //! Evaluate the distribution
  double evaluate( const unsigned incoming_energy_bin,
                   const double scattering_angle ) const;

  //! Evaluate the PDF
  double evaluate( const double incoming_energy,
                   const double scattering_angle ) const;

  //! Evaluate the PDF
  double evaluatePDF( const unsigned incoming_energy_bin,
                      const double scattering_angle ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle ) const;

  //! Evaluate the cross section ratio for the cutoff angle
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
                        SubshellType& shell_of_interaction ) const;
                        
  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& adjoint_electron,
                               ParticleBank& bank,
                               SubshellType& shell_of_interaction ) const;



//protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

private:

  // The scattering angle above which the analog distribution is used
  double d_lower_cutoff_angle;

  // Independent parameter flag: false = angle cosine, true = angle (in units of pi)
  bool d_angle_is_used_as_independent_variable;

  // elastic scattering distribution without forward screening data
  ElasticDistribution d_elastic_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

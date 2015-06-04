//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron hard elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HARD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_HARD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

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
class HardElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                  public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the  elastic distribution
  typedef Teuchos::Array<Utility::Pair< double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Constructor
  HardElasticElectronScatteringDistribution(
                 const int atomic_number,
                 const ElasticDistribution& elastic_scattering_distribution);

  //! Destructor 
  virtual ~HardElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
                           const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
virtual double evaluatePDF( const double incoming_energy,
const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSection( const double incoming_energy,
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

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
                        ParticleBank& bank,
                        SubshellType& shell_of_interaction ) const;
                        
  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& electron,
                               ParticleBank& bank,
                               SubshellType& shell_of_interaction ) const;



protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

  // Evaluate the screening angle at the given electron energy
  double evaluateScreeningFactor( const double energy ) const;

  // Evaluate the scattering angle from the analytical function
  double evaluateScreenedScatteringAngle( const double energy ) const; 

  // Sample a scattering angle cosine
  double sampleScatteringAngleCosine( const double energy ) const;

private:

  // Cutoff angle cosine between the distribution and analytical function
  static double s_mu_cutoff;

  // Difference btw cutoff angle cosine and forward peak (mu = 1)
  static double s_delta_cutoff;

  // The fine structure constant (fsc) squared
  static double s_fine_structure_const_squared;

  // A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
  static double s_screening_param1;

  // Atomic number (Z) of the target atom
  int d_atomic_number;

  // Atomic number (Z) of the target atom to the 2/3 power (Z^2/3)
  double d_Z_two_thirds_power;

  // A parameter for moliere's screening factor (3.76*fsc**2*Z**2)
  double d_screening_param2;

  // elastic scattering distribution without forward screening data
  ElasticDistribution d_elastic_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

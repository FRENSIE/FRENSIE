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
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class HardElasticElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the  elastic distribution
  typedef Teuchos::Array<Utility::Pair<double,
                                     Teuchos::RCP<Utility::OneDDistribution> > >
                                     ElasticDistribution;

  //! Constructor
  HardElasticElectronScatteringDistribution(
                 const int atomic_number,
                 const double cutoff_angle_cosine,
                 const ElasticDistribution& elastic_scattering_distribution);

  //! Destructor 
  virtual ~HardElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
	                    ParticleBank& bank,
                        SubshellType& shell_of_interaction ) const;

//protected:

// Evaluate the screening angle at the given electron energy
double evaluateScreeningAngle( const double energy ) const;

// Evaluate the scattering angle from the analytical function
double evaluateScreenedScatteringAngle( const double energy ) const; 

private:

  // Atomic number (Z) of the target atom
  const int d_atomic_number;

  // Cutoff angle cosine between the distribution and analytical function
  const double d_cutoff_angle_cosine;

  // elastic scattering distribution without forward screening data
  ElasticDistribution d_elastic_scattering_distribution;


};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

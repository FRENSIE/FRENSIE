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

  //! Typedef for the elastic distribution
  typedef Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::OneDDistribution> > >
                                                        ElasticDistribution;

  //! Typedef for the elastic interpolation array
  typedef Teuchos::Array< Utility::Pair< double,double > > WeightArray;

  //! Constructor
  HardElasticElectronScatteringDistribution(
  ElasticDistribution& elastic_scattering_distribution,
  WeightArray& interpolation_weights );

  //! Destructor
  virtual ~HardElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
	                    ParticleBank& bank) const;

private:

  // elastic scattering distribution 
  ElasticDistribution d_elastic_scattering_distribution;

  // energy grid interpolation fractions for elastic scattering distributions
  WeightArray d_interpolation_weights;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionFactory.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution factory base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_FACTORY_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution factory base class
class CoherentScatteringDistributionFactory
{

public:

  //! Create a Thompson distribution
  static void createThompsonDistribution(
                            Teuchos::RCP<const CoherentScatteringDistribution>&
			    coherent_distribution );

private:

  // The default Thompson distribution
  static Teuchos::RCP<const CoherentScatteringDistribution>
  s_thompson_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionFactory.hpp
//---------------------------------------------------------------------------//

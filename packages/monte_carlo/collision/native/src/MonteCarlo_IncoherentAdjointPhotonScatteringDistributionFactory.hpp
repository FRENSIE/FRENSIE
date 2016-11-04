//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution factory
//!         base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_FACTORY_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The incoherent adjoint photon scattering distribution factory base class
class IncoherentAdjointPhotonScatteringDistributionFactory
{

protected:

  //! Create a Klein-Nishina distribution
  static void createKleinNishinaDistribution(
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution,
          const double max_energy );
};
  
} // end MonteCarlo namespace


#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.hpp
//---------------------------------------------------------------------------//

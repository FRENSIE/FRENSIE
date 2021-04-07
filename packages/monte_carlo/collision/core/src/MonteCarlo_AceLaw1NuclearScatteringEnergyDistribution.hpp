//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.hpp
//! \author Alex Bennett
//! \brief  The nuclear equiprobable bin scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_1_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_1_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! \brief The inelastic equiprobable energy bins scattering energy
 * distribution class (ENDF Law 1)
 * \ingroup ace_laws
 */
class AceLaw1NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  typedef std::vector<std::pair<double,std::vector<double> > >
  EnergyDistArray;

  //! Constructor
  AceLaw1NuclearScatteringEnergyDistribution(EnergyDistArray& energy_grid);

  //! Destructor
  ~AceLaw1NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const override;

private:

  EnergyDistArray d_energy_grid;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_1_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//


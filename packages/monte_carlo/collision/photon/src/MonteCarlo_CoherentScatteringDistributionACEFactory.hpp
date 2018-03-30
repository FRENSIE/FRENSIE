//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"
#include "MonteCarlo_FormFactorSquared.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution factory class that uses ACE data
class CoherentScatteringDistributionACEFactory : public CoherentScatteringDistributionFactory
{

public:

  //! Create a basic coherent distribution
  static void createBasicCoherentDistribution(
			 const Data::XSSEPRDataExtractor& raw_photoatom_data,
			 std::shared_ptr<const CoherentScatteringDistribution>&
                         coherent_distribution );

  //! Create an efficient coherent distribution
  static void createEfficientCoherentDistribution(
			 const Data::XSSEPRDataExtractor& raw_photoatom_data,
			 std::shared_ptr<const CoherentScatteringDistribution>&
                         coherent_distribution );

protected:

  //! Create the form factor squared distribution
  static void createFormFactorSquared(
               const Data::XSSEPRDataExtractor& raw_photoatom_data,
               std::shared_ptr<const FormFactorSquared>& form_factor_squared );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

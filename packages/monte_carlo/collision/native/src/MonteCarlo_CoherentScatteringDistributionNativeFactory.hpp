//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution factory class that uses native data
class CoherentScatteringDistributionNativeFactory : public CoherentScatteringDistributionFactory
{

public:

  //! Create a basic coherent distribution
  template<typename NativeContainer, template<typename> class SmartPtr>
  static void createBasicCoherentDistribution(
                                const NativeContainer& raw_photoatom_data,
	                        SmartPtr<const CoherentScatteringDistribution>&
                                coherent_distribution );

  //! Create an efficient coherent distribution
  template<typename NativeContainer, template<typename> class SmartPtr>
  static void createEfficientCoherentDistribution(
                                const NativeContainer& raw_photoatom_data,
                                SmartPtr<const CoherentScatteringDistribution>&
                                coherent_distribution );

protected:

  //! Create the form factor squared distribution
  template<typename NativeContainer, template<typename> class SmartPtr>
  static void createFormFactorSquared(
                              const NativeContainer& raw_photoatom_data,
                              SmartPtr<const FormFactorSquared>& form_factor );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoherentScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistribution.i
//! \author Luke Kersting
//! \brief  The ElectronScatteringDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp"
%}

// Include std::string support
%include <std_string.i>

// C++ STL support
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the PyFrensie Teuchos Array conversion helpers
%import "PyFrensie_ArrayConversionHelpers.hpp"

// Import the explicit template instantiation helpers
%import "Utility_ExplicitTemplateInstantiationMacros.hpp"

// Include the electron scattering distribution distribution helpers
%include "MonteCarlo_ElectronScatteringDistributionHelpers.i"

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AnalogElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::HybridElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::CutoffElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::MomentPreservingElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::BremsstrahlungElectronScatteringDistribution)
%shared_ptr(MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution)
%shared_ptr(MonteCarlo::AtomicExcitationElectronScatteringDistribution)

// Ignore scatter electron
%ignore *::scatterElectron( ElectronState&, ParticleBank&, Data::SubshellType& ) const;
/*%ignore ElectronState;*/
/*%ignore ParticleBank;*/

/*%apply MonteCarlo::ElectronState& INOUT { ElectronState& electron };*/
/*%apply MonteCarlo::ParticleBank& INOUT { ParticleBank& bank };*/

//---------------------------------------------------------------------------//
// Add support for the electron scattering distribution native factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::ElectronScatteringDistributionNativeFactoryHelpers
"The Electron Scattering Distribution Native Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the elastic electron scattering distributions
//---------------------------------------------------------------------------//

// Add a general typemap for sampling
%apply double& OUTPUT { double& outgoing_energy };
%apply double& OUTPUT { double& scattering_angle_cosine };

%include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( AnalogElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( HybridElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( CutoffElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( MomentPreservingElasticElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the bremsstrahlung electron scattering distribution
//---------------------------------------------------------------------------//

// Add a typemap for sampling bremsstrahlung distribution
%apply double& OUTPUT { double& photon_energy };
%apply double& OUTPUT { double& photon_angle_cosine };

%include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( BremsstrahlungElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the electroionization subshell electron scattering distribution
//---------------------------------------------------------------------------//

// Add a typemap for sampling electroionization subshell distribution
%apply double& OUTPUT { double& knock_on_energy };
%apply double& OUTPUT { double& knock_on_angle_cosine };

%include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

// Basic electron scattering distribution interface setup
%electron_distribution_interface_setup( ElectroionizationSubshellElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the atomic excitation electron scattering distribution
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( AtomicExcitationElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistribution.i
//---------------------------------------------------------------------------//

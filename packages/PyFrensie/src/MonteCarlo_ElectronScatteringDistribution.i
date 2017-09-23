//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistribution.i
//! \author Luke Kersting
//! \brief  The ElectronScatteringDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"
#include "MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp"
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
%shared_ptr(MonteCarlo::CoupledElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::HybridElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::CutoffElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::MomentPreservingElasticElectronScatteringDistribution)
%shared_ptr(MonteCarlo::BremsstrahlungElectronScatteringDistribution)
%shared_ptr(MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution)
%shared_ptr(MonteCarlo::AtomicExcitationElectronScatteringDistribution)
%shared_ptr(MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution)
%shared_ptr(MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution)
%shared_ptr(MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution)

// Ignore scatter electron
%ignore *::scatterElectron( ElectronState&, ParticleBank&, Data::SubshellType& ) const;
// Ignore scatter adjoint electron
%ignore *::scatterAdjointElectron( AdjointElectronState&, ParticleBank&, Data::SubshellType& ) const;


//---------------------------------------------------------------------------//
// Add support for the electron scattering distribution native factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::ElectronScatteringDistributionNativeFactoryHelpers
"The Electron Scattering Distribution Native Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the electron scattering distribution ACE factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::ElectronScatteringDistributionACEFactoryHelpers
"The Electron Scattering Distribution ACE Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the adjoint electron scattering distribution native factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::AdjointElectronScatteringDistributionNativeFactoryHelpers
"The Adjoint Electron Scattering Distribution Native Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the elastic electron scattering distributions (forward and adjoint)
//---------------------------------------------------------------------------//

// Add a general typemap for sampling
%apply double& OUTPUT { double& outgoing_energy };
%apply double& OUTPUT { double& scattering_angle_cosine };

%ignore *::evaluateMoliereScreeningConstant( const double, const double, const double, const double );

%ignore *::evaluateCDFAtCutoff( const double, const double );

%include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
%include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( CoupledElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( HybridElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( CutoffElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( ScreenedRutherfordElasticElectronScatteringDistribution )
%electron_distribution_interface_setup( MomentPreservingElasticElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the extra coupled electron scattering distribution functions
//---------------------------------------------------------------------------//

/*%feature("autodoc",*/
/*"evaluateMoliereScreeningConstant(DISTRIBUTION self, const double incoming_energy ) -> double" )*/
/*MonteCarlo::DISTRIBUTION::evaluateMoliereScreeningConstant;*/

/*%feature("autodoc",*/
/*"evaluateAtCutoff(DISTRIBUTION self, const double incoming_energy ) -> double" )*/
/*MonteCarlo::DISTRIBUTION::evaluateAtCutoff;*/

/*%feature("autodoc",*/
/*"evaluatePDFAtCutoff(DISTRIBUTION self, const double incoming_energy ) -> double" )*/
/*MonteCarlo::DISTRIBUTION::evaluatePDFAtCutoff;*/

/*%feature("autodoc",*/
/*"evaluateCDFAtCutoff(DISTRIBUTION self, const double incoming_energy ) -> double" )*/
/*MonteCarlo::DISTRIBUTION::evaluateCDFAtCutoff;*/

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

%apply double& OUTPUT { double& knock_on_energy };
%apply double& OUTPUT { double& knock_on_angle_cosine };

%include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

%feature("autodoc",
"samplePrimaryAndSecondary(ElectroionizationSubshellElectronScatteringDistribution self, const double incoming_energy) -> double, double, double, double")
MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributio::samplePrimaryAndSecondary;

// Basic electron scattering distribution interface setup
%electron_distribution_interface_setup( ElectroionizationSubshellElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the atomic excitation electron scattering distribution
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( AtomicExcitationElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the adjoint bremsstrahlung electron scattering distribution
//---------------------------------------------------------------------------//

// Add a typemap for sampling adjoint bremsstrahlung distribution
%apply double& OUTPUT { double& outgoing_energy };
%apply double& OUTPUT { double& outgoing_angle_cosine };

%include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( BremsstrahlungAdjointElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the adjoint electroionization subshell electron scattering distribution
//---------------------------------------------------------------------------//

// Add a typemap for sampling adjoint electroionization subshell distribution
%apply double& OUTPUT { double& outgoing_energy };
%apply double& OUTPUT { double& outgoing_angle_cosine };

%include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( ElectroionizationSubshellAdjointElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// Add support for the adjoint atomic excitation electron scattering distribution
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"

// Electron scattering distribution interface setup
%electron_distribution_interface_setup( AtomicExcitationAdjointElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistribution.i
//---------------------------------------------------------------------------//

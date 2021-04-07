//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Photon.i
//! \author Alex Robinson
//! \brief  The MonteCarlo.Photon sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_photon_docstring
"
PyFrensie.MonteCarlo.Photon is the python interface to the FRENSIE
monte_carlo/collision/photon subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_photon_docstring) Photon

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"

#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Data_NativeMomentPreservingElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Data_NuclearDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"

#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_CoherentScatteringDistribution.hpp"
#include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"

#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the classes needed to use the distribution interfaces
%import "Utility_DistributionTraits.hpp"
%import "Data_SubshellType.i"
%import "Data.ACE.i"
%import "Data.Native.i"
%import "MonteCarlo_ParticleState.i"
%import "MonteCarlo_IncoherentModelType.hpp"
%import "MonteCarlo_IncoherentAdjointModelType.hpp"
%import "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Global swig features
%feature("autodoc", "1");

// Add a few general typemaps
%typemap(in,numinputs=0) bool& energetically_possible (bool temp) "$1 = &temp;"

%typemap(argout) bool& energetically_possible {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) double& outgoing_energy (double temp) "$1 = &temp;"

%typemap(argout) double& outgoing_energy {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) double& electron_momentum_projection (double temp) "$1 = &temp;"

%typemap(argout) double& electron_momentum_projection {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%typemap(in,numinputs=0) double& scattering_angle_cosine (double temp) "$1 = &temp;"

%typemap(argout) double& scattering_angle_cosine {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%apply Utility::DistributionTraits::Counter& INOUT { Utility::DistributionTraits::Counter& trials };

%typemap(in,numinputs=0) Data::SubshellType& shell_of_interaction (Data::SubshellType temp) "$1 = &temp;"

%typemap(argout) Data::SubshellType& shell_of_interaction {
  %append_output(PyFrensie::convertToPython( static_cast<int>( *$1 ) ));
}

//---------------------------------------------------------------------------//
// Photon Kinematic Helpers Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_PhotonKinematicsHelpers.hpp"

//---------------------------------------------------------------------------//
// Adjoint Photon Kinematic Helpers Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"

//---------------------------------------------------------------------------//
// Scattering Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::ScatteringDistribution )
%include "MonteCarlo_ScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Photon Scattering Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::PhotonScatteringDistribution )
%include "MonteCarlo_PhotonScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Incoherent Photon Scattering Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::IncoherentPhotonScatteringDistribution )
%include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Incoherent Photon Scattering Distribution Factory Support
//---------------------------------------------------------------------------//
%typemap(in,numinputs=0) std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution>& incoherent_distribution (std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution> temp ) "$1 = &temp;"

%typemap(argout) std::shared_ptr<const MonteCarlo::IncoherentPhotonScatteringDistribution>& incoherent_distribution {
  std::shared_ptr< const MonteCarlo::IncoherentPhotonScatteringDistribution > *smartresult = *$1 ? new std::shared_ptr< const MonteCarlo::IncoherentPhotonScatteringDistribution >(*$1) : 0;
  %append_output(SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_MonteCarlo__IncoherentPhotonScatteringDistribution_t, SWIG_POINTER_OWN));
}

%include "MonteCarlo_IncoherentPhotonScatteringDistributionFactory.hpp"

//---------------------------------------------------------------------------//
// Incoherent Photon Scattering Distribution ACE Factory Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Incoherent Photon Scattering Distribution Native Factory Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// Doppler Broadened Photon Energy Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::DopplerBroadenedPhotonEnergyDistribution )
%include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"

//---------------------------------------------------------------------------//
// Complete Doppler Broadened Photon Energy Distribution
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution )
%include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"

//---------------------------------------------------------------------------//
// Subshell Doppler Broadened Photon Energy Distribution
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::SubshellDopplerBroadenedPhotonEnergyDistribution );
%include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"

//---------------------------------------------------------------------------//
// Doppler Broadened Photon Energy Distribution ACE Factory Support
//---------------------------------------------------------------------------//
%typemap(in,numinputs=0) std::vector<Data::SubshellType>& subshell_order (std::vector<Data::SubshellType> temp) "$1 = &temp;"

%typemap(argout) std::vector<Data::SubshellType>& subshell_order {
  std::vector<int> output( $1->begin(), $1->end() );
  
  %append_output(PyFrensie::convertToPython(output));
}

%extend MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory
{
  //! Create a coupled complete Doppler broadened photon energy dist
  static std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution> createCoupledCompleteDistribution(
                           const Data::XSSEPRDataExtractor& raw_photoatom_data,
                           const bool use_full_profile )
  {
    std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution> doppler_broadened_dist;

    MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
                                                        raw_photoatom_data,
                                                        doppler_broadened_dist,
                                                        use_full_profile );

    return doppler_broadened_dist;
  }

  //! Create a decoupled complete Doppler broadened photon energy dist
  static std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution> createDecoupledCompleteDistribution(
                           const Data::XSSEPRDataExtractor& raw_photoatom_data,
                           const bool use_full_profile )
  {
    std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution> doppler_broadened_dist;

    MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
                                                        raw_photoatom_data,
                                                        doppler_broadened_dist,
                                                        use_full_profile );

    return doppler_broadened_dist;
  }

  //! Create a subshell Doppler broadened photon energy dist
  static std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution> createSubshellDistribution(
                           const Data::XSSEPRDataExtractor& raw_photoatom_data,
                           const unsigned endf_subshell,
                           const bool use_full_profile )
  {
    std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution> doppler_broadened_dist;

    MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution(
                                                        raw_photoatom_data,
                                                        endf_subshell,
                                                        doppler_broadened_dist,
                                                        use_full_profile );

    return doppler_broadened_dist;
  }
};

%ignore MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution;
%ignore MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution;
%ignore MonteCarlo::DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution;

%include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Doppler Broadened Photon Energy Distribution Native Factory Support
//---------------------------------------------------------------------------//
%extend MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory
{
  //! Create a coupled complete Doppler broadened photon energy dist
  static std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution> createCoupledCompleteDistribution( const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data )
  {
    std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution> doppler_broadened_dist;

    MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution(
                                                      raw_photoatom_data,
                                                      doppler_broadened_dist );

    return doppler_broadened_dist;
  }

  //! Create a subshell distribution
  static std::shared_ptr<const MonteCarlo::SubshellDopplerBroadenedPhotonEnergyDistribution> createSubshellDistribution( const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
                                                                                                                         const unsigned endf_subshell )
  {
    std::shared_ptr<const MonteCarlo::SubshellDopplerBroadenedPhotonEnergyDistribution> doppler_broadened_dist;

    MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution(
                                                      raw_photoatom_data,
                                                      endf_subshell,
                                                      doppler_broadened_dist );

    return doppler_broadened_dist;
  }
};

%ignore MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createCoupledCompleteDistribution;
%ignore MonteCarlo::DopplerBroadenedPhotonEnergyDistributionNativeFactory::createSubshellDistribution;

%include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// Adjoint Photon Scattering Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::AdjointPhotonScatteringDistribution )
%include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Incoherent Adjoint Photon Scattering Distribution Support
//---------------------------------------------------------------------------//
%ignore MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::setExternalIntegratedCrossSectionEvaluator;
%ignore MonteCarlo::IncoherentAdjointPhotonScatteringDistribution::unsetExternalIntegratedCrossSectionEvaluator;

%shared_ptr( MonteCarlo::IncoherentAdjointPhotonScatteringDistribution )
%include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Subshell Incoherent Adjoint Photon Scattering Distribution Support
//---------------------------------------------------------------------------//
%ignore MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution::SubshellIncoherentAdjointPhotonScatteringDistribution;

%shared_ptr( MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution )

%include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Incoherent Adjoint Photon Scattering Distribution Native Factory Support
//---------------------------------------------------------------------------//
%extend MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory
{
  //! Create an incoherent adjoint distribution
  static std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution> createDistribution(
                const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_photoatom_data,
                const IncoherentAdjointModelType incoherent_adjoint_model,
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                const unsigned endf_subshell = 0u )
  {
    std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution> incoherent_adjoint_distribution;

    MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                                               raw_adjoint_photoatom_data,
                                               incoherent_adjoint_distribution,
                                               incoherent_adjoint_model,
                                               adjoint_kn_sampling,
                                               max_energy,
                                               endf_subshell );

    return incoherent_adjoint_distribution;
  }

  //! Create an incoherent adjoint distribution
  static std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution> createDistribution(
                const Data::ElectronPhotonRelaxationDataContainer&
                raw_photoatom_data,
                const IncoherentAdjointModelType incoherent_adjoint_model,
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                const unsigned endf_subshell = 0u )
  {
    std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution> incoherent_adjoint_distribution;

    MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution(
                                               raw_photoatom_data,
                                               incoherent_adjoint_distribution,
                                               incoherent_adjoint_model,
                                               adjoint_kn_sampling,
                                               max_energy,
                                               endf_subshell );

    return incoherent_adjoint_distribution;
  }

  //! Create a subshell distribution
  static std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> createSubshellDistribution(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_photoatom_data,
        const IncoherentAdjointModelType incoherent_adjoint_model,
        const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
        const double max_energy,
        const unsigned endf_subshell )
  {
    std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> incoherent_adjoint_distribution;

    MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                                               raw_adjoint_photoatom_data,
                                               incoherent_adjoint_distribution,
                                               incoherent_adjoint_model,
                                               adjoint_kn_sampling,
                                               max_energy,
                                               endf_subshell );

    return incoherent_adjoint_distribution;
  }

  //! Create a subshell distribution
  static std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> createSubshellDistribution(
        const Data::ElectronPhotonRelaxationDataContainer&
        raw_photoatom_data,
        const IncoherentAdjointModelType incoherent_adjoint_model,
        const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
        const double max_energy,
        const unsigned endf_subshell )
  {
    std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> incoherent_adjoint_distribution;

    MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution(
                                               raw_photoatom_data,
                                               incoherent_adjoint_distribution,
                                               incoherent_adjoint_model,
                                               adjoint_kn_sampling,
                                               max_energy,
                                               endf_subshell );

    return incoherent_adjoint_distribution;
  }
};

%ignore MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createDistribution;
%ignore MonteCarlo::IncoherentAdjointPhotonScatteringDistributionNativeFactory::createSubshellDistribution;

%include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::CoherentScatteringDistribution )
%include "MonteCarlo_CoherentScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution Factory Support
//---------------------------------------------------------------------------//
%typemap(in,numinputs=0) std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution>& coherent_distribution (std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> temp) "$1 = &temp;"

%typemap(argout) std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution>& coherent_distribution {
  std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution>* smartresult = *$1 ? new std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution>(*$1) : 0;
  %append_output(SWIG_NewPointerObj(SWIG_as_voidptr(smartresult), SWIGTYPE_p_std__shared_ptrT_MonteCarlo__CoherentScatteringDistribution_t, SWIG_POINTER_OWN));
}

%include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution ACE Factory Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution Native Factory Support
//---------------------------------------------------------------------------//
%extend MonteCarlo::CoherentScatteringDistributionNativeFactory
{
  //! Create a basic coherent distribution
  static std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> createBasicCoherentDistribution( const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data )
  {
    std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> coherent_distribution;

    MonteCarlo::CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution( raw_photoatom_data, coherent_distribution );

    return coherent_distribution;
  }

  //! Create a basic coherent distribution
  static std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> createBasicCoherentDistribution( const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_photoatom_data )
  {
    std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> coherent_distribution;

    MonteCarlo::CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution( raw_adjoint_photoatom_data, coherent_distribution );

    return coherent_distribution;
  }

  //! Create a efficient coherent distribution
  static std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> createEfficientCoherentDistribution( const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data )
  {
    std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> coherent_distribution;

    MonteCarlo::CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution( raw_photoatom_data, coherent_distribution );

    return coherent_distribution;
  }

  //! Create a efficient coherent distribution
  static std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> createEfficientCoherentDistribution( const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_photoatom_data )
  {
    std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> coherent_distribution;

    MonteCarlo::CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution( raw_adjoint_photoatom_data, coherent_distribution );

    return coherent_distribution;
  }
};

%ignore MonteCarlo::CoherentScatteringDistributionNativeFactory::createBasicCoherentDistribution;
%ignore MonteCarlo::CoherentScatteringDistributionNativeFactory::createEfficientCoherentDistribution;

%include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo.Photon.i
//---------------------------------------------------------------------------//

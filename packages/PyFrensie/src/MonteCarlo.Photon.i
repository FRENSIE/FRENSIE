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
#include "MonteCarlo_PhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp"

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
%import "MonteCarlo_ParticleBank.i"
%import "MonteCarlo_IncoherentModelType.hpp"

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
%apply Utility::DistributionTraits::Counter& INOUT { Utility::DistributionTraits::Counter& trials };
%apply Utility::DistributionTraits::double& OUTPUT { double& outgoing_energy };
%apply Utility::DistributionTraits::double& OUTPUT { double& scattering_angle_cosine };
%apply MonteCarlo::PhotonState& INOUT { MonteCarlo::PhotonState& photon };
%apply MonteCarlo::AdjointPhotonState& INOUT { MonteCarlo::AdjointPhotonState& photon };
%apply MonteCarlo::ParticleBank& INOUT { MonteCarlo::ParticleBank& bank };
%apply Data::SubshellType& OUTPUT { Data::SubshellType& shell_of_interaction };

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
%apply std::shared_ptr<const IncoherentPhotonScatteringDistribution>& OUTPUT { std::shared_ptr<const IncoherentPhotonScatteringDistribution>& incoherent_distribution };

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
%include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"

//---------------------------------------------------------------------------//
// Doppler Broadened Photon Energy Distribution ACE Factory Support
//---------------------------------------------------------------------------//
%apply std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>& OUTPUT { std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>& doppler_broadened_dist };
%apply std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>& OUTPUT { std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>& doppler_broadened_dist };

%include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Doppler Broadened Photon Energy Distribution Native Factory Support
//---------------------------------------------------------------------------//
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
%shared_ptr( MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution )
%include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Incoherent Adjoint Photon Scattering Distribution Native Factory Support
//---------------------------------------------------------------------------//
%apply std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>& OUTPUT { std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>& incoherent_adjoint_distribution };

%apply std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>& OUTPUT { std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>& incoherent_adjoint_distribution };

%include "MonteCarlo_IncoherentPhotonScatteringDistributionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution Support
//---------------------------------------------------------------------------//
%shared_ptr( MonteCarlo::CoherentScatteringDistribution )
%include "MonteCarlo_CoherentScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution Factory Support
//---------------------------------------------------------------------------//
%apply std::shared_ptr<const CoherentScatteringDistribution>& OUTPUT { std::shared_ptr<const CoherentScatteringDistribution>& coherent_distribution };

%shared_ptr( MonteCarlo::CoherentScatteringDistributionFactory )
%include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution ACE Factory Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_CoherentScatteringDistributionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Coherent Scattering Distribution Native Factory Support
//---------------------------------------------------------------------------//
%include "MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo.Photon.i
//---------------------------------------------------------------------------//

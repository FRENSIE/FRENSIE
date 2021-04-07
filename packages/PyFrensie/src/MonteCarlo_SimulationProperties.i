//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties.i
//! \author Luke Kersting
//! \brief  The SimulationProperties classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ToStringTraitsDecl.hpp"

// Add the MonteCarlo namespace to the global lookup scope
using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_vector.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Include the MonteCarlo simulation properties helpers
%include "MonteCarlo_SimulationPropertiesHelpers.i"

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

// General ignore directives
%ignore *::operator<<;

//---------------------------------------------------------------------------//
// Add support for the different particle/model types and modes
//---------------------------------------------------------------------------//
// Import the ParticleType
%include "MonteCarlo_ParticleType.hpp"

// Import the ParticleModeType
%include "MonteCarlo_ParticleModeType.hpp"

// Import the IncoherentModelType
%include "MonteCarlo_IncoherentModelType.hpp"

// Import the IncoherentAdjointModelType
%include "MonteCarlo_IncoherentAdjointModelType.hpp"

// Import the AdjointKleinNishinaSamplingType
%include "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"

// Import the TwoDInterpolationType
%include "MonteCarlo_TwoDInterpolationType.hpp"

// Import the TwoDGridType
%include "MonteCarlo_TwoDGridType.hpp"

// Import the BremsstrahlungAngularDistributionType
%include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

// Import the ElectroionizationSamplingType
%include "MonteCarlo_ElectroionizationSamplingType.hpp"

// Import the ElasticElectronDistributionType
%include "MonteCarlo_ElasticElectronDistributionType.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationGeneralProperties
//---------------------------------------------------------------------------//

// Add typemaps for converting const uint64_t to and from Python float/int
%typemap(in) const uint64_t histories ( uint64_t temp ){

  if( PyFloat_Check($input) )
  {
    temp = static_cast<uint64_t>( PyFloat_AsDouble( $input ) );
  }
  else if( PyInt_Check($input) )
  {
    temp = PyInt_AsUnsignedLongMask( $input );
  }

  $1 = temp;
}

%typemap(typecheck, precedence=70) (const uint64_t histories) {
  $1 = (PyFloat_Check($input) || PyInt_Check($input) ) ? 1 : 0;
}

%feature("docstring") MonteCarlo::SimulationGeneralProperties
"The SimulationGeneralProperties class stores general simulation properties. It can be used for setting and getting the general simulation properties when running a simulation."

%general_properties_setup( SimulationGeneralProperties )

%shared_ptr(MonteCarlo::SimulationGeneralProperties);

// Import the SimulationGeneralProperties
%include "MonteCarlo_SimulationGeneralProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationNeutronProperties.
//---------------------------------------------------------------------------//

%feature("docstring") MonteCarlo::SimulationNeutronProperties
"The SimulationNeutronProperties class stores the neutron simulation properties. It can be used for setting and getting the neutron simulation properties when running a simulation."

%neutron_properties_setup( SimulationNeutronProperties )

%shared_ptr(MonteCarlo::SimulationNeutronProperties);

// Import the SimulationNeutronProperties.
%include "MonteCarlo_SimulationNeutronProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationPhotonProperties
//---------------------------------------------------------------------------//

%feature("docstring") MonteCarlo::SimulationPhotonProperties
"The SimulationPhotonProperties class stores the photon simulation properties. It can be used for setting and getting the photon simulation properties when running a simulation."

%photon_properties_setup( SimulationPhotonProperties )

%shared_ptr(MonteCarlo::SimulationPhotonProperties);

// Import the SimulationPhotonProperties
%include "MonteCarlo_SimulationPhotonProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationAdjointPhotonProperties
//---------------------------------------------------------------------------//

%feature("docstring") MonteCarlo::SimulationAdjointPhotonProperties
"The SimulationAdjointPhotonProperties class stores the adjoint photon simulation properties. It can be used for setting and getting the adjoint photon simulation properties when running a simulation."

%adjoint_photon_properties_setup( SimulationAdjointPhotonProperties )

// Add template for std::vector<double>
%template(DoubleVector) std::vector<double>;

%shared_ptr(MonteCarlo::SimulationAdjointPhotonProperties);

// Import the SimulationAdjointPhotonProperties
%include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationElectronProperties
//---------------------------------------------------------------------------//

%feature("docstring") MonteCarlo::SimulationElectronProperties
"The SimulationElectronProperties class stores the electron simulation properties. It can be used for setting and getting the electron simulation properties when running a simulation."

%electron_properties_setup( SimulationElectronProperties )

%shared_ptr(MonteCarlo::SimulationElectronProperties);

// Import the SimulationElectronProperties
%include "MonteCarlo_SimulationElectronProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationAdjointElectronProperties
//---------------------------------------------------------------------------//

%feature("docstring") MonteCarlo::SimulationAdjointElectronProperties
"The SimulationAdjointElectronProperties class stores the adjoint electron simulation properties. It can be used for setting and getting the adjoint electron simulation properties when running a simulation."

%adjoint_electron_properties_setup( SimulationAdjointElectronProperties )

%shared_ptr(MonteCarlo::SimulationAdjointElectronProperties);

// Import the SimulationAdjointElectronProperties
%include "MonteCarlo_SimulationAdjointElectronProperties.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the SimulationProperties
// //---------------------------------------------------------------------------//

%feature("docstring") MonteCarlo::SimulationProperties
"The SimulationProperties class stores the simulation properties. It can be used for setting and getting the simulation properties when running a simulation."

%simulation_properties_setup( SimulationProperties )

%ignore MonteCarlo::SimulationProperties::getMinParticleEnergy() const;
%ignore MonteCarlo::SimulationProperties::getMaxParticleEnergy() const;

%shared_ptr(MonteCarlo::SimulationProperties);

// Include the SimulationProperties
%include "MonteCarlo_SimulationProperties.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.i
//---------------------------------------------------------------------------//e

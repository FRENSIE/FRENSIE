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
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ToStringTraitsDecl.hpp"

// Add the MonteCarlo namespace to the global lookup scope
using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
// %include <std_set.i>
// %include <std_shared_ptr.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Include the explicit template instantiation helpers
%include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"

// // Include the data property helpers
// %include "MonteCarlo_PropertyHelpers.i"

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

// // General ignore directives
// %ignore *::operator<<;

// // Add general templates
// %template(IntSet) std::set< unsigned int>;

//---------------------------------------------------------------------------//
// Add support for the ParticleType
//---------------------------------------------------------------------------//
// Import the ParticleType
%include "MonteCarlo_ParticleType.hpp"

//---------------------------------------------------------------------------//
// Add support for the PhotoatomicDataProperties
//---------------------------------------------------------------------------//

// %atomic_properties_interface_setup( PhotoatomicDataProperties );

// Import the PhotoatomicDataProperties
%include "MonteCarlo_SimulationGeneralProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationNeutronProperties.
//---------------------------------------------------------------------------//

// %atomic_properties_interface_setup( SimulationNeutronProperties. );

// Import the SimulationNeutronProperties.
%include "MonteCarlo_SimulationNeutronProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationPhotonProperties
//---------------------------------------------------------------------------//

// %atomic_properties_interface_setup( SimulationPhotonProperties );

// Import the SimulationPhotonProperties
%include "MonteCarlo_SimulationPhotonProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationAdjointPhotonProperties
//---------------------------------------------------------------------------//

// %atomic_properties_interface_setup( SimulationAdjointPhotonProperties );

// Import the SimulationAdjointPhotonProperties
%include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationElectronProperties
//---------------------------------------------------------------------------//

// %atomic_properties_interface_setup( SimulationElectronProperties );

// Import the SimulationElectronProperties
%include "MonteCarlo_SimulationElectronProperties.hpp"

//---------------------------------------------------------------------------//
// Add support for the SimulationAdjointElectronProperties
//---------------------------------------------------------------------------//

// %atomic_properties_interface_setup( SimulationAdjointElectronProperties );

// Import the SimulationAdjointElectronProperties
%include "MonteCarlo_SimulationAdjointElectronProperties.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the SimulationProperties
// //---------------------------------------------------------------------------//

// %ignore *::AtomicWeight;
// %ignore Data::SimulationProperties::SimulationProperties( const Data::AtomType, const AtomicWeight );

// %feature("docstring") Data::SimulationProperties
// "The SimulationProperties class stores a atomic data properties. It can be used for
// querying atomic data properties and for creating atomic data extractors or
// container, which can be used to read atomic data."

// %feature("autodoc", "atom(SimulationProperties self) -> AtomType")
// Data::SimulationProperties::atom;

// %feature("autodoc", "atomicNumber(SimulationProperties self) -> unsigned")
// Data::SimulationProperties::atomicNumber;

// %feature("autodoc", "atomicWeight(SimulationProperties self) -> AtomicWeight")
// Data::SimulationProperties::atomicWeight;

// %feature("autodoc", "atomicWeightRatio(SimulationProperties self) -> double")
// Data::SimulationProperties::atomicWeightRatio;

// // Allow shared pointers of SimulationProperties objects
// %shared_ptr( Data::SimulationProperties );

// // Rename the overloaded getDataFileVersions functions
// %atom_properties_interface_setup( Photoatomic, photoatomic )
// %atom_properties_interface_setup( AdjointPhotoatomic, adjointPhotoatomic )
// %atom_properties_interface_setup( Electroatomic, electroatomic )
// %atom_properties_interface_setup( AdjointElectroatomic, adjointElectroatomic )

// // Add typemaps for converting AtomicWeight to and from Python float
// %apply const Data::PhotoatomicDataProperties::AtomicWeight {
//   const Data::SimulationProperties::AtomicWeight }
// %apply Data::PhotoatomicDataProperties::AtomicWeight {
//   Data::SimulationProperties::AtomicWeight }

// // Import the SimulationProperties
// %include "MonteCarlo_SimulationProperties.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.i
//---------------------------------------------------------------------------//e

//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.Collision.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The MonteCarlo.Collision sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_collision_docstring
"
PyFrensie.MonteCarlo.Collision is the python interface to the FRENSIE
monte_carlo/collision subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_collision_docstring) Collision

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_ScatteringCenterDefinition.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"

#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DesignByContract.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Include the explicit template instantiation helpers
%include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"

// Simulation properties handling
%import MonteCarlo.MonteCarlo__init__.i
%import MonteCarlo_SimulationProperties.i

// Atom properties handling
%import(module="PyFrensie.Data") Data_AtomProperties.i

// Nuclide properties handling
%import(module="PyFrensie.Data") Data_NuclideProperties.i

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

//---------------------------------------------------------------------------//
// Add ScatteringCenterDefinition support
//---------------------------------------------------------------------------//

// // Add typemaps for the atomic_weight
// %typemap(in,numinputs=0) double* atomic_weight (std::vector<double> temp)
// {
//   temp.resize( 2 );
//   $1 = temp.data();
// }

// %typemap(argout) double* atomic_weight {
//   double atomic_weight_temp = $1[0];

//   if( $1[0] )
//     %append_output(PyFrensie::convertToPython( atomic_weight_temp ));
// }

%shared_ptr(MonteCarlo::ScatteringCenterDefinition);

%include "MonteCarlo_ScatteringCenterDefinition.hpp"

// Add some useful methods to the ScatteringCenterDefinition class
%extend MonteCarlo::ScatteringCenterDefinition
{
  // Get the atomic weight of the PhotoatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getPhotoatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getPhotoatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the AdjointPhotoatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointPhotoatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getAdjointPhotoatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the ElectroatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getElectroatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getElectroatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the AdjointElectroatomicDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointElectroatomicDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getAdjointElectroatomicDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight ratio of the NuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getNuclearDataAtomicWeightRatio() const
  {
    double atomic_weight_ratio;
    $self->getNuclearDataProperties(&atomic_weight_ratio);
    return atomic_weight_ratio;
  }

  // Get the atomic weight ratio of the AdjointNuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointNuclearDataAtomicWeightRatio() const
  {
    double atomic_weight_ratio;
    $self->getAdjointNuclearDataProperties(&atomic_weight_ratio);
    return atomic_weight_ratio;
  }

  // Get the atomic weight of the PhotonuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getPhotonuclearDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getPhotonuclearDataProperties(&atomic_weight);
    return atomic_weight;
  }

  // Get the atomic weight of the AdjointPhotonuclearDataProperties
  double MonteCarlo::ScatteringCenterDefinition::getAdjointPhotonuclearDataAtomicWeight() const
  {
    double atomic_weight;
    $self->getAdjointPhotonuclearDataProperties(&atomic_weight);
    return atomic_weight;
  }

};

//---------------------------------------------------------------------------//
// Add ScatteringCenterDefinitionDatabase support
//---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::ScatteringCenterDefinitionDatabase);

%include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"

// Material support
%pythoncode
%{
from PyFrensie.MonteCarlo.Material import *
%}

// Geometry Model support
%pythoncode
%{
from PyFrensie.MonteCarlo.GeometryModel import *
%}

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo.Collision.i
//---------------------------------------------------------------------------//

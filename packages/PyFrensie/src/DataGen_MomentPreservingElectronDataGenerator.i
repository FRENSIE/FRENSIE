//---------------------------------------------------------------------------//
//!
//! \file   DataGen_MomentPreservingElectronDataGenerator.i
//! \author Luke Kersting
//! \brief  The MomentPreservingElectronDataGenerator class's interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"
%}

// Include std::string support
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

%import(module="PyFrensie.Data.Native") Data.Native.i
%import(module="PyFrensie.Data.ENDL") Data.ENDL.i
%import(module="PyFrensie.MonteCarlo") MonteCarlo_SimulationProperties.i

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

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

//---------------------------------------------------------------------------//
// Create aliases for common type found in native data tables
//---------------------------------------------------------------------------//

// Allow std::vector<double> output type
%template(DoubleVector) std::vector<double>;

// Add use of std::shared_ptr
%shared_ptr(DataGen::StandardMomentPreservingElectronDataGenerator)

// Ignore populateMomentPreservingData
%ignore *::populateMomentPreservingData( Data::MomentPreservingElectronVolatileDataContainer&, const int& ) const;
// Ignore setMomentPreservingElectronData
%ignore *::setMomentPreservingElectronData( Data::MomentPreservingElectronVolatileDataContainer&, const int& ) const;

//---------------------------------------------------------------------------//
// Add support for the StandardMomentPreservingElectronDataGenerator
//---------------------------------------------------------------------------//
// Add a more detailed docstring for the StandardMomentPreservingElectronDataGenerator
%feature("docstring")
DataGen::EPRDataGeneratorHelpers
"
The EPRDataGeneratorHelpers can be used to generate
elastic moment preserving data.
A brief usage tutorial for this class is shown below:

 import PyFrensie.DataGen.ElectronPhoton, PyTrilinos, numpy, matplotlib.pyplot

 ...

 h_native_data = PyFrensie.Data.ENDL.ENDLDataContainer( h_endl_file_name )

 matplotlib.pyplot.loglog( h_native_data.getElasticEnergyGrid(), h_native_data.getCutoffElasticCrossSection() )
 matplotlib.pyplot.loglog( h_native_data.getElasticEnergyGrid(), h_native_data.getElasticTransportCrossSection() )
 matplotlib.pyplot.show()
"

// Include the EPRDataGeneratorHelpers.hpp
%include "DataGen_EPRDataGeneratorHelpers.hpp"

//---------------------------------------------------------------------------//
// Add support for the StandardMomentPreservingElectronDataGenerator
//---------------------------------------------------------------------------//

%feature("docstring")
DataGen::StandardMomentPreservingElectronDataGenerator
"The StandardMomentPreservingElectronDataGenerator can be used to generate
elastic moment preserving data."

// Add a general typemap
%apply std::vector<double>& OUTPUT { std::vector<double>& discrete_angles };
%apply std::vector<double>& OUTPUT { std::vector<double>& weights };

%feature("autodoc",
"evaluateDiscreteAnglesAndWeights(StandardMomentPreservingElectronDataGenerator self, const double & energy, const unsigned int & number_of_discrete_angles ) -> DoubleVector, DoubleVector" )
DataGen::StandardMomentPreservingElectronDataGenerator::evaluateDiscreteAnglesAndWeights;

%include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"

/*  // Generate elastic discrete angle cosines and weights*/
/*  void evaluateDiscreteAnglesAndWeights(*/
/*    const double& energy,*/
/*    const int& number_of_discrete_angles,*/
/*    std::vector<double>& discrete_angles,*/
/*    std::vector<double>& weights ) const;*/

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end DataGen_MomentPreservingElectronDataGenerator.i
//---------------------------------------------------------------------------//

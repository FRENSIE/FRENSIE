//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.i
//! \author Alex Robinson
//! \brief  The uniform distribution swig interface file. Note that units
//!         will not be enabled in the interface.
//!
//---------------------------------------------------------------------------//

%{
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "PyFrensie_Utility.hpp"
%}

%import "PyFrensie_Utility.hpp"
%include "std_string.i"

%inline %{
//! Initialize the random number generator
void initFrensiePrng()
{
  // Initilize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}
%}

%include <typemaps.i>

%apply unsigned& INOUT { unsigned& trials };

%ignore Utility::UnitAwareOneDDistribution<void,void>::IndepUnit;
%ignore Utility::UnitAwareOneDDistribution<void,void>::DepUnit;
%ignore Utility::UnitAwareOneDDistribution<void,void>::IndepQuantity;
%ignore Utility::UnitAwareOneDDistribution<void,void>::InverseIndepQuantity;
%ignore Utility::UnitAwareOneDDistribution<void,void>::DepQuantity;
%ignore Utility::UnitAwareOneDDistribution<void,void>::getDistributionType;
%import "Utility_OneDDistribution.hpp"

%typemap(in) Utility::UnitAwareOneDDistribution<void,void>::IndepQuantity {
  $1 = PyFloat_AsDouble($input);
}

%typemap(out) Utility::UnitAwareOneDDistribution<void,void>::IndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareOneDDistribution<void,void>::DepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareOneDDistribution<void,void>::InverseIndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%template(OneDDistribution) Utility::UnitAwareOneDDistribution<void,void>;

%apply unsigned& OUTPUT { unsigned& sampled_bin_index };

%ignore Utility::UnitAwareTabularOneDDistribution<void,void>::IndepQuantity;
%ignore Utility::UnitAwareTabularOneDDistribution<void,void>::InverseIndepQuantity;
%ignore Utility::UnitAwareTabularOneDDistribution<void,void>::DepQuantity;
%import "Utility_TabularOneDDistribution.hpp"

%typemap(in) Utility::UnitAwareTabularOneDDistribution<void,void>::IndepQuantity {
  $1 = PyFloat_AsDouble($input);
}

%typemap(out) Utility::UnitAwareTabularOneDDistribution<void,void>::IndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareTabularOneDDistribution<void,void>::DepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareTabularOneDDistribution<void,void>::InverseIndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%template(TabularOneDDistribution) Utility::UnitAwareTabularOneDDistribution<void,void>;

%ignore Utility::UnitAwareUniformDistribution<void,void>::ThisType;
%ignore Utility::UnitAwareUniformDistribution<void,void>::IndepQuantity;
%ignore Utility::UnitAwareUniformDistribution<void,void>::InverseIndepQuantity;
%ignore Utility::UnitAwareUniformDistribution<void,void>::getDistributionType;
%ignore Utility::UnitAwareUniformDistribution<void,void>::fromUnitlessDistribution;
%ignore Utility::UnitAwareUniformDistribution<void,void>::DepQuantity;
%ignore Utility::UnitAwareUniformDistribution<void,void>::toStream;
%ignore Utility::UnitAwareUniformDistribution<void,void>::fromStream;
%ignore Utility::UnitAwareUniformDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, unsigned& );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleWithRandomNumber( const IndepQuantity, const IndepQuantity, double );
%import "Utility_UniformDistribution.hpp"

%typemap(in) Utility::UnitAwareUniformDistribution<void,void>::IndepQuantity {
  $1 = PyFloat_AsDouble($input);
}

%typemap(out) Utility::UnitAwareUniformDistribution<void,void>::IndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareUniformDistribution<void,void>::DepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareUniformDistribution<void,void>::InverseIndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%extend Utility::UnitAwareUniformDistribution<void,void> 
{
  // Instantiate the desired version of the template constructor
  %template(UniformDistribution) Utility::UnitAwareUniformDistribution::UnitAwareUniformDistribution<double,double>;

  // Add a method for exporting to a Python parameter list
  void toParameterList( const std::string& name,
                        PyObject* python_parameter_list )
  {
    
    // Check that the python object is a parameter list
    if( !PyFrensie::addToParameterList( name, *$self, python_parameter_list ) )
    {
      PyErr_SetString(PyExc_TypeError, "The PyObject is not a Teuchos::RCP<Teuchos::ParameterList>" );
    }
  }
};

%typemap(default) const double& dependent_value {
  double default_dependent_value = 1.0;
  $1 = &default_dependent_value;
}

%template(UniformDistribution) Utility::UnitAwareUniformDistribution<void,void>;






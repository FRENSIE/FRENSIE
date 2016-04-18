//---------------------------------------------------------------------------//
//!
//! \file   Utility_DistributionHelper.i
//! \author Alex Robinson
//! \brief  The distribution helper macros
//!
//---------------------------------------------------------------------------//

%{
#include "PyFrensie_Utility.hpp"
%}

// Include std::string support
%include "std_string.i"

// Import the PyFrensie utility
%import "PyFrensie_Utility.hpp"

// Macro for setting up a OneDDistribution class python interface
%define %distribution_interface_setup( DISTRIBUTION )

%feature("docstring") Utility::UnitAware ## DISTRIBUTION ## <void,void>
"The DISTRIBUTION proxy class. This class can be evaluated, sampled from, 
exported to an XML file (using the PyTrilinos.Teuchos.ParameterList and the
PyTrilinos.Teuchos.XMLParameterListWriter), and imported from an XML file
(using the PyTrilinos.Teuchos.ParameterList and the
PyTrilinos.Teuchos.XMLParameterListReader). Before sampling, make sure to
initialize the Frensie Pseudo-Random Number Generator 
(PyFrensie.Utility.initFrensiePrng())"

%feature("autodoc",
"evaluate(DISTRIBUTION self, double indep_var_value ) -> double" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::evaluate;

%feature("autodoc",
"evaluatePDF(DISTRIBUTION self, double indep_var_value ) -> double" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::evaluatePDF;

%feature("autodoc",
"sample(DISTRIBUTION self) -> double" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::sample;

%feature("autodoc",
"sampleAndRecordTrials(DISTRIBUTION self, unsigned int & trials ) -> double, unsigned int

Sample from the DISTRIBUTION and record the number of trials (iterations) that
were required to generate the sample. The first element of the returned tuple
is the sample. The second element of the returned tuple is the trials counter.
The trials counter can be reused as such:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.DISTRIBUTION( ... )
  trials_counter = 0
 
  sample,trials_counter = u.sampleAndRecordTrials( trials_counter )
  sample,trials_counter = u.sampleAndRecordTrials( trials_counter )

  print trials_counter
  2")
Utility::UnitAware ## DISTRIBUTION ## <void,void>::sampleAndRecordTrials;

%feature("autodoc",
"getUpperBoundOfIndepVar(DISTRIBUTION self) -> double" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::getUpperBoundOfIndepVar;

%feature("autodoc",
"getLowerBoundOfIndepVar(DISTRIBUTION self) -> double" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::getLowerBoundOfIndepVar;

%feature("autodoc",
"toParameterList(DISTRIBUTION self, const std::string & parameter_name, PyObject * python_parameter_list)

The python ParameterList only supports native python and numpy array
types. To add a python DISTRIBUTION to a python ParameterList, only this 
function can be used. The dictionary methods cannot be used to add a
python DISTRIBUTION to a python ParameterList. Once a python DISTRIBUTION
object has been added to the python ParameterList, you will not be able
to call print or str will it. Be careful when calling the ParameterList set
method after a python DISTRIBUTION has been added as it returns a 
ParameterList object which python will try (and fail) to print. Calls to set
should be done like this:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.DISTRIBUTION( ... )

  p = PyTrilinos.Teuchos.ParameterList()

  u.toParameterList( 'my_dist', p )
 
  p = p.set( 'my_double', 1.0 )

You can use the XMLParameterListWriter to write the ParameterList to an 
XML file like this (continued from the previous example):
 
  writer = PyTrilinos.Teuchos.XMLParameterListWriter()

  xml_obj = writer.toXML( p )

  xml_file = open( 'my_list', 'w' )
  xml_file.write( xml_obj.toString() )
  xml_file.close()
" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::toParameterList;

%feature("autodoc",
"fromParameterList(DISTRIBUTION self, const std::string & parameter_name, PyObject * python_parameter_list)

The python ParameterList only supports native python and numpy array
types. To get a python DISTRIBUTION from a python ParameterList, only this 
function can be used. The dictionary methods cannot be used to get a
python DISTRIBUTION from a python ParameterList. 
" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::fromParameterList;

%feature("autodoc", 
"__str__(DISTRIBUTION self) -> string

Convert the DISTRIBUTION to a string. The output string format is the same
that is used to add the distribution to a Teuchos::ParameterList.")
Utility::UnitAware ## DISTRIBUTION ## <void,void>::__str__;

%feature("autodoc",
"__repr__(DISTRIBUTION self) -> string

Convert the DISTRIBUTION to a string wrapped inside of DISTRIBUTION(...).")
Utility::UnitAware ## DISTRIBUTION ## <void,void>::__repr__;

%feature("autodoc",
"__eq__(DISTRIBUTION self, DISTRIBUTION other_dist ) -> bool 

Check if two DISTRIBUTION objects are equal (using the == operator). This will
return the same value as self.isEqual( other_dist )" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::__eq__;

%feature("autodoc",
"__ne__(DISTRIBUTION self, DISTRIBUTION other_dist ) -> bool 

Check if two DISTRIBUTION objects are not equal (using the != operator). This
will return the same value as !self.isEqual( other_dist )" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::__ne__;

%typemap(in) Utility::UnitAware ## DISTRIBUTION ## <void,void>::IndepQuantity 
{
  $1 = PyFloat_AsDouble($input);
}

%typemap(out) Utility::UnitAware ## DISTRIBUTION ## <void,void>::IndepQuantity 
{
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAware ## DISTRIBUTION ## <void,void>::DepQuantity 
{
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAware ## DISTRIBUTION ## <void,void>::InverseIndepQuantity 
{
  $result = PyFloat_FromDouble($1);
}

%extend Utility::UnitAware ## DISTRIBUTION ## <void,void>
{
  // Add a method for exporting to a Python parameter list
  void toParameterList( const std::string& name,
                        PyObject* python_parameter_list ) const
  {
    // Check that the python object is a parameter list
    if( !PyFrensie::addDistToParameterList( name, *$self, python_parameter_list ) )
    {
      PyErr_SetString(PyExc_TypeError, "The PyObject is not a PyTrilinos.Teuchos.ParameterList (a.k.a Teuchos::RCP<Teuchos::ParameterList>)." );
    }
  }

  // Add a method for importing from a Python parameter list
  void fromParameterList( const std::string& name,
                          PyObject* python_parameter_list )
  {
    PyFrensie::getDistFromParameterList( name, python_parameter_list, *$self );
  }
  
  // String representation method
  PyObject* __repr__() const
  {
    std::string repr_string( #DISTRIBUTION );
    repr_string += "(";

    std::ostringstream oss;

    $self->toStream( oss );

    repr_string += oss.str() + ")";

    return PyString_FromString( repr_string.c_str() );
  }

  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;

    $self->toStream( oss );

    return PyString_FromString( oss.str().c_str() );
  }

  // Equality operator
  PyObject* __eq__( const DISTRIBUTION& other_dist ) const
  {
    if( $self->isEqual( other_dist ) )
      Py_RETURN_TRUE;
    else
      Py_RETURN_FALSE;
  }

  // Inequality operator
  PyObject* __ne__( const DISTRIBUTION& other_dist ) const
  {
    if( !$self->isEqual( other_dist ) )
      Py_RETURN_TRUE;
    else
      Py_RETURN_FALSE;
  }
};

%template(DISTRIBUTION) Utility::UnitAware ## DISTRIBUTION ## <void,void>;

%enddef

// Macro for setting up a TabularOneDDistribution class python interface
%define %tab_distribution_interface_setup( DISTRIBUTION )

%feature("autodoc",
"evaluate(DISTRIBUTION self, double indep_var_value ) -> double" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::evaluateCDF;

%feature("autodoc",
"sampleAndRecordBinIndex(DISTRIBUTION self) -> double, unsigned int

Sample from the DISTRIBUTION and record the bin index corresponding to the 
sample. The first element of the returned tuple is the sample. The second 
element of the returned tuple is the bin index. This method can be called
as follows:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.DISTRIBUTION( ... )
  
  sample,bin_index = u.sampleAndRecordBinIndex()")
Utility::UnitAware ## DISTRIBUTION ## <void,void>::sampleAndRecordBinIndex;

%feature("autodoc",
"sampleWithRandomNumber(DISTRIBUTION self, const double random_number) -> double

Sample from the DISTRIBUTION using the supplied random number instead of using
the hidden Utility::RandomNumberGenerator.")
Utility::UnitAware ## DISTRIBUTION ## <void,void>::sampleWithRandomNumber;

%feature("autodoc",
"sampleInSubrange(DISTRIBUTION self, const double max_indep_var ) -> double

Sample from the DISTRIBUTION in the subrange [self.getLowerBoundOfIndepVar(),max_indep_var]" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::sampleInSubrange;

%feature("autodoc",
"sampleWithRandomNumberInSubrange(DISTRIBUTION self, const double random_number, const double max_indep_var ) -> double

Sample from the DISTRIBUTION using the supplied random number in the subrange
[self.getLowerBoundOfIndepVar(),max_indep_var]" )
Utility::UnitAware ## DISTRIBUTION ## <void,void>::sampleWithRandomNumberInSubrange;

%distribution_interface_setup( DISTRIBUTION )

%enddef


//---------------------------------------------------------------------------//
// end Utility_DistributionHelper.i
//---------------------------------------------------------------------------//

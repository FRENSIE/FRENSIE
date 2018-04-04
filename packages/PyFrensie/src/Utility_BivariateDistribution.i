//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistribution.i
//! \author Luke Kersting
//! \brief  The BivariateDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DistributionSerializationHelpers.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_BasicBivariateDistribution.hpp"
#include "Utility_BivariateDistribution.hpp"
// #include "Utility_SeparableBivariateDistribution.hpp"
#include "Utility_TabularBasicBivariateDistribution.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_TwoDGridPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;

// std::vector<TabDistPtr> toVectorPtr(std::vector<TabularDistribution_LinLin>& vec);
// std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void, void> > > changeDist(const std::vector<TabDistPtr>& vec )

// std::vector<TabDistPtr> toVectorPtr(const std::vector<TabularDistribution_LinLin>& vec )
// {
//     std::vector<TabDistPtr> vec_out;
//     for(auto x : vec)
//     {
//         vec_out.push_back(std::make_shared<TabularDistribution_LinLin>(x));
//     }
//     return vec_out;
// }

// std::vector<TestPtr> changeDist(const std::vector<TabDistPtr>& vec );
// std::vector<constTestPtr> changeConstDist(const std::vector<TabDistPtr>& vec );
%}

// %inline %{

// std::vector<TabDistPtr> toVectorPtr(const std::vector<TabularDistribution_LinLin>& vec )
// {
//     std::vector<TabDistPtr> vec_out;
//     for(auto x : vec)
//     {
//         vec_out.push_back(std::make_shared<TabularDistribution_LinLin>(x));
//     }
//     return vec_out;
// }

// std::vector<TestPtr> changeDist(const std::vector<TabDistPtr>& vec )
// {
//     std::vector<TestPtr> vec_ptr;
//     for ( unsigned i = 0; i < vec.size(); ++i )
//     {
//       std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<void,void> > ptr;
//       ptr = vec[i];

//       vec_ptr.push_back(ptr);
//     }

//   // Create the two-dimensional distribution
//   {
//     std::vector<constTestPtr> sec_dists(2);
//     std::vector<double> prim_grid( 2 );
//     prim_grid[0] = 0.0;
//     prim_grid[1] = 1.0;
//     for ( unsigned i = 0; i < vec.size(); ++i )
//     {
//       sec_dists[i] = vec[i];
//     }

//     std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> tab_distribution;

//     tab_distribution.reset( new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LinLinLin> >(
//                                                                prim_grid,
//                                                                sec_dists,
//                                                                1e-3,
//                                                                1e-7 ) );

//     std::cout << std::setprecision(16) << std::scientific << "tab_distribution->evaluate( 1.0, 5.0) = \t" << tab_distribution->evaluate( 1.0, 5.0) << std::endl;

//   }

//   return vec_ptr;
// }

// std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void, void> > > changeConstDist(const std::vector<TabDistPtr>& vec )
// {
//     std::vector<constTestPtr> vec_ptr;
//     for ( unsigned i = 0; i < vec.size(); ++i )
//     {
//       std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void, void> > ptr;
//       ptr = vec[i];

//       vec_ptr.push_back(ptr);
//     }

//   return vec_ptr;
// }

// %}

// Include std::string support
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

// Include vector support
%include <std_vector.i>

// Include shared pointer support
%include <std_shared_ptr.i>

// Include macros to find initialized numpy
%include "numpy.i"

// Include the serialization helpers
%include "Utility_SerializationHelpers.hpp"
%include "Utility_DistributionSerializationHelpers.hpp"

// Import the explicit template instantiation helpers
%import "Utility_ExplicitTemplateInstantiationMacros.hpp"

// Import the distribution traits class
%import "Utility_DistributionTraits.hpp"

// Include the univariate distribution
%include "Utility_UnivariateDistribution.i"

// Include the bivariate distribution helpers
%include "Utility_BivariateDistributionHelpers.i"

// Add a few general typemaps
typedef unsigned int size_t;
// %apply Utility::DistributionTraits::Counter& INOUT { Utility::DistributionTraits::Counter& trials };
%apply unsigned& OUTPUT { unsigned& primary_bin_index };
%apply unsigned& OUTPUT { unsigned& secondary_bin_index };

// %typemap(in) const std::vector<double>& (std::vector<double> temp)
// {
//   temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

//   $1 = &temp;
// }

%typemap(in) const std::vector<std::vector<double> >& (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}


// // // The typecheck precedence, which is used by SWIG to determine which
// // // overloaded method should be called, should be set to
// // // SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the std::vector<double>&. You will
// // // get a Python error when calling the overloaded method in Python without this
// // // typecheck
// // %typemap(typecheck, precedence=1050) (const std::vector<double>&) {
// //   $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
// // }

// Set the typecheck precedence
%typemap(typecheck, precedence=1050) (const std::vector<std::vector<double> >&) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// General ignore directives
%ignore *::PrimaryIndepUnit;
%ignore *::SecondaryIndepUnit;
%ignore *::PrimaryIndepQuantity;
%ignore *::SecondaryIndepQuantity;
%ignore *::InverseSecondaryIndepQuantity;
// %ignore *::DepUnit;
// %ignore *::ThisType;
// %ignore *::DepQuantity;
// %ignore *::operator=;
// %ignore *::toStream;
// %ignore *::fromStream;

//---------------------------------------------------------------------------//
// Add support for the BasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the BasicBivariateDistribution
%import "Utility_BasicBivariateDistribution.hpp"

// Basic distribution interface setup
%basic_bivariate_distribution_interface_setup( BasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the BivariateDistribution
//---------------------------------------------------------------------------//
// Import the BivariateDistribution
%import "Utility_BivariateDistribution.hpp"

// Basic distribution interface setup
%basic_bivariate_distribution_interface_setup( BivariateDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the TabularBasicBivariateDistribution
// //---------------------------------------------------------------------------//
// // Import the TabularBasicBivariateDistribution
// %import "Utility_TabularBasicBivariateDistribution.hpp"

// typedef Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> > TabularBasicBivariateDistribution;

// // %shared_ptr(TabularBasicBivariateDistribution)
// // %shared_ptr(Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> > )

// %feature("docstring") Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> >
// "The RENAMED_DISTRIBUTION proxy class. This class can be evaluated and sampled.
// Before sampling, make sure to initialize the Frensie Pseudo-Random Number
// Generator (PyFrensie.Utility.initFrensiePrng())"

// %template(TabularBasicBivariateDistribution) Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> >;

// // Basic distribution interface setup
// // %basic_tab_bivariate_distribution_interface_setup( TabularBasicBivariateDistribution, TabularUnivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the FullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the FullyTabularBasicBivariateDistribution
%import "Utility_FullyTabularBasicBivariateDistribution.hpp"

// Standard tabular distribution interface setup
%standard_tab_bivariate_distribution_interface_setup( FullyTabularBasicBivariateDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the InterpolatedTabularBasicBivariateDistributionImplBase
// //---------------------------------------------------------------------------//
// // Import the InterpolatedTabularBasicBivariateDistributionImplBase
// %import "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

// // There are many interpolated tabular distributions - use this macro to set up each
// %define %tabular_bivariate_distribution_base_interface_setup( GRID, INTERP, BASE )

// // Add a more detailed docstring for the constructor
// %feature("docstring")
// Utility::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase< Utility::GRID< Utility::INTERP >,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> >
// "The primary independent values should be stored in a NumPy array. The secondary independent values and dependent values should be stored in a list of NumPy arrays.
// "

// %advanced_bivariate_distribution_interface_setup( InterpolatedTabularBasicBivariateDistributionImplBase_ ## INTERP ## _ ## GRID, InterpolatedTabularBasicBivariateDistributionImplBase, Utility::INTERP, Utility::GRID, Utility::BASE )

// %enddef

// // Basic distribution interface setup
// %tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLin, UnitAwareFullyTabularBasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the InterpolatedFullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the InterpolatedFullyTabularBasicBivariateDistribution
%include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
%import "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %tabular_bivariate_distribution_interface_setup( GRID, INTERP )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>::InterpolatedFullyTabularBasicBivariateDistribution
"The primary independent values should be stored in a NumPy array. The secondary independent values and dependent values should be stored in a list of NumPy array.
"

// Typemap for std::vector<PrimaryIndepQuantity
%typemap(in) const std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity > > & (std::vector<double> temp)
{
  temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

  $1 = &temp;
}

// Typecheck for std::vector<PrimaryIndepQuantity>
%typemap(typecheck, precedence=1050) (const std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity > > &) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// Typemap for std::vector< std::vector< SecondaryIndepQuantity > >
%typemap(in) const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > > > > & (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}

// Typecheck for std::vector< std::vector< SecondaryIndepQuantity > >
%typemap(typecheck, precedence=1050) (const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > > > > &) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// Typemap for std::vector< std::vector< DepQuantity > >
%typemap(in) const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > > > > & (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}

// Typecheck for std::vector< std::vector< DepQuantity > >
%typemap(typecheck, precedence=1050) (const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > > > > &) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// %typemap(in) const std::vector< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const >,std::allocator< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const > > > & (std::vector<std::shared_ptr<UnivariateDistribution> > temp)
// {
//   temp = PyFrensie::convertFromPython<std::vector<std::shared_ptr<UnivariateDistribution> > >( $input );

//   $1 = &temp;
// }

// %typemap(in) const std::vector< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const >,std::allocator< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const > > > & (std::vector<std::shared_ptr<const TabularUnivariateDistribution> > temp)
// {
//   std::cout << "typemap for constructor called!" << std::endl;
//   // An exception will be thrown if this fails
//   // PyArrayObject* py_array = (PyArrayObject*)($input);

//   std::cout << PyList_Check($input) << std::endl;
//   std::cout << PyList_Size($input) << std::endl;

//   std::vector<std::shared_ptr<const TabularUnivariateDistribution> >::size_type dimensions = PyList_Size($input);

//   std::vector<constTestPtr> output_array( dimensions );

//   std::vector< Utility::UnitAwareTabularDistribution< Utility::LinLin,void,void >,std::allocator< Utility::UnitAwareTabularDistribution< Utility::LinLin,void,void > > > *ptr = (std::vector< Utility::UnitAwareTabularDistribution< Utility::LinLin,void,void >,std::allocator< Utility::UnitAwareTabularDistribution< Utility::LinLin,void,void > > > *)0;
//   int res = swig::asptr($input, &ptr);
//   std::cout << std::setprecision(16) << std::scientific << "res = \t" << res << std::endl;
//   std::vector< TabularDistribution_LinLin,std::allocator< TabularDistribution_LinLin > > *out_test = 0 ;
//   out_test = ptr;

//   std::vector< TabularDistribution_LinLin,std::allocator< TabularDistribution_LinLin > > &vr = *out_test;

//   vr[0].evaluate(1.0);


//     if (!SWIG_IsOK(res))
//     {
//       std::cout << "BAD!" << std::endl;
//     }

//   for( std::vector<std::shared_ptr<const TabularUnivariateDistribution> >::size_type i = 0; i < dimensions; ++i )
//   {
//     PyObject* py_elem = PyList_GetItem( $input, i );


//     // std::cout << std::setprecision(16) << std::scientific << "PyClass_Check( py_elem ) = \t" << PyClass_Check( py_elem ) << std::endl;
//     // std::cout << std::setprecision(16) << std::scientific << "PyTuple_Check( py_elem ) = \t" << PyTuple_Check( py_elem ) << std::endl;
//     // std::cout << std::setprecision(16) << std::scientific << "PyFunction_Check( py_elem ) = \t" << PyFunction_Check( py_elem ) << std::endl;

//     // std::shared_ptr<const TabularUnivariateDistribution> *ptr = (std::shared_ptr<const TabularUnivariateDistribution> *)0;
//     // std::shared_ptr<const TabularDistribution_LinLin> *ptr1 = (std::shared_ptr<const TabularDistribution_LinLin> *)0;
//     // // std::cout << std::setprecision(16) << std::scientific << "swig::asptr(obj1, &ptr) = \t" << swig::asptr(py_elem, &ptr) << std::endl;

//     // int res = swig::asptr(py_elem, &ptr);
//     // std::cout << std::setprecision(16) << std::scientific << "res = \t" << res << std::endl;

//     // int res1 = swig::asptr(py_elem, &ptr1);
//     // std::cout << std::setprecision(16) << std::scientific << "res1 = \t" << res1 << std::endl;

//     // if (!SWIG_IsOK(res))
//     // {
//     //   std::cout << "BAD!" << std::endl;
//     // }

//     // if (!SWIG_IsOK(res1))
//     // {
//     //   std::cout << "BAD!" << std::endl;
//     // }
//     // std::cout << std::setprecision(16) << std::scientific << "PyArg_ParseTuple( py_elem ) = \t" << PyArg_ParseTuple( py_elem ) << std::endl;

//     PyArrayObject *py_array = (PyArrayObject*)(py_elem);
//       // Details::getNumPyArray<std::vector<std::shared_ptr<const TabularUnivariateDistribution> >::value_type::value_type>( py_elem, &is_new_array );

//     auto data = PyArray_DATA(py_array);

//     TabularUnivariateDistribution* data1 =
//       (TabularUnivariateDistribution*)PyArray_DATA(py_array);

//     TabularDistribution_LinLin* data2 =
//       (TabularDistribution_LinLin*)PyArray_DATA(py_array);

//     std::cout << "data = " << typeid(data).name() << std::endl;
//     std::cout << "data1 = " << typeid(data1).name() << std::endl;
//     std::cout << "data2 = " << typeid(data2).name() << std::endl;
//     std::cout << std::setprecision(16) << std::scientific << "data2->evaluate(1.0) = \t" << data2->evaluate(1.0) << std::endl;

//     TestPtr output_array_i;

//       output_array_i.reset( (data1) );
//       output_array_i.reset( std::move(data1) );

//       // output_array_i.reset( *(data) );
//       // output_array_i.reset( std::move(*data) );
//       // output_array_i = std::make_shared<const TabularUnivariateDistribution>(data);

//     // if( is_new_array )
//     //   Py_DECREF(py_array);
//     std::cout << std::setprecision(16) << std::scientific << "output_array_i->evaluate(1.0) = \t" << output_array_i->evaluate(1.0) << std::endl;

//     output_array[i] = output_array_i;
//   }

//   $1 = &output_array;
// }

// %typemap(in) const std::vector< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const >,std::allocator< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const > > > & (std::vector<std::shared_ptr<const TabularDistribution_LinLin> > temp)
// {
//   temp = PyFrensie::convertFromPython<std::vector<std::shared_ptr<const TabularDistribution_LinLin> > >( $input );

//   $1 = &temp;
// }

// %typemap(typecheck, precedence=1050) (const std::vector< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const >,std::allocator< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const > > > &) {
//   $1 = (PyList_Check($input)) ? 1 : 0;
// }


%advanced_tab_bivariate_distribution_interface_setup( InterpolatedFullyTabularBasicBivariateDistribution_ ## INTERP ## _ ## GRID, InterpolatedFullyTabularBasicBivariateDistribution, Utility::INTERP, Utility::GRID )

// %typedef double Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity;
// %template(VectorPrim) std::vector<Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity>;

%enddef

// %tabular_bivariate_distribution_interface_setup( Direct, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( Direct, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( Direct, LogLogLog )
%tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( UnitBase, LogLogLog )
// %tabular_bivariate_distribution_interface_setup( Correlated, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( Correlated, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( Correlated, LogLogLog )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LogLogLog )

// //---------------------------------------------------------------------------//
// // end Utility_BivariateDistribution.i
// //---------------------------------------------------------------------------//

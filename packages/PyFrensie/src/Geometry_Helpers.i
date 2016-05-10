//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Helpers.i
//! \author Alex Robinson
//! \brief  The geometry swig interface helpers
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_ModuleTraits.hpp"
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_set.i>
%include <std_map.i>

// SWIG will not parse typedefs. Create some typemaps that map the typedefs
// to their true type
%typemap(in) Geometry::ModuleTraits::InternalCellHandle
{
  $1 = PyInt_AsLong($input);
}

%typemap(in) Geometry::ModuleTraits::InternalSurfaceHandle
{
  $1 = PyInt_AsLong($input);
}

%typemap(out) Geometry::ModuleTraits::InternalCellHandle
{
  $result = PyInt_FromLong($1);
}

%typemap(out) Geometry::ModuleTraits::InternalSurfaceHandle
{
  $result = PyInt_AsLong($1);
}

// This macro can be used to instantiate some standard geometry template
// methods
%define %standard_geom_template_extends( CLASS )

// Instantiate an IdSet
%template(IdSet) std::set<unsigned long long>;

// Instantiate the template getMaterialIds method
%template(getMaterialIds) Geometry::CLASS::getMaterialIds<std::set<unsigned long long> >;

// Instantiate the template getCells method
%template(getCells) Geometry::CLASS::getCells<std::set<unsigned long long> >;

// Add methods that return a std::set (since the OUTPUT typemaps don't seem
// to work in this case)
// %extend Geometry::CLASS
// {
//   // Output the material id set
//   static std::set<unsigned long long> getMaterialIds()
//   {
//     std::set<unsigned long long> mat_ids;
//     Geometry::CLASS::getMaterialIds( mat_ids );

//     return mat_ids;
//   }

//   // Output the cell id set
//   static std::set<unsigned long long> getCells()
//   {
//     std::set<unsigned long long> cell_ids;
//     Geometry::CLASS::getCells( cell_ids );

//     return cell_ids;
//   }
// };

// Instantiate a cell id to mat id map
%template(CellIdMatIdMap) std::map<unsigned long long, unsigned long long>;

// Instantiate the template getCellMaterialIds method
%template(getCellMaterialIds) Geometry::CLASS::getCellMaterialIds<std::map<unsigned long long, unsigned long long> >;

// Add method that returns a std::map (since the OUTPUT typemaps don't seem
// to work in this case)
%extend Geometry::CLASS
{
  // Output the cell id to material id map
  static std::map<unsigned long long, unsigned long long> getCellMaterialIds()
  {
    std::map<unsigned long long,unsigned long long> cell_id_mat_id_map;
    Geometry::CLASS::getCellMaterialIds( cell_id_mat_id_map );

    return cell_id_mat_id_map;
  }
};

// Instantiate a cell id to density map
%template(CellIdDensityMap) std::map<unsigned long long, double>;

// Instantiate the template getCellDensities method
%template(getCellDensities) Geometry::CLASS::getCellDensities<std::map<unsigned long long, double> >;

// Add method that returns a std::map (since the OUTPUT typemaps don't seem
// to work in this case)
%extend Geometry::CLASS
{
  // Output the cell id to material id map
  static std::map<unsigned long long,double> getCellDensities()
  {
    std::map<unsigned long long,double> cell_id_density_map;
    Geometry::CLASS::getCellDensities( cell_id_density_map );

    return cell_id_density_map;
  }
};

%enddef

//---------------------------------------------------------------------------//
// end Geometry_Helpers.i
//---------------------------------------------------------------------------//

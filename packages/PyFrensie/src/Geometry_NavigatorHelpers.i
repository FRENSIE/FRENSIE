//---------------------------------------------------------------------------//
//!
//! \file   Geometry_NavigatorHelpers.i
//! \author Luke Kersting
//! \brief  The Navigator helper macros
//!
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// Helper macro for setting up a Navigator class python interface
//---------------------------------------------------------------------------//
%define %navigator_interface_setup_helper( NAVIGATOR )

%feature("docstring")
Geometry::NAVIGATOR
"
The NAVIGATOR class is primarily used to traverse a Model. Some geometric data,
such as the surface normal at a point on a surface or the relationship between
a point and a cell, can also be queried. A brief useage tutorial for this
class is shown below:
"

%feature("autodoc",
"getPointLocation(NAVIGATOR self, Sequence position, Sequence direction, Long cell_id ) -> PointLocation
getPointLocation(NAVIGATOR self, Ray ray, Long cell_id) -> PointLocation

The position and direction sequences must have a size of three. The point
location returned can be one of three values:
   1. PyFrensie.Geometry.POINT_INSIDE_CELL
   2. PyFrensie.Geometry.POINT_ON_CELL
   3. PyFrensie.Geometry.POINT_OUTSIDE_CELL
" )
Geometry::NAVIGATOR::getPointLocation;

%feature("autodoc",
"getSurfaceNormal(NAVIGATOR self, Long surface_id, Sequence position, Sequence direction) -> Numpy Array
getSurfaceNormal(NAVIGATOR self, Long surface_id, Ray ray) -> Numpy Array

The position and direction sequences must have a size of three. The returned
value is a Numpy Array of size three.
" )
Geometry::NAVIGATOR::getSurfaceNormal;

%feature("autodoc",
"findCellContainingRay(NAVIGATOR self, Sequence position, Sequence direction) -> cell_id(Long)
findCellContainingRay(NAVIGATOR self, Ray ray) -> cell_id(Long)

The position and direction sequences must have a size of three.
" )
Geometry::NAVIGATOR::findCellContainingRay;

%feature("autodoc",
"setRay(NAVIGATOR self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction)
setRay(NAVIGATOR self, Sequence position, Sequence direction)
setRay(NAVIGATOR self, Ray ray)

setRay(NAVIGATOR self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction, Long cell_id)
setRay(NAVIGATOR self, Sequence position, Sequence direction, Long cell_id)
setRay(NAVIGATOR self, Ray ray, Long cell_id)

The position and direction sequences must have a size of three.
" )
Geometry::NAVIGATOR::setState;

%feature("autodoc", "getPosition(NAVIGATOR self) -> Numpy Array")
Geometry::NAVIGATOR::getPosition;

%feature("autodoc", "getDirection(NAVIGATOR self) -> Numpy Array")
Geometry::NAVIGATOR::getDirection;

%feature("docstring")
Geometry::NAVIGATOR::fireRay
"
The distance to the surface that was hit will be returned.
"

%feature("autdoc",
"fireRayAndGetSurfaceHit(NAVIGATOR self) -> [distance_to_surface(Float), surface_hit(Long)]
" )
Geometry::NAVIGATOR::fireRayAndGetSurfaceHit;

%feature("docstring")
Geometry::NAVIGATOR::advanceToCellBoundary
"
If a reflecting surface was encountered at the cell boundary True will be
returned. False will be returned if a normal surface was encountered.
"

%feature("autodoc",
"advanceToCellBoundaryAndGetSurfaceNormal(NAVIGATOR self) -> [reflecting_surface(Bool),surface_normal(Numpy Array)]
" )
Geometry::NAVIGATOR::advanceToCellBoundaryAndGetSurfaceNormal;

%feature("autodoc",
"changeInternalRayDirection(NAVIGATOR self, Float x_direction, Float y_direction, Float z_direction)
changeInternalRayDirection(NAVIGATOR self, Sequence direction)

The direction sequence must have a size of three.
" )
Geometry::NAVIGATOR::changeDirection;

// Allow shared pointers of NAVIGATOR objects
%shared_ptr(Geometry::NAVIGATOR);

// // Ignore the findCellContainingRay methods that take a cache
// %ignore Geometry::NAVIGATOR::findCellContainingRay( const double[3], const double[3], Geometry::NAVIGATOR::CellIdSet& );
// %ignore Geometry::NAVIGATOR::findCellContainingRay( const Ray&, Geometry::NAVIGATOR::CellIdSet& );
// %ignore Geometry::NAVIGATOR::findCellContainingRay( const Ray&, Geometry::NAVIGATOR::CellIdSet& ) const;

// // Rename a few overloaded methods
// %rename(fireRayAndGetSurfaceHit) Geometry::NAVIGATOR::fireRay( InternalSurfaceHandle* );
// %rename(fireRayAndGetSurfaceHit2) Geometry::NAVIGATOR::fireRay( InternalSurfaceHandle& );
// %rename(advanceToCellBoundaryAndGetSurfaceNormal) Geometry::NAVIGATOR::advanceToCellBoundary( double* );

// // Add a few general type maps
// %typemap(in,numinputs=0) Geometry::NAVIGATOR::InternalSurfaceHandle* (Geometry::NAVIGATOR::InternalSurfaceHandle temp) "$1 = &temp;"

// %typemap(argout) Geometry::NAVIGATOR::InternalSurfaceHandle* {
//   %append_output(PyFrensie::convertToPython( *$1 ));
// }

// %typemap(in,numinputs=0) double normal[3] (std::vector<double> temp)
// {
//   temp.resize( 3 );
//   $1 = temp.data();
// }

// %typemap(argout) double normal[3] {
//   Utility::ArrayView<const double> output_view( $1, 3 );

//   npy_intp dims[1] = { output_view.size() };

//   $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

//   if( !$result )
//     SWIG_fail;

//   // %append_output(PyFrensie::convertToPython( output_view ));
// }

// %typemap(in,numinputs=0) double* surface_normal (std::vector<double> temp)
// {
//   temp.resize( 3 );
//   $1 = temp.data();
// }

// %typemap(argout) double* surface_normal {
//   Utility::ArrayView<const double> output_view( $1, 3 );

//   npy_intp dims[1] = { output_view.size() };

//   $result = PyArray_SimpleNewFromData( 1, dims, NPY_DOUBLE, (void*)output_view.data() );

//   if( !$result )
//     SWIG_fail;

//   // %append_output(PyFrensie::convertToPython( output_view ));
// }

// %typemap(in) Geometry::NAVIGATOR::CellIdSet& (std::set<unsigned long long> temp)
// {
//   $1 = &temp;
// }

// %typemap(argout) Geometry::NAVIGATOR::InternalSurfaceHandle* {
//   %append_output(PyFrensie::convertToPython( *$1 ));
// }

// %typemap(in,numinputs=0) double normal[3] (std::vector<double> temp)
// {
//   temp.resize( 3 );
//   $1 = temp.data();
// }

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a Navigator class python interface
//---------------------------------------------------------------------------//
%define %navigator_interface_setup( NAVIGATOR )

// Set up the navigator interface
%navigator_interface_setup_helper( NAVIGATOR )

%enddef

//---------------------------------------------------------------------------//
// end Geometry_NavigatorHelpers.i
//---------------------------------------------------------------------------//
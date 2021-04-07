//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Helpers.i
//! \author Luke Kersting
//! \brief  The geometry helper macros
//!
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// Helper macro for setting up a Model class python interface
//---------------------------------------------------------------------------//
%define %model_interface_setup_helper( MODEL )

%feature("docstring") Geometry::MODEL
"The MODEL class stores a geometric model. It can be used for querying
properties of the geometry and for creating navigators,
which can be used to traverse the geometry."

%feature("autodoc", "getName() -> std::string" )
Geometry::MODEL::getName;

%feature("autodoc", "isAdvanced() -> bool" )
Geometry::MODEL::isAdvanced;

%feature("autodoc", "hasCellEstimatorData() -> bool" )
Geometry::MODEL::hasCellEstimatorData;

%feature("autodoc", "getMaterialIds(MODEL self) -> set[material_id]" )
Geometry::MODEL::getMaterialIds;

%feature("autodoc", "getCells(MODEL self, bool include_void_cells, bool include_termination_cells) -> set[cell_id]")
Geometry::MODEL::getCells;

%feature("autodoc","getCellMaterialIds(MODEL self) -> dictionary[cell_id,material_id]" )
Geometry::MODEL::getCellMaterialIds;

%feature("autodoc", "getCellDensities(MODEL self) -> dictionary[cell_id,density(float)]" )
Geometry::MODEL::getCellDensities;

%feature("autodoc",
"getCellEstimatorData(MODEL self) -> dictionary[estimator_id,estimator_data]

The mapped value (estimator_data) is a tuple of size three with the following
elements:
   1. Estimator type (e.g. Geometry.CELL_TRACK_LENGTH_FLUX_ESTIMATOR)
   2. Particle type (e.g. Geometry.NEUTRON)
   3. Numpy array of cells assigned to this estimator
" )
Geometry::MODEL::getCellEstimatorData;

%feature("autodoc", "doesCellExist(MODEL self, cell_id(int) ) -> bool" )
Geometry::MODEL::doesCellExist;

%feature("autodoc", "isTerminationCell(MODEL self, cell_id(int) ) -> bool" )
Geometry::MODEL::isTerminationCell;

%feature("autodoc", "isVoidCell(MODEL self, cell_id(int) ) -> bool" )
Geometry::MODEL::isVoidCell;

%feature("autodoc", "getCellVolume(MODEL self, cell_id(int) ) -> Volume(float)" )
Geometry::MODEL::getCellVolume;

%feature("autodoc", "createNavigator(MODEL self) -> std::shared_ptr<Navigator>" )
Geometry::MODEL::createNavigator;

%ignore *::createNavigatorAdvanced;

// Allow shared pointers of MODEL objects
%shared_ptr(Geometry::MODEL);

// Add some useful methods to the MODEL class
%extend Geometry::MODEL
{
  // String conversion method
  PyObject* __str__() const
  {
    return PyFrensie::convertToPython( $self->getName() );
  }

  // String representation method
  PyObject* __repr__() const
  {
    std::string string_rep( "Model(" );
    string_rep += $self->getName();
    string_rep += ")";

    return PyFrensie::convertToPython( string_rep );
  }

  // MODEL comparison method
  bool __eq__( const Geometry::MODEL& that ) const
  {
    return $self == &that;
  }

  // MODEL comparison method
  bool __ne__( const Geometry::MODEL& that ) const
  {
    return $self != &that;
  }
};

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up an AdvancedModel class python interface
//---------------------------------------------------------------------------//
%define %advanced_model_interface_setup_helper( MODEL )

%feature("docstring") Geometry::MODEL
"The MODEL class stores a geometric model. It can be used for querying
properties of the geometry and for creating navigators,
which can be used to traverse the geometry."

%feature("autodoc", "hasSurfaceEstimatorData() -> bool")
Geometry::MODEL::hasSurfaceEstimatorData;

%feature("autodoc", "getMaterialIds(MODEL self) -> set[material_id]")
Geometry::MODEL::getMaterialIds;

%feature("autodoc", "getSurfaces(MODEL self) -> set[surface_id]")
Geometry::MODEL::getSurfaces;

%feature("autodoc",
"getSurfaceEstimatorData(MODEL self) -> dictionary[estimator_id,estimator_data]

The mapped value (estimator_data) is a tuple of size three with the following
elements:
   1. Estimator type (e.g. Geometry.SURFACE_FLUX_ESTIMATOR)
   2. Particle type (e.g. Geometry.NEUTRON)
   3. Numpy array of surfaces assigned to this estimator
")
Geometry::MODEL::getSurfaceEstimatorData;

%feature("autodoc", "doesSurfaceExist(MODEL self, surface_id(int) ) -> bool")
Geometry::MODEL::doesSurfaceExist;

%feature("autodoc", "getSurfaceArea(MODEL self, surface_id(int) ) -> Area(float)")
Geometry::MODEL::getSurfaceArea;

%feature("autodoc", "isReflectingSurface(MODEL self, surface_id(int) ) -> bool")
Geometry::MODEL::isReflectingSurface;

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a Model class python interface
//---------------------------------------------------------------------------//
%define %model_interface_setup( MODEL )

// Set up the model interface
%model_interface_setup_helper( MODEL )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a AdvancedModel class python interface
//---------------------------------------------------------------------------//
%define %advanced_model_interface_setup( MODEL )

// Set up the model interface
%model_interface_setup_helper( MODEL )

// Set up the advanced model interface
%advanced_model_interface_setup_helper( MODEL )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a Navigator class python interface
//---------------------------------------------------------------------------//
%define %navigator_interface_setup( NAVIGATOR )

%feature("docstring")
Geometry::NAVIGATOR
"
The NAVIGATOR class is primarily used to traverse a Model. Some geometric data,
such as the surface normal at a point on a surface or the relationship between
a point and a cell, can also be queried.
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
"findCellContainingRay(NAVIGATOR self, Float x_position, Float y_position, Float z_position, Float x_direction, Float y_direction, Float z_direction) -> cell_id(Long)
findCellContainingRay(NAVIGATOR self, Sequence position, Sequence direction) -> cell_id(Long)
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
"changeDirection(NAVIGATOR self, Float x_direction, Float y_direction, Float z_direction)
changeDirection(NAVIGATOR self, Sequence direction)

The direction sequence must have a size of three.
" )
Geometry::NAVIGATOR::changeDirection;

// Allow shared pointers of NAVIGATOR objects
%shared_ptr(Geometry::NAVIGATOR);

%enddef

//---------------------------------------------------------------------------//
// end Geometry_ModelHelpers.i
//---------------------------------------------------------------------------//

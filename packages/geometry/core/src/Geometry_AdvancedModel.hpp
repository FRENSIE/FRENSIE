//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Model.hpp
//! \author Alex Robinson
//! \brief  The advanced geometry model base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ADVANCED_MODEL_HPP
#define GEOMETRY_ADVANCED_MODEL_HPP

// FRENSIE Includes
#include "Geometry_Model.hpp"

namespace Geometry{

//! The advanced model base class
class AdvancedModel : public Model
{
  
public:

  //! The surface set type
  typedef std::unordered_set<ModuleTraits::InternalSurfaceHandle> SurfaceIdSet;

  //! Constructor
  AdvancedModel()
  { /* ... */ }

  //! Destructor
  virtual ~AdvancedModel()
  { /* ... */ }

  //! Check if a surface exists
  virtual bool doesSurfaceExist(
              const ModuleTraits::InternalSurfaceHandle surface_id ) const = 0;

  //! Get the surfaces
  virtual void getSurfaces( SurfaceIdSet& surfaces ) const = 0;

  //! Get the surface area
  virtual double getSurfaceArea(
              const ModuleTraits::InternalSurfaceHandle surface_id ) const = 0;

  //! Check if the surface is a reflecting surface
  virtual bool isReflectingSurface(
              const ModuleTraits::InternalSurfaceHandle surface_id ) const = 0;
};
  
} // end Geometry namespace

#endif // end GEOMETRY_ADVANCED_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_AdvancedModel.hpp
//---------------------------------------------------------------------------//

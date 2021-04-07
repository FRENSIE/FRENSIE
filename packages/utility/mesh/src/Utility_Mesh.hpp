//---------------------------------------------------------------------------//
//!
//! \file   Utility_Mesh.hpp
//! \author Alex Robinson
//! \brief  The mesh base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MESH_HPP
#define UTILITY_MESH_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// Std Lib Includes
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Utility{

//! The mesh base class
class Mesh
{

public:

  //! The mesh element handle
  typedef uint64_t ElementHandle;

  //! Iterator over all mesh elements
  typedef std::vector<ElementHandle>::const_iterator ElementHandleIterator;

  //! The mesh element handle, primary intersection point, track length tuple array
  typedef std::vector<std::tuple<ElementHandle,std::array<double,3>,double> > ElementHandleTrackLengthArray;

  //! The mesh element handle, volume map
  typedef std::unordered_map<ElementHandle,double> ElementHandleVolumeMap;

  //! The mesh data tag name set
  typedef std::set<std::string> TagNameSet;

  //! The mesh element handle, data map
  typedef std::unordered_map<ElementHandle,std::map<std::string,std::vector<std::pair<std::string,double> > > > MeshElementHandleDataMap;

  //! Constructor
  Mesh()
  { /* ... */ }

  //! Destructor
  virtual ~Mesh()
  { /* ... */ }

  //! Get the mesh type name
  virtual std::string getMeshTypeName() const = 0;

  //! Get the mesh element type name
  virtual std::string getMeshElementTypeName() const = 0;

  //! Get the start iterator of the mesh element list
  virtual ElementHandleIterator getStartElementHandleIterator() const = 0;

  //! Get the end iterator of the mesh element list
  virtual ElementHandleIterator getEndElementHandleIterator() const = 0;

  //! Get the number of mesh elements
  virtual size_t getNumberOfElements() const = 0;

  //! Return the volumes of each mesh element
  virtual void getElementVolumes( ElementHandleVolumeMap& element_volumes ) const = 0;

  //! Return the volume of a specific mesh element
  virtual double getElementVolume( ElementHandle element ) const = 0;

  //! Check if a point is inside of the mesh
  virtual bool isPointInMesh( const double point[3] ) const = 0;

  //! Determine the mesh element that contains a given point
  virtual ElementHandle whichElementIsPointIn( const double point[3] ) const = 0;

  //! Determine the mesh elements that a line segment intersects
  virtual void computeTrackLengths(
              const double start_point[3],
              const double end_point[3],
              ElementHandleTrackLengthArray& element_track_lengths ) const = 0;

  //! Export the mesh to a file (type determined by suffix - e.g. mesh.vtk)
  virtual void exportData( const std::string& output_file_name,
                           const TagNameSet& tag_root_names,
                           const MeshElementHandleDataMap& mesh_tag_data ) const = 0;

  //! Export the mesh to a file
  void exportData( const std::string& output_file_name ) const;

protected:

  //! Default implementation of export method
  void exportDataImpl( const std::string& output_file_name,
                       const TagNameSet& tag_root_names,
                       const MeshElementHandleDataMap& mesh_tag_data,
                       void* obfuscated_moab_interface,
                       const ElementHandle mesh_handle,
                       const std::function<ElementHandle(const ElementHandle)>&
                       convert_external_element_handle_to_internal_handle ) const;

private:

  // Serialize the mesh data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( Mesh, Utility );
BOOST_SERIALIZATION_CLASS_VERSION( Mesh, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, Mesh );

#endif // end UTILITY_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_Mesh.hpp
//---------------------------------------------------------------------------//

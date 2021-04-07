//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceMesh.hpp
//! \author Philip Britt
//! \brief  Importance mesh class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_MESH_HPP
#define MONTE_CARLO_IMPORTANCE_MESH_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Importance.hpp"
#include "Utility_Mesh.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The importance mesh class
class ImportanceMesh : public Importance
{

public:

  //! Constructor
  ImportanceMesh();

  //! Destructor
  ~ImportanceMesh()
  { /* ... */ }

  //! Set the mesh for a particle
  void setMesh( const std::shared_ptr<const Utility::Mesh> mesh );

  //! Set the discretization map for the importance mesh (vector index is discretization index)
  void setImportanceMap( std::unordered_map<Utility::Mesh::ElementHandle, std::vector<double>>& importance_map );

  double getImportance( ParticleState& particle) const final override;

  bool isParticleInImportanceDiscretization( ParticleState& particle ) const final override;

  std::shared_ptr<const Utility::Mesh> getMesh() const;

  const std::unordered_map<Utility::Mesh::ElementHandle, std::vector<double>>& getImportanceMap() const;

private:

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  std::shared_ptr<const Utility::Mesh > d_mesh;

  //! Map that contains importance windows. First key is the index of the mesh element, second key is the index of the discretization
  std::unordered_map<Utility::Mesh::ElementHandle, std::vector<double>> d_importance_map;

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {   
    // Serialize the base class data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Importance );
    // Serialize the member data
    ar & BOOST_SERIALIZATION_NVP( d_mesh );
    ar & BOOST_SERIALIZATION_NVP( d_importance_map );
  }

};

} // end MonteCarlo namespace

  
BOOST_CLASS_VERSION( MonteCarlo::ImportanceMesh, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ImportanceMesh );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_MESH_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceMesh.hpp
//---------------------------------------------------------------------------//

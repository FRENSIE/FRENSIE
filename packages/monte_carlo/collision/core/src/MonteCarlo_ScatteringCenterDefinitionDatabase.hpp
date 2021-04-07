//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringCenterDefinitionDatabase.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCATTERING_CENTER_DEFINITION_DATABASE_HPP
#define MONTE_CARLO_SCATTERING_CENTER_DEFINITION_DATABASE_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScatteringCenterDefinition.hpp"
#include "Data_ZAID.hpp"
#include "Utility_OStreamableObject.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The scattering center properties class
class ScatteringCenterDefinitionDatabase : public Utility::OStreamableObject
{

public:

  //! Constructor
  ScatteringCenterDefinitionDatabase();

  //! Destructor
  ~ScatteringCenterDefinitionDatabase()
  { /* ... */ }

  //! Check if a scattering center definition exists
  bool doesDefinitionExist( const std::string& name ) const;

  //! Create a new scattering center definition
  ScatteringCenterDefinition& createDefinition( const Data::ZAID& zaid );
  
  //! Create a new scattering center definition
  ScatteringCenterDefinition& createDefinition( const std::string& name,
                                                const Data::ZAID& zaid );

  //! Check if the scattering center name is an alias
  bool isDefinitionNameAnAlias( const std::string& name ) const;

  //! Create a scattering center definition alias
  void createDefinitionAlias( const std::string& name,
                              const std::string& alias );

  //! Resolve the scattering center alias
  std::string resolveDefinitionAlias( const std::string& alias ) const;

  //! Get a scattering center definition
  ScatteringCenterDefinition& getDefinition( const std::string& name );

  //! Get a scattering center definition
  const ScatteringCenterDefinition& getDefinition(
                                               const std::string& name ) const;

  //! Remove a scattering center definition
  void removeDefinition( const std::string& name );

  //! Place the object in an output stream
  void toStream( std::ostream& os ) const final override;

private:

  // Save the object to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { ar & BOOST_SERIALIZATION_NVP( d_scattering_center_definitions ); }

  // Load the object from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_NVP( d_scattering_center_definitions ); }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The scattering center definitions
  std::map<std::string,std::shared_ptr<ScatteringCenterDefinition> > d_scattering_center_definitions;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ScatteringCenterDefinitionDatabase, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ScatteringCenterDefinitionDatabase );

#endif // end MONTE_CARLO_SCATTERING_CENTER_DEFINITION_DATABASE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringCenterDefinitionDatabase.hpp
//---------------------------------------------------------------------------//

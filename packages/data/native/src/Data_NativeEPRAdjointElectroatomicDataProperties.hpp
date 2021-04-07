//---------------------------------------------------------------------------//
//!
//! \file   Data_NativeEPRAdjointElectroatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The Native EPR adjoint electroatomic data properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_NATIVE_EPR_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP
#define DATA_NATIVE_EPR_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP

// FRENSIE Includes
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Data{

//! The Native EPR electroatomic data properties class
class NativeEPRAdjointElectroatomicDataProperties : public AdjointElectroatomicDataProperties
{

public:

  //! Constructor
  NativeEPRAdjointElectroatomicDataProperties(
                                      const AtomicWeight atomic_weight,
                                      const boost::filesystem::path& file_path,
                                      const unsigned file_version,
                                      const AtomType atom );

  //! Destructor
  ~NativeEPRAdjointElectroatomicDataProperties()
  { /* ... */ }

  //! Get the atom that the file specifies data for
  AtomType atom() const override;

  //! Get the electroatomic data file type
  FileType fileType() const override;

  //! Get the atomic weight of the atom that the file specifies data for
  AtomicWeight atomicWeight() const override;

  //! Get the electroatomic data file path (relative to the data directory)
  boost::filesystem::path filePath() const override;

  //! Get the electroatomic data file start line
  size_t fileStartLine() const override;

  //! Get the photoatomic data file version
  unsigned fileVersion() const override;

  //! Get the electroatomic table name
  std::string tableName() const override;

  //! Clone the properties
  NativeEPRAdjointElectroatomicDataProperties* clone() const override;

private:

  // Default constructor
  NativeEPRAdjointElectroatomicDataProperties();

  // Copy constructor
  NativeEPRAdjointElectroatomicDataProperties( const NativeEPRAdjointElectroatomicDataProperties& other );

  // Assignment operator
  NativeEPRAdjointElectroatomicDataProperties& operator=( const NativeEPRAdjointElectroatomicDataProperties& other );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atomic weight of the atom that the file specifies data for
  AtomicWeight d_atomic_weight;

  // The file path (relative to the data directory)
  boost::filesystem::path d_file_path;

  // The file version
  unsigned d_file_version;

  // The atom type
  AtomType d_atom;
};

// Save the properties to an archive
template<typename Archive>
void NativeEPRAdjointElectroatomicDataProperties::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( AdjointElectroatomicDataProperties );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );
  
  std::string raw_path = d_file_path.string();
  
  ar & BOOST_SERIALIZATION_NVP( raw_path );
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_atom );
}

// Load the properties from an archive
template<typename Archive>
void NativeEPRAdjointElectroatomicDataProperties::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( AdjointElectroatomicDataProperties );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_atomic_weight );
  
  std::string raw_path;  
  ar & BOOST_SERIALIZATION_NVP( raw_path );

  d_file_path = raw_path;
  d_file_path.make_preferred();
  
  ar & BOOST_SERIALIZATION_NVP( d_file_version );
  ar & BOOST_SERIALIZATION_NVP( d_atom );
}

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( NativeEPRAdjointElectroatomicDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( NativeEPRAdjointElectroatomicDataProperties, Data );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, NativeEPRAdjointElectroatomicDataProperties );

#endif // end DATA_NATIVE_EPR_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_NativeEPRAdjointElectroatomicDataProperties.hpp
//---------------------------------------------------------------------------//

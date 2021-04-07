//---------------------------------------------------------------------------//
//!
//! \file   TestNuclearDataProperties.hpp
//! \author Alex Robinson
//! \brief  The data properties class implementation for testing
//!
//---------------------------------------------------------------------------//

#ifndef TEST_NUCLEAR_DATA_PROPERTIES_HPP
#define TEST_NUCLEAR_DATA_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "Data_NuclearDataProperties.hpp"
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Data_AdjointThermalNuclearDataProperties.hpp"
#include "Data_PhotonuclearDataProperties.hpp"
#include "Data_AdjointPhotonuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace Data{

//! The nuclear data properties test class
template<typename BaseProperties>
class TestNuclearDataProperties : public BaseProperties
{

public:

  //! Default constructor
  TestNuclearDataProperties()
  { /* ... */ }

  //! Constructor
  TestNuclearDataProperties(
                  const Data::ZAID& zaid,
                  const double atomic_weight_ratio,
                  const typename BaseProperties::Energy evaluation_temperature,
                  const typename BaseProperties::FileType file_type,
                  const unsigned version )
    : d_zaid( zaid ),
      d_atomic_weight_ratio( atomic_weight_ratio ),
      d_evaluation_temperature( evaluation_temperature ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }

  //! Destructor
  ~TestNuclearDataProperties()
  { /* ... */ }

  //! Get the ZAID that the file specifies data for
  Data::ZAID zaid() const override
  { return d_zaid; }

  //! Get the atomic weight ratio of the nuclide that the file specifies data for
  double atomicWeightRatio() const override
  { return d_atomic_weight_ratio; }

  //! Get the nuclear data evaluation temperature (MeV)
  typename BaseProperties::Energy evaluationTemperatureInMeV() const override
  { return d_evaluation_temperature; }

  //! Get the nuclear data evaluation temperature (Kelvin)
  typename BaseProperties::Temperature evaluationTemperature() const
  { return d_evaluation_temperature/Utility::PhysicalConstants::boltzmann_constant_q; }

  //! Get the nuclear data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the nuclear data file start line
  size_t fileStartLine() const override
  { return 0; }

  //! Get the nuclear data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the nuclear data file major version
  unsigned fileMajorVersion() const
  { return d_version; }

  //! Get the nuclear data file table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestNuclearDataProperties* clone() const override
  {
    return new TestNuclearDataProperties( d_zaid,
                                          d_atomic_weight_ratio,
                                          d_evaluation_temperature,
                                          d_file_type,
                                          d_version );
  }

private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_zaid );
    ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
    ar & BOOST_SERIALIZATION_NVP( d_evaluation_temperature );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
    ar & BOOST_SERIALIZATION_NVP( d_version );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The evaluation temperature
  typename BaseProperties::Energy d_evaluation_temperature;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The file version
  unsigned d_version;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( TestNuclearDataProperties<Data::NuclearDataProperties>, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestNuclearDataProperties<Data::NuclearDataProperties>, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestNuclearDataProperties<Data::NuclearDataProperties>, Data );

BOOST_SERIALIZATION_CLASS_VERSION( TestNuclearDataProperties<Data::AdjointNuclearDataProperties>, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestNuclearDataProperties<Data::AdjointNuclearDataProperties>, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestNuclearDataProperties<Data::AdjointNuclearDataProperties>, Data );

namespace Data{

//! The nuclear data properties test class
template<typename BaseProperties>
class TestThermalNuclearDataProperties : public BaseProperties
{

public:

  //! Default constructor
  TestThermalNuclearDataProperties()
  { /* ... */ }

  //! Constructor
  TestThermalNuclearDataProperties(
                  const std::string& name,
                  const std::set<Data::ZAID>& zaids,
                  const typename BaseProperties::Energy evaluation_temperature,
                  const typename BaseProperties::FileType file_type,
                  const unsigned version )
    : d_name( name ),
      d_zaids( zaids ),
      d_evaluation_temperature( evaluation_temperature ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }

  //! Destructor
  ~TestThermalNuclearDataProperties()
  { /* ... */ }

  //! Get the name of the properties
  std::string name() const override
  { return d_name; }

  //! Check if the file specifies data for the ZAID of interest
  bool hasDataForZAID( const Data::ZAID& zaid ) const override
  { return d_zaids.find( zaid ) != d_zaids.end(); }

  //! Get the ZAIDS that the file specifies data for
  std::set<Data::ZAID> zaids() const override
  { return d_zaids; }

  //! Get the nuclear data evaluation temperature (MeV)
  typename BaseProperties::Energy evaluationTemperatureInMeV() const override
  { return d_evaluation_temperature; }

  //! Get the nuclear data evaluation temperature (Kelvin)
  typename BaseProperties::Temperature evaluationTemperature() const
  { return d_evaluation_temperature/Utility::PhysicalConstants::boltzmann_constant_q; }

  //! Get the nuclear data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the nuclear data file start line
  size_t fileStartLine() const override
  { return 0; }
  
  //! Get the nuclear data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the nuclear data file table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestThermalNuclearDataProperties* clone() const override
  {
    return new TestThermalNuclearDataProperties( d_name,
                                                 d_zaids,
                                                 d_evaluation_temperature,
                                                 d_file_type,
                                                 d_version );
  }
  
private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_name );
    ar & BOOST_SERIALIZATION_NVP( d_zaids );
    ar & BOOST_SERIALIZATION_NVP( d_evaluation_temperature );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
    ar & BOOST_SERIALIZATION_NVP( d_version );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The name
  std::string d_name;

  // The zaids
  std::set<Data::ZAID> d_zaids;

  // The evaluation temperature
  typename BaseProperties::Energy d_evaluation_temperature;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The file version
  unsigned d_version;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( TestThermalNuclearDataProperties<Data::ThermalNuclearDataProperties>, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestThermalNuclearDataProperties<Data::ThermalNuclearDataProperties>, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestThermalNuclearDataProperties<Data::ThermalNuclearDataProperties>, Data );

BOOST_SERIALIZATION_CLASS_VERSION( TestThermalNuclearDataProperties<Data::AdjointThermalNuclearDataProperties>, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestThermalNuclearDataProperties<Data::AdjointThermalNuclearDataProperties>, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestThermalNuclearDataProperties<Data::AdjointThermalNuclearDataProperties>, Data );

namespace Data{

//! The nuclear data properties test class
template<typename BaseProperties>
class TestPhotonuclearDataProperties : public BaseProperties
{

public:

  //! Default constructor
  TestPhotonuclearDataProperties()
  { /* ... */ }

  //! Constructor
  TestPhotonuclearDataProperties(
                  const Data::ZAID& zaid,
                  const double atomic_weight_ratio,
                  const typename BaseProperties::FileType file_type,
                  const unsigned version )
    : d_zaid( zaid ),
      d_atomic_weight_ratio( atomic_weight_ratio ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }

  //! Destructor
  ~TestPhotonuclearDataProperties()
  { /* ... */ }

  //! Get the ZAID that the file specifies data for
  Data::ZAID zaid() const override
  { return d_zaid; }

  //! Get the atomic weight of the nuclide that the file specifies data for
  typename BaseProperties::AtomicWeight atomicWeight() const override
  { return d_atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q; }

  //! Get the nuclear data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the nuclear data file start line
  size_t fileStartLine() const override
  { return 0; }

  //! Get the nuclear data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the nuclear data file table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestPhotonuclearDataProperties* clone() const override
  {
    return new TestPhotonuclearDataProperties( d_zaid,
                                               d_atomic_weight_ratio,
                                               d_file_type,
                                               d_version );
  }

private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_zaid );
    ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
    ar & BOOST_SERIALIZATION_NVP( d_version );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The version
  unsigned d_version;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( TestPhotonuclearDataProperties<Data::PhotonuclearDataProperties>, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestPhotonuclearDataProperties<Data::PhotonuclearDataProperties>, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestPhotonuclearDataProperties<Data::PhotonuclearDataProperties>, Data );

BOOST_SERIALIZATION_CLASS_VERSION( TestPhotonuclearDataProperties<Data::AdjointPhotonuclearDataProperties>, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestPhotonuclearDataProperties<Data::AdjointPhotonuclearDataProperties>, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestPhotonuclearDataProperties<Data::AdjointPhotonuclearDataProperties>, Data );

#endif // end TEST_NUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end TestNuclearDataProperties.hpp
//---------------------------------------------------------------------------//

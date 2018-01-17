//---------------------------------------------------------------------------//
//!
//! \file   Data_StandardNuclideProperties.hpp
//! \author Alex Robinson
//! \brief  The standard nuclide properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_STANDARD_NUCLIDE_PROPERTIES_HPP
#define DATA_STANDARD_NUCLIDE_PROPERTIES_HPP

// Std Lib Includes
#include <memory>
#include <algorithm>

// FRENSIE Includes
#include "Data_StandardAtomProperties.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace Data{

//! The standard nuclide properties
class StandardNuclideProperties : public StandardAtomProperties
{

public:

  //! Constructor
  StandardNuclideProperties( const std::string& name,
                             const ZAID& zaid,
                             const double atomic_weight_ratio );
  
  //! Destructor
  ~StandardNuclideProperties()
  { /* ... */ }

  //! Check if the scattering center is a nuclide
  bool isNuclide() const override;

  //! Get the atomic weight
  AtomicWeight atomicWeight() const override;

  //! Get the atomic weight ratio (atomic weight/neutron weight)
  double atomicWeightRatio() const override;

  //! Check if there is nuclear data
  bool nuclearDataAvailable() const override;

  //! Check if there is nuclear data available at the evaluation temp
  bool nuclearDataAvailable( const Energy evaluation_temp ) const override;

  //! Check if the nuclear data is evaluated at discrete temps
  bool nuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the nuclear data evaluation temps
  std::vector<Energy> getNuclearDataEvaluationTempsInMeV() const override;

  //! Get the nuclear data properties
  const NuclearDataProperties* getNuclearDataProperties(
                                        const Energy evaluation_temp,
                                        const bool find_exact ) const override;

  //! Set the nuclear data properties
  void addNuclearDataProperties( const std::shared_ptr<const NuclearDataProperties>& properties );

  //! Check if there is any thermal nuclear data
  bool thermalNuclearDataAvailable() const override;

  //! Check if there is thermal nuclear data available at the evaluation temp
  bool thermalNuclearDataAvailable( const Energy evaluation_temp ) const override;

  //! Check if the thermal nuclear data is evaluated at discrete temps
  bool thermalNuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the thermal nuclear data evaluation temps
  std::vector<Energy> getThermalNuclearDataEvaluationTempsInMeV() const override;

  //! Get the thermal nuclear data properties
  const ThermalNuclearDataProperties* getThermalNuclearDataProperties(
                                        const Energy evaluation_temp,
                                        const bool find_exact ) const override;

  //! Add the thermal nuclear data properties
  void addThermalNuclearDataProperties( const std::shared_ptr<const ThermalNuclearDataProperties>& properties );

  //! Check if there is adjoint nuclear data
  bool adjointNuclearDataAvailable() const override;

  //! Check if there is adjoint nuclear data available at the evaluation temp
  bool adjointNuclearDataAvailable( const Energy evaluation_temp ) const override;

  //! Check if the adjoint nuclear data is evaluation at discrete temps
  bool adjointNuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the adjoint nuclear data evaluation temps
  std::vector<Energy> getAdjointNuclearDataEvaluationTempsInMeV() const override;

  //! Get the adjoint nuclear data
  virtual const AdjointNuclearDataProperties* getAdjointNuclearDataProperties(
                                        const Energy evaluation_temp,
                                        const bool find_exact ) const override;

  //! Add the adjoint nuclear data properties
  void addAdjointNuclearDataProperties( const std::shared_ptr<const AdjointNuclearDataProperties>& properties );

  //! Check if there is any adjoint thermal nuclear data
  bool adjointThermalNuclearDataAvailable() const override;

  //! Check if there is adjoint thermal nuclear data available at the evaluation temp
  bool adjointThermalNuclearDataAvailable( const Energy evaluation_temp ) const override;

  //! Check if the adjoint thermal nuclear data is evaluated at discrete temps
  bool adjointThermalNuclearDataEvaluatedAtDiscreteTemps() const override;

  //! Get the adjoint thermal nuclear data evaluation temps
  std::vector<Energy> getAdjointThermalNuclearDataEvaluationTempsInMeV() const override;

  //! Get the adjoint thermal nuclear data
  const AdjointThermalNuclearDataProperties* getAdjointThermalNuclearDataProperties(
                                        const Energy evaluation_temp,
                                        const bool find_exact ) const override;

  //! Add the adjoint thermal nuclear data properties
  void addAdjointThermalNuclearDataProperties( const std::shared_ptr<const AdjointThermalNuclearDataProperties>& properties );

  //! Check if there is photonuclear data
  bool photonuclearDataAvailable() const override;

  //! Get the photonuclear data properties
  const PhotonuclearDataProperties* getPhotonuclearDataProperties() const override;

  //! Set the photonuclear data properties
  void setPhotonuclearDataProperties( const std::shared_ptr<const PhotonuclearDataProperties>& properties );

  //! Check if there is adjoint photonuclear data
  bool adjointPhotonuclearDataAvailable() const override;

  //! Get the adjoint photonuclear data
  const AdjointPhotonuclearDataProperties* getAdjointPhotonuclearDataProperties() const override;

  //! Set the adjoint photonuclear data properties
  void setAdjointPhotonuclearDataProperties( const std::shared_ptr<const AdjointPhotonuclearDataProperties>& properties );

  //! Clone the properties
  StandardNuclideProperties* clone() const override;

  //! Deep clone the properties
  StandardNuclideProperties* deepClone() const override;

private:

  // Default constructor
  StandardNuclideProperties();

  // Copy constructor
  StandardNuclideProperties( const StandardNuclideProperties& other );

  // Assignment operator
  StandardNuclideProperties& operator=( const StandardNuclideProperties& other );

  // Check if there is data available at the temp of interest
  template<typename PropertiesType>
  static bool dataAvailable( const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& data,
                             const Energy evaluation_temp );

  // Get the evaluation temps
  template<typename PropertiesType>
  static std::vector<Energy> getEvaluationTemps( const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& data );

  // Get the data properties at the temp of interest
  template<typename PropertiesType>
  static const PropertiesType* getDataProperties( const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& data,
                                                  const std::string& properties_type,
                                                  const Energy evaluation_temp,
                                                  const bool find_exact );

  // Add the data properties
  template<typename PropertiesType>
  static void addDataProperties( std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& data,
                                 const std::string& properties_type,
                                 const std::shared_ptr<const PropertiesType>& properties );

  // Clone the data properties
  template<typename PropertiesType>
  static void cloneDataProperties( const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& data,
                                   std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& cloned_data );

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The nuclear data properties
  typedef std::vector<std::pair<Energy,std::shared_ptr<const NuclearDataProperties> > > NuclearDataPropertiesArray;
  NuclearDataPropertiesArray d_nuclear_data_properties;

  // The thermal nuclear data properties
  typedef std::vector<std::pair<Energy,std::shared_ptr<const ThermalNuclearDataProperties> > > ThermalNuclearDataPropertiesArray;
  ThermalNuclearDataPropertiesArray d_thermal_nuclear_data_properties;

  // The adjoint nuclear data properties
  typedef std::vector<std::pair<Energy,std::shared_ptr<const AdjointNuclearDataProperties> > > AdjointNuclearDataPropertiesArray;
  AdjointNuclearDataPropertiesArray d_adjoint_nuclear_data_properties;

  // The thermal adjoint nuclear data properties
  typedef std::vector<std::pair<Energy,std::shared_ptr<const AdjointThermalNuclearDataProperties> > > AdjointThermalNuclearDataPropertiesArray;
  AdjointThermalNuclearDataPropertiesArray d_adjoint_thermal_nuclear_data_properties;

  // The photonuclear data properties
  std::shared_ptr<const PhotonuclearDataProperties>
  d_photonuclear_data_properties;

  // The adjoint photonuclear data properties
  std::shared_ptr<const AdjointPhotonuclearDataProperties>
  d_adjoint_photonuclear_data_properties;
};

// Check if there is data available at the temp of interest
template<typename PropertiesType>
inline bool StandardNuclideProperties::dataAvailable(
  const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >&
  data,
  const Energy evaluation_temp )
{
  typename std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >::const_iterator properties_it =
    std::find_if( data.begin(),
                  data.end(),
                  [&evaluation_temp]( const std::pair<Energy,std::shared_ptr<const PropertiesType> >& element ) -> bool
                  { return element.first == evaluation_temp; } );

  return properties_it != data.end();
}

// Get the evaluation temps
template<typename PropertiesType>
inline auto StandardNuclideProperties::getEvaluationTemps(
  const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >&
  data ) -> std::vector<Energy>
{
  std::vector<Energy> evaluation_temps( data.size() );

  for( size_t i = 0; i < data.size(); ++i )
    evaluation_temps[i] = data[i].first;

  return evaluation_temps;
}

// Get the data properties at the temp of interest
template<typename PropertiesType>
inline const PropertiesType* StandardNuclideProperties::getDataProperties(
  const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >&
  data,
  const std::string& properties_type,
  const Energy evaluation_temp,
  const bool find_exact )
{
  typename std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >::const_iterator properties_it;
  
  if( evaluation_temp < data.front().first )
    properties_it = data.begin();
  else if( evaluation_temp >= data.back().first )
  {
    properties_it = data.end();
    --properties_it;
  }
  else
  {
    properties_it =
      Utility::Search::binaryLowerBound<0>( data.begin(),
                                            data.end(),
                                            evaluation_temp );
  }

  // Check if there are suitable properties available
  if( properties_it->first != evaluation_temp )
  {
    if( find_exact )
    {
      THROW_EXCEPTION( std::runtime_error,
                       "There are no " << properties_type << " data "
                       "properties evaluated at "
                       << evaluation_temp << "!" );
    }
    else
    {
      // Check if we have the closest evaluation temp
      if( std::distance( properties_it, data.end() ) > 1 )
      {
        typename std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >::const_iterator next_properties_it =
          properties_it;
        ++next_properties_it;

        Energy mid_temp =
          (properties_it->first + next_properties_it->first)/2.0;

        if( evaluation_temp >= mid_temp )
          ++properties_it;
      }

      FRENSIE_LOG_TAGGED_WARNING( "Nuclide Properties",
                                  "There are no " << properties_type <<
                                  " data properties evaluated at "
                                  << evaluation_temp << "! "
                                  "Data for the closest evaluation temp ("
                                  << properties_it->first << ") will be "
                                  "returned!" );
    }
  }

  return properties_it->second.get();
}

// Add the data properties
template<typename PropertiesType>
inline void StandardNuclideProperties::addDataProperties(
        std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >&
        data,
        const std::string& properties_type,
        const std::shared_ptr<const PropertiesType>& properties )
{
  Energy evaluation_temp = properties->evaluationTemperatureInMeV();
  
  if( data.empty() )
    data.push_back( std::make_pair( evaluation_temp, properties ) );
  else
  {
    if( evaluation_temp < data.front().first )
    {
      data.insert( data.begin(),
                   std::make_pair( evaluation_temp, properties ) );
    }
    else if( evaluation_temp > data.back().first )
    {
      data.insert( data.end(),
                   std::make_pair( evaluation_temp, properties ) );
    }
    else
    {
      typename std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >::iterator properties_it = 
        Utility::Search::binaryLowerBound<0>( data.begin(),
                                              data.end(),
                                              evaluation_temp );

      if( properties_it->first == evaluation_temp )
      {
        FRENSIE_LOG_TAGGED_WARNING( "Nuclide Properties",
                                    properties_type << " data properties "
                                    "evaluated at " << evaluation_temp << 
                                    "have already been added! The previous "
                                    "properties will be removed." );
        
        properties_it->second = properties;
      }
      else
      {
        ++properties_it;
        
        data.insert( properties_it,
                     std::make_pair( evaluation_temp, properties ) );
      }
    }
  }
}

// Clone the data properties
template<typename PropertiesType>
void StandardNuclideProperties::cloneDataProperties( const std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& data,
                                                     std::vector<std::pair<Energy,std::shared_ptr<const PropertiesType> > >& cloned_data )
{
  cloned_data.clear();
  cloned_data.resize( data.size() );
  
  for( size_t i = 0; i < data.size(); ++i )
  {
    std::shared_ptr<const PropertiesType> clone( data[i].second->clone() );

    cloned_data[i] = std::make_pair( data[i].first, clone );
  }
}

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardNuclideProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StandardNuclideProperties, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( StandardNuclideProperties );

#endif // end DATA_STANDARD_NUCLIDE_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_StandardNuclideProperties.hpp
//---------------------------------------------------------------------------//

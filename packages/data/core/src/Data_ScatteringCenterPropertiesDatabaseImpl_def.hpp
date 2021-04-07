//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabaseImpl_def.hpp
//! \author Alex Robinson
//! \brief  The scattering center properties database impl. definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_IMPL_DEF_HPP
#define DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_IMPL_DEF_HPP

namespace Data{

// Initialize the atom properties
template<typename WeightDataType>
inline AtomProperties& ScatteringCenterPropertiesDatabaseImpl::initializeAtomPropertiesImpl(
                                             const AtomType atom,
                                             const WeightDataType weight_data )
{
  AtomPropertiesMap::iterator properties_it = d_atom_properties.find( atom );
  
  if( properties_it != d_atom_properties.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterPropertiesDatabase",
                                "Atom properties for "
                                << atom << " already exist! "
                                "The existing properties will be "
                                "returned." );
    
    return *properties_it->second;
  }
  else
  {
    std::unique_ptr<AtomProperties>& properties = d_atom_properties[atom];
    
    properties.reset( new AtomProperties( atom, weight_data ) );

    return *properties;
  }
}

// Initialize the nuclide properties
template<typename WeightDataType>
NuclideProperties& ScatteringCenterPropertiesDatabaseImpl::initializeNuclidePropertiesImpl(
                                             const Data::ZAID zaid,
                                             const WeightDataType weight_data )
{
  NuclidePropertiesMap::iterator properties_it =
    d_nuclide_properties.find( zaid );

  if( properties_it != d_nuclide_properties.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterPropertiesDatabase",
                                "Nuclide properties for zaid "
                                << zaid << " already exist! "
                                "The existing properties will be "
                                "returned." );
    
    return *properties_it->second;
  }
  else
  {
    std::unique_ptr<NuclideProperties>& properties =
      d_nuclide_properties[zaid];
    
    properties.reset( new NuclideProperties( zaid, weight_data ) );

    return *properties;
  }
}

// Save the model to an archive
template<typename Archive>
void ScatteringCenterPropertiesDatabaseImpl::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_atom_properties );
  ar & BOOST_SERIALIZATION_NVP( d_nuclide_properties );
}

// Load the model from an archive
template<typename Archive>
void ScatteringCenterPropertiesDatabaseImpl::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_atom_properties );
  ar & BOOST_SERIALIZATION_NVP( d_nuclide_properties );
}
  
} // end Data namespace

#endif // end DATA_SCATTERING_CENTER_PROPERTIES_DATABASE_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabaseImpl_def.hpp
//---------------------------------------------------------------------------//

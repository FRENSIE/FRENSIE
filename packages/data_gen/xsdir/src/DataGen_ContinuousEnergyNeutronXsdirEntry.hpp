//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ContinuousEnergyNeutronXsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The continuous energy neutron xsdir entry class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_HPP
#define DATA_GEN_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_HPP

// FRENSIE Includes
#include "DataGen_XsdirEntry.hpp"

namespace DataGen{

//! The continuous energy neutron xsdir entry
class ContinuousEnergyNeutronXsdirEntry : public XsdirEntry
{
  
public:

  //! Constructor
  template<typename STLCompliantContainer>
  ContinuousEnergyNeutronXsdirEntry( 
				   const STLCompliantContainer& entry_tokens );

  //! Destructor
  ~ContinuousEnergyNeutronXsdirEntry()
  { /* ... */ }

  //! Return the table alias
  const std::string& getTableAlias() const;

  //! Add information to parameter list
  void addInfoToParameterList( Teuchos::ParameterList& parameter_list ) const;

private:

  // The atomic number
  unsigned d_atomic_number;

  // The atomic mass number
  unsigned d_atomic_mass_number;

  // The isomer number
  unsigned d_isomer_number;

  // The alias
  std::string d_alias;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_ContinuousEnergyNeutronXsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end DataGen_ContinuousEnergyNeutronXsdirEntry.hpp
//---------------------------------------------------------------------------//

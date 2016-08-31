//---------------------------------------------------------------------------//
//!
//! \file   Data_ContinuousEnergyNeutronXsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The continuous energy neutron xsdir entry class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_HPP
#define DATA_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_HPP

// FRENSIE Includes
#include "Data_XsdirEntry.hpp"

namespace Data{

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

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ContinuousEnergyNeutronXsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_CONTINUOUS_ENERGY_NEUTRON_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end Data_ContinuousEnergyNeutronXsdirEntry.hpp
//---------------------------------------------------------------------------//

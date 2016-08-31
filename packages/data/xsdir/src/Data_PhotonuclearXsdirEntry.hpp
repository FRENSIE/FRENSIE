//---------------------------------------------------------------------------//
//!
//! \file   Data_PhotonuclearXsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The photonuclear xsdir entry class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PHOTONUCLEAR_XSDIR_ENTRY_HPP
#define DATA_PHOTONUCLEAR_XSDIR_ENTRY_HPP

// FRENSIE Includes
#include "Data_XsdirEntry.hpp"

namespace Data{

//! The photonuclear xsdir entry
class PhotonuclearXsdirEntry : public XsdirEntry
{

public:

  //! Constructor
  template<typename STLCompliantContainer>
  PhotonuclearXsdirEntry(
				   const STLCompliantContainer& entry_tokens );

  //! Destructor
  ~PhotonuclearXsdirEntry()
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

#include "Data_PhotonuclearXsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_PHOTONUCLEAR_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end Data_PhotonuclearXsdirEntry.hpp
//---------------------------------------------------------------------------//

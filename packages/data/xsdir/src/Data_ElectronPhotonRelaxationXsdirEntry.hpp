//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationXsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation xsdir entry class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_HPP

// FRENSIE Includes
#include "Data_XsdirEntry.hpp"

namespace Data{

//! The electron-photon-relaxation xsdir entry
class ElectronPhotonRelaxationXsdirEntry : public XsdirEntry
{

public:

  //! Constructor
  template<typename STLCompliantContainer>
  ElectronPhotonRelaxationXsdirEntry(
				   const STLCompliantContainer& entry_tokens );

  //! Destructor
  ~ElectronPhotonRelaxationXsdirEntry()
  { /* ... */ }

  //! Return the table alias
  const std::string& getTableAlias() const;

  //! Add information to parameter list
  void addInfoToParameterList( Teuchos::ParameterList& parameter_list ) const;

private:

  // The atomic number
  unsigned d_atomic_number;

  // The table alias
  std::string d_alias;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ElectronPhotonRelaxationXsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end DatGen_ElectronPhotonRelaxationXsdirEntry.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   DataGen_XsdirEntryFactory.hpp
//! \author Alex Robinson
//! \brief  The xsdir entry factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_XSDIR_ENTRY_FACTORY_HPP
#define DATA_GEN_XSDIR_ENTRY_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_XsdirEntry.hpp"

namespace DataGen{

//! The xsdir entry factory
class XsdirEntryFactory
{

public:

  //! Create the xsdir entry
  template<typename STLCompliantContainer>
  static void createEntry( const STLCompliantContainer& entry_tokens,
			   Teuchos::RCP<XsdirEntry>& entry );

private:

  // Constructor
  XsdirEntryFactory();
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_XsdirEntryFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_XSDIR_ENTRY_FACTORY_HPP

//---------------------------------------------------------------------------//
// end DataGen_XsdirEntryFactory.hpp
//---------------------------------------------------------------------------//

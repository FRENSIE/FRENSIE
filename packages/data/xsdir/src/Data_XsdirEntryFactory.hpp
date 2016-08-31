//---------------------------------------------------------------------------//
//!
//! \file   Data_XsdirEntryFactory.hpp
//! \author Alex Robinson
//! \brief  The xsdir entry factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSDIR_ENTRY_FACTORY_HPP
#define DATA_XSDIR_ENTRY_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_XsdirEntry.hpp"

namespace Data{

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

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_XsdirEntryFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_XSDIR_ENTRY_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Data_XsdirEntryFactory.hpp
//---------------------------------------------------------------------------//

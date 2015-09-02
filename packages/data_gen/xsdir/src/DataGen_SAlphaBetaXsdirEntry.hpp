//---------------------------------------------------------------------------//
//!
//! \file   DataGen_SAlphaBetaXsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The S(alpha,beta) xsdir entry class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_S_ALPHA_BETA_XSDIR_ENTRY_HPP
#define DATA_GEN_S_ALPHA_BETA_XSDIR_ENTRY_HPP

// FRENSIE Includes
#include "DataGen_XsdirEntry.hpp"

namespace DataGen{

//! The S(alpha,beta) xsdir entry
class SAlphaBetaXsdirEntry : public XsdirEntry
{
  
public:

  //! Constructor
  template<typename STLCompliantContainer>
  SAlphaBetaXsdirEntry( const STLCompliantContainer& entry_tokens );

  //! Destructor
  ~SAlphaBetaXsdirEntry()
  { /* ... */ }

  //! Return the table alias
  const std::string& getTableAlias() const;

  //! Add information to parameter list
  void addInfoToParameterList( Teuchos::ParameterList& parameter_list ) const;

private:

  // The alias
  std::string d_alias;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_SAlphaBetaXsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_S_ALPHA_BETA_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end DataGen_SAlphaBetaXsdirEntry.hpp
//---------------------------------------------------------------------------//

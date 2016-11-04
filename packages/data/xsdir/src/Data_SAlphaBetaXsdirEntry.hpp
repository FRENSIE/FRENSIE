//---------------------------------------------------------------------------//
//!
//! \file   Data_SAlphaBetaXsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The S(alpha,beta) xsdir entry class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_S_ALPHA_BETA_XSDIR_ENTRY_HPP
#define DATA_S_ALPHA_BETA_XSDIR_ENTRY_HPP

// FRENSIE Includes
#include "Data_XsdirEntry.hpp"

namespace Data{

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

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_SAlphaBetaXsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_S_ALPHA_BETA_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end Data_SAlphaBetaXsdirEntry.hpp
//---------------------------------------------------------------------------//

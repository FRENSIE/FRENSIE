//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotoNuclearDataExtractor.cpp
//! \author Ryan Pease
//! \brief  XSS array (from ace table) photonuclear table extractor def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */ 
XSSPhotonuclearDataExtractor::XSSPhotonuclearDataExtractor(
				  const Teuchos::ArrayView<const int>& nxs,
				  const Teuchos::ArrayView<const int>& jxs,
				  const Teuchos::ArrayRCP<const double>& xss )
  : d_nxs( nxs ),
    d_jxs( jxs ),
    d_xss( xss )
{
  // Make sure the arrays have the correct size
  testPrecondition( nxs.size() == 16 );
  testPrecondition( jxs.size() == 32 );
  testPrecondition( xss.size() == nxs[0] );

  //Adjust the indices in the JXS array so they are zero indexed
  for( unsigned i = 0; i < d_jxs.size();i++)
    d_jxs[i] -= 1;   
}

  // Extract the ESZ block  
Teuchos::ArrayView<const double> 
XSSPhotonuclearDataExtractor::extractESZBlock() const{
  return d_xss(d_jxs[0],d_jxs[0]+d_nxs[2]-1;
}

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

// Check if elastic scattering data exists
/* \details Check this before attempting to extract the ELS block.
 */
bool XSSPhotonuclearDataExtractor::hasElasticScatteringData() const
{
    return d_jxs[3] != -1;
}

// Check if average heating numbers data exists
/* \details Check this before attempting to extract the THN block.
 */
bool XSSPhotonuclearDataExtractor::hasHeatingNumberData() const
{
    return d_jxs[4] != -1;
}

  //! Extract the ESZ block  
Teuchos::ArrayView<const double> 
XSSPhotonuclearDataExtractor::extractESZBlock() const
{
  return d_xss( d_jxs[0], d_nxs[2] );
}

 //! Extract the TOT block
 Teuchos::ArrayView<const double>
 XSSPhotonuclearDataExtractor::extractTOTBlock() const
{
  return d_xss( d_jxs[1], d_nxs[2] );
}
 
  //! Extract the NON block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractNONBlock() const
{

  if( hasElasticScatteringData() )
  {
    return d_xss( d_jxs[2] , d_nxs[2] ); 
  }
  else
  {
    return extractTOTBlock();
  }
}

  //! Extract the ELS block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractELSBlock() const
{
  if ( hasElasticScatteringData() )
  {
    return d_xss( d_jxs[3], d_nxs[2] );
  }
  else
  {
    return Teuchos::ArrayView<const double>();    
  } 
}

  //! Extract the THN block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractTHNBlock() const
{
  if ( hasHeatingNumberData() )
  {
    return d_xss( d_jxs[4], d_nxs[2] );
  }
  else
  {
    return Teuchos::ArrayView<const double>();    
  } 
}

  //! Extract the MTR block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractMTRBlock() const
{
  return d_xss( d_jxs[5], d_nxs[3] );
}

  //! Extract the LQR block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLQRBlock() const
{
  return d_xss( d_jxs[6], d_nxs[3] );
}

  //! Extract the LSIG block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLSIGBlock() const
{
  return d_xss( d_jxs[7], d_nxs[3] );
}

  //! Extract the SIG block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractSIGBlock() const
{
  return d_xss( d_jxs[8], d_jxs[9]-d_jxs[8] );
}

  //! Extract the IXS block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractIXSBlock() const
{
  return d_xss( d_jxs[9], d_nxs[0]-d_jxs[9] );
}


} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSPhotonuclearDataExtractor.cpp
//---------------------------------------------------------------------------//

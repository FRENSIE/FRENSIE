//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSSabDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) S(a,b) data extractor class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSSabDataExtractor.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that is can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSSabDataExtractor::XSSSabDataExtractor( 
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
  
  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( unsigned i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;
  
  // Extract and cache the ITIE block
  d_itie_block = d_xss( d_jxs[0], (int)d_xss[d_jxs[0]]*4 + 1 );
  
  // Find appropriate data for ITXE block
  int last_position = d_xss[ (int)d_xss[d_jxs[0]]*4 ];
  int last_energies = d_xss[ (int)d_xss[d_jxs[0]]*3 ];
  int number_angles = d_jxs[2];
  int distance      = last_position*last_energies*(number_angles + 2) - 
                        (int)d_xss[d_jxs[0]]*4 + 1;
  
  // Extract and cache the ITXE block                     
  d_itxe_block = d_xss( (int)d_xss[d_jxs[0]]*4 + 1, distance );
  
  // Extract and cache the ITCE block
  if( d_jxs[3] != 0 )
  {
    d_itce_block = d_xss( d_jxs[3], (int)d_xss[d_jxs[3]]*2 + 1 );
  }
    
  // Extract and cache the ITCA block
  if( d_jxs[3] != 0 && d_nxs[5] != -1 )
  {
    int elastic_energies = (int)d_xss[d_jxs[3]];
    d_itca_block = d_xss( d_jxs[5], elastic_energies*(d_nxs[5] + 1) );
  }
}

// Return the inelastic scattering mode
SabInelasticMode XSSSabDataExtractor::getInelasticScatteringMode() const
{
  try{
    return convertUnsignedToSabInelasticMode( d_nxs[1] );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: invalid inelastic scattering mode found "
			   "while parsing nxs array.\n" );
}

// Return if elastic scattering cross section data is present
/*! \details Elastic scattering cross section data is only present if 
 * jxs[3] != -1
 */
bool XSSSabDataExtractor::hasElasticScatteringCrossSectionData() const
{
  return d_jxs[3] != 0;
}

// Return if elastic scattering angular distribution is present
/*! \details Elastic scattering cross section data is only present if
 * jxs[3] != -1 and nxs[5] != -1
 */ 
bool XSSSabDataExtractor::hasElasticScatteringAngularDistributionData() const
{
  return d_jxs[3] != 0 && d_nxs[5] != -1;
}

// Return the elastic scattering mode
SabElasticMode XSSSabDataExtractor::getElasticScatteringMode() const
{
  return convertUnsignedToSabElasticMode( d_nxs[4] );
}

// Extract the ITIE block from the XSS array
Teuchos::ArrayView<const double> XSSSabDataExtractor::extractITIEBlock() const
{
  return d_itie_block;
}

// Extract the inelastic energy grid from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractInelasticEnergyGrid() const
{
  return d_itie_block( 1, (int)d_itie_block[0] );
}

// Extract the inelastic cross section from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractInelasticCrossSection() const
{
  return d_itie_block( 1+(int)d_itie_block[0], (int)d_itie_block[0] );
}

// Extract the inelastic distribution locations from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractInelasticDistributionLocations() const
{
  return d_itie_block( 1+2*(int)d_itie_block[0], (int)d_itie_block[0] );
}

// Extract the number of outgoing energies list from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractNumberOfOutgoingEnergies() const
{
  return d_itie_block( 1+3*(int)d_itie_block[0], (int)d_itie_block[0] );
}

// Extract the ITCE block from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractITCEBlock() const
{
  return d_itce_block;
}

// Extract the elastic energy grid from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractElasticEnergyGrid() const
{
  if( hasElasticScatteringCrossSectionData() )
    return d_itce_block( 1, (int)d_itce_block[0] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the elastic cross section from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractElasticCrossSection() const
{
  if( hasElasticScatteringCrossSectionData() )
    return d_itce_block( 1+(int)d_itce_block[0], (int)d_itce_block[0] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the ITXE block from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractITXEBlock() const
{
  return d_itxe_block;
}

// Extract the ITCA block from the XSS array
Teuchos::ArrayView<const double> 
XSSSabDataExtractor::extractITCABlock() const
{
  return d_itca_block;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSSabDataExtractor.cpp
//---------------------------------------------------------------------------//

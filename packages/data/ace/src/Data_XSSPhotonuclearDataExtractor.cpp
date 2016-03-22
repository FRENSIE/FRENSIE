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

  // Parse secondary partcle types
  unsigned num_secondary_particle_types = d_nxs[4];
  unsigned ixs_array_subsize = d_nxs[6];

  Teuchos::ArrayView<const double> ixs_array = extractIXSBlock();

  for( unsigned i = 0; i < num_secondary_particle_types;i++)
  {

    unsigned particle_type = (unsigned)ixs_array[i*ixs_array_subsize];
   
    d_secondary_particle_types.insert( particle_type );
    d_secondary_particle_order[ particle_type ] = i;
  }
}

// Check if particle type exists in this data library
/* \details Check this before extracting any sublocks of IXS block
 */
  bool XSSPhotonuclearDataExtractor::hasSecondaryParticleType(const unsigned secondary_particle_type) const
  {
    if(d_secondary_particle_types.count(secondary_particle_type)==1)
      {
      return true;
      }
    else
      {
      return false;
      }
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

  //! Extract the PXS block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractPXSBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+2]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+3]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the PHN block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractPHNBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+3]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+4]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the MTRP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractMTRPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+4]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+5]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the TYRP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractTYRPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+5]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+6]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the LSIGP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLSIGPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+6]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+7]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the SIGP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractSIGPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+7]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+8]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the LANDP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLANDPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+8]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+9]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the ANDP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractANDPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+9]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+10]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the LDLWP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLDLWPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+10]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+11]-1;

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

  //! Extract the DLWP block
Teuchos::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractDLWPBlock(const unsigned secondary_particle_type) const
{
  if( hasSecondaryParticleType(secondary_particle_type) )
    {
      Teuchos::ArrayView<const double> ixs_block = extractIXSBlock();
      
      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      unsigned front = -1;
      unsigned rear = -1;

      // Is this the last particle in the IXS array?
      if (order+1 == d_secondary_particle_types.size() )
	{
	  // locate sub-block within IXS block
	  front = ixs_block[d_nxs[6]*order+11]-1;
	  rear  = d_nxs[0];  
	}
      else
	{
	  // locate sub-block within IXS block
	  front = ixs_block[d_nxs[6]*order+11]-1;
	  rear  = ixs_block[d_nxs[6]*order+14]-1;
	}

      return d_xss( front , rear - front );
    }
  else
    {
      return Teuchos::ArrayView<const double>();
    }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSPhotonuclearDataExtractor.cpp
//---------------------------------------------------------------------------//

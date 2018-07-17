//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotoNuclearDataExtractor.cpp
//! \author Ryan Pease
//! \brief  XSS array (from ace table) photonuclear table extractor def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSPhotonuclearDataExtractor::XSSPhotonuclearDataExtractor(
                       const Utility::ArrayView<const int>& nxs,
                       const Utility::ArrayView<const int>& jxs,
                       const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view(),
    d_secondary_particle_types(),
    d_secondary_particle_order()
{
  // Make sure that the xss array exists
  testPrecondition( xss.get() );

  // Make sure the arrays have the correct size
  TEST_FOR_EXCEPTION( nxs.size() != 16,
                      std::runtime_error,
                      "Invalid nxs array encountered!" );

  TEST_FOR_EXCEPTION( jxs.size() != 32,
                      std::runtime_error,
                      "Invalid jxs array encountered!" );

  TEST_FOR_EXCEPTION( xss->size() != nxs[0],
                      std::runtime_error,
                      "The nxs array expected the xss array to have size "
                      << nxs[0] << " but it was found to have size "
                      << xss->size() << "!" );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( size_t i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Create the XSS view
  d_xss_view = Utility::arrayViewOfConst( *d_xss );

  // Parse secondary particle types
  unsigned num_secondary_particle_types = d_nxs[4];
  unsigned ixs_array_subsize = d_nxs[6];

  Utility::ArrayView<const double> ixs_array = this->extractIXSBlock();

  for( unsigned i = 0; i < num_secondary_particle_types; ++i )
  {
    unsigned particle_type = (unsigned)ixs_array[i*ixs_array_subsize];

    d_secondary_particle_types.insert( particle_type );
    d_secondary_particle_order[ particle_type ] = i;
  }
}

// Check if particle type exists in this data library
/* \details Check this before extracting any sublocks of IXS block
 */
bool XSSPhotonuclearDataExtractor::hasSecondaryParticleType(const OutgoingParticleType secondary_particle_type) const
{
  if(d_secondary_particle_types.count(secondary_particle_type))
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

// Return secondary particle types
const std::set<unsigned>&
XSSPhotonuclearDataExtractor::getSecondaryParticleTypes() const
{
  return d_secondary_particle_types;
}

  //! Extract the ESZ block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractESZBlock() const
{
  return d_xss_view( d_jxs[0], d_nxs[2] );
}

 //! Extract the TOT block
 Utility::ArrayView<const double>
 XSSPhotonuclearDataExtractor::extractTOTBlock() const
{
  return d_xss_view( d_jxs[1], d_nxs[2] );
}

  //! Extract the NON block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractNONBlock() const
{

  if( this->hasElasticScatteringData() )
  {
    return d_xss_view( d_jxs[2] , d_nxs[2] );
  }
  else
  {
    return this->extractTOTBlock();
  }
}

  //! Extract the ELS block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractELSBlock() const
{
  if ( this->hasElasticScatteringData() )
  {
    return d_xss_view( d_jxs[3], d_nxs[2] );
  }
  else
  {
    return Utility::ArrayView<const double>();
  }
}

  //! Extract the THN block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractTHNBlock() const
{
  if ( this->hasHeatingNumberData() )
  {
    return d_xss_view( d_jxs[4], d_nxs[2] );
  }
  else
  {
    return Utility::ArrayView<const double>();
  }
}

  //! Extract the MTR block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractMTRBlock() const
{
  return d_xss_view( d_jxs[5], d_nxs[3] );
}

  //! Extract the LQR block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLQRBlock() const
{
  return d_xss_view( d_jxs[6], d_nxs[3] );
}

  //! Extract the LSIG block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLSIGBlock() const
{
  return d_xss_view( d_jxs[7], d_nxs[3] );
}

  //! Extract the SIG block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractSIGBlock() const
{
  return d_xss_view( d_jxs[8], d_jxs[9]-d_jxs[8] );
}

  //! Extract the IXS block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractIXSBlock() const
{
  return d_xss_view( d_jxs[9], d_nxs[0]-d_jxs[9] );
}

  //! Extract the PXS block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractPXSBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+2]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+3]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the PHN block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractPHNBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+3]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+4]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the MTRP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractMTRPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+4]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+5]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the TYRP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractTYRPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+5]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+6]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the LSIGP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLSIGPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+6]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+7]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the SIGP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractSIGPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+7]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+8]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the LANDP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLANDPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+8]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+9]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the ANDP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractANDPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+9]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+10]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the LDLWP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractLDLWPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

      unsigned order = d_secondary_particle_order.find
	( secondary_particle_type )->second;

      // locate sub-block within IXS block
      unsigned front = ixs_block[d_nxs[6]*order+10]-1;
      unsigned rear  = ixs_block[d_nxs[6]*order+11]-1;

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

  //! Extract the DLWP block
Utility::ArrayView<const double>
XSSPhotonuclearDataExtractor::extractDLWPBlock(const OutgoingParticleType secondary_particle_type) const
{
  if( this->hasSecondaryParticleType(secondary_particle_type) )
    {
      Utility::ArrayView<const double> ixs_block = this->extractIXSBlock();

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

      return d_xss_view( front , rear - front );
    }
  else
    {
      return Utility::ArrayView<const double>();
    }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSPhotonuclearDataExtractor.cpp
//---------------------------------------------------------------------------//

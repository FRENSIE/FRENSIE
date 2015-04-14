//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotonuclearDataExtractor.hpp
//! \author Ryan Pease
//! \brief  XSS array (from ace table) photonuclear transport data extractor 
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_PHOTONUCLEAR_DATA_EXTRACTOR_HPP
#define DATA_XSS_PHOTONUCLEAR_DATA_EXTRACTOR_HPP

// Std Lib Includes
#include <set>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ArrayRCP.hpp>

namespace Data{

/*! \defgroup photonulcear_table Photonuclear Table
 * \ingroup ace_table
 * \todo Ensure SIG and ISX block are correct.
 *
 * After a photonuclear transport table has been read by the 
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSPhotonuclearDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks. The NXS
 * array elements have the following meanings:
 * <ul>
 *  <li> NXS[0] = length of XSS data block</li>
 *  <li> NXS[1] = ZA=Z*1000+A</li>
 *  <li> NXS[2] = number of energies in main grid (Ng)</li>
 *  <li> NXS[3] = number of MT entries n the main energy grid</li>
 *  <li> NXS[4] = number of secondary particle types with IXS information</li>
 *  <li> NXS[5] = number of parameter entries (fixed values) in the IXS array
 *                per secondary particle</li>
 *  <li> NXS[6] = number of entries (fixed values and locators) in the IXS
 *                array per secondary particle</li>
 *  <li> NXS[7-14] = unused (fill with zeros)</li>
 *  <li> NXS[15] = table format version</li>
 * </ul>
 * The JXS array elements have the following meanings:
 * <ul>
 *  <li> JXS[0] = main energy grid</li>
 *  <li> JXS[1] = total cross-section data</li>
 *  <li> JXS[2] = total nonelastic cross-section data</li>
 *  <li> JXS[3] = elastic cross-section data</li>
 *  <li> JXS[4] = total heatng number data</li>
 *  <li> JXS[5] = MT reaction numbers</li>
 *  <li> JXS[6] = Q-value reaction energy data</li>
 *  <li> JXS[7] = cross-section locators (relatve to JXS[8])</li>
 *  <li> JXS[8] = primary locator for cross-section data</li>
 *  <li> JXS[9] = first word of IXS array</li>
 *  <li> JXS[10] = first word of IXS block</li>
 *  <li> JXS[11-31] = unused (fill with zeros)</li>
 * </ul>
 */

/*! The XSS photonuclear data extractor class
 * \ingroup photonuclear_table
 */
class XSSPhotonuclearDataExtractor
{
  
public:

  //! Constructor
  XSSPhotonuclearDataExtractor( const Teuchos::ArrayView<const int>& nxs,
		       const Teuchos::ArrayView<const int>& jxs,
		       const Teuchos::ArrayRCP<const double>& xss );

  //! Destructor
  ~XSSPhotonuclearDataExtractor()
  { /* ... */ }

  //! Check if this secondary particle type exists in this data
  bool hasSecondaryParticleType(const unsigned secondary_particle_type) const;

  //! Check if elastic scattering data exists
  bool hasElasticScatteringData() const;

  //! Check if average heating number data exists
  bool hasHeatingNumberData() const;

  //! Return secondary particle types
  const std::set<unsigned>& getSecondaryParticleTypes() const;  
  
  //! Extract the ESZ block
  Teuchos::ArrayView<const double> extractESZBlock() const;

  //! Extract the TOT block
  Teuchos::ArrayView<const double> extractTOTBlock() const;
 
  //! Extract the NON block
  Teuchos::ArrayView<const double> extractNONBlock() const;

  //! Extract the ELS block
  Teuchos::ArrayView<const double> extractELSBlock() const;

  //! Extract the THN block
  Teuchos::ArrayView<const double> extractTHNBlock() const;

  //! Extract the MTR block
  Teuchos::ArrayView<const double> extractMTRBlock() const;

  //! Extract the LQR block
  Teuchos::ArrayView<const double> extractLQRBlock() const;

  //! Extract the LSIG block
  Teuchos::ArrayView<const double> extractLSIGBlock() const;

  //! Extract the SIG block
  Teuchos::ArrayView<const double> extractSIGBlock() const;

  //! Extract the IXS block
  Teuchos::ArrayView<const double> extractIXSBlock() const;

  //! Extract the PXS block for secondary particle
  Teuchos::ArrayView<const double> extractPXSBlock( const unsigned secondary_particle_type ) const;

  //! Extract the PHN block for secondary particle
  Teuchos::ArrayView<const double> extractPHNBlock( const unsigned secondary_particle_type ) const;

  //! Extract the MTRP block for secondary particle
  Teuchos::ArrayView<const double> extractMTRPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the TYRP block for secondary particle
  Teuchos::ArrayView<const double> extractTYRPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the LSIGP block for secondary particle
  Teuchos::ArrayView<const double> extractLSIGPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the SIGP block for secondary particle
  Teuchos::ArrayView<const double> extractSIGPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the LANDP block for secondary particle
  Teuchos::ArrayView<const double> extractLANDPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the ANDP block for secondary particle
  Teuchos::ArrayView<const double> extractANDPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the LDLWP block for secondary particle
  Teuchos::ArrayView<const double> extractLDLWPBlock( const unsigned secondary_particle_type ) const;

  //! Extract the DLWP block for secondary particle
  Teuchos::ArrayView<const double> extractDLWPBlock( const unsigned secondary_particle_type ) const;
 
private:

  // The nxs array (a copy will be stored)
  Teuchos::Array<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  Teuchos::Array<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  Teuchos::ArrayRCP<const double> d_xss;

  // The secondary particle types within the data
  std::set<unsigned> d_secondary_particle_types;

  // The order of which the secondary particles occur within the IXS block
  std::map<unsigned,unsigned> d_secondary_particle_order;
};

} // end Data namespace

#endif // end DATA_XSS_PHOTONUCLEAR_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSPhotonuclearDataExtractor.hpp
//---------------------------------------------------------------------------//

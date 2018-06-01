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
#include <memory>

// FRENSIE Includes
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"

/*! \defgroup photonuclear_table Photonuclear Table
 * \ingroup ace_table
 * \todo Ensure SIG and ISX block are correct.
 *
 * After a photonuclear transport table has been read by the
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSPhotonuclearDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks.
 */

namespace Data{

/*! The XSS photonuclear data extractor class
 * \ingroup photonuclear_table
 */
class XSSPhotonuclearDataExtractor
{

public:

  /*! The outgoing particle types that may have data
   *
   * Casting the type enum to an integer gives the value used in the
   * XSS array.
   */
  enum OutgoingParticleType
  {
    NEUTRON = 1,
    PHOTON = 2,
    ELECTRON = 3,
    PROTON = 9,
    DEUTERON = 31,
    TRITON = 32,
    HE3 = 33,
    HE4 = 34
  };

  //! Constructor
  XSSPhotonuclearDataExtractor( const Utility::ArrayView<const int>& nxs,
                                const Utility::ArrayView<const int>& jxs,
                                const std::shared_ptr<const std::vector<double> >& xss );

  //! Destructor
  ~XSSPhotonuclearDataExtractor()
  { /* ... */ }

  //! Check if this secondary particle type exists in this data
  bool hasSecondaryParticleType(const OutgoingParticleType secondary_particle_type) const;

  //! Check if elastic scattering data exists
  bool hasElasticScatteringData() const;

  //! Check if average heating number data exists
  bool hasHeatingNumberData() const;

  //! Return secondary particle types
  const std::set<unsigned>& getSecondaryParticleTypes() const;

  //! Extract the ESZ block
  Utility::ArrayView<const double> extractESZBlock() const;

  //! Extract the TOT block
  Utility::ArrayView<const double> extractTOTBlock() const;

  //! Extract the NON block
  Utility::ArrayView<const double> extractNONBlock() const;

  //! Extract the ELS block
  Utility::ArrayView<const double> extractELSBlock() const;

  //! Extract the THN block
  Utility::ArrayView<const double> extractTHNBlock() const;

  //! Extract the MTR block
  Utility::ArrayView<const double> extractMTRBlock() const;

  //! Extract the LQR block
  Utility::ArrayView<const double> extractLQRBlock() const;

  //! Extract the LSIG block
  Utility::ArrayView<const double> extractLSIGBlock() const;

  //! Extract the SIG block
  Utility::ArrayView<const double> extractSIGBlock() const;

  //! Extract the IXS block
  Utility::ArrayView<const double> extractIXSBlock() const;

  //! Extract the PXS block for secondary particle
  Utility::ArrayView<const double> extractPXSBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the PHN block for secondary particle
  Utility::ArrayView<const double> extractPHNBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the MTRP block for secondary particle
  Utility::ArrayView<const double> extractMTRPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the TYRP block for secondary particle
  Utility::ArrayView<const double> extractTYRPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the LSIGP block for secondary particle
  Utility::ArrayView<const double> extractLSIGPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the SIGP block for secondary particle
  Utility::ArrayView<const double> extractSIGPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the LANDP block for secondary particle
  Utility::ArrayView<const double> extractLANDPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the ANDP block for secondary particle
  Utility::ArrayView<const double> extractANDPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the LDLWP block for secondary particle
  Utility::ArrayView<const double> extractLDLWPBlock( const OutgoingParticleType secondary_particle_type ) const;

  //! Extract the DLWP block for secondary particle
  Utility::ArrayView<const double> extractDLWPBlock( const OutgoingParticleType secondary_particle_type ) const;

private:

  // The nxs array (a copy will be stored)
  std::vector<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  std::vector<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  std::shared_ptr<const std::vector<double> > d_xss;

  // The xss array view (stored for quicker slicing)
  Utility::ArrayView<const double> d_xss_view;

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

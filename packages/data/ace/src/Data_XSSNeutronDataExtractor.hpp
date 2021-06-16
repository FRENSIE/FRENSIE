//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSNeutronDataExtractor.hpp
//! \author Alex Robinson, Lewis Gross
//! \brief  XSS array (from ace table) neutron data extractor class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP
#define DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP

// Std Lib Includes
#include <memory>


// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Data_ACEBlocks.hpp"

/*! \defgroup continuous_energy_neutron_table Continuous Energy Neutron Table
 * \ingroup ace_table
 *
 * After a continuous energy neutron table has been read by the
 * Data::ACEFileHandler the individual data blocks must be extracted from
 * the XSS array using the Data::XSSNeutronDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks.
 */

namespace Data{


/*! The XSS neutron data extractor class
 * \ingroup continuous_energy_neutron_table
 */
class XSSNeutronDataExtractor
{

public:

  //! The energy unit
  typedef Utility::Units::MegaElectronVolt EnergyUnit;

  //! The energy quantity
  typedef boost::units::quantity<EnergyUnit> Energy;

  //! The area unit
  typedef Utility::Units::Barn AreaUnit;

  //! The area quantity
  typedef boost::units::quantity<AreaUnit> Area;

  //! Constructor
  XSSNeutronDataExtractor( const Utility::ArrayView<const int>& nxs,
			   const Utility::ArrayView<const int>& jxs,
			   const std::shared_ptr<const std::vector<double> >& xss );

  //! Destructor
  ~XSSNeutronDataExtractor()
  { /* ... */ }

  //! checks if a provided block has data or not
  bool hasData(int block_id) const;

  //! extracts the data for a queried block
  Utility::ArrayView<const double> extractBlock(int block_id) const;

  //! Check if the nuclide is fissionable
  inline bool hasFissionData() const { return hasData(nu); }

  //! Check if the nuclide has delayed neutron data
  inline bool hasDelayedNeutronData() const { return hasData(dnu); }

  //! Check if the nuclide has unresolved resonances
  inline bool hasUnresolvedResonanceData() const { return hasData(lunr); }

  // Query block size in the map given a blockId 
  int queryBlockSize(int block_index) const;

  // Query the nxs array, returns whatever value is is stored at nxs_index
  int queryNXS(int nxs_index) const;

  // Query the jxs array, returns whatever value is is stored at jxs_index  (the c style version, so a -1 is posisble)
  int queryJXS(int jxs_index) const;

  //! Extract the ESZ block from the XSS array
  Utility::ArrayView<const double> extractESZBlock() const;

  //! Extract the energy grid from the XSS array
  Utility::ArrayView<const double> extractEnergyGrid() const;

  //! Extract the energy grid from the XSS array
  Utility::ArrayView<const Energy> extractEnergyGridInMeV() const;

  //! Extract the total cross section from the XSS array
  Utility::ArrayView<const double> extractTotalCrossSection() const;

  //! Extract the total cross section from the XSS array
  Utility::ArrayView<const Area> extractTotalCrossSectionInBarns() const;

  //! Extract the total absorption cross section from the XSS array
  Utility::ArrayView<const double> extractTotalAbsorptionCrossSection() const;

  //! Extract the total absorption cross section from the XSS array
  Utility::ArrayView<const Area> extractTotalAbsorptionCrossSectionInBarns() const;

  //! Extract the total elastic cross section from the XSS array
  Utility::ArrayView<const double> extractElasticCrossSection() const;

  //! Extract the total elastic cross section from the XSS array
  Utility::ArrayView<const Area> extractElasticCrossSectionInBarns() const;

  //! Extract the average heating numbers (MeV/collision) from the XSS array
  Utility::ArrayView<const double> extractAverageHeatingNumbers() const;

  //! Extract the average heating numbers (MeV/collision) from the XSS array
  Utility::ArrayView<const Energy> extractAverageHeatingNumbersInMeV() const;

  //! Extract the NU block form the XSS array
  inline Utility::ArrayView<const double> extractNUBlock() const { return extractBlock(nu); }

  //! Extract the MTR block from the XSS array
  inline Utility::ArrayView<const double> extractMTRBlock() const { return extractBlock(mtr); }

  //! Extract the MTRP block from the XSS array
  inline Utility::ArrayView<const double> extractMTRPBlock() const { return extractBlock(mtrp); }

  //! Extract the LQR block from the XSS array
  inline Utility::ArrayView<const double> extractLQRBlock() const { return extractBlock(lqr); }

  //! Extract the TYR block from the XSS array
  inline Utility::ArrayView<const double> extractTYRBlock() const { return extractBlock(tyr); }

  //! Extract the LSIG block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractLSIGBlock() const { return extractBlock(lsig); }

  //! Extract the LSIGP block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractLSIGPBlock() const { return extractBlock(lsigp); }

  //! Extract the SIG block from the XSS array
  inline Utility::ArrayView<const double> extractSIGBlock() const { return extractBlock(sig); }

  //! Extract the LAND block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractLANDBlock() const
  {
    if(!hasData(landb)) {
      THROW_EXCEPTION(std::logic_error, "Expected land block to exist")
    }
    return extractBlock(landb);
  }

  //! Extract the AND block from the XSS array
  inline Utility::ArrayView<const double> extractANDBlock() const
  {
    if(!hasData(andb)) {
      THROW_EXCEPTION(std::logic_error, "Expected and block to exist")
    }
    return extractBlock(andb);
  }

  //! Extract the LDLW block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractLDLWBlock() const { return extractBlock(ldlw); }

  //! Extract the LDLWP block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractLDLWPBlock() const { return extractBlock(ldlwp); }

  //! Extract the DLW block from the XSS array
  inline Utility::ArrayView<const double> extractDLWBlock() const { return extractBlock(dlw); }

  //! Extract the DLWP block from the XSS array
  inline Utility::ArrayView<const double>  extractDLWPBlock() const { return extractBlock(dlwp); }

  //! Extract the GPD block from the XSS array
  /*! \details For newer evaluations the GPD block only contains the total
  * photon production cross section (size=nxs[2]). For older evaluations, the
  * block also contains the 30*20 matrix of secondary photon energies.
  */
  inline Utility::ArrayView<const double> extractGPDBlock() const { return extractBlock(gpd); }

  //! Extract the SIGP block from the XSS array
  inline Utility::ArrayView<const double> extractSIGPBlock() const { return extractBlock(sigp); }

  //! Extract the LANDP block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractLANDPBlock() const { return extractBlock(landp); }

  //! Extract the ANDP block from the XSS array
  /*! \details Even if photon production interactions are present (nxs[5] != 0 ),
  * it is possible that there will be no ANDP block. This can occur if every
  * entry in the LANDP block is 0 (indicating that the outgoing photon angle is
  * isotropic in the lab frame).
  */
  inline Utility::ArrayView<const double> extractANDPBlock() const { return extractBlock(andp); }

  //! Extract the YP block from the XSS array
  inline Utility::ArrayView<const double> extractYPBlock() const { return extractBlock(yp); }

  //! Extract the FIS block from the XSS array
  inline Utility::ArrayView<const double> extractFISBlock() const { return extractBlock(fis); }

  //! Extract the UNR block from the XSS array
  inline Utility::ArrayView<const double> extractUNRBlock() const { return extractBlock(lunr); }

  //! Extract the DNU (delayed NU) block form the XSS array
  inline Utility::ArrayView<const double> extractDNUBlock() const { return extractBlock(dnu); }

  //! Extract the BDD (basic delayed data) block from the XSS array
  inline Utility::ArrayView<const double> extractBDDBlock() const { return extractBlock(bdd); }

  //! Extract the DNEDL (delayed neutron LDLW) block from the XSS array
  /*! \details All indices in this array are for Fortran arrays.
  * Subtract by one to get the corresponding C array indices.
  */
  inline Utility::ArrayView<const double> extractDNEDLBlock() const { return extractBlock(dnedl); }

  //! Extract the DNED (delayed neutron DLW) block from the XSS array
  inline Utility::ArrayView<const double> extractDNEDBlock() const { return extractBlock(dned); }

  //! Extract the Ace Laws used for each MT Number from the XSS array
  std::vector<double> extractAceLaws() const;

private:

  // The nxs array (a copy will be stored)
  std::vector<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  std::vector<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  std::shared_ptr<const std::vector<double> > d_xss;

  // The xss array view (stored for quicker slicing)
  Utility::ArrayView<const double> d_xss_view;

  // The ESZ block (cached for quick access to cross sections in this block)
  Utility::ArrayView<const double> d_esz_block;

  // create map that accepts a block key and returns a start-length pair
  std::map<int, std::pair<int,int> > block_to_start_length_pair; 
};

} // end Data namespace

#endif // end DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSNeutronDataExtractor.hpp
//---------------------------------------------------------------------------//

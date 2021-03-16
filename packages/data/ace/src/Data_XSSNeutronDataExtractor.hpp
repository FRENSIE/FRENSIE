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

  //! Check if the nuclide is fissionable
  bool hasFissionData() const;

  //! Check if the nuclide has delayed neutron data
  bool hasDelayedNeutronData() const;

  //! Check if the nuclide has unresolved resonances
  bool hasUnresolvedResonanceData() const;

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
  Utility::ArrayView<const double> extractNUBlock() const;

  //! Extract the MTR block from the XSS array
  Utility::ArrayView<const double> extractMTRBlock() const;

  //! Extract the MTRP block from the XSS array
  Utility::ArrayView<const double> extractMTRPBlock() const;

  //! Extract the LQR block from the XSS array
  Utility::ArrayView<const double> extractLQRBlock() const;

  //! Extract the TYR block from the XSS array
  Utility::ArrayView<const double> extractTYRBlock() const;

  //! Extract the LSIG block from the XSS array
  Utility::ArrayView<const double> extractLSIGBlock() const;

  //! Extract the LSIGP block from the XSS array
  Utility::ArrayView<const double> extractLSIGPBlock() const;

  //! Extract the SIG block from the XSS array
  Utility::ArrayView<const double> extractSIGBlock() const;

  //! Extract the LAND block from the XSS array
  Utility::ArrayView<const double> extractLANDBlock() const;

  //! Extract the AND block from the XSS array
  Utility::ArrayView<const double> extractANDBlock() const;

  //! Extract the LDLW block from the XSS array
  Utility::ArrayView<const double> extractLDLWBlock() const;

  //! Extract the LDLWP block from the XSS array
  Utility::ArrayView<const double> extractLDLWPBlock() const;

  //! Extract the DLW block from the XSS array
  Utility::ArrayView<const double> extractDLWBlock() const;

  //! Extract the DLWP block from the XSS array
  Utility::ArrayView<const double> extractDLWPBlock() const;

  //! Extract the GPD block from the XSS array
  Utility::ArrayView<const double> extractGPDBlock() const;

  //! Extract the SIGP block from the XSS array
  Utility::ArrayView<const double> extractSIGPBlock() const;

  //! Extract the LANDP block from the XSS array
  Utility::ArrayView<const double> extractLANDPBlock() const;

  //! Extract the ANDP block from the XSS array
  Utility::ArrayView<const double> extractANDPBlock() const;

  //! Extract the YP block from the XSS array
  Utility::ArrayView<const double> extractYPBlock() const;

  //! Extract the FIS block from the XSS array
  Utility::ArrayView<const double> extractFISBlock() const;

  //! Extract the UNR block from the XSS array
  Utility::ArrayView<const double> extractUNRBlock() const;

  //! Extract the DNU (delayed NU) block form the XSS array
  Utility::ArrayView<const double> extractDNUBlock() const;

  //! Extract the BDD (basic delayed data) block from the XSS array
  Utility::ArrayView<const double> extractBDDBlock() const;

  //! Extract the DNEDL (delayed neutron LDLW) block from the XSS array
  Utility::ArrayView<const double> extractDNEDLBlock() const;

  //! Extract the DNED (delayed neutron DLW) block from the XSS array
  Utility::ArrayView<const double> extractDNEDBlock() const;

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

  // enum to give nxs array parameters appropriate indexing value 
  enum nxsId {    xss_length, // 0, last value position in xss arrary
                  ZAID, // 1, 1000*Z+A
                  nes, // 2, number of energies in grid
                  ntr, // 3, number of reactions, excluding elastic
                  nr, // 4,  number of reactions having secondery neutrons, excluding elastic
                  ntrp, // 5, number of neutron in photon out reactions
                  nxs_place_holder, // 6, place holder for future development in MCNP
                  npcr, // 7, number of delayed neutron precursor families
                  };

  // enum to give block ids appropriate indexing value in jxs array
  enum blockId  {  esz, // 0, location of energy table
                    nu, // 1, location of fission nu data
                    mtr, // 2, location of MT array
                    lqr, // 3, location of Q-value array
                    tyr, // 4, location of reaction type array
                    lsig, // 5, location of table of cross section locators
                    sig, // 6, location of cross sections
                    landb, // 7, location of table of angular distribution locators
                    andb, // 8, location of angular distributions
                    ldlw, // 9, location of table of energy distribution locators
                    dlw, // 10, location of energy distributions
                    gpd, // 11, location of photon production data
                    mtrp, // 12, location of photon production MT array
                    lsigp, // 13, location of photon production cross section locators
                    sigp, // 14, location of photon production cross sections
                    landp, // 15, location of table of photon production angular distribution locators
                    andp, // 16, location of photon production angular distributions
                    ldlwp, // 17, location of table of photon production energy distribution locators
                    dlwp, // 18, location of photon production energy distributions
                    yp, // 19, location of table of yield multipliers
                    fis, // 20, location of totalf ission cross section
                    end, // 21, locaiton of end of last non particle production block ( this is different from nxs[xss_length] sometimes )
                    lunr, // 22, location of probability tables
                    dnu, // 23, locaiton of delayed nubar data
                    bdd, //24, location of basic delayed data (decay rates and probabilities)
                    dnedl, // 25,  location of table of energy distirbution locators 
                    dned // 26, location or energy distributions
                    // the blocks after here (listed in the mcnp manual) can be read about in the NJOY open source code on GitHub
                    // these are particle production blocks that FRENSIE does not support
                    // these blocks appear to come after jxs[end], which explains whey nxs[xss_length] is not always equal to jxs[end]
                  };

  // create map that accepts a block key and returns a start-length pair
  std::map<int, std::pair<int,int> > block_to_start_length_pair; 
};

} // end Data namespace

#endif // end DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSNeutronDataExtractor.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSSabDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) S(a,b) data extractor class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_SAB_DATA_EXTRACTOR_HPP
#define DATA_XSS_SAB_DATA_EXTRACTOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Data_SabInelasticMode.hpp"
#include "Data_SabElasticMode.hpp"

namespace Data{

/*! \defgroup neutron_sab_table Neutron S(a,b) Table
 * \ingroup ace_table
 *
 * After a neutron S(a,b) table has been read by the Data::ACEFileHandler the
 * individual data blocks must be extracted from the XSS array using the
 * Data::XSSSabDataExtractor. Both the NXS array and the JXS array are 
 * required to successfully extract the blocks. The NXS array elements have
 * the following meanings:
 * <ul>
 *  <li> NXS[0] = length of second block of data
 *  <li> NXS[1] = inelastic scattering mode (IDPNI)
 *  <li> NXS[2] = inelastic dimensioning parameter (NIL)
 *  <li> NXS[3] = number of inelastic exciting energies (NIEB)
 *  <li> NXS[4] = elastic scattering mode (IDPNC)
 *  <li> NXS[5] = elastic dimensioning parameter (NCL)
 *  <li> NXS[6] = secondary energy mode (IFENG)
 * </ul>
 * The JXS array elements have the following meanings:
 * <ul>
 *  <li> JXS[0] = location of inelastic energy table (ITIE)
 *  <li> JXS[1] = location of inelastic cross sections (ITIX)
 *  <li> JXS[2] = location of inelastic energy/angle distributions (ITXE)
 *  <li> JXS[3] = location of elastic energy table (ITCE)
 *  <li> JXS[4] = location of elastic cross sections (ITCX)
 *  <li> JXS[5] = location of elastic angular distributions (ITCA)
 * </ul>
 */

/*! The XSS S(a,b) data extractor class
 * \ingroup neutron_sab_table
 */
class XSSSabDataExtractor
{

public:

  //! Constructor
  XSSSabDataExtractor( const Teuchos::ArrayView<const int>& nxs,
		       const Teuchos::ArrayView<const int>& jxs,
		       const Teuchos::ArrayRCP<const double>& xss );

  //! Destructor
  ~XSSSabDataExtractor()
  { /* ... */ }

  //! Return the inelastic scattering mode
  SabInelasticMode getInelasticScatteringMode() const;

  //! Return if elastic scattering cross section data is present
  bool hasElasticScatteringCrossSectionData() const;

  //! Return if elastic scattering angular distribution data is present
  bool hasElasticScatteringAngularDistributionData() const;

  //! Return the elastic scattering mode
  SabElasticMode getElasticScatteringMode() const;

  //! Extract the ITIE block from the XSS array
  Teuchos::ArrayView<const double> extractITIEBlock() const;

  //! Extract the inelastic energy grid from the XSS array
  Teuchos::ArrayView<const double> extractInelasticEnergyGrid() const;

  //! Extract the inelastic cross section from the XSS array
  Teuchos::ArrayView<const double> extractInelasticCrossSection() const;

  //! Extract the ITCE block from the XSS array
  Teuchos::ArrayView<const double> extractITCEBlock() const;

  //! Extract the elastic energy grid from the XSS array
  Teuchos::ArrayView<const double> extractElasticEnergyGrid() const;

  //! Extract the elastic cross section from the XSS array
  Teuchos::ArrayView<const double> extractElasticCrossSection() const;

  //! Extract the ITXE block from the XSS array
  Teuchos::ArrayView<const double> extractITXEBlock() const;

  //! Extract the ITCA block from the XSS array
  Teuchos::ArrayView<const double> extractITCABlock() const;

private:

  // The nxs array (a copy will be stored)
  Teuchos::Array<int> d_nxs;

  // The jxs array (a copy will be stored)
  Teuchos::Array<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  Teuchos::ArrayRCP<const double> d_xss;

  // The ITIE block (cached for quick access to data in this block)
  Teuchos::ArrayView<const double> d_itie_block;

  // The ITCE block (cached for quick access to data in this block)
  Teuchos::ArrayView<const double> d_itce_block;
};

} // end MonteCarlo namespace

#endif // end DATA_XSS_SAB_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSSabDataExtractor.hpp
//---------------------------------------------------------------------------//

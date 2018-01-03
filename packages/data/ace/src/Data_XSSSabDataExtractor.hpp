//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSSabDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) S(a,b) data extractor class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_SAB_DATA_EXTRACTOR_HPP
#define DATA_XSS_SAB_DATA_EXTRACTOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"

// FRENSIE Includes
#include "Data_SabInelasticMode.hpp"
#include "Data_SabElasticMode.hpp"

/*! \defgroup neutron_sab_table Neutron S(a,b) Table
 * \ingroup ace_table
 *
 * After a neutron S(a,b) table has been read by the Data::ACEFileHandler the
 * individual data blocks must be extracted from the XSS array using the
 * Data::XSSSabDataExtractor. Both the NXS array and the JXS array are
 * required to successfully extract the blocks.
 */

namespace Data{

/*! The XSS S(a,b) data extractor class
 * \ingroup neutron_sab_table
 */
class XSSSabDataExtractor
{

public:

  //! Constructor
  XSSSabDataExtractor( const Utility::ArrayView<const int>& nxs,
		       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss );

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
  Utility::ArrayView<const double> extractITIEBlock() const;

  //! Extract the inelastic energy grid from the XSS array
  Utility::ArrayView<const double> extractInelasticEnergyGrid() const;

  //! Extract the inelastic cross section from the XSS array
  Utility::ArrayView<const double> extractInelasticCrossSection() const;

  //! Extract the ITCE block from the XSS array
  Utility::ArrayView<const double> extractITCEBlock() const;

  //! Extract the elastic energy grid from the XSS array
  Utility::ArrayView<const double> extractElasticEnergyGrid() const;

  //! Extract the elastic cross section from the XSS array
  Utility::ArrayView<const double> extractElasticCrossSection() const;

  //! Extract the ITXE block from the XSS array
  Utility::ArrayView<const double> extractITXEBlock() const;

  //! Extract the ITCA block from the XSS array
  Utility::ArrayView<const double> extractITCABlock() const;

private:

  // The nxs array (a copy will be stored)
  std::vector<int> d_nxs;

  // The jxs array (a copy will be stored)
  std::vector<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  std::shared_ptr<const std::vector<double> > d_xss;

  // The xss array view (stored for quicker slicing)
  Utility::ArrayView<const double> d_xss_view;

  // The ITIE block (cached for quick access to data in this block)
  Utility::ArrayView<const double> d_itie_block;

  // The ITCE block (cached for quick access to data in this block)
  Utility::ArrayView<const double> d_itce_block;
};

} // end MonteCarlo namespace

#endif // end DATA_XSS_SAB_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSSabDataExtractor.hpp
//---------------------------------------------------------------------------//

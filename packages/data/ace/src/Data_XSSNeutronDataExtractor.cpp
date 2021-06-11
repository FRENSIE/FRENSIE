//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSNeutronDataExtractor.cpp
//! \author Alex Robinson, Lewis Gross
//! \brief  XSS array (from ace table) neutron data extractor class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Data_ACEBlocks.hpp"
#include "Utility_LoggingMacros.hpp"

#define STRINGIFY( name ) # name // returns a string if you use stringify with some name

typedef std::map<int,std::pair<int,int> >::const_iterator block_iterator;

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSNeutronDataExtractor::XSSNeutronDataExtractor(
            const Utility::ArrayView<const int>& nxs,
            const Utility::ArrayView<const int>& jxs,
            const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view(),
    d_esz_block()
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

  // Extract and cache the ESZ block
  d_esz_block = d_xss_view( d_jxs[esz], 5*d_nxs[nes] );

  // sort given jxs array into map data structure to be used later
  // perhaps turn below into a class method and call from the constructor

  // first, add available blocks 
  // this is the index of the last block that FRENSIE knows how to process
  // if FRENSIE gains particle production blocks or new blocks from MCNP, 
  // this should be changed from dned to the index of the last block in the array
  int last_block = dned;
  std::vector<std::pair<int,int> > available_blocks;
  for(int block = 0 ; block <= last_block ; block++) {
    if(d_jxs[block]>=0) {
      available_blocks.push_back(std::make_pair(d_jxs[block],block));
    }
    // initialize the map to contain all blocks that map to a pair of 0,0, so 
    // blocks that not available can be returned with a start,length pair of (0,0)
    block_to_start_length_pair.insert(std::make_pair(block,std::make_pair(0,0)));
  }

  // sort pairs by first (jxs locations) to get monotone order
  std::sort(available_blocks.begin(),available_blocks.end());

  // compute the correct lengths for blocks in available_blocks
  // first parameter is the block's start, second parameter is the length of that block
  for(std::vector<std::pair<int,int> >::iterator soi=available_blocks.begin() ; soi<available_blocks.end() -1 ; soi++ ) {
      // soi stands for sorted order iterator 
      int block_id = soi->second;    // grab the block corresponding to the first value in the pair
      int start = soi->first;       // grab the jxs position corresponding to the current block
      int next_start = (soi+1)->first;   // grab the jxs position corresponding to the current block
      int length = next_start - start ;    // the difference next - curr is the length of the block curr
      int mcnp_length = length ;    // placeholder for mcnp length if it exists
      std::string block_name = "";
      switch(block_id) {
        case esz:
          block_name = "esz";
          mcnp_length = 5*d_nxs[nes];
          break;
        case mtr:
          block_name = "mtr";
          mcnp_length = d_nxs[ntr];
          break;
        case lqr:
          block_name = "lqr";
          mcnp_length = d_nxs[ntr];
          break;
        case tyr:
          block_name = "tyr";
          mcnp_length = d_nxs[ntr];
          break;
        case lsig:
          block_name = "lsig";
          mcnp_length = d_nxs[ntr];
          break;
        case mtrp:
          block_name = "mtrp";
          mcnp_length = d_nxs[ntrp];
          break;
        case lsigp: 
          block_name = "lsigp";
          mcnp_length = d_nxs[ntrp];
          break;
        case ldlwp:
          block_name = "ldlwp";
          mcnp_length = d_nxs[ntrp];
          break;
        case landp:
          block_name = "landp";
          mcnp_length = d_nxs[ntrp];
          break;
        case landb:
          block_name = "landb";
          mcnp_length = d_nxs[nr] + 1;
          break;
        case ldlw:
          block_name = "ldlw";
          mcnp_length = d_nxs[nr];
          break;
        case dnedl:
          block_name = "dnedl";
          mcnp_length = d_nxs[npcr];
          break;
        case yp:
          block_name = "yp";
          mcnp_length = (int) d_xss_view[d_jxs[yp]] + 1;
          break;
        case fis:
          block_name = "fis";
          mcnp_length = (int) d_xss_view[d_jxs[fis]+1] + 2;
          break;
      }
      if(length!=mcnp_length) {
        FRENSIE_LOG_WARNING("Check ACE Data, size of " << block_name << " BLOCK does not match MCNP Manual");
      }
      block_to_start_length_pair[block_id] = std::make_pair(start,mcnp_length);
  }
}

// checks if a provided block has data or not
bool XSSNeutronDataExtractor::hasData(int block_id) const {
  bool hasData = false;
  if(block_id < last_jxs) {
    if(block_to_start_length_pair.at(block_id).first>0){
      hasData = true;
    }
  }
  return hasData;
}

// return an ArrayView of the block corresponding to block_id
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractBlock(int block_id) const {
  Utility::ArrayView<const double> extracted_block;
  if(block_id < last_jxs) {
    int start = block_to_start_length_pair.at(block_id).first;
    int length = block_to_start_length_pair.at(block_id).second;
    extracted_block = d_xss_view(start,length);
  }
  return extracted_block;
}

// Check if the nuclide is fissionable
bool XSSNeutronDataExtractor::hasFissionData() const
{
  return hasData(nu);
}

// check if the nuclide has delayed neutron data
bool XSSNeutronDataExtractor::hasDelayedNeutronData() const
{
  return hasData(dnu);
}

// Check if the nuclide has unresolved resonances
bool XSSNeutronDataExtractor::hasUnresolvedResonanceData() const
{
  return hasData(lunr);
}

// given a block index, return the size in the map
int XSSNeutronDataExtractor::queryBlockSize(int block_id) const
{
  // need a const iterator since this function is declared const
  block_iterator it = block_to_start_length_pair.find(block_id);
  int block_size = 0;
  if ( it!=block_to_start_length_pair.end() ) {
    // if block exists, return the length 
    block_size = it->second.second;
  }
  return block_size;
}

int XSSNeutronDataExtractor::queryNXS(int nxs_index) const
{
  int nxs_value = 0;
  if(nxs_index < last_nxs) {
    nxs_value = d_nxs[nxs_index];
  }
  return nxs_value;
}

// TODO, should we return the negative 1 or just a 0 in that case?
int XSSNeutronDataExtractor::queryJXS(int jxs_index) const 
{
  int jxs_value = 0;
  if(jxs_index < last_jxs) {
    jxs_value = d_jxs[jxs_index];
  }
  return jxs_value;

}

// Extract the ESZ block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractESZBlock() const
{
  return d_esz_block;
}

// Extract the energy grid from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractEnergyGrid() const
{
  Utility::ArrayView<const double> energy_grid = d_esz_block( 0, d_nxs[nes] );

  // Make sure the extracted energy grid is sorted
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                         energy_grid.end() ),
                      std::runtime_error,
                      "An unsorted energy grid was encountered!" );

  return energy_grid;
}

// Extract the energy grid from the XSS array
auto XSSNeutronDataExtractor::extractEnergyGridInMeV() const -> Utility::ArrayView<const Energy>
{
  Utility::ArrayView<const Energy> energy_grid(
                  Utility::reinterpretAsQuantity<Energy>( d_esz_block.data() ),
                  Utility::ArrayView<const Energy>::size_type(d_nxs[nes]) ); 

  // Make sure the extracted energy grid is sorted
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                         energy_grid.end() ),
                      std::runtime_error,
                      "An unsorted energy grid was encountered!" );

  return energy_grid;
}

// Extract the total cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTotalCrossSection() const
{
  return d_esz_block( d_nxs[nes], d_nxs[nes] );
}

// Extract the total cross section from the XSS array
auto XSSNeutronDataExtractor::extractTotalCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
           Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+d_nxs[nes] ),
           Utility::ArrayView<const Area>::size_type(d_nxs[nes]) );
}

// Extract the total absorption cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTotalAbsorptionCrossSection() const
{
  return d_esz_block( 2*d_nxs[nes], d_nxs[nes] );
}

// Extract the total absorption cross section from the XSS array
auto XSSNeutronDataExtractor::extractTotalAbsorptionCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
         Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+2*d_nxs[nes] ),
         Utility::ArrayView<const Area>::size_type(d_nxs[nes]) );
}

// Extract the elastic cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractElasticCrossSection() const
{
  return d_esz_block( 3*d_nxs[nes], d_nxs[nes] );
}

// Extract the elastic cross section from the XSS array
auto XSSNeutronDataExtractor::extractElasticCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
         Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+3*d_nxs[nes] ),
         Utility::ArrayView<const Area>::size_type(d_nxs[nes]) );
}

// Extract the average heating numbers from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractAverageHeatingNumbers() const
{
  return d_esz_block( 4*d_nxs[nes], d_nxs[nes] );
}

// Extract the average heating numbers from the XSS array
auto XSSNeutronDataExtractor::extractAverageHeatingNumbersInMeV() const -> Utility::ArrayView<const Energy>
{
  return Utility::ArrayView<const Energy>(
       Utility::reinterpretAsQuantity<Energy>( d_esz_block.data()+4*d_nxs[nes] ),
       Utility::ArrayView<const Energy>::size_type(d_nxs[nes]) );
}

// Extract the NU block form the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractNUBlock() const
{
  return extractBlock(nu);
}

// Extract the MTR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractMTRBlock() const
{
  return extractBlock(mtr);
}

// Extract the MTRP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractMTRPBlock() const
{
  return extractBlock(mtrp);
}

// Extract the LQR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLQRBlock() const
{
  return extractBlock(lqr);
}

// Extract the TYR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTYRBlock() const
{
  return extractBlock(tyr);
}

// Extract the LSIG block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLSIGBlock() const
{
  return extractBlock(lsig);
}

// Extract the LSIGP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLSIGPBlock() const
{
  return extractBlock(lsigp);
}

// Extract the SIG block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractSIGBlock() const
{
  return extractBlock(sig);
}

// Extract the LAND block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLANDBlock() const
{
  if(!hasData(landb)) {
    THROW_EXCEPTION(std::logic_error, "Expected land block to exist")
  }
  return extractBlock(landb);
}

// Extract the AND block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractANDBlock() const
{
  if(!hasData(andb)) {
    THROW_EXCEPTION(std::logic_error, "Expected and block to exist")
  }
  return extractBlock(andb);
}

// Extract the LDLW block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLDLWBlock() const
{
  return extractBlock(ldlw);
}

// Extract the LDLWP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLDLWPBlock() const
{
  return extractBlock(ldlwp);
}

// Extract the DLW block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWBlock() const
{
  return extractBlock(dlw);
}

// Extract the DLWP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWPBlock() const
{
    return extractBlock(dlwp);
}

// Extract the GPD block from the XSS array
/*! \details For newer evaluations the GPD block only contains the total
 * photon production cross section (size=nxs[2]). For older evaluations, the
 * block also contains the 30*20 matrix of secondary photon energies.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractGPDBlock() const
{
    return extractBlock(gpd);
}

// Extract the SIGP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractSIGPBlock() const
{
  return extractBlock(sigp);
}

// Extract the LANDP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLANDPBlock() const
{
  return extractBlock(landp);
}

// Extract the ANDP block from the XSS array
/*! \details Even if photon production interactions are present (nxs[5] != 0 ),
 * it is possible that there will be no ANDP block. This can occur if every
 * entry in the LANDP block is 0 (indicating that the outgoing photon angle is
 * isotropic in the lab frame).
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractANDPBlock() const
{
  return extractBlock(andp);
}

// Extract the YP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractYPBlock() const
{
  return extractBlock(yp);
}

// Extract the FIS block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractFISBlock() const
{
  return extractBlock(fis);
}

// Extract the UNR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractUNRBlock() const
{
  return extractBlock(lunr);
}

// Extract the DNU (delayed NU) block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNUBlock() const
{
  return extractBlock(dnu);
}

// Extract the BDD (basic delayed data) block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractBDDBlock() const
{
  return extractBlock(bdd);
}

// Extract the DNEDL (delayed neutron LDLW) block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNEDLBlock() const
{
  return extractBlock(dnedl);
}

// Extract the delayed neutron DLW block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNEDBlock() const
{
  return extractBlock(dned);
}

// Extract the Ace Laws from the XSS array
std::vector<double> XSSNeutronDataExtractor::extractAceLaws() const
{
  std::vector<double> ace_laws;

  if( d_nxs[4] != 0 )
  {
    Utility::ArrayView<const double> ldlw_block =
      XSSNeutronDataExtractor::extractLDLWBlock();

    Utility::ArrayView<const double> mtr_block =
      XSSNeutronDataExtractor::extractMTRBlock();

    ace_laws.resize( ldlw_block.size() );

    for( size_t i = 0; i < ldlw_block.size(); ++i )
    {
      if( d_xss_view[int(ldlw_block[i]) + int(d_jxs[10]) -1] == 0 )
        ace_laws[i] = d_xss_view[int(ldlw_block[i]) + int(d_jxs[10])];
      
      else
      {
        FRENSIE_LOG_TAGGED_WARNING( "XSSNeutronDataExtractor",
                                    "More than one ACE Law found for MT "
                                    "number " << int(mtr_block[i]) << ". "
                                    "This is not currently supported!" );
      }
    }
  }
  
  return ace_laws;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSNeutronDataExtractor.cpp
//---------------------------------------------------------------------------//


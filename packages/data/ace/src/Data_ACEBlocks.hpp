//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEBlocks.hpp
//! \author Lewis Gross
//! \brief  Contains enums so that block names can be used like their indices
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_BLOCKS_HPP
#define DATA_ACE_BLOCKS_HPP

namespace Data{

// enum to give nxs array parameters appropriate indexing value 
enum nxsId {    xss_length, // 0, last value position in xss arrary
                ZAID_idx, // 1, 1000*Z+A
                nes, // 2, number of energies in grid
                ntr, // 3, number of reactions, excluding elastic
                nr, // 4,  number of reactions having secondery neutrons, excluding elastic
                ntrp, // 5, number of neutron in photon out reactions
                nxs_place_holder, // 6, place holder for future development in MCNP
                npcr, // 7, number of delayed neutron precursor families
                last_nxs // 8, used to prevent asking for part of the nxs array that doesn't exist in queryNXS
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
                fis, // 20, location of total fission cross section
                end, // 21, location of the last value in the table of last non particle production block ( this is different from nxs[xss_length] sometimes )
                lunr, // 22, location of probability tables
                dnu, // 23, location of delayed nubar data
                bdd, //24, location of basic delayed data (decay rates and probabilities)
                dnedl, // 25,  location of table of energy distirbution locators 
                dned, // 26, location or energy distributions
                last_jxs // 27, used to prevent asking for part of the jxs array that doesn't exist in queryJXS
                // the blocks after here (listed in the mcnp manual) can be read about in the NJOY open source code on GitHub
                // these are particle production blocks that FRENSIE does not support
                // these blocks appear to come after jxs[end], which explains whey nxs[xss_length] is not always equal to jxs[end]
                };

} // end Data namespace

#endif // end DATA_ACE_BLOCKS_HPP

//---------------------------------------------------------------------------//
// end Data_ACEBlocks.hpp
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_AllIsotopes.cpp
//! \author Alex Bennett
//! \brief  Gives all possible isotopes for depletion.
//!
//---------------------------------------------------------------------------//

// Std Includes
#include <vector>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/assign/list_of.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Transmutation_AllIsotopes.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Transmutation {

// Initializing static member data.
// All isotopes with a half life greater then 1 second.
boost::unordered_map<int, std::pair<int,int> > AllIsotopes::master_isotope_map = 
       boost::assign::list_of< std::pair<int,std::pair<int,int> > >
     (1,std::make_pair(1,7))
     (2,std::make_pair(3,10))
     (3,std::make_pair(4,12))
     (4,std::make_pair(6,16))
     (5,std::make_pair(7,19))
     (6,std::make_pair(8,22))
     (7,std::make_pair(11,24))
     (8,std::make_pair(12,28))
     (9,std::make_pair(15,31))
     (10,std::make_pair(16,34))
     (11,std::make_pair(18,37))
     (12,std::make_pair(19,40))
     (13,std::make_pair(21,43))
     (14,std::make_pair(22,44))
     (15,std::make_pair(25,46))
     (16,std::make_pair(26,49))
     (17,std::make_pair(29,51))
     (18,std::make_pair(30,53))
     (19,std::make_pair(33,56))
     (20,std::make_pair(34,58))
     (21,std::make_pair(39,61))
     (22,std::make_pair(39,63))
     (23,std::make_pair(42,66))
     (24,std::make_pair(42,68))
     (25,std::make_pair(44,71))
     (26,std::make_pair(45,74))
     (27,std::make_pair(50,76))
     (28,std::make_pair(48,79))
     (29,std::make_pair(53,82))
     (30,std::make_pair(54,85))
     (31,std::make_pair(60,87))
     (32,std::make_pair(60,90))
     (33,std::make_pair(63,91))
     (34,std::make_pair(64,95))
     (35,std::make_pair(68,98))
     (36,std::make_pair(69,101))
     (37,std::make_pair(72,103))
     (38,std::make_pair(73,107))
     (39,std::make_pair(76,109))
     (40,std::make_pair(78,112))
     (41,std::make_pair(81,115))
     (42,std::make_pair(83,117))
     (43,std::make_pair(85,120))
     (44,std::make_pair(87,124))
     (45,std::make_pair(89,126))
     (46,std::make_pair(91,128))
     (47,std::make_pair(94,130))
     (48,std::make_pair(96,133))
     (49,std::make_pair(98,135))
     (50,std::make_pair(100,138))
     (51,std::make_pair(103,140))
     (52,std::make_pair(105,143))
     (53,std::make_pair(108,145))
     (54,std::make_pair(109,148))
     (55,std::make_pair(112,151))
     (56,std::make_pair(113,152))
     (57,std::make_pair(117,153))
     (58,std::make_pair(121,155))
     (59,std::make_pair(121,156))
     (60,std::make_pair(125,158))
     (61,std::make_pair(128,159))
     (62,std::make_pair(129,162))
     (63,std::make_pair(130,165))
     (64,std::make_pair(135,166))
     (65,std::make_pair(135,168))
     (66,std::make_pair(139,169))
     (67,std::make_pair(140,172))
     (68,std::make_pair(144,175))
     (69,std::make_pair(144,178))
     (70,std::make_pair(149,180))
     (71,std::make_pair(150,184))
     (72,std::make_pair(153,187))
     (73,std::make_pair(155,192))
     (74,std::make_pair(157,194))
     (75,std::make_pair(160,196))
     (76,std::make_pair(161,202))
     (77,std::make_pair(164,203))
     (78,std::make_pair(166,205))
     (79,std::make_pair(170,210))
     (80,std::make_pair(171,216))
     (81,std::make_pair(176,217))
     (82,std::make_pair(178,220))
     (83,std::make_pair(184,224))
     (84,std::make_pair(187,227))
     (85,std::make_pair(191,229))
     (86,std::make_pair(193,231))
     (87,std::make_pair(199,233))
     (88,std::make_pair(201,234))
     (89,std::make_pair(206,235))
     (90,std::make_pair(208,238))
     (91,std::make_pair(212,239))
     (92,std::make_pair(217,242))
     (93,std::make_pair(226,244))
     (94,std::make_pair(228,247))
     (95,std::make_pair(230,248))
     (96,std::make_pair(233,252))
     (97,std::make_pair(234,251))
     (98,std::make_pair(237,256))
     (99,std::make_pair(241,257))
     (100,std::make_pair(241,260));

boost::unordered_map<int, std::vector<int> > AllIsotopes::master_meta_state_isotope_map = 
       boost::assign::list_of< std::pair<int,std::vector<int> > >
     (11,boost::assign::list_of(1011024))
     (13,boost::assign::list_of(1013026))
     (19,boost::assign::list_of(1019038))
     (21,boost::assign::list_of(1021050)(1021045))
     (25,boost::assign::list_of(1025052))
     (27,boost::assign::list_of(1027060))
     (29,boost::assign::list_of(1029070)(1029068))
     (30,boost::assign::list_of(1030071)(1030069))
     (31,boost::assign::list_of(1031074)(1031072))
     (32,boost::assign::list_of(1032079)(1032077)(1032081)(1032075)(1032073)(1032071))
     (33,boost::assign::list_of(1033082)(1033074)(1033084))
     (34,boost::assign::list_of(1034073)(1034083)(1034085)(1034079)(1034081)(1034077))
     (35,boost::assign::list_of(1035072)(1035082)(1035086)(1035079)(1035077)(1035080)(1035084))
     (36,boost::assign::list_of(1036081)(1036083)(1036079)(1036085))
     (37,boost::assign::list_of(1037081)(1037090)(1037086))
     (38,boost::assign::list_of(1038083)(1038087)(1038085))
     (39,boost::assign::list_of(1039083)(1039098)(1039096)(1039093)(1039090)(1039087)(1039091)
                               (1039089)(1039097))
     (40,boost::assign::list_of(1040089)(1040090))
     (41,boost::assign::list_of(2041090)(1041091)(1041100)(1041098)(1041097)(1041104)(1041095)
                               (1041094)(1041093)(1041102)(1041099))
     (42,boost::assign::list_of(1042093))
     (43,boost::assign::list_of(1043094)(1043095)(1043102)(1043097)(1043099))
     (44,boost::assign::list_of(1044109))
     (45,boost::assign::list_of(1045097)(1045096)(1045099)(1045108)(1045106)(1045105)(1045109)
                               (1045104)(1045102)(1045103)(1045110)(1045101))
     (46,boost::assign::list_of(1046111)(1046107)(1046109))
     (47,boost::assign::list_of(1047101)(1047105)(1047102)(1047122)(1047117)(1047116)(1047115)
                               (1047111)(1047107)(1047106)(1047118)(1047109)(1047120)(1047113)
                               (1047108)(1047110))
     (48,boost::assign::list_of(1048121)(1048119)(1048115)(1048111)(1048117)(1048113))
     (49,boost::assign::list_of(1049110)(1049108)(1049106)(1049115)(1049114)(1049112)(1049104)
                               (1049129)(1049128)(1049127)(1049126)(1049124)(1049113)(2049120)
                               (1049118)(1049117)(1049125)(1049116)(2049130)(1049130)(1049119)
                               (1049121)(1049123)(2049116)(1049120)(1049122)(2049122)(2049118)
                               (1049131))
     (50,boost::assign::list_of(1050113)(1050130)(1050119)(1050117)(1050121)(1050123)(1050129)
                               (1050131)(1050125)(1050127)(1050128))
     (51,boost::assign::list_of(1051132)(1051130)(1051128)(1051134)(1051126)(2051124)(1051120)
                               (1051118)(2051126)(1051124)(1051122))
     (52,boost::assign::list_of(1052119)(1052133)(1052131)(1052127)(1052123)(1052121)(1052129)
                               (1052125))
     (53,boost::assign::list_of(1053133)(1053132)(1053130)(1053134)(1053136))
     (54,boost::assign::list_of(1054135)(1054134)(1054133)(1054125)(1054131)(1054129)(1054127)
                               (1054143))
     (55,boost::assign::list_of(1055136)(1055134)(1055138)(1055135))
     (56,boost::assign::list_of(1056129)(1056137)(1056136)(1056135))
     (57,boost::assign::list_of(1057146))
     (58,boost::assign::list_of(1058139))
     (59,boost::assign::list_of(1059142)(1059148)(1059144))
     (60,boost::assign::list_of(1060137)(1060141))
     (61,boost::assign::list_of(1061148)(1061152)(2061152)(1061154))
     (62,boost::assign::list_of(1062141)(1062143))
     (63,boost::assign::list_of(1063152)(2063152)(1063154))
     (65,boost::assign::list_of(1065158)(1065162)(1065156))
     (66,boost::assign::list_of(1066165))
     (67,boost::assign::list_of(1067156)(1067159)(1067166)(1067163)(1067162)(1067164)(1067170)
                               (1067161))
     (68,boost::assign::list_of(1068167))
     (70,boost::assign::list_of(1070169))
     (71,boost::assign::list_of(1071166)(1071172)(1071171)(2071166)(1071169))
     (74,boost::assign::list_of(1074183))
     (76,boost::assign::list_of(1076189)(1076183))
     (77,boost::assign::list_of(1077193)(1077191)(1077168))
     (79,boost::assign::list_of(1079195))
     (80,boost::assign::list_of(1080195))
     (82,boost::assign::list_of(1082201)(1082203))
     (83,boost::assign::list_of(1083201))
     (91,boost::assign::list_of(1091234))
     (92,boost::assign::list_of(1092235))
     (93,boost::assign::list_of(1093240))
     (94,boost::assign::list_of(1094237))
     (95,boost::assign::list_of(1095246));

// Returns the limits of the zaid
std::pair<int,int> AllIsotopes::getZaidLimits(const int z)
{
     if( AllIsotopes::master_isotope_map.find(z) != AllIsotopes::master_isotope_map.end())
     {
          return AllIsotopes::master_isotope_map.find(z)->second;
     }
     else
     {
          TEST_FOR_EXCEPTION( AllIsotopes::master_isotope_map.find(z) == 
                              AllIsotopes::master_isotope_map.end(), 
                              std::logic_error,
                              "Error: The z number " << z << " is invalid.");
     }
} 

void AllIsotopes::getZaids(const int z, Teuchos::Array<int>& zaids)
{
     zaids.clear();
     int array_loc = 0;

     boost::unordered_map<int, std::pair<int,int> >::const_iterator it = AllIsotopes::master_isotope_map.find(z);

     if( it != AllIsotopes::master_isotope_map.end())
     {
  
          zaids.resize(it->second.second - it->second.first + 1);

          for(int i = it->second.first ;
                  i <= it->second.second ;
                ++i)
          {
               zaids[array_loc] = z*1000 + i;
               array_loc++;
          }
     }
     else
     {
          TEST_FOR_EXCEPTION( AllIsotopes::master_isotope_map.find(z) == 
                              AllIsotopes::master_isotope_map.end(), 
                              std::logic_error,
                              "Error: The z number " << z << " is invalid.");
     }
} 

void AllIsotopes::getAllZaids( Teuchos::Array<int>& zaids)
{
     zaids.clear();

     boost::unordered_map<int, std::pair<int,int> >::const_iterator it;
    
     for( it = AllIsotopes::master_isotope_map.begin();
          it != AllIsotopes::master_isotope_map.end();
          ++it)
     {
          for(int i = it->second.first ;
                  i <= it->second.second ;
                ++i)
          {
               zaids.push_back(it->first*1000 + i);
          }
     }
} 


void AllIsotopes::getMetaStateZaids(const int z, Teuchos::Array<int>& meta_state_zaids)
{
     // Test for a valid z number
     testPrecondition( z > 0 and z < 101 );

     meta_state_zaids.clear();

     boost::unordered_map<int, std::vector<int> >::const_iterator it = AllIsotopes::master_meta_state_isotope_map.find(z);

     if( it != AllIsotopes::master_meta_state_isotope_map.end())
     {
  
          meta_state_zaids.resize( it->second.size() );

          meta_state_zaids.assign( it->second.begin(), it->second.end());
     }
}

void AllIsotopes::getAllMetaStateZaids( Teuchos::Array<int>& meta_state_zaids)
{
     // Clear the meta state state list
     meta_state_zaids.clear();

     // Create a list of zaids
     boost::unordered_set<int> zaids_set;
     boost::unordered_map<int, std::vector<int> >::const_iterator it;

     // Fill the list of zaids
     for(it = AllIsotopes::master_meta_state_isotope_map.begin();
         it != AllIsotopes::master_meta_state_isotope_map.end();
         ++it)
     { 
          zaids_set.insert(it->second.begin(),
                           it->second.end());
     }

     meta_state_zaids.insert( meta_state_zaids.end(), zaids_set.begin(), zaids_set.end());          
}

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_AllIsotopes.cpp
//---------------------------------------------------------------------------//

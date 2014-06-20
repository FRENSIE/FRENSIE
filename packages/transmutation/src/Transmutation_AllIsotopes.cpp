//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_AllIsotopes.cpp
//! \author Alex Bennett
//! \brief  Gives all possible isotopes for depletion.
//!
//---------------------------------------------------------------------------//

// Std Includes
#include <stdexcept>
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

namespace Transmutation {

// Initializing static member data.
// All isotopes with a half life greater then 1 second.
boost::unordered_map<int, std::pair<int,int> > AllIsotopes::master_isotope_map = 
       boost::assign::list_of< std::pair<int,std::pair<int,int> > >
     (1,std::make_pair(1,3))
     (2,std::make_pair(3,4))
     (3,std::make_pair(6,7))
     (4,std::make_pair(7,11))
     (5,std::make_pair(10,11))
     (6,std::make_pair(10,15))
     (7,std::make_pair(13,17))
     (8,std::make_pair(14,22))
     (9,std::make_pair(17,23))
     (10,std::make_pair(18,24))
     (11,std::make_pair(21,26))
     (12,std::make_pair(22,29))
     (13,std::make_pair(24,30))
     (14,std::make_pair(26,34))
     (15,std::make_pair(29,37))
     (16,std::make_pair(30,42))
     (17,std::make_pair(33,43))
     (18,std::make_pair(35,47))
     (19,std::make_pair(37,49))
     (20,std::make_pair(40,52))
     (21,std::make_pair(43,53))
     (22,std::make_pair(44,55))
     (23,std::make_pair(47,55))
     (24,std::make_pair(48,59))
     (25,std::make_pair(51,59))
     (26,std::make_pair(52,64))
     (27,std::make_pair(55,65))
     (28,std::make_pair(56,72))
     (29,std::make_pair(58,75))
     (30,std::make_pair(60,78))
     (31,std::make_pair(63,81))
     (32,std::make_pair(64,83))
     (33,std::make_pair(67,85))
     (34,std::make_pair(68,88))
     (35,std::make_pair(71,90))
     (36,std::make_pair(72,93))
     (37,std::make_pair(75,94))
     (38,std::make_pair(76,96))
     (39,std::make_pair(79,99))
     (40,std::make_pair(80,103))
     (41,std::make_pair(83,105))
     (42,std::make_pair(84,108))
     (43,std::make_pair(87,108))
     (44,std::make_pair(88,112))
     (45,std::make_pair(91,114))
     (46,std::make_pair(93,118))
     (47,std::make_pair(95,120))
     (48,std::make_pair(96,124))
     (49,std::make_pair(99,127))
     (50,std::make_pair(101,134))
     (51,std::make_pair(105,135))
     (52,std::make_pair(108,138))
     (53,std::make_pair(111,139))
     (54,std::make_pair(112,142))
     (55,std::make_pair(115,143))
     (56,std::make_pair(116,146))
     (57,std::make_pair(120,149))
     (58,std::make_pair(123,152))
     (59,std::make_pair(124,154))
     (60,std::make_pair(127,156))
     (61,std::make_pair(128,159))
     (62,std::make_pair(131,162))
     (63,std::make_pair(135,165))
     (64,std::make_pair(135,166))
     (65,std::make_pair(139,168))
     (66,std::make_pair(142,169))
     (67,std::make_pair(145,172))
     (68,std::make_pair(145,175))
     (69,std::make_pair(150,177))
     (70,std::make_pair(151,180))
     (71,std::make_pair(154,184))
     (72,std::make_pair(154,186))
     (73,std::make_pair(160,192))
     (74,std::make_pair(162,190))
     (75,std::make_pair(165,196))
     (76,std::make_pair(168,200))
     (77,std::make_pair(171,202))
     (78,std::make_pair(175,204))
     (79,std::make_pair(176,205))
     (80,std::make_pair(179,209))
     (81,std::make_pair(180,213))
     (82,std::make_pair(185,215))
     (83,std::make_pair(190,218))
     (84,std::make_pair(195,222))
     (85,std::make_pair(198,224))
     (86,std::make_pair(200,229))
     (87,std::make_pair(204,232))
     (88,std::make_pair(207,234))
     (89,std::make_pair(214,235))
     (90,std::make_pair(215,238))
     (91,std::make_pair(215,239))
     (92,std::make_pair(227,242))
     (93,std::make_pair(228,244))
     (94,std::make_pair(228,247))
     (95,std::make_pair(230,248))
     (96,std::make_pair(233,252))
     (97,std::make_pair(234,251))
     (98,std::make_pair(239,256))
     (99,std::make_pair(241,257))
     (100,std::make_pair(245,259));

boost::unordered_map<int, std::vector<int> > AllIsotopes::master_meta_state_isotope_map = 
       boost::assign::list_of< std::pair<int,std::vector<int> > >
     (29,boost::assign::list_of(1029070)(1029068))
     (30,boost::assign::list_of(1030071)(1030069))
     (31,boost::assign::list_of(1031074)(1031072))
     (32,boost::assign::list_of(1032079)(1032077)(1032075)(1032073)(1032071))
     (33,boost::assign::list_of(1033082)(1033074)(1033084))
     (34,boost::assign::list_of(1034073)(1034083)(1034085)(1034079)(1034081)(1034077))
     (35,boost::assign::list_of(1035082)(1035086)(1035079)(1035077)(1035080)(1035084))
     (36,boost::assign::list_of(1036081)(1036083)(1036079)(1036085))
     (37,boost::assign::list_of(1037090)(1037086))
     (38,boost::assign::list_of(1038087)(1038085))
     (39,boost::assign::list_of(1039098)(1039096)(1039093)(1039090)(1039091)(1039089)
                               (1039097))
     (40,boost::assign::list_of(1040090))
     (41,boost::assign::list_of(1041100)(1041098)(1041097)(1041104)(1041095)(1041094)
                               (1041093)(1041102)(1041099))
     (42,boost::assign::list_of(1042093))
     (43,boost::assign::list_of(1043095)(1043102)(1043097)(1043099))
     (44,boost::assign::list_of(1044109))
     (45,boost::assign::list_of(1045108)(1045106)(1045105)(1045109)(1045104)(1045102)
                               (1045103)(1045110)(1045101))
     (46,boost::assign::list_of(1046111)(1046107)(1046109))
     (47,boost::assign::list_of(1047105)(1047122)(1047117)(1047116)(1047115)(1047111)
                               (1047107)(1047106)(1047118)(1047109)(1047120)(1047113)
                               (1047108)(1047110))
     (48,boost::assign::list_of(1048121)(1048119)(1048115)(1048111)(1048117)(1048113))
     (49,boost::assign::list_of(1049115)(1049114)(1049112)(1049129)(1049128)(1049127)
                               (1049126)(1049124)(1049113)(2049120)(1049118)(1049117)
                               (1049125)(1049116)(2049130)(1049130)(1049119)(1049121)
                               (1049123)(2049116)(1049120)(1049122)(2049122)(2049118)
                               (1049131))
     (50,boost::assign::list_of(1050113)(1050130)(1050119)(1050117)(1050121)(1050123)
                               (1050129)(1050131)(1050125)(1050127)(1050128))
     (51,boost::assign::list_of(1051132)(1051130)(1051128)(1051134)(1051126)(2051124)
                               (1051120)(1051118)(2051126)(1051124)(1051122))
     (52,boost::assign::list_of(1052133)(1052131)(1052127)(1052123)(1052121)(1052129)
                               (1052125))
     (53,boost::assign::list_of(1053133)(1053132)(1053130)(1053134)(1053136))
     (54,boost::assign::list_of(1054135)(1054134)(1054133)(1054125)(1054131)(1054129)
                               (1054127)(1054143))
     (55,boost::assign::list_of(1055136)(1055134)(1055138)(1055135))
     (56,boost::assign::list_of(1056137)(1056136)(1056135))
     (57,boost::assign::list_of(1057146))
     (58,boost::assign::list_of(1058139))
     (59,boost::assign::list_of(1059142)(1059148)(1059144))
     (61,boost::assign::list_of(1061148)(1061152)(2061152)(1061154))
     (63,boost::assign::list_of(1063152)(2063152)(1063154))
     (65,boost::assign::list_of(1065158)(1065162)(1065156))
     (66,boost::assign::list_of(1066165))
     (67,boost::assign::list_of(1067159)(1067166)(1067163)(1067162)(1067164)(1067170)
                               (1067161))
     (68,boost::assign::list_of(1068167))
     (70,boost::assign::list_of(1070169))
     (71,boost::assign::list_of(1071172)(1071171)(1071169));


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
     meta_state_zaids.clear();

     boost::unordered_set<int> zaids_set;
     boost::unordered_map<int, std::vector<int> >::const_iterator it;

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

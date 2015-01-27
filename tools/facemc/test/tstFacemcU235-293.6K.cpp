//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcU235-293.6K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for U-235 at 293.6K
//!
//---------------------------------------------------------------------------//

// Teuchos Includes
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_LocalTestingHelpers.hpp>

// FRENSIE Includes
#include "facemcCore.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

int main( int argc, char** argv )
{
  Teuchos::FancyOStream& out = 
    *Teuchos::VerboseObjectBase::getDefaultOStream();

  bool success = true;

  // Run the test problem
  int return_value = facemcCore( argc, argv );

  if( return_value == 0 )
  {
    Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering( 1 ),
      dimension_ordering_result;

    dimension_ordering[0] = MonteCarlo::ENERGY_DIMENSION;

    Teuchos::Array<double> energy_bins( 125 ),
      energy_bins_result;
    energy_bins[0] = 1e-11;
    energy_bins[1] = 0.001; 
    energy_bins[2] = 0.0010778; 
    energy_bins[3] = 0.0011616; 
    energy_bins[4] = 0.0012519; 
    energy_bins[5] = 0.0013492; 
    energy_bins[6] = 0.0014541;
    energy_bins[7] = 0.0015672; 
    energy_bins[8] = 0.001689; 
    energy_bins[9] = 0.0018204; 
    energy_bins[10] = 0.0019619; 
    energy_bins[11] = 0.0021145; 
    energy_bins[12] = 0.0022789;
    energy_bins[13] = 0.0024561; 
    energy_bins[14] = 0.0026471; 
    energy_bins[15] = 0.0028529; 
    energy_bins[16] = 0.0030747; 
    energy_bins[17] = 0.0033138; 
    energy_bins[18] = 0.0035715;
    energy_bins[19] = 0.0038492; 
    energy_bins[20] = 0.0041485; 
    energy_bins[21] = 0.004471;
    energy_bins[22] = 0.0048187;
    energy_bins[23] = 0.0051933; 
    energy_bins[24] = 0.0055972;
    energy_bins[25] = 0.0060324;
    energy_bins[26] = 0.0065014;
    energy_bins[27] = 0.0070069;
    energy_bins[28] = 0.0075518;
    energy_bins[29] = 0.008139;
    energy_bins[30] = 0.0087718;
    energy_bins[31] = 0.0094539;
    energy_bins[32] = 0.010189;
    energy_bins[33] = 0.010981; 
    energy_bins[34] = 0.011835;
    energy_bins[35] = 0.012755;
    energy_bins[36] = 0.013747;
    energy_bins[37] = 0.014816;
    energy_bins[38] = 0.015968;
    energy_bins[39] = 0.01721;
    energy_bins[40] = 0.018548;
    energy_bins[41] = 0.01999;
    energy_bins[42] = 0.021544;
    energy_bins[43] = 0.02322;
    energy_bins[44] = 0.025025;
    energy_bins[45] = 0.026971;
    energy_bins[46] = 0.029068;
    energy_bins[47] = 0.031328;
    energy_bins[48] = 0.033764;
    energy_bins[49] = 0.036389;
    energy_bins[50] = 0.039219;
    energy_bins[51] = 0.042268;
    energy_bins[52] = 0.045555;
    energy_bins[53] = 0.049097;
    energy_bins[54] = 0.052915; 
    energy_bins[55] = 0.057029;
    energy_bins[56] = 0.061464;
    energy_bins[57] = 0.066243;
    energy_bins[58] = 0.071393;
    energy_bins[59] = 0.076945;
    energy_bins[60] = 0.082928;
    energy_bins[61] = 0.089376;
    energy_bins[62] = 0.096325;
    energy_bins[63] = 0.10382;
    energy_bins[64] = 0.11189;
    energy_bins[65] = 0.12059;
    energy_bins[66] = 0.12996;
    energy_bins[67] = 0.14007;
    energy_bins[68] = 0.15096;
    energy_bins[69] = 0.1627;
    energy_bins[70] = 0.17535; 
    energy_bins[71] = 0.18898;
    energy_bins[72] = 0.20368; 
    energy_bins[73] = 0.21951;
    energy_bins[74] = 0.23658; 
    energy_bins[75] = 0.25498; 
    energy_bins[76] = 0.2748; 
    energy_bins[77] = 0.29617; 
    energy_bins[78] = 0.3192; 
    energy_bins[79] = 0.34402; 
    energy_bins[80] = 0.37077; 
    energy_bins[81] = 0.3996;
    energy_bins[82] = 0.43067; 
    energy_bins[83] = 0.46416; 
    energy_bins[84] = 0.50025; 
    energy_bins[85] = 0.53915; 
    energy_bins[86] = 0.58107; 
    energy_bins[87] = 0.62625; 
    energy_bins[88] = 0.67494; 
    energy_bins[89] = 0.72743;
    energy_bins[90] = 0.78399; 
    energy_bins[91] = 0.84495; 
    energy_bins[92] = 0.91065; 
    energy_bins[93] = 0.98145; 
    energy_bins[94] = 1.0578; 
    energy_bins[95] = 1.14; 
    energy_bins[96] = 1.2287; 
    energy_bins[97] = 1.3242;
    energy_bins[98] = 1.4272; 
    energy_bins[99] = 1.5381; 
    energy_bins[100] = 1.6577; 
    energy_bins[101] = 1.7866; 
    energy_bins[102] = 1.9255; 
    energy_bins[103] = 2.0753; 
    energy_bins[104] = 2.2366; 
    energy_bins[105] = 2.4105; 
    energy_bins[106] = 2.598;
    energy_bins[107] = 2.8; 
    energy_bins[108] = 3.0177; 
    energy_bins[109] = 3.2523; 
    energy_bins[110] = 3.5052; 
    energy_bins[111] = 3.7778; 
    energy_bins[112] = 4.0715; 
    energy_bins[113] = 4.3881; 
    energy_bins[114] = 4.7293; 
    energy_bins[115] = 5.097;
    energy_bins[116] = 5.4934; 
    energy_bins[117] = 5.9205; 
    energy_bins[118] = 6.3808; 
    energy_bins[119] = 6.877; 
    energy_bins[120] = 7.4117; 
    energy_bins[121] = 7.988; 
    energy_bins[122] = 8.6091; 
    energy_bins[123] = 9.2785; 
    energy_bins[124] = 10;

    Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 124 ),
      raw_bin_data_result;
    raw_bin_data[0](61, 61);
    raw_bin_data[1](9, 9);
    raw_bin_data[2](6, 6);
    raw_bin_data[3](9, 9);
    raw_bin_data[4](19, 19);
    raw_bin_data[5](14, 14);
    raw_bin_data[6](17, 17);
    raw_bin_data[7](14, 14);
    raw_bin_data[8](17, 17);
    raw_bin_data[9](12, 12);
    raw_bin_data[10](20, 20);
    raw_bin_data[11](21, 21);
    raw_bin_data[12](22, 22);
    raw_bin_data[13](42, 42);
    raw_bin_data[14](26, 26);
    raw_bin_data[15](39, 39);
    raw_bin_data[16](33, 33);
    raw_bin_data[17](35, 35);
    raw_bin_data[18](47, 47);
    raw_bin_data[19](55, 55);
    raw_bin_data[20](65, 65);
    raw_bin_data[21](72, 72);
    raw_bin_data[22](60, 60);
    raw_bin_data[23](72, 72);
    raw_bin_data[24](88, 88);
    raw_bin_data[25](106, 106);
    raw_bin_data[26](102, 102);
    raw_bin_data[27](143, 143);
    raw_bin_data[28](152, 152);
    raw_bin_data[29](174, 174);
    raw_bin_data[30](174, 174);
    raw_bin_data[31](253, 253);
    raw_bin_data[32](255, 255); 
    raw_bin_data[33](277, 277);
    raw_bin_data[34](280, 280);
    raw_bin_data[35](373, 373);
    raw_bin_data[36](409, 409); 
    raw_bin_data[37](428, 428);
    raw_bin_data[38](481, 481);
    raw_bin_data[39](534, 534);
    raw_bin_data[40](631, 631);
    raw_bin_data[41](651, 651);
    raw_bin_data[42](782, 782);
    raw_bin_data[43](864, 864); 
    raw_bin_data[44](1035, 1035);
    raw_bin_data[45](1111, 1111); 
    raw_bin_data[46](1196, 1196);
    raw_bin_data[47](1407, 1409);
    raw_bin_data[48](1583, 1585); 
    raw_bin_data[49](1713, 1715); 
    raw_bin_data[50](2074, 2074); 
    raw_bin_data[51](2204, 2204); 
    raw_bin_data[52](2482, 2490);
    raw_bin_data[53](2900, 2906); 
    raw_bin_data[54](3051, 3061);
    raw_bin_data[55](3583, 3595);
    raw_bin_data[56](3961, 3971);
    raw_bin_data[57](4531, 4539);
    raw_bin_data[58](5042, 5066); 
    raw_bin_data[59](5564, 5590); 
    raw_bin_data[60](6416, 6444);
    raw_bin_data[61](7087, 7121);
    raw_bin_data[62](7917, 7955);
    raw_bin_data[63](8978, 9026); 
    raw_bin_data[64](10103, 10165); 
    raw_bin_data[65](11244, 11330); 
    raw_bin_data[66](12881, 13003);
    raw_bin_data[67](14093, 14219); 
    raw_bin_data[68](15922, 16092); 
    raw_bin_data[69](18143, 18327); 
    raw_bin_data[70](20270, 20522);
    raw_bin_data[71](22735, 23055); 
    raw_bin_data[72](24813, 25227); 
    raw_bin_data[73](27826, 28370); 
    raw_bin_data[74](30890, 31444);
    raw_bin_data[75](34842, 35656); 
    raw_bin_data[76](37705, 38609);
    raw_bin_data[77](41429, 42483);
    raw_bin_data[78](45134, 46274);
    raw_bin_data[79](50182, 51670); 
    raw_bin_data[80](54884, 56776); 
    raw_bin_data[81](59525, 61649);
    raw_bin_data[82](65047, 67693);
    raw_bin_data[83](70047, 73047); 
    raw_bin_data[84](75904, 79412); 
    raw_bin_data[85](81133, 85141);
    raw_bin_data[86](86649, 91417);
    raw_bin_data[87](92251, 97497); 
    raw_bin_data[88](96766, 102674); 
    raw_bin_data[89](102283, 109033); 
    raw_bin_data[90](107383, 114701);
    raw_bin_data[91](112077, 120289); 
    raw_bin_data[92](116760, 125812); 
    raw_bin_data[93](120815, 130789); 
    raw_bin_data[94](124791, 135079); 
    raw_bin_data[95](128420, 139714); 
    raw_bin_data[96](131612, 143678); 
    raw_bin_data[97](134046, 146704);
    raw_bin_data[98](135732, 149272); 
    raw_bin_data[99](136645, 150663); 
    raw_bin_data[100](136248, 150198); 
    raw_bin_data[101](136515, 150775); 
    raw_bin_data[102](134048, 148034); 
    raw_bin_data[103](130295, 144029); 
    raw_bin_data[104](126504, 139512);
    raw_bin_data[105](121319, 133701); 
    raw_bin_data[106](116504, 128024); 
    raw_bin_data[107](109842, 120212);
    raw_bin_data[108](103919, 113153);
    raw_bin_data[109](96296, 104296); 
    raw_bin_data[110](88231, 94737); 
    raw_bin_data[111](79091, 84183);
    raw_bin_data[112](71451, 75521); 
    raw_bin_data[113](64149, 67421); 
    raw_bin_data[114](57425, 59821); 
    raw_bin_data[115](49353, 51047);
    raw_bin_data[116](42209, 43351); 
    raw_bin_data[117](39303, 40033); 
    raw_bin_data[118](34957, 35451); 
    raw_bin_data[119](26957, 27219);
    raw_bin_data[120](33848, 34018); 
    raw_bin_data[121](31655, 31721); 
    raw_bin_data[122](24166, 24196); 
    raw_bin_data[123](8637804, 8637818);

    Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 124 ),
      processed_bin_data_result;
    processed_bin_data[0](6.1e-06, 0.128036489419817); 
    processed_bin_data[1](9e-07, 0.3333331833333);
    processed_bin_data[2](6e-07, 0.408248167989357); 
    processed_bin_data[3](9e-07, 0.3333331833333);
    processed_bin_data[4](1.9e-06, 0.229415515925511);
    processed_bin_data[5](1.4e-06, 0.26726105482949);
    processed_bin_data[6](1.7e-06, 0.242535418880964);
    processed_bin_data[7](1.4e-06, 0.26726105482949);
    processed_bin_data[8](1.7e-06, 0.242535418880964); 
    processed_bin_data[9](1.2e-06, 0.28867496138968);
    processed_bin_data[10](2e-06, 0.223606574143069);
    processed_bin_data[11](2.1e-06, 0.218217661107087);
    processed_bin_data[12](2.2e-06, 0.213200481834693); 
    processed_bin_data[13](4.2e-06, 0.154303025924717);
    processed_bin_data[14](2.6e-06, 0.196115880187043); 
    processed_bin_data[15](3.9e-06, 0.160127841554883);
    processed_bin_data[16](3.3e-06, 0.174077368727329); 
    processed_bin_data[17](3.5e-06, 0.169030555141455);
    processed_bin_data[18](4.7e-06, 0.145864648714762); 
    processed_bin_data[19](5.5e-06, 0.134839601682214);
    processed_bin_data[20](6.5e-06, 0.124034331475666); 
    processed_bin_data[21](7.2e-06, 0.117850705932926);
    processed_bin_data[22](6e-06, 0.129099057574665); 
    processed_bin_data[23](7.2e-06, 0.117850705932926);
    processed_bin_data[24](8.8e-06, 0.106599889135197); 
    processed_bin_data[25](1.06e-05, 0.0971280714528552);
    processed_bin_data[26](1.02e-05, 0.0990142493211328); 
    processed_bin_data[27](1.43e-05, 0.0836236030855344);
    processed_bin_data[28](1.52e-05, 0.0811100941216385);
    processed_bin_data[29](1.74e-05, 0.0758091448097234);
    processed_bin_data[30](1.74e-05, 0.0758091448097234); 
    processed_bin_data[31](2.53e-05, 0.0628686660424768);
    processed_bin_data[32](2.55e-05, 0.0626216306674537); 
    processed_bin_data[33](2.77e-05, 0.0600833446409993);
    processed_bin_data[34](2.8e-05, 0.0597605938008364); 
    processed_bin_data[35](3.73e-05, 0.051777071638449);
    processed_bin_data[36](4.09e-05, 0.0494458064456545);
    processed_bin_data[37](4.28e-05, 0.0483357900331715);
    processed_bin_data[38](4.81e-05, 0.0455949786599586);
    processed_bin_data[39](5.34e-05, 0.0432730768033654);
    processed_bin_data[40](6.31e-05, 0.0398081154274191); 
    processed_bin_data[41](6.51e-05, 0.0391918143276355);
    processed_bin_data[42](7.82e-05, 0.035758528752126);
    processed_bin_data[43](8.64e-05, 0.0340192211463962);
    processed_bin_data[44](0.0001035, 0.0310818849955923);
    processed_bin_data[45](0.0001111, 0.0299998334828862);
    processed_bin_data[46](0.0001196, 0.0289140173849604);
    processed_bin_data[47](0.0001407, 0.0266766252386026);
    processed_bin_data[48](0.0001583, 0.0251477644991419);
    processed_bin_data[49](0.0001713, 0.0241733890723475);
    processed_bin_data[50](0.0002074, 0.0219558665769678); 
    processed_bin_data[51](0.0002204, 0.0212983686738438);
    processed_bin_data[52](0.0002482, 0.0201022267268064); 
    processed_bin_data[53](0.00029, 0.0185860437584805);
    processed_bin_data[54](0.0003051, 0.0181310690527097);
    processed_bin_data[55](0.0003583, 0.0167311225849398);
    processed_bin_data[56](0.0003961, 0.0159059381272913); 
    processed_bin_data[57](0.0004531, 0.0148657830676279);
    processed_bin_data[58](0.0005042, 0.0141130460003191); 
    processed_bin_data[59](0.0005564, 0.0134337880053195);
    processed_bin_data[60](0.0006416, 0.0125076191852496);
    processed_bin_data[61](0.0007087, 0.0119029565592964);
    processed_bin_data[62](0.0007917, 0.0112612937033266);
    processed_bin_data[63](0.0008978, 0.0105772814072851);
    processed_bin_data[64](0.0010103, 0.00997436331267495); 
    processed_bin_data[65](0.0011244, 0.00946131878510711);
    processed_bin_data[66](0.0012881, 0.00884697787348323);
    processed_bin_data[67](0.0014093, 0.00845527134294251);
    processed_bin_data[68](0.0015922, 0.00796095251164792);
    processed_bin_data[69](0.0018143, 0.00745497555688942);
    processed_bin_data[70](0.002027, 0.0070602634140091);
    processed_bin_data[71](0.0022735, 0.00667114263269969);
    processed_bin_data[72](0.0024813, 0.00639326807591387);
    processed_bin_data[73](0.0027826, 0.00604484861854888);
    processed_bin_data[74](0.003089, 0.00573180007530197);
    processed_bin_data[75](0.0034842, 0.00541031635990328);
    processed_bin_data[76](0.0037705, 0.00520168767828047); 
    processed_bin_data[77](0.0041429, 0.00496505497332904);
    processed_bin_data[78](0.0045134, 0.00475561467823832); 
    processed_bin_data[79](0.0050182, 0.00451866733884127);
    processed_bin_data[80](0.0054884, 0.00432993620441133); 
    processed_bin_data[81](0.0059525, 0.00415922081504803);
    processed_bin_data[82](0.0065047, 0.00398733829100727); 
    processed_bin_data[83](0.0070047, 0.00384545867910522);
    processed_bin_data[84](0.0075904, 0.00369910992308427); 
    processed_bin_data[85](0.0081133, 0.0035825022334017);
    processed_bin_data[86](0.0086649, 0.00347503465706039); 
    processed_bin_data[87](0.0092251, 0.00336992941118938);
    processed_bin_data[88](0.0096766, 0.00329623394857652);
    processed_bin_data[89](0.0102283, 0.00321278686898568);
    processed_bin_data[90](0.0107383, 0.00313800766210992);
    processed_bin_data[91](0.0112077, 0.00307834267767074);
    processed_bin_data[92](0.011676, 0.00302135052775223); 
    processed_bin_data[93](0.0120815, 0.00297664970031684);
    processed_bin_data[94](0.0124791, 0.00292814578414031);
    processed_bin_data[95](0.012842, 0.0028934025923193);
    processed_bin_data[96](0.0131612, 0.00286263401653467); 
    processed_bin_data[97](0.0134046, 0.00283982170344991);
    processed_bin_data[98](0.0135732, 0.0028288519345876);
    processed_bin_data[99](0.0136645, 0.00282293977143004);
    processed_bin_data[100](0.0136248, 0.00282684121190991);
    processed_bin_data[101](0.0136515, 0.00282672493291369);
    processed_bin_data[102](0.0134048, 0.00285278120255906); 
    processed_bin_data[103](0.0130295, 0.00289549280639101);
    processed_bin_data[104](0.0126504, 0.00293559579396991);
    processed_bin_data[105](0.0121319, 0.00299733175008086);
    processed_bin_data[106](0.0116504, 0.00305485330683318);
    processed_bin_data[107](0.0109842, 0.00314061742838905);
    processed_bin_data[108](0.0103919, 0.00322148195355378);
    processed_bin_data[109](0.0096296, 0.00333876841663956);
    processed_bin_data[110](0.0088231, 0.00347413670064323); 
    processed_bin_data[111](0.0079091, 0.00365481628851762);
    processed_bin_data[112](0.0071451, 0.00383312204966238); 
    processed_bin_data[113](0.0064149, 0.0040353226724687);
    processed_bin_data[114](0.0057425, 0.00424742281523246); 
    processed_bin_data[115](0.0049353, 0.00456702040843028);
    processed_bin_data[116](0.0042209, 0.00492266459539348);
    processed_bin_data[117](0.0039303, 0.00508093752743926);
    processed_bin_data[118](0.0034957, 0.00537687937434838); 
    processed_bin_data[119](0.0026957, 0.00611200948582397);
    processed_bin_data[120](0.0033848, 0.00543987367829484); 
    processed_bin_data[121](0.0031655, 0.00561751294645283);
    processed_bin_data[122](0.0024166, 0.00642898297776987); 
    processed_bin_data[123](0.8637804, 0.000125580067272171);

    Teuchos::Array<Utility::Quad<double,double,double,double> >
      raw_total_data( 1 ), raw_total_data_result;
    raw_total_data[0](13024850, 25888450, 87211652, 418111270);

    Teuchos::Array<Utility::Quad<double,double,double,double> >
      processed_total_data( 1 ), processed_total_data_result;
    processed_total_data[0]( 1.302485, 
			     0.00022935153672447, 
			     1.66956482175551e-06, 
			     151845.18598923 );

    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
	 "FacemcU235-293.6K.h5", 
	 MonteCarlo::EstimatorHDF5FileHandler::READ_ONLY_ESTIMATOR_HDF5_FILE );

    // Check the dimension ordering
    hdf5_file_handler.getEstimatorDimensionOrdering(
					       1u, dimension_ordering_result );

    TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
    TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

    // Check the energy bins
    hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
						      1u, energy_bins_result );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bins,
					  energy_bins_result,
					  1e-15 );

    // Check the raw entity bin data
    hdf5_file_handler.getRawEstimatorEntityBinData(
						 1u, 1u, raw_bin_data_result );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
					  raw_bin_data_result,
					  1e-15 );

    // Check the processed entity bin data
    hdf5_file_handler.getProcessedEstimatorEntityBinData(
				           1u, 1u, processed_bin_data_result );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
					  processed_bin_data_result,
					  1e-12 );

    // Check the raw total data
    hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_result );

    UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
					  raw_total_data_result,
					  1e-15 );

    // Check the processed total data (ignore fom)
    hdf5_file_handler.getProcessedEstimatorTotalData(
					     1u, processed_total_data_result );

    TEST_FLOATING_EQUALITY( processed_total_data[0].first,
			    processed_total_data_result[0].first,
			    1e-15 );
    TEST_FLOATING_EQUALITY( processed_total_data[0].second,
			    processed_total_data_result[0].second,
			    1e-15 );
    TEST_FLOATING_EQUALITY( processed_total_data[0].third,
			    processed_total_data[0].third,
			    1e-15 );
  }
  else // Bad return value
    success = false;

  if( success )
    out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    out << "\nEnd Result: TEST FAILED" << std::endl;

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstFacemcU235-293.6K.cpp
//---------------------------------------------------------------------------//

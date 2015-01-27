//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcWater-293.6K.cpp
//! \author Alex Robinson
//! \brief  facemc executable verification test for Water at 293.6K
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

    Teuchos::Array<double> energy_bins( 124 ),
      energy_bins_result;
    energy_bins[0] = 1e-11;
    energy_bins[1] = 1.2584e-11;
    energy_bins[2] = 1.5836e-11;
    energy_bins[3] = 1.9929e-11;
    energy_bins[4] = 2.5079e-11;
    energy_bins[5] = 3.156e-11;
    energy_bins[6] = 3.9716e-11;
    energy_bins[7] = 4.9979e-11;
    energy_bins[8] = 6.2895e-11;
    energy_bins[9] = 7.9149e-11;
    energy_bins[10] = 9.9603e-11;
    energy_bins[11] = 1.2534e-10;
    energy_bins[12] = 1.5773e-10;
    energy_bins[13] = 1.985e-10;
    energy_bins[14] = 2.4979e-10;
    energy_bins[15] = 3.1435e-10;
    energy_bins[16] = 3.9558e-10;
    energy_bins[17] = 4.9781e-10;
    energy_bins[18] = 6.2646e-10;
    energy_bins[19] = 7.8835e-10;
    energy_bins[20] = 9.9208e-10;
    energy_bins[21] = 1.2485e-09;
    energy_bins[22] = 1.5711e-09;
    energy_bins[23] = 1.9771e-09;
    energy_bins[24] = 2.488e-09;
    energy_bins[25] = 3.131e-09;
    energy_bins[26] = 3.9401e-09;
    energy_bins[27] = 4.9583e-09;
    energy_bins[28] = 6.2397e-09;
    energy_bins[29] = 7.8522e-09;
    energy_bins[30] = 9.8814e-09;
    energy_bins[31] = 1.2435e-08;
    energy_bins[32] = 1.5648e-08;
    energy_bins[33] = 1.9692e-08;
    energy_bins[34] = 2.4781e-08;
    energy_bins[35] = 3.1186e-08;
    energy_bins[36] = 3.9245e-08;
    energy_bins[37] = 4.9387e-08;
    energy_bins[38] = 6.2149e-08;
    energy_bins[39] = 7.821e-08;
    energy_bins[40] = 9.8422e-08;
    energy_bins[41] = 1.2386e-07;
    energy_bins[42] = 1.5586e-07;
    energy_bins[43] = 1.9614e-07;
    energy_bins[44] = 2.4683e-07;
    energy_bins[45] = 3.1062e-07;
    energy_bins[46] = 3.9089e-07;
    energy_bins[47] = 4.9191e-07;
    energy_bins[48] = 6.1903e-07;
    energy_bins[49] = 7.79e-07;
    energy_bins[50] = 9.8031e-07;
    energy_bins[51] = 1.2336e-06;
    energy_bins[52] = 1.5525e-06;
    energy_bins[53] = 1.9536e-06;
    energy_bins[54] = 2.4585e-06;
    energy_bins[55] = 3.0939e-06;
    energy_bins[56] = 3.8934e-06;
    energy_bins[57] = 4.8995e-06;
    energy_bins[58] = 6.1657e-06;
    energy_bins[59] = 7.7591e-06;
    energy_bins[60] = 9.7642e-06;
    energy_bins[61] = 1.2287e-05;
    energy_bins[62] = 1.5463e-05;
    energy_bins[63] = 1.9459e-05;
    energy_bins[64] = 2.4488e-05;
    energy_bins[65] = 3.0816e-05;
    energy_bins[66] = 3.8779e-05;
    energy_bins[67] = 4.8801e-05;
    energy_bins[68] = 6.1412e-05;
    energy_bins[69] = 7.7283e-05;
    energy_bins[70] = 9.7254e-05;
    energy_bins[71] = 0.00012239;
    energy_bins[72] = 0.00015402;
    energy_bins[73] = 0.00019382;
    energy_bins[74] = 0.0002439;
    energy_bins[75] = 0.00030693;
    energy_bins[76] = 0.00038625;
    energy_bins[77] = 0.00048607;
    energy_bins[78] = 0.00061168;
    energy_bins[79] = 0.00076976;
    energy_bins[80] = 0.00096868;
    energy_bins[81] = 0.001219;
    energy_bins[82] = 0.001534;
    energy_bins[83] = 0.0019305;
    energy_bins[84] = 0.0024294;
    energy_bins[85] = 0.0030572;
    energy_bins[86] = 0.0038472;
    energy_bins[87] = 0.0048414;
    energy_bins[88] = 0.0060926;
    energy_bins[89] = 0.007667;
    energy_bins[90] = 0.0096484;
    energy_bins[91] = 0.012142;
    energy_bins[92] = 0.015279;
    energy_bins[93] = 0.019228;
    energy_bins[94] = 0.024197;
    energy_bins[95] = 0.03045;
    energy_bins[96] = 0.038319;
    energy_bins[97] = 0.048222;
    energy_bins[98] = 0.060684;
    energy_bins[99] = 0.076366;
    energy_bins[100] = 0.096101;
    energy_bins[101] = 0.12094;
    energy_bins[102] = 0.15219;
    energy_bins[103] = 0.19152;
    energy_bins[104] = 0.24101;
    energy_bins[105] = 0.30329;
    energy_bins[106] = 0.38167;
    energy_bins[107] = 0.48031;
    energy_bins[108] = 0.60443;
    energy_bins[109] = 0.76063;
    energy_bins[110] = 0.95719;
    energy_bins[111] = 1.2046;
    energy_bins[112] = 1.5158;
    energy_bins[113] = 1.9076;
    energy_bins[114] = 2.4005;
    energy_bins[115] = 3.0209;
    energy_bins[116] = 3.8016;
    energy_bins[117] = 4.784;
    energy_bins[118] = 6.0203;
    energy_bins[119] = 7.5761;
    energy_bins[120] = 9.5339;
    energy_bins[121] = 11.998;
    energy_bins[122] = 15.098;
    energy_bins[123] = 19;

    Teuchos::Array<Utility::Pair<double,double> > raw_bin_data( 123 ),
      raw_bin_data_result;
    raw_bin_data[0](0, 0);
    raw_bin_data[1](0, 0);
    raw_bin_data[2](0, 0);
    raw_bin_data[3](0, 0);
    raw_bin_data[4](0, 0);
    raw_bin_data[5](0, 0);
    raw_bin_data[6](0, 0);
    raw_bin_data[7](0, 0);
    raw_bin_data[8](0, 0);
    raw_bin_data[9](0, 0);
    raw_bin_data[10](0, 0);
    raw_bin_data[11](0, 0);
    raw_bin_data[12](0, 0);
    raw_bin_data[13](0, 0);
    raw_bin_data[14](0, 0);
    raw_bin_data[15](0, 0);
    raw_bin_data[16](0, 0);
    raw_bin_data[17](0, 0);
    raw_bin_data[18](0, 0);
    raw_bin_data[19](0, 0);
    raw_bin_data[20](1, 1);
    raw_bin_data[21](2, 2);
    raw_bin_data[22](3, 3);
    raw_bin_data[23](2, 2);
    raw_bin_data[24](6, 6);
    raw_bin_data[25](9, 9);
    raw_bin_data[26](11, 11);
    raw_bin_data[27](32, 32);
    raw_bin_data[28](29, 29);
    raw_bin_data[29](52, 52);
    raw_bin_data[30](78, 78);
    raw_bin_data[31](115, 115);
    raw_bin_data[32](168, 168);
    raw_bin_data[33](215, 215);
    raw_bin_data[34](273, 273);
    raw_bin_data[35](370, 370);
    raw_bin_data[36](408, 408);
    raw_bin_data[37](482, 482);
    raw_bin_data[38](477, 477);
    raw_bin_data[39](450, 450);
    raw_bin_data[40](362, 362);
    raw_bin_data[41](289, 289);
    raw_bin_data[42](261, 261);
    raw_bin_data[43](192, 192);
    raw_bin_data[44](228, 228);
    raw_bin_data[45](212, 212);
    raw_bin_data[46](219, 219);
    raw_bin_data[47](221, 221);
    raw_bin_data[48](265, 265);
    raw_bin_data[49](246, 246);
    raw_bin_data[50](283, 283);
    raw_bin_data[51](291, 291);
    raw_bin_data[52](296, 296);
    raw_bin_data[53](292, 292);
    raw_bin_data[54](296, 296);
    raw_bin_data[55](321, 321);
    raw_bin_data[56](327, 327);
    raw_bin_data[57](335, 335);
    raw_bin_data[58](367, 367);
    raw_bin_data[59](378, 378);
    raw_bin_data[60](414, 414);
    raw_bin_data[61](396, 396);
    raw_bin_data[62](436, 436);
    raw_bin_data[63](435, 435);
    raw_bin_data[64](484, 484);
    raw_bin_data[65](485, 485);
    raw_bin_data[66](512, 512);
    raw_bin_data[67](550, 550);
    raw_bin_data[68](533, 533);
    raw_bin_data[69](625, 625);
    raw_bin_data[70](629, 629);
    raw_bin_data[71](656, 656);
    raw_bin_data[72](693, 693);
    raw_bin_data[73](723, 723);
    raw_bin_data[74](803, 803);
    raw_bin_data[75](760, 760);
    raw_bin_data[76](815, 815);
    raw_bin_data[77](816, 816);
    raw_bin_data[78](850, 850);
    raw_bin_data[79](936, 936);
    raw_bin_data[80](983, 983);
    raw_bin_data[81](1013, 1013);
    raw_bin_data[82](1040, 1040);
    raw_bin_data[83](1023, 1023);
    raw_bin_data[84](1151, 1151);
    raw_bin_data[85](1180, 1180);
    raw_bin_data[86](1280, 1280);
    raw_bin_data[87](1368, 1368);
    raw_bin_data[88](1387, 1387);
    raw_bin_data[89](1554, 1554);
    raw_bin_data[90](1654, 1654);
    raw_bin_data[91](1666, 1666);
    raw_bin_data[92](1776, 1778);
    raw_bin_data[93](1938, 1938);
    raw_bin_data[94](2083, 2083);
    raw_bin_data[95](2283, 2283);
    raw_bin_data[96](2643, 2645);
    raw_bin_data[97](2779, 2779);
    raw_bin_data[98](3081, 3081);
    raw_bin_data[99](3553, 3555);
    raw_bin_data[100](4040, 4042);
    raw_bin_data[101](4543, 4545);
    raw_bin_data[102](5275, 5279);
    raw_bin_data[103](6198, 6200);
    raw_bin_data[104](7465, 7465);
    raw_bin_data[105](8899, 8901);
    raw_bin_data[106](9492, 9492);
    raw_bin_data[107](12687, 12697);
    raw_bin_data[108](15826, 15842);
    raw_bin_data[109](19662, 19698);
    raw_bin_data[110](22121, 22159);
    raw_bin_data[111](29145, 29197);
    raw_bin_data[112](36768, 36800);
    raw_bin_data[113](46506, 46516);
    raw_bin_data[114](58566, 58566);
    raw_bin_data[115](68511, 68511);
    raw_bin_data[116](85715, 85715);
    raw_bin_data[117](107759, 107759);
    raw_bin_data[118](125109, 125109);
    raw_bin_data[119](129443, 129443);
    raw_bin_data[120](183228, 183228);
    raw_bin_data[121](164010, 164010);
    raw_bin_data[122](8679613, 8679613);

    Teuchos::Array<Utility::Pair<double,double> > processed_bin_data( 123 ),
      processed_bin_data_result;
    processed_bin_data[0](0, 0);
    processed_bin_data[1](0, 0);
    processed_bin_data[2](0, 0);
    processed_bin_data[3](0, 0);
    processed_bin_data[4](0, 0);
    processed_bin_data[5](0, 0);
    processed_bin_data[6](0, 0);
    processed_bin_data[7](0, 0);
    processed_bin_data[8](0, 0);
    processed_bin_data[9](0, 0);
    processed_bin_data[10](0, 0);
    processed_bin_data[11](0, 0);
    processed_bin_data[12](0, 0);
    processed_bin_data[13](0, 0);
    processed_bin_data[14](0, 0);
    processed_bin_data[15](0, 0);
    processed_bin_data[16](0, 0);
    processed_bin_data[17](0, 0);
    processed_bin_data[18](0, 0);
    processed_bin_data[19](0, 0);
    processed_bin_data[20](1e-07, 0.999999949999999);
    processed_bin_data[21](2e-07, 0.707106710475866);
    processed_bin_data[22](3e-07, 0.577350182587079);
    processed_bin_data[23](2e-07, 0.707106710475866);
    processed_bin_data[24](6e-07, 0.408248167989357);
    processed_bin_data[25](9e-07, 0.3333331833333);
    processed_bin_data[26](1.1e-06, 0.301511178746478);
    processed_bin_data[27](3.2e-06, 0.176776412453698);
    processed_bin_data[28](2.9e-06, 0.185695068918616);
    processed_bin_data[29](5.2e-06, 0.138674688500711);
    processed_bin_data[30](7.8e-06, 0.113227261825555);
    processed_bin_data[31](1.15e-05, 0.0932499446322251);
    processed_bin_data[32](1.68e-05, 0.0771510269042542);
    processed_bin_data[33](2.15e-05, 0.0681987007991917);
    processed_bin_data[34](2.73e-05, 0.0605219271256597);
    processed_bin_data[35](3.7e-05, 0.051986562712904);
    processed_bin_data[36](4.08e-05, 0.0495063671880382);
    processed_bin_data[37](4.82e-05, 0.0455476541292798);
    processed_bin_data[38](4.77e-05, 0.045785762620057);
    processed_bin_data[39](4.5e-05, 0.0471393914069987);
    processed_bin_data[40](3.62e-05, 0.0525578817992746);
    processed_bin_data[41](2.89e-05, 0.0588226794056234);
    processed_bin_data[42](2.61e-05, 0.0618976382790254);
    processed_bin_data[43](1.92e-05, 0.0721680908250546);
    processed_bin_data[44](2.28e-05, 0.0662258628655052);
    processed_bin_data[45](2.12e-05, 0.0686795539594971);
    processed_bin_data[46](2.19e-05, 0.0675729979034681);
    processed_bin_data[47](2.21e-05, 0.0672665360920871);
    processed_bin_data[48](2.65e-05, 0.0614286977369729);
    processed_bin_data[49](2.46e-05, 0.0637568870821538);
    processed_bin_data[50](2.83e-05, 0.0594429886916333);
    processed_bin_data[51](2.91e-05, 0.0586201852337443);
    processed_bin_data[52](2.96e-05, 0.0581229591330171);
    processed_bin_data[53](2.92e-05, 0.0585197191914535);
    processed_bin_data[54](2.96e-05, 0.0581229591330171);
    processed_bin_data[55](3.21e-05, 0.0558136613877623);
    processed_bin_data[56](3.27e-05, 0.0552992221964755);
    processed_bin_data[57](3.35e-05, 0.0546349213128899);
    processed_bin_data[58](3.67e-05, 0.0521986172261965);
    processed_bin_data[59](3.78e-05, 0.0514334778670726);
    processed_bin_data[60](4.14e-05, 0.0491463013582718);
    processed_bin_data[61](3.96e-05, 0.0502508957656729);
    processed_bin_data[62](4.36e-05, 0.0478902702190265);
    processed_bin_data[63](4.35e-05, 0.0479452873045166);
    processed_bin_data[64](4.84e-05, 0.0454534454412351);
    processed_bin_data[65](4.85e-05, 0.0454065597695211);
    processed_bin_data[66](5.12e-05, 0.0441930424388274);
    processed_bin_data[67](5.5e-05, 0.0426389706510584);
    processed_bin_data[68](5.33e-05, 0.0433136538274009);
    processed_bin_data[69](6.25e-05, 0.0399987499804681);
    processed_bin_data[70](6.29e-05, 0.0398713571281049);
    processed_bin_data[71](6.56e-05, 0.0390421598263011);
    processed_bin_data[72](6.93e-05, 0.0379855425524165);
    processed_bin_data[73](7.23e-05, 0.0371890557080126);
    processed_bin_data[74](8.03e-05, 0.0352878167708531);
    processed_bin_data[75](7.6e-05, 0.0362724340744347);
    processed_bin_data[76](8.15e-05, 0.0350270447658759);
    processed_bin_data[77](8.16e-05, 0.0350055737858763);
    processed_bin_data[78](8.5e-05, 0.0342982592595498);
    processed_bin_data[79](9.36e-05, 0.0326844927813798);
    processed_bin_data[80](9.83e-05, 0.0318934789254075);
    processed_bin_data[81](0.0001013, 0.0314176197569846);
    processed_bin_data[82](0.000104, 0.0310070711538265);
    processed_bin_data[83](0.0001023, 0.0312636707145748);
    processed_bin_data[84](0.0001151, 0.0294738821784471);
    processed_bin_data[85](0.000118, 0.0291094078799045);
    processed_bin_data[86](0.000128, 0.0279490608071184);
    processed_bin_data[87](0.0001368, 0.0270350541343417);
    processed_bin_data[88](0.0001387, 0.0268492184900342);
    processed_bin_data[89](0.0001554, 0.0253653433546767);
    processed_bin_data[90](0.0001654, 0.0245864784262135);
    processed_bin_data[91](0.0001666, 0.0244977569593303);
    processed_bin_data[92](0.0001776, 0.0237402009909149);
    processed_bin_data[93](0.0001938, 0.0227133412784871);
    processed_bin_data[94](0.0002083, 0.0219083731091555);
    processed_bin_data[95](0.0002283, 0.0209265417335701);
    processed_bin_data[96](0.0002643, 0.0194562133016628);
    processed_bin_data[97](0.0002779, 0.0189668571372631);
    processed_bin_data[98](0.0003081, 0.0180130492927519);
    processed_bin_data[99](0.0003553, 0.0167782813370025);
    processed_bin_data[100](0.000404, 0.0157336356091472);
    processed_bin_data[101](0.0004543, 0.0148362990268935);
    processed_bin_data[102](0.0005275, 0.0137701565750776);
    processed_bin_data[103](0.0006198, 0.0127001744565073);
    processed_bin_data[104](0.0007465, 0.0115697222470295);
    processed_bin_data[105](0.0008899, 0.0105970482522838);
    processed_bin_data[106](0.0009492, 0.0102592336586794);
    processed_bin_data[107](0.0012687, 0.00887597698727879);
    processed_bin_data[108](0.0015826, 0.00794676300419114);
    processed_bin_data[109](0.0019662, 0.00713110418371772);
    processed_bin_data[110](0.0022121, 0.0067218724152463);
    processed_bin_data[111](0.0029145, 0.00585426511665805);
    processed_bin_data[112](0.0036768, 0.00520780507856986);
    processed_bin_data[113](0.0046506, 0.00462679429342473);
    processed_bin_data[114](0.0058566, 0.00412004287232733);
    processed_bin_data[115](0.0068511, 0.00380738706086761);
    processed_bin_data[116](0.0085715, 0.00340096595767359); 
    processed_bin_data[117](0.0107759, 0.00302984609089554);
    processed_bin_data[118](0.0125109, 0.0028094536973889);
    processed_bin_data[119](0.0129443, 0.00276141414762122);
    processed_bin_data[120](0.0183228, 0.00231466652899225);
    processed_bin_data[121](0.016401, 0.00244891592256262);
    processed_bin_data[122](0.8679613, 0.000123339004580268);

    Teuchos::Array<Utility::Quad<double,double,double,double> >
      raw_total_data( 1 ), raw_total_data_result;
    raw_total_data[0]( 9887431, 9890059, 9895315, 9905827 );

    Teuchos::Array<Utility::Quad<double,double,double,double> >
      processed_total_data( 1 ), processed_total_data_result;
    processed_total_data[0]( 0.9887431, 
			     3.41377775187904e-05, 
			     8.39116752915233e-06, 
			     5751194.92569135 );

    MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler(
	 "FacemcWater-293.6K.h5",
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

    // Check the processed entity bin data
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
			    processed_total_data_result[0].third,
			    1e-15 );    
  }
  else // bad return value
    success = false;

  if( success )
    out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    out << "\nEnd Result: TEST FAILED" << std::endl;

  return (success ? 0 : 1 );
}

//---------------------------------------------------------------------------//
// end tstFacemcWater-293.6K.cpp
//---------------------------------------------------------------------------//

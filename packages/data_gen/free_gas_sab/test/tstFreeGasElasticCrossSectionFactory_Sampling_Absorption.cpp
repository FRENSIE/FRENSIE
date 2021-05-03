//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticCrossSectionFactory.cpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering generator tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>
#include <limits>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <array>
#include <cstdio>

// Boost Includes
#include <boost/unordered_map.hpp>


// FRENSIE Includes
#include <Utility_UnitTestHarnessWithMain.hpp>
#include "DataGen_FreeGasElasticCrossSectionFactory.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_UniformDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_neutron_ace_file_name = "/home/ecmoll/software/frensie/FRENSIE/packages/test_files/ace/test_h1_ace_file.txt";
std::string table_name = "1001.70c";
std::shared_ptr<DataGen::FreeGasElasticCrossSectionFactory> free_gas_factory;
std::vector<double> kT_vector{ 2.5301e-8, 5.1704e-8, 7.556e-8, 1.03408e-7, 2.15433e-7};
int num_particles = 1e6;
int num_scatters  = 50;
std::vector<double> abs_e{1E-11,1.03125E-11,1.0625E-11,1.09375E-11,1.125E-11,1.15625E-11,1.1875E-11,1.21875E-11,1.25E-11,1.28125E-11,1.3125E-11,1.34375E-11,1.375E-11,1.4375E-11,1.5E-11,1.5625E-11,1.625E-11,1.6875E-11,1.75E-11,1.8125E-11,1.875E-11,1.9375E-11,2E-11,2.09375E-11,2.1875E-11,2.28125E-11,2.375E-11,2.46875E-11,2.5625E-11,2.65625E-11,2.75E-11,2.84375E-11,2.9375E-11,3.03125E-11,3.125E-11,3.21875E-11,3.3125E-11,3.40625E-11,3.5E-11,3.59375E-11,3.6875E-11,3.78125E-11,3.875E-11,3.96875E-11,4.0625E-11,4.25E-11,4.4375E-11,4.625E-11,4.8125E-11,5E-11,5.15625E-11,5.3125E-11,5.46875E-11,5.625E-11,5.78125E-11,5.9375E-11,6.09375E-11,6.25E-11,6.40625E-11,6.5625E-11,6.71875E-11,6.875E-11,7.1875E-11,7.5E-11,7.8125E-11,8.125E-11,8.4375E-11,8.75E-11,9.0625E-11,9.375E-11,9.6875E-11,1E-10,1.03125E-10,1.0625E-10,1.09375E-10,1.125E-10,1.15625E-10,1.1875E-10,1.21875E-10,1.25E-10,1.28125E-10,1.3125E-10,1.34375E-10,1.375E-10,1.4375E-10,1.5E-10,1.5625E-10,1.625E-10,1.6875E-10,1.75E-10,1.8125E-10,1.875E-10,1.9375E-10,2E-10,2.09375E-10,2.1875E-10,2.28125E-10,2.375E-10,2.46875E-10,2.5625E-10,2.65625E-10,2.75E-10,2.84375E-10,2.9375E-10,3.03125E-10,3.125E-10,3.21875E-10,3.3125E-10,3.40625E-10,3.5E-10,3.59375E-10,3.6875E-10,3.78125E-10,3.875E-10,3.96875E-10,4.0625E-10,4.25E-10,4.4375E-10,4.625E-10,4.8125E-10,5E-10,5.15625E-10,5.3125E-10,5.46875E-10,5.625E-10,5.78125E-10,5.9375E-10,6.09375E-10,6.25E-10,6.40625E-10,6.5625E-10,6.71875E-10,6.875E-10,7.1875E-10,7.5E-10,7.8125E-10,8.125E-10,8.4375E-10,8.75E-10,9.0625E-10,9.375E-10,9.6875E-10,1E-09,1.03125E-09,1.0625E-09,1.09375E-09,1.125E-09,1.15625E-09,1.1875E-09,1.21875E-09,1.25E-09,1.28125E-09,1.3125E-09,1.34375E-09,1.375E-09,1.4375E-09,1.5E-09,1.5625E-09,1.625E-09,1.6875E-09,1.75E-09,1.8125E-09,1.875E-09,1.9375E-09,2E-09,2.09375E-09,2.1875E-09,2.28125E-09,2.375E-09,2.46875E-09,2.5625E-09,2.65625E-09,2.75E-09,2.84375E-09,2.9375E-09,3.03125E-09,3.125E-09,3.21875E-09,3.3125E-09,3.40625E-09,3.5E-09,3.59375E-09,3.6875E-09,3.78125E-09,3.875E-09,3.96875E-09,4.0625E-09,4.25E-09,4.4375E-09,4.625E-09,4.8125E-09,5E-09,5.15625E-09,5.3125E-09,5.46875E-09,5.625E-09,5.78125E-09,5.9375E-09,6.09375E-09,6.25E-09,6.40625E-09,6.5625E-09,6.71875E-09,6.875E-09,7.1875E-09,7.5E-09,7.8125E-09,8.125E-09,8.4375E-09,8.75E-09,9.0625E-09,9.375E-09,9.6875E-09,1E-08,1.03125E-08,1.0625E-08,1.09375E-08,1.125E-08,1.15625E-08,1.1875E-08,1.21875E-08,1.25E-08,1.28125E-08,1.3125E-08,1.34375E-08,1.375E-08,1.4375E-08,1.5E-08,1.5625E-08,1.625E-08,1.6875E-08,1.75E-08,1.8125E-08,1.875E-08,1.9375E-08,2E-08,2.06625E-08,2.1325E-08,2.19875E-08,2.265E-08,2.33125E-08,2.3975E-08,2.46375E-08,2.53E-08,2.645782E-08,2.761563E-08,2.877344E-08,2.993125E-08,3.108907E-08,3.224688E-08,3.340469E-08,3.45625E-08,3.552735E-08,3.649219E-08,3.745704E-08,3.842188E-08,3.938673E-08,4.035157E-08,4.131641E-08,4.228125E-08,4.421094E-08,4.614063E-08,4.807032E-08,5E-08,5.15625E-08,5.3125E-08,5.46875E-08,5.625E-08,5.78125E-08,5.9375E-08,6.09375E-08,6.25E-08,6.40625E-08,6.5625E-08,6.71875E-08,6.875E-08,7.1875E-08,7.5E-08,7.8125E-08,8.125E-08,8.4375E-08,8.75E-08,9.0625E-08,9.375E-08,9.6875E-08,1E-07,1.03125E-07,1.0625E-07,1.09375E-07,1.125E-07,1.15625E-07,1.1875E-07,1.21875E-07,1.25E-07,1.28125E-07,1.3125E-07,1.34375E-07,1.375E-07,1.4375E-07,1.5E-07,1.5625E-07,1.625E-07,1.6875E-07,1.75E-07,1.8125E-07,1.875E-07,1.9375E-07,2E-07,2.09375E-07,2.1875E-07,2.28125E-07,2.375E-07,2.46875E-07,2.5625E-07,2.65625E-07,2.75E-07,2.84375E-07,2.9375E-07,3.03125E-07,3.125E-07,3.21875E-07,3.3125E-07,3.40625E-07,3.5E-07,3.59375E-07,3.6875E-07,3.78125E-07,3.875E-07,3.96875E-07,4.0625E-07,4.25E-07,4.4375E-07,4.625E-07,5E-07,5.3125E-07,5.625E-07,5.9375E-07,6.25E-07,6.875E-07,7.5E-07,8.125E-07,8.75E-07,9.375E-07,1E-06,1.0625E-06,1.125E-06,1.1875E-06,1.25E-06,1.375E-06,1.5E-06,1.625E-06,1.75E-06,1.875E-06,2E-06,2.1875E-06,2.375E-06,2.5625E-06,2.75E-06,2.9375E-06,3.125E-06,3.3125E-06,3.5E-06,3.875E-06,4.25E-06,4.625E-06,5E-06};
std::vector<double> abs_xs{16.72987,16.47443,16.23035,15.99681,15.77307,15.55846,15.35238,15.15427,14.96365,14.78004,14.60302,14.43222,14.26728,13.95367,13.65988,13.38389,13.12398,12.87865,12.64659,12.42663,12.21776,12.01909,11.8298,11.56192,11.31145,11.07659,10.85577,10.64765,10.45106,10.26497,10.08849,9.920798,9.761203,9.609071,9.463838,9.324996,9.192092,9.064712,8.942486,8.825074,8.712169,8.603489,8.498777,8.397798,8.300334,8.115173,7.941878,7.779228,7.626179,7.481822,7.367589,7.258433,7.15399,7.053929,6.957952,6.86579,6.777195,6.691944,6.609831,6.530669,6.454284,6.380518,6.24027,6.108881,5.985457,5.869223,5.759508,5.655725,5.557357,5.463949,5.375098,5.290446,5.209671,5.132486,5.058634,4.98788,4.920015,4.854846,4.7922,4.731918,4.673856,4.617879,4.563867,4.511707,4.412537,4.319631,4.232356,4.150167,4.072587,3.999201,3.929644,3.863595,3.800768,3.74091,3.656199,3.576994,3.502723,3.432895,3.367082,3.304916,3.24607,3.190259,3.137232,3.086764,3.038655,2.992728,2.948823,2.906795,2.866514,2.827862,2.790733,2.75503,2.720662,2.687549,2.655617,2.624796,2.566243,2.511442,2.460007,2.411609,2.365959,2.329836,2.295318,2.26229,2.230648,2.200297,2.171153,2.143137,2.116178,2.090212,2.065179,2.041024,2.017697,1.973346,1.931798,1.892767,1.856011,1.821316,1.788497,1.757391,1.727852,1.699755,1.672986,1.647443,1.623035,1.59968,1.577306,1.555845,1.535237,1.515427,1.496364,1.478003,1.460302,1.443222,1.426727,1.395367,1.365987,1.338389,1.312398,1.287865,1.264658,1.242663,1.221776,1.201909,1.18298,1.156192,1.131145,1.107658,1.085577,1.064765,1.045106,1.026497,1.008848,0.9920797,0.9761203,0.9609071,0.9463837,0.9324996,0.9192091,0.9064712,0.8942486,0.8825074,0.8712168,0.8603488,0.8498777,0.8397798,0.8300334,0.8115173,0.7941876,0.7779226,0.7626177,0.7481821,0.7367588,0.7258432,0.7153989,0.7053928,0.6957952,0.6865789,0.6777195,0.6691944,0.6609831,0.6530668,0.6454284,0.6380518,0.624027,0.6108881,0.5985456,0.5869223,0.5759508,0.5655725,0.5557357,0.5463949,0.5375099,0.5290446,0.5209671,0.5132487,0.5058634,0.4987881,0.4920015,0.4854847,0.4792201,0.4731919,0.4673857,0.461788,0.4563868,0.4511708,0.4412538,0.4319632,0.4232358,0.4150168,0.4072588,0.3999202,0.3929646,0.3863596,0.380077,0.3740911,0.3680451,0.362283,0.3567833,0.3515267,0.3464958,0.341675,0.3370499,0.3326076,0.3252486,0.3183575,0.3118866,0.3057948,0.3000466,0.2946109,0.2894602,0.2845706,0.2806799,0.2769445,0.2733544,0.2699003,0.266574,0.2633677,0.2602744,0.2572876,0.2516101,0.2462925,0.2412984,0.2365963,0.232984,0.2295322,0.2262294,0.2230653,0.2200302,0.2171158,0.2143142,0.2116184,0.2090218,0.2065184,0.204103,0.2017703,0.1973353,0.1931804,0.1892774,0.1856018,0.1821324,0.1788505,0.1757399,0.1727861,0.1699764,0.1672995,0.1647452,0.1623044,0.159969,0.1577316,0.1555855,0.1535247,0.1515437,0.1496374,0.1478013,0.1460312,0.1443232,0.1426738,0.1395377,0.1365998,0.1338399,0.1312409,0.1287876,0.1264669,0.1242674,0.1221787,0.1201919,0.118299,0.1156203,0.1131156,0.1107669,0.1085588,0.1064777,0.1045118,0.102651,0.1008862,0.09920939,0.09761353,0.09609231,0.09464008,0.09325178,0.09192286,0.0906492,0.08942707,0.08825308,0.08712417,0.08603751,0.08499054,0.08398089,0.08300639,0.08115506,0.07942233,0.07779607,0.0748224,0.07258876,0.07054392,0.06866268,0.06692435,0.06381031,0.06109416,0.05869779,0.05656294,0.0546452,0.05291001,0.05133011,0.04988364,0.04855284,0.04732312,0.04512035,0.04319935,0.04150477,0.03999519,0.03863902,0.03741184,0.03577205,0.03433075,0.03305116,0.03190509,0.03087053,0.02993024,0.02907066,0.02828091,0.02687687,0.02566326,0.02460091,0.02366085};
std::vector<double> abs_e_t(abs_e);
std::vector<double> abs_xs_t(abs_xs);

std::vector<double> scat_e{1E-11,1.03125E-11,1.0625E-11,1.09375E-11,1.125E-11,1.15625E-11,1.1875E-11,1.21875E-11,1.25E-11,1.28125E-11,1.3125E-11,1.34375E-11,1.375E-11,1.4375E-11,1.5E-11,1.5625E-11,1.625E-11,1.6875E-11,1.75E-11,1.8125E-11,1.875E-11,1.9375E-11,2E-11,2.09375E-11,2.1875E-11,2.28125E-11,2.375E-11,2.46875E-11,2.5625E-11,2.65625E-11,2.75E-11,2.84375E-11,2.9375E-11,3.03125E-11,3.125E-11,3.21875E-11,3.3125E-11,3.40625E-11,3.5E-11,3.59375E-11,3.6875E-11,3.78125E-11,3.875E-11,3.96875E-11,4.0625E-11,4.25E-11,4.4375E-11,4.625E-11,4.8125E-11,5E-11,5.15625E-11,5.3125E-11,5.46875E-11,5.625E-11,5.78125E-11,5.9375E-11,6.09375E-11,6.25E-11,6.40625E-11,6.5625E-11,6.71875E-11,6.875E-11,7.1875E-11,7.5E-11,7.8125E-11,8.125E-11,8.4375E-11,8.75E-11,9.0625E-11,9.375E-11,9.6875E-11,1E-10,1.03125E-10,1.0625E-10,1.09375E-10,1.125E-10,1.15625E-10,1.1875E-10,1.21875E-10,1.25E-10,1.28125E-10,1.3125E-10,1.34375E-10,1.375E-10,1.4375E-10,1.5E-10,1.5625E-10,1.625E-10,1.6875E-10,1.75E-10,1.8125E-10,1.875E-10,1.9375E-10,2E-10,2.09375E-10,2.1875E-10,2.28125E-10,2.375E-10,2.46875E-10,2.5625E-10,2.65625E-10,2.75E-10,2.84375E-10,2.9375E-10,3.03125E-10,3.125E-10,3.21875E-10,3.3125E-10,3.40625E-10,3.5E-10,3.59375E-10,3.6875E-10,3.78125E-10,3.875E-10,3.96875E-10,4.0625E-10,4.25E-10,4.4375E-10,4.625E-10,4.8125E-10,5E-10,5.15625E-10,5.3125E-10,5.46875E-10,5.625E-10,5.78125E-10,5.9375E-10,6.09375E-10,6.25E-10,6.40625E-10,6.5625E-10,6.71875E-10,6.875E-10,7.1875E-10,7.5E-10,7.8125E-10,8.125E-10,8.4375E-10,8.75E-10,9.0625E-10,9.375E-10,9.6875E-10,1E-09,1.03125E-09,1.0625E-09,1.09375E-09,1.125E-09,1.15625E-09,1.1875E-09,1.21875E-09,1.25E-09,1.28125E-09,1.3125E-09,1.34375E-09,1.375E-09,1.4375E-09,1.5E-09,1.5625E-09,1.625E-09,1.6875E-09,1.75E-09,1.8125E-09,1.875E-09,1.9375E-09,2E-09,2.09375E-09,2.1875E-09,2.28125E-09,2.375E-09,2.46875E-09,2.5625E-09,2.65625E-09,2.75E-09,2.84375E-09,2.9375E-09,3.03125E-09,3.125E-09,3.21875E-09,3.3125E-09,3.40625E-09,3.5E-09,3.59375E-09,3.6875E-09,3.78125E-09,3.875E-09,3.96875E-09,4.0625E-09,4.25E-09,4.4375E-09,4.625E-09,4.8125E-09,5E-09,5.15625E-09,5.3125E-09,5.46875E-09,5.625E-09,5.78125E-09,5.9375E-09,6.09375E-09,6.25E-09,6.40625E-09,6.5625E-09,6.71875E-09,6.875E-09,7.1875E-09,7.5E-09,7.8125E-09,8.125E-09,8.4375E-09,8.75E-09,9.0625E-09,9.375E-09,9.6875E-09,1E-08,1.03125E-08,1.0625E-08,1.09375E-08,1.125E-08,1.15625E-08,1.1875E-08,1.21875E-08,1.25E-08,1.28125E-08,1.3125E-08,1.34375E-08,1.375E-08,1.4375E-08,1.5E-08,1.5625E-08,1.625E-08,1.6875E-08,1.75E-08,1.8125E-08,1.875E-08,1.9375E-08,2E-08,2.06625E-08,2.1325E-08,2.19875E-08,2.265E-08,2.33125E-08,2.3975E-08,2.46375E-08,2.53E-08,2.64578E-08,2.76156E-08,2.87734E-08,2.99312E-08,3.10891E-08,3.22469E-08,3.34047E-08,3.45625E-08,3.55273E-08,3.64922E-08,3.7457E-08,3.84219E-08,3.93867E-08,4.03516E-08,4.13164E-08,4.22813E-08,4.42109E-08,4.61406E-08,4.80703E-08,5E-08,5.15625E-08,5.3125E-08,5.46875E-08,5.625E-08,5.78125E-08,5.9375E-08,6.09375E-08,6.25E-08,6.40625E-08,6.5625E-08,6.71875E-08,6.875E-08,7.1875E-08,7.5E-08,7.8125E-08,8.125E-08,8.4375E-08,8.75E-08,9.0625E-08,9.375E-08,9.6875E-08,1E-07,1.03125E-07,1.0625E-07,1.09375E-07,1.125E-07,1.15625E-07,1.1875E-07,1.21875E-07,1.25E-07,1.28125E-07,1.3125E-07,1.34375E-07,1.375E-07,1.4375E-07,1.5E-07,1.5625E-07,1.625E-07,1.6875E-07,1.75E-07,1.8125E-07,1.875E-07,1.9375E-07,2E-07,2.09375E-07,2.1875E-07,2.28125E-07,2.375E-07,2.46875E-07,2.5625E-07,2.65625E-07,2.75E-07,2.84375E-07,2.9375E-07,3.03125E-07,3.125E-07,3.21875E-07,3.3125E-07,3.40625E-07,3.5E-07,3.59375E-07,3.6875E-07,3.78125E-07,3.875E-07,3.96875E-07,4.0625E-07,4.25E-07,4.4375E-07,4.625E-07,5E-07,5.3125E-07,5.625E-07,5.9375E-07,6.25E-07,6.875E-07,7.5E-07,8.125E-07,8.75E-07,9.375E-07,1E-06,1.0625E-06,1.125E-06,1.1875E-06,1.25E-06,1.375E-06,1.5E-06,1.625E-06,1.75E-06,1.875E-06,2E-06,2.1875E-06,2.375E-06,2.5625E-06,2.75E-06,2.9375E-06,3.125E-06,3.3125E-06,3.5E-06,3.875E-06,4.25E-06,4.625E-06,5E-06};
std::vector<double> scat_xs{1160.18,1142.48,1125.56,1109.37,1093.86,1078.99,1064.71,1050.97,1037.76,1025.03,1012.77,1000.93,989.494,967.757,947.393,928.263,910.248,893.244,877.158,861.912,847.435,833.664,820.544,801.976,784.616,768.337,753.031,738.607,724.981,712.083,699.85,688.228,677.167,666.623,656.557,646.934,637.723,628.895,620.424,612.286,604.461,596.929,589.673,582.674,575.92,563.088,551.079,539.807,529.201,519.198,511.282,503.719,496.481,489.548,482.898,476.512,470.374,464.467,458.778,453.293,448.001,442.89,433.174,424.072,415.522,407.47,399.87,392.682,385.868,379.399,373.245,367.382,361.789,356.443,351.329,346.43,341.731,337.219,332.881,328.708,324.688,320.813,317.073,313.463,306.598,300.168,294.128,288.44,283.072,277.994,273.182,268.613,264.266,260.126,254.267,248.79,243.654,238.827,234.277,229.98,225.913,222.056,218.392,214.906,211.582,208.41,205.378,202.476,199.694,197.026,194.463,191.999,189.627,187.342,185.139,183.013,178.974,175.195,171.649,168.314,165.168,162.679,160.302,158.027,155.849,153.76,151.754,149.826,147.972,146.186,144.464,142.803,141.2,138.153,135.299,132.619,130.096,127.716,125.465,123.333,121.309,119.385,117.552,115.804,114.134,112.537,111.008,109.541,108.134,106.781,105.48,104.228,103.021,101.856,100.733,98.5975,96.5987,94.7225,92.957,91.2919,89.7181,88.2276,86.8135,85.4694,84.1898,82.3808,80.6914,79.1092,77.6234,76.2247,74.9051,73.6575,72.4756,71.3541,70.2879,69.2728,68.3049,67.3807,66.4971,65.6512,64.8405,64.0627,63.3156,62.5973,61.906,61.2402,60.5984,59.3811,58.2445,57.1802,56.1812,55.241,54.4987,53.7907,53.1146,52.4681,51.8492,51.2561,50.687,50.1405,49.6151,49.1095,48.6209,48.1533,47.2636,46.4332,45.6562,44.9272,44.2416,43.5956,42.9855,42.4084,41.8615,41.3423,40.8488,40.3789,39.931,39.5034,39.0948,38.7038,38.3293,37.9703,37.6257,37.2947,36.9765,36.6702,36.091,35.5522,35.0496,34.5796,34.139,33.725,33.3354,32.9678,32.6206,32.2919,31.9622,31.6502,31.3545,31.0737,30.8069,30.5529,30.3109,30.0799,29.7009,29.3499,29.0241,28.7207,28.4377,28.1729,27.9247,27.6915,27.5078,27.3329,27.1662,27.0072,26.8554,26.7103,26.5714,26.4384,26.1886,25.9583,25.7453,25.5478,25.3981,25.2567,25.123,24.9964,24.8762,24.7622,24.6537,24.5505,24.4521,24.3582,24.2685,24.1828,24.0222,23.8746,23.7386,23.6127,23.496,23.3875,23.2864,23.1919,23.1034,23.0204,22.9423,22.8689,22.7995,22.734,22.6721,22.6133,22.5575,22.5045,22.4541,22.4061,22.3603,22.3166,22.2349,22.1599,22.091,22.0273,21.9684,21.9136,21.8627,21.8151,21.7706,21.7288,21.6709,21.618,21.5694,21.5246,21.4832,21.4449,21.4092,21.376,21.345,21.316,21.2887,21.2631,21.239,21.2163,21.1948,21.1744,21.1551,21.1368,21.1194,21.1029,21.0871,21.0726,21.044,21.0182,20.9946,20.9526,20.9222,20.8951,20.8709,20.8491,20.8115,20.7801,20.7536,20.7308,20.7111,20.6938,20.6786,20.6651,20.653,20.6421,20.6232,20.6075,20.5942,20.5829,20.573,20.5643,20.5532,20.5439,20.5359,20.529,20.5229,20.5176,20.5129,20.5087,20.5015,20.4956,20.4906,20.3829};
std::vector<double> scat_e_t(scat_e);
std::vector<double> scat_xs_t(scat_xs);

std::shared_ptr<Utility::UnivariateDistribution> absorption_cross_section;
std::shared_ptr<Utility::UnivariateDistribution> scattering_cross_section;

//---------------------------------------------------------------------------//
// Check that the energy grid can be returned
FRENSIE_UNIT_TEST( FreeGasElasticCrossSectionFactory,
		   tstSampling293K )
{
  double kT            = kT_vector[0];
  std::string filename = "/home/ecmoll/software/frensie/test_data/forward_transport/H_293K.transport";

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
                            table_name,
                            1u ) );

  free_gas_factory->serializeMapIn( filename );

  std::shared_ptr<MonteCarlo::AceLaw4NuclearScatteringEnergyDistribution> distribution;

  free_gas_factory->getEnergyDistribution( distribution );

  absorption_cross_section.reset(
    new Utility::TabularDistribution<Utility::LogLog>( 
      abs_e_t,
      abs_xs_t ) );

  scattering_cross_section.reset(
    new Utility::TabularDistribution<Utility::LogLog>( 
      scat_e_t,
      scat_xs_t ) );

  double initial_e  = 2.53010e-8;

  std::map< int, std::vector<double> > population;

  std::vector<double> no_scatters;
  for(int i = 0; i < num_particles; ++i )
  {
      no_scatters.push_back( initial_e );
  }

  population[ 0 ] = no_scatters;

  for( int i = 1; i <= num_scatters; ++i )
  {
    std::vector<double> collision_bin;

    for( int j = 0; j < num_particles; ++j )
    {
      if( population[i-1][j] != 0 )
      {
        double temp_e = distribution->sampleEnergy( population[i-1][j] );
        double kill_value = absorption_cross_section->evaluate( population[i-1][j] )/scattering_cross_section->evaluate( population[i-1][j] );
        double random_num = 
              Utility::RandomNumberGenerator::getRandomNumber<double>();

        if( random_num < kill_value )
        {
          collision_bin.push_back(0);
        }
        else
        {
          collision_bin.push_back( distribution->sampleEnergy( population[i-1][j] ) );
        }
      }
      else
      {
        collision_bin.push_back(0);
      }
    }

    population[ i ] = collision_bin;
  }

  std::array<int, 2> preamble = {num_scatters + 1, num_particles};

  std::ofstream file_out("/home/ecmoll/software/frensie/test_data/forward_transport/H_293K_absorption.output", std::ios::out | std::ios::binary );
  file_out.write((char*)&num_scatters,  sizeof( uint32_t ));
  file_out.write((char*)&num_particles, sizeof( uint32_t ));

  for( int i = 0; i <= num_scatters; ++i )
  {
    for( int j = 0; j < num_particles; ++j )
    {
      file_out.write((char*)&population[i][j], sizeof( double ));
    }
  }
  file_out.close();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

 ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_neutron_ace_file",
                                       test_neutron_ace_file_name,
                                       "",
                                       "Test neutron ACE file name" );
 
  std::string table_name( "1001.70c" );

  free_gas_factory.reset( new DataGen::FreeGasElasticCrossSectionFactory(
                            test_neutron_ace_file_name,
						    table_name,
						    1u ) ); 
}
FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//

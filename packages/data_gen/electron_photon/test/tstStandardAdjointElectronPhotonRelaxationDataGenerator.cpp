//---------------------------------------------------------------------------//
//!
//! \file   tstStandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard adjoint electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardAdjointElectronPhotonRelaxationDataGenerator : public DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator
{
public:

  TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy,
      std::ostream* os_log = &std::cout,
      std::ostream* os_warn = &std::cerr )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
        forward_epr_data,
        min_photon_energy,
        max_photon_energy,
        min_electron_energy,
        max_electron_energy,
        os_log,
        os_warn )
  { /* ... */ }

  TestStandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& forward_epr_data,
      std::ostream* os_log = &std::cout )
    : DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator(
        forward_epr_data,
        os_log )
  { /* ... */ }

  ~TestStandardAdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  // Allow public access to the AnalogElasticElectronScatteringDistribution protected member functions
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setTableData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointRelaxationData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setComptonProfileData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setOccupationNumberData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData;
  using DataGen::StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData;
};

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<TestStandardAdjointElectronPhotonRelaxationDataGenerator>
  data_generator_h, data_generator_c;

Data::AdjointElectronPhotonRelaxationVolatileDataContainer
    h_data_container, c_data_container;

std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer>
  h_epr_data_container, c_epr_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the table data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setTableData_h )
{
    data_generator_h.reset(
        new TestStandardAdjointElectronPhotonRelaxationDataGenerator(
            h_epr_data_container, 0.001, 20.0, 1.0e-5, 20.0 ) );

  data_generator_h->setAdjointBremsstrahlungCrossSectionEvaluationTolerance( 1e-3 );
  data_generator_h->setAdjointElectroionizationCrossSectionEvaluationTolerance( 1e-4 );
  data_generator_h->setAdjointElectronGridConvergenceTolerance( 1e-3 );
  data_generator_h->setAdjointElectronAbsoluteDifferenceTolerance( 1e-16 );
  data_generator_h->setAdjointElectronDistanceTolerance( 1e-8 );

  data_generator_h->setTableData( h_data_container );

  // Check the table settings data
  TEST_EQUALITY_CONST( h_data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( h_data_container.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( h_data_container.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( h_data_container.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( h_data_container.getMaxElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( h_data_container.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST( h_data_container.getNumberOfAdjointMomentPreservingAngles(), 1 );
  TEST_EQUALITY_CONST( h_data_container.getGridConvergenceTolerance(), 0.001 );
  TEST_EQUALITY_CONST(
    h_data_container.getGridAbsoluteDifferenceTolerance(), 1e-12 );
  TEST_EQUALITY_CONST( h_data_container.getGridDistanceTolerance(), 1e-14 );

  h_data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Check that the adjoint relaxation data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointRelaxationData_h )
{

  data_generator_h->setAdjointRelaxationData( h_data_container );

  // Check the relaxation data
  TEST_EQUALITY_CONST( h_data_container.getSubshells().size(), 1 );
  TEST_ASSERT( h_data_container.getSubshells().count( 1 ) );
  TEST_EQUALITY_CONST( h_data_container.getSubshellOccupancy( 1 ), 1 );
  TEST_EQUALITY_CONST( h_data_container.getSubshellBindingEnergy( 1 ),
		       1.361000000000E-05 );

  h_data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

////---------------------------------------------------------------------------//
//// Check that the adjoint photon data can be set
//TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
//                   setAdjointPhotonData_h )
//{

//  data_generator_h->setAdjointPhotonData( h_data_container );

//  // Check the photon data

//  h_data_container.exportData( "test_h_epr.xml",
//			     Utility::ArchivableObject::XML_ARCHIVE );
//}

//---------------------------------------------------------------------------//
// Check that the adjoint electron data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
                   setAdjointElectronData_h )
{
  data_generator_h->setAdjointElectronData( h_data_container );

  // Check the electron data
  TEST_EQUALITY_CONST( data_generator_h->getAdjointBremsstrahlungCrossSectionEvaluationTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( data_generator_h->getAdjointElectroionizationCrossSectionEvaluationTolerance(),
                       1e-4 );
  TEST_EQUALITY_CONST( data_generator_h->getAdjointElectronGridConvergenceTolerance(),
                       1e-3 );
  TEST_EQUALITY_CONST( data_generator_h->getAdjointElectronAbsoluteDifferenceTolerance(),
                       1e-16 );
  TEST_EQUALITY_CONST( data_generator_h->getAdjointElectronDistanceTolerance(),
                       1e-8 );

  std::vector<double> energy_grid = h_data_container.getAdjointElectronEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 20 );
  TEST_EQUALITY_CONST( energy_grid.size(), 848 );

   // Check the elastic data
   unsigned threshold =
     h_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   std::vector<double> cross_section =
     h_data_container.getAdjointCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.74896e+8 );
  TEST_FLOATING_EQUALITY( cross_section.back(), 304.72762372903747519, 1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 848-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   threshold =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  TEST_EQUALITY_CONST( threshold, 604 );

   cross_section =
     h_data_container.getAdjointScreenedRutherfordElasticCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 0.89606536249266355298 );
   TEST_EQUALITY_CONST( cross_section.back(), 12717.394891258003554 );
   TEST_EQUALITY_CONST( cross_section.size(), 848-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   std::vector<double> angular_grid =
     h_data_container.getAdjointElasticAngularEnergyGrid();

   TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
   TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
   TEST_EQUALITY_CONST( angular_grid.size(), 16 );

   std::vector<double> elastic_angles =
     h_data_container.getAdjointCutoffElasticAngles(1.0e-5);

   TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
   TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
   TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

   elastic_angles =
     h_data_container.getAdjointCutoffElasticAngles(1.0e+5);

   TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
   TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
   TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

   std::vector<double> elastic_pdf =
     h_data_container.getAdjointCutoffElasticPDF(1.0e-5);

   TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
   TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
   TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

   elastic_pdf =
     h_data_container.getAdjointCutoffElasticPDF(1.0e+5);

   TEST_EQUALITY_CONST( elastic_pdf.front(), 6.25670e-13 );
   TEST_EQUALITY_CONST( elastic_pdf.back(), 9.86945e+5 );
   TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

   TEST_ASSERT( h_data_container.hasAdjointMomentPreservingData() );

   std::vector<double> discrete_angles =
     h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1.0e-5 );

   TEST_EQUALITY_CONST( discrete_angles.front(), 9.33333333326667125e-01 );
   TEST_EQUALITY_CONST( discrete_angles.back(), 9.33333333326667125e-01 );
   TEST_EQUALITY_CONST( discrete_angles.size(), 1 );

   discrete_angles =
     h_data_container.getAdjointMomentPreservingElasticDiscreteAngles( 1.0e+5 );

   TEST_EQUALITY_CONST( discrete_angles.front(), 9.96847743255378838e-01 );
   TEST_EQUALITY_CONST( discrete_angles.back(), 9.96847743255378838e-01 );
   TEST_EQUALITY_CONST( discrete_angles.size(), 1 );

   std::vector<double> discrete_weights =
     h_data_container.getAdjointMomentPreservingElasticWeights( 1.0e-5 );

   TEST_EQUALITY_CONST( discrete_weights.front(), 1.0 );
   TEST_EQUALITY_CONST( discrete_weights.back(), 1.0 );
   TEST_EQUALITY_CONST( discrete_weights.size(), 1 );

   discrete_weights =
     h_data_container.getAdjointMomentPreservingElasticWeights( 1.0e+5 );

   TEST_EQUALITY_CONST( discrete_weights.front(), 1.0 );
   TEST_EQUALITY_CONST( discrete_weights.back(), 1.0 );
   TEST_EQUALITY_CONST( discrete_weights.size(), 1 );

   threshold =
     h_data_container.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     h_data_container.getAdjointMomentPreservingCrossSection();

   TEST_FLOATING_EQUALITY( cross_section.front(), 1.0308605152240909636E+07, 1e-15 );
   TEST_FLOATING_EQUALITY( cross_section.back(), 0.73821976945064415876, 1e-15 );
   TEST_EQUALITY_CONST( cross_section.size(), 848-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   // Check the atomic excitation data
   threshold =
     h_data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     h_data_container.getAdjointAtomicExcitationCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 6.12229969785753563e+07 );
   TEST_EQUALITY_CONST( cross_section.back(), 0.0 );
   TEST_EQUALITY_CONST( cross_section.size(), 848-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   std::vector<double> atomic_excitation_energy_grid =
     h_data_container.getAdjointAtomicExcitationEnergyGrid();

   TEST_FLOATING_EQUALITY( atomic_excitation_energy_grid.front(), 9.2946e-06, 1e-13 );
   TEST_FLOATING_EQUALITY( atomic_excitation_energy_grid.back(), 20.0-2.10108e-5, 1e-15 );
   TEST_EQUALITY_CONST( atomic_excitation_energy_grid.size(), 99 );

   std::vector<double> atomic_excitation_energy_gain =
     h_data_container.getAdjointAtomicExcitationEnergyGain();

   TEST_EQUALITY_CONST( atomic_excitation_energy_gain.front(), 1.57054e-05 );
   TEST_EQUALITY_CONST( atomic_excitation_energy_gain.back(), 2.10108e-5 );
   TEST_EQUALITY_CONST( atomic_excitation_energy_gain.size(), 99 );

   // Check the bremsstrahlung data
   threshold =
     h_data_container.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     h_data_container.getAdjointBremsstrahlungCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 4.33592710577003047e+01 );
   TEST_EQUALITY_CONST( cross_section.back(), 8.36680792493486147e-01 );
   TEST_EQUALITY_CONST( cross_section.size(), 848-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

//   std::vector<double> bremsstrahlung_energy_grid =
//     h_data_container.getAdjointBremsstrahlungEnergyGrid();

//   TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.size(), 11 );

//   std::vector<double> bremsstrahlung_photon_energy =
//     h_data_container.getAdjointBremsstrahlungPhotonEnergy( 1.00000e-5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

//   bremsstrahlung_photon_energy =
//     h_data_container.getAdjointBremsstrahlungPhotonEnergy( 1.00000e+5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 2 );

//   std::vector<double> bremsstrahlung_photon_pdf =
//     h_data_container.getAdjointBremsstrahlungPhotonPDF( 1.00000e-5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 1.46394848379322421e+06 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 1.46824029287934118e+04 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

//   bremsstrahlung_photon_pdf =
//     h_data_container.getAdjointBremsstrahlungPhotonPDF( 1.00000e+5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(),  0.0 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  0.0 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 2 );

  // Check the electroionization data
  threshold =
    h_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( 1u );

  TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     h_data_container.getAdjointElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 4.60123626953526840e+10 );
  TEST_EQUALITY_CONST( cross_section.back(), 6.24366840971903148e+04 );
  TEST_EQUALITY_CONST( cross_section.size(), 848-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

//   std::vector<double> electroionization_energy_grid =
//     h_data_container.getAdjointElectroionizationEnergyGrid( 1u );

//   TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 1.36100e-5 );
//   TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 8 );

//   std::vector<double> electroionization_recoil_energy =
//     h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 1.36100e-5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.79866e-9 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.79866e-8 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     h_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 147 );

//   std::vector<double> electroionization_recoil_pdf =
//     h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 1.36100e-5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 3.97015e+7 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 3.97015e+7 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     h_data_container.getAdjointElectroionizationRecoilPDF( 1u, 1.00000e+5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.61897e+5 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 2.77550e-15 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 147 );
//

  h_data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Check that the table data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
		           setTableData_c )
{
  data_generator_c.reset(
       new TestStandardAdjointElectronPhotonRelaxationDataGenerator(
            c_epr_data_container, 0.001, 20.0, 1.0e-5, 20.0 ) );

  data_generator_c->setAdjointBremsstrahlungCrossSectionEvaluationTolerance( 1e-6 );
  data_generator_c->setAdjointElectroionizationCrossSectionEvaluationTolerance( 1e-6 );
  data_generator_c->setAdjointElectronGridConvergenceTolerance( 1e-3 );
  data_generator_c->setAdjointElectronAbsoluteDifferenceTolerance( 1e-16 );
  data_generator_c->setAdjointElectronDistanceTolerance( 1e-8 );

  data_generator_c->setTableData( c_data_container );

  // Check the table settings data
  TEST_EQUALITY_CONST( c_data_container.getAtomicNumber(), 6 );
  TEST_EQUALITY_CONST( c_data_container.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( c_data_container.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( c_data_container.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( c_data_container.getMaxElectronEnergy(), 20.0 );
  TEST_EQUALITY_CONST( c_data_container.getCutoffAngleCosine(), 1.0 );
  TEST_EQUALITY_CONST( c_data_container.getNumberOfAdjointMomentPreservingAngles(), 0 );
  TEST_EQUALITY_CONST( c_data_container.getGridConvergenceTolerance(), 0.001 );
  TEST_EQUALITY_CONST(
    c_data_container.getGridAbsoluteDifferenceTolerance(), 1e-12 );
  TEST_EQUALITY_CONST( c_data_container.getGridDistanceTolerance(), 1e-14 );

  c_data_container.exportData( "test_c_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Check that the table data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
		           setAdjointRelaxationData_c )
{

  data_generator_c->setAdjointRelaxationData( c_data_container );

  // Check the relaxation data
  TEST_EQUALITY_CONST( c_data_container.getSubshells().size(), 4 );
  TEST_ASSERT( c_data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( c_data_container.getSubshells().count( 2 ) );
  TEST_ASSERT( c_data_container.getSubshells().count( 3 ) );
  TEST_ASSERT( c_data_container.getSubshells().count( 4 ) );
  TEST_EQUALITY_CONST( c_data_container.getSubshellOccupancy( 1 ), 2 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellOccupancy( 2 ), 2 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellOccupancy( 3 ), 0.67 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellOccupancy( 4 ), 1.33 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellBindingEnergy( 1 ),
		       2.9101e-4 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellBindingEnergy( 2 ),
		       1.7560e-5 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellBindingEnergy( 3 ),
		       8.9900e-6 );
  TEST_EQUALITY_CONST( c_data_container.getSubshellBindingEnergy( 4 ),
		       8.9800e-6 );
  TEST_ASSERT( !c_data_container.hasAdjointRelaxationData() );

  c_data_container.exportData( "test_c_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

////---------------------------------------------------------------------------//
//// Check that the table data can be set
//TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
//		           setAdjointPhotonData_c )
//{

//  data_generator_c->setAdjointPhotonData( c_data_container );

//  // Check the photon data

//  c_data_container.exportData( "test_c_epr.xml",
//			     Utility::ArchivableObject::XML_ARCHIVE );
//}

//---------------------------------------------------------------------------//
// Check that the table data can be set
TEUCHOS_UNIT_TEST( StandardAdjointElectronPhotonRelaxationDataGenerator,
		           setAdjointElectronData_c )
{
  data_generator_c->setAdjointElectronData( c_data_container );

  // Check the electron data
   std::vector<double> energy_grid = c_data_container.getAdjointElectronEnergyGrid();

   TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
   TEST_EQUALITY_CONST( energy_grid.back(), 20.0 );
   TEST_EQUALITY_CONST( energy_grid.size(), 776 );

   // Check the elastic data
   TEST_ASSERT( !c_data_container.hasAdjointMomentPreservingData() );

   unsigned threshold =
     c_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   std::vector<double> cross_section =
     c_data_container.getAdjointCutoffElasticCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 3.06351e+9 );
   TEST_FLOATING_EQUALITY( cross_section.back(), 10402.358457801836266, 1e-15 );
   TEST_EQUALITY_CONST( cross_section.size(), 776-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   threshold =
     c_data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 639 );

   cross_section =
     c_data_container.getAdjointScreenedRutherfordElasticCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 2.05508471144130453e+01 );
   TEST_EQUALITY_CONST( cross_section.back(), 1.30888131403400272e+05 );
   TEST_EQUALITY_CONST( cross_section.size(), 776-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   std::vector<double> angular_grid =
     c_data_container.getAdjointElasticAngularEnergyGrid();

   TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
   TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
   TEST_EQUALITY_CONST( angular_grid.size(), 16 );

   std::vector<double> elastic_angles =
     c_data_container.getAdjointCutoffElasticAngles(1.0e-5);

   TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
   TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
   TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

   elastic_angles =
     c_data_container.getAdjointCutoffElasticAngles(1.0e+5);

   TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
   TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
   TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

   std::vector<double> elastic_pdf =
     c_data_container.getAdjointCutoffElasticPDF(1.0e-5);

   TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
   TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
   TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

   elastic_pdf =
     c_data_container.getAdjointCutoffElasticPDF(1.0e+5);

   TEST_EQUALITY_CONST( elastic_pdf.front(), 1.693970E-11 );
   TEST_EQUALITY_CONST( elastic_pdf.back(), 9.868670E+05 );
   TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

   // Check the atomic excitation data
   threshold =
     c_data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     c_data_container.getAdjointAtomicExcitationCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 5.90068663943557292e+07 );
   TEST_EQUALITY_CONST( cross_section.back(), 0.0 );
   TEST_EQUALITY_CONST( cross_section.size(), 776-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

   std::vector<double> atomic_excitation_energy_grid =
     c_data_container.getAdjointAtomicExcitationEnergyGrid();

   TEST_FLOATING_EQUALITY( atomic_excitation_energy_grid.front(), 9.9016e-06, 1e-14 );
   TEST_FLOATING_EQUALITY( atomic_excitation_energy_grid.back(), 20.0-1.97981e-05, 1e-15 );
   TEST_EQUALITY_CONST( atomic_excitation_energy_grid.size(), 109 );

   std::vector<double> atomic_excitation_energy_gain =
     c_data_container.getAdjointAtomicExcitationEnergyGain();

   TEST_EQUALITY_CONST( atomic_excitation_energy_gain.front(), 1.13484e-05 );
   TEST_EQUALITY_CONST( atomic_excitation_energy_gain.back(), 1.97981e-05 );
   TEST_EQUALITY_CONST( atomic_excitation_energy_gain.size(), 109 );

   // Check the bremsstrahlung data
   threshold =
     c_data_container.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex();

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     c_data_container.getAdjointBremsstrahlungCrossSection();

   TEST_EQUALITY_CONST( cross_section.front(), 9.10973391010646765e+02 );
   TEST_EQUALITY_CONST( cross_section.back(), 1.09968948521074097e+01 );
   TEST_EQUALITY_CONST( cross_section.size(), 776-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

//   std::vector<double> bremsstrahlung_energy_grid =
//     c_data_container.getAdjointBremsstrahlungEnergyGrid();

//   TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.size(), 10 );

//   std::vector<double> bremsstrahlung_photon_energy =
//     c_data_container.getAdjointBremsstrahlungPhotonEnergy( 1.00000e-5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

//   bremsstrahlung_photon_energy =
//     c_data_container.getAdjointBremsstrahlungPhotonEnergy( 1.00000e+5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 2 );

//   std::vector<double> bremsstrahlung_photon_pdf =
//     c_data_container.getAdjointBremsstrahlungPhotonPDF( 1.00000e-5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(),1.40925689457137836e+06 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 1.43093090368334142e+04 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

//   bremsstrahlung_photon_pdf =
//     c_data_container.getAdjointBremsstrahlungPhotonPDF( 1.00000e+5 );

//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 0.0 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  0.0 );
//   TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 2 );
// 
   // Check the electroionization data
   threshold =
     c_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( 1u );

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     c_data_container.getAdjointElectroionizationCrossSection( 1u );

   TEST_EQUALITY_CONST( cross_section.front(), 1.58054886047042942e+09 );
   TEST_EQUALITY_CONST( cross_section.back(), 1.01386550694160269e+04 );
   TEST_EQUALITY_CONST( cross_section.size(), 776-threshold );
std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;

//   std::vector<double> electroionization_energy_grid =
//     c_data_container.getAdjointElectroionizationEnergyGrid( 1u );

//   TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 2.910100E-04 );
//   TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 7 );

//   std::vector<double> electroionization_recoil_energy =
//     c_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 2.910100E-04 );

//   TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-8 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     c_data_container.getAdjointElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 128 );

//   std::vector<double> electroionization_recoil_pdf =
//     c_data_container.getAdjointElectroionizationRecoilPDF( 1u, 2.910100E-04 );

//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.111110E+07 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.111110E+07 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     c_data_container.getAdjointElectroionizationRecoilPDF( 1u, 1.00000e+5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 7.358100E+03 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 3.45597E-14 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 128 );

   threshold =
     c_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( 4u );

   TEST_EQUALITY_CONST( threshold, 0 );

   cross_section =
     c_data_container.getAdjointElectroionizationCrossSection( 4u );

   TEST_EQUALITY_CONST( cross_section.front(), 1.38107051010506134e+11 );
   TEST_EQUALITY_CONST( cross_section.back(), 1.20330712777701134e+05 );
   TEST_EQUALITY_CONST( cross_section.size(), 776-threshold );

std::cout << std::setprecision(20) << "cross_section.front() = " << cross_section.front() << std::endl;
std::cout << std::setprecision(20) << "cross_section.back() = " << cross_section.back() << std::endl;
//   electroionization_energy_grid =
//     c_data_container.getAdjointElectroionizationEnergyGrid( 4u );

//   TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 8.980000E-06 );
//   TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
//   TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 8 );

//   electroionization_recoil_energy =
//     c_data_container.getAdjointElectroionizationRecoilEnergy( 4u, 8.980000E-06 );

//   TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.550000E-09 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.550000E-08 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

//   electroionization_recoil_energy =
//     c_data_container.getAdjointElectroionizationRecoilEnergy( 4u, 1.00000e+5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
//   TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 143 );

//   electroionization_recoil_pdf =
//     c_data_container.getAdjointElectroionizationRecoilPDF( 4u, 8.980000E-06 );

//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 4.357300E+07 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 4.357300E+07 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

//   electroionization_recoil_pdf =
//     c_data_container.getAdjointElectroionizationRecoilPDF( 4u, 1.00000e+5 );

//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.120930E+05 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.515230E-15 );
//   TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 143 );
// 

  c_data_container.exportData( "test_c_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_native_file, test_c_native_file;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_native_file",
                 &test_h_native_file,
                 "Test h native file name" );
  clp.setOption( "test_c_native_file",
                 &test_c_native_file,
                 "Test c native file name" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the native data file container for h
  h_epr_data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                                                        test_h_native_file ) );
  c_epr_data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                                                        test_c_native_file ) );

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstStandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//

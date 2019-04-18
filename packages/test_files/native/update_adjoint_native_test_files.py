#!/usr/bin/python2.7
##---------------------------------------------------------------------------##
## Adjoint test data updater
##---------------------------------------------------------------------------##

import os
import sys
import datetime

# Simple class for color output
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

# If specific install version of frensie is desired the line below can be
# uncommented and that path to PyFrensie can be manually inserted.
# sys.path.insert(0, '/home/lkersting/research/frensie-repos/lkersting/lib/python2.7/site-packages/')

import PyFrensie.Utility as Utility
import PyFrensie.Data.Native as Native
import PyFrensie.MonteCarlo as MonteCarlo
import PyFrensie.DataGen.ElectronPhoton as ElectronPhoton

# Get the date for the table notes
today = str(datetime.datetime.today())
notes="This table was generated on " + today + ". It is for testing only!"

# Update adjoint Hydrogen data
print bcolors.BOLD + "Updating the adjoint H native test data ...\n" + bcolors.ENDC

h_epr_data = Native.ElectronPhotonRelaxationDataContainer( "test_epr_1_native.xml" )

generator_h = ElectronPhoton.StandardAdjointElectronPhotonRelaxationDataGenerator( h_epr_data, 1e-3, 20.0, 1e-5, 20.0 )

# Set default photon grid tolerances
generator_h.setDefaultPhotonGridConvergenceTolerance( 1e-3 )
generator_h.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 )
generator_h.setDefaultPhotonGridDistanceTolerance( 1e-16 )

generator_h.setPhotonThresholdEnergyNudgeFactor( 1.0001 )
generator_h.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_h.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_h.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_h.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_h.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 )
generator_h.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-5 )
generator_h.setAdjointIncoherentEvaluationTolerance( 1e-2 )
generator_h.setAdjointIncoherentGridConvergenceTolerance( 0.5 )
generator_h.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 )
generator_h.setAdjointIncoherentGridDistanceTolerance( 1e-16 )

# Set default electron grid tolerances
generator_h.setDefaultElectronGridConvergenceTolerance( 1e-2 )
generator_h.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-16 )
generator_h.setDefaultElectronGridDistanceTolerance( 1e-9 )

generator_h.setElectronTabularEvaluationTolerance( 1e-7 )
generator_h.setElectronTwoDInterpPolicy( MonteCarlo.LOGLOGLOG_INTERPOLATION )
generator_h.setElectronTwoDGridPolicy( MonteCarlo.UNIT_BASE_CORRELATED_GRID )

generator_h.setCutoffAngleCosine( 0.9 )
generator_h.setNumberOfMomentPreservingAngles( 2 )

generator_h.setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 )
generator_h.setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-6 )
generator_h.setAdjointBremsstrahlungEvaluationTolerance( 1e-3 )
generator_h.setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 )
generator_h.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 )
generator_h.setAdjointBremsstrahlungDistanceTolerance( 1e-9 )

generator_h.setForwardElectroionizationSamplingMode( MonteCarlo.KNOCK_ON_SAMPLING )
generator_h.setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 )
generator_h.setAdjointElectroionizationMaxEnergyNudgeValue( 1e-6 )
generator_h.setAdjointElectroionizationEvaluationTolerance( 1e-3 )
generator_h.setAdjointElectroionizationGridConvergenceTolerance( 0.5 )
generator_h.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 )
generator_h.setAdjointElectroionizationDistanceTolerance( 1e-9 )

# Set the notes
generator_h.setNotes( notes )

# Generate the data
try:
    generator_h.populateEPRDataContainer( True, True )
except Exception as e:
    print(bcolors.BOLD + bcolors.FAIL + '\nadjoint H native data FAILED to update: '+ str(e))
    sys.exit(1)

print bcolors.BOLD + bcolors.OKGREEN + "adjoint H native data updated successfully!\n" + bcolors.ENDC
print "-------------------------------------------\n"

# Save the file
h_data_container = generator_h.getDataContainer()
h_data_container.saveToFile( "test_aepr_1_native.xml", True)

# Update adjoint Carbon data
print bcolors.BOLD + "Updating the adjoint C native test data ...\n" + bcolors.ENDC

c_epr_data = Native.ElectronPhotonRelaxationDataContainer( "test_epr_6_native.xml" )

generator_c = ElectronPhoton.StandardAdjointElectronPhotonRelaxationDataGenerator( c_epr_data, 1e-3, 20.0, 1e-5, 20.0 )

# Set default photon grid tolerances
generator_c.setDefaultPhotonGridConvergenceTolerance( 1e-3 )
generator_c.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 )
generator_c.setDefaultPhotonGridDistanceTolerance( 1e-16 )

generator_c.setPhotonThresholdEnergyNudgeFactor( 1.0001 )
generator_c.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_c.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_c.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_c.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_c.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 )
generator_c.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-5 )
generator_c.setAdjointIncoherentEvaluationTolerance( 1e-2 )
generator_c.setAdjointIncoherentGridConvergenceTolerance( 0.5 )
generator_c.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 )
generator_c.setAdjointIncoherentGridDistanceTolerance( 1e-16 )

# Set default electron grid tolerances
generator_c.setDefaultElectronGridConvergenceTolerance( 1e-2 )
generator_c.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-16 )
generator_c.setDefaultElectronGridDistanceTolerance( 1e-9 )

generator_c.setElectronTabularEvaluationTolerance( 1e-5 )
generator_c.setElectronTwoDInterpPolicy( MonteCarlo.LOGLOGLOG_INTERPOLATION )
generator_c.setElectronTwoDGridPolicy( MonteCarlo.UNIT_BASE_CORRELATED_GRID )

generator_c.setCutoffAngleCosine( 0.9 )
generator_c.setNumberOfMomentPreservingAngles( 2 )

generator_c.setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 )
generator_c.setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-2 )
generator_c.setAdjointBremsstrahlungEvaluationTolerance( 1e-3 )
generator_c.setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 )
generator_c.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 )
generator_c.setAdjointBremsstrahlungDistanceTolerance( 1e-9 )

generator_c.setForwardElectroionizationSamplingMode( MonteCarlo.KNOCK_ON_SAMPLING )
generator_c.setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 )
generator_c.setAdjointElectroionizationMaxEnergyNudgeValue( 1e-2 )
generator_c.setAdjointElectroionizationEvaluationTolerance( 1e-3 )
generator_c.setAdjointElectroionizationGridConvergenceTolerance( 0.5 )
generator_c.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 )
generator_c.setAdjointElectroionizationDistanceTolerance( 1e-9 )

# Set the notes
generator_c.setNotes( notes )

# Generate the data
try:
    generator_c.populateEPRDataContainer( True, True )
except Exception as e:
    print(bcolors.BOLD + bcolors.FAIL + '\nadjoint C native data FAILED to update: '+ str(e))
    sys.exit(1)

print bcolors.BOLD + bcolors.OKGREEN + "adjoint C native data updated successfully!\n" + bcolors.ENDC
print "-------------------------------------------\n"

# Save the file
c_data_container = generator_c.getDataContainer()
c_data_container.saveToFile( "test_aepr_6_native.xml", True)

# Update adjoint Aluminum data
print bcolors.BOLD + "Updating the adjoint Al native test data ...\n" + bcolors.ENDC

al_epr_data = Native.ElectronPhotonRelaxationDataContainer( "test_epr_13_native.xml" )

generator_al = ElectronPhoton.StandardAdjointElectronPhotonRelaxationDataGenerator( al_epr_data, 1e-3, 20.0, 1e-5, 20.0 )

# Set default photon grid tolerances
generator_al.setDefaultPhotonGridConvergenceTolerance( 1e-3 )
generator_al.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 )
generator_al.setDefaultPhotonGridDistanceTolerance( 1e-16 )

generator_al.setPhotonThresholdEnergyNudgeFactor( 1.0001 )
generator_al.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_al.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_al.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_al.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_al.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 )
generator_al.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-5 )
generator_al.setAdjointIncoherentEvaluationTolerance( 1e-2 )
generator_al.setAdjointIncoherentGridConvergenceTolerance( 0.5 )
generator_al.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 )
generator_al.setAdjointIncoherentGridDistanceTolerance( 1e-16 )

# Set default electron grid tolerances
generator_al.setDefaultElectronGridConvergenceTolerance( 1e-2 )
generator_al.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-16 )
generator_al.setDefaultElectronGridDistanceTolerance( 1e-9 )

generator_al.setElectronTabularEvaluationTolerance( 1e-5 )
generator_al.setElectronTwoDInterpPolicy( MonteCarlo.LOGLOGLOG_INTERPOLATION )
generator_al.setElectronTwoDGridPolicy( MonteCarlo.UNIT_BASE_CORRELATED_GRID )

generator_al.setCutoffAngleCosine( 0.9 )
generator_al.setNumberOfMomentPreservingAngles( 2 )

generator_al.setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 )
generator_al.setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-2 )
generator_al.setAdjointBremsstrahlungEvaluationTolerance( 1e-3 )
generator_al.setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 )
generator_al.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 )
generator_al.setAdjointBremsstrahlungDistanceTolerance( 1e-9 )

generator_al.setForwardElectroionizationSamplingMode( MonteCarlo.KNOCK_ON_SAMPLING )
generator_al.setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 )
generator_al.setAdjointElectroionizationMaxEnergyNudgeValue( 1e-2 )
generator_al.setAdjointElectroionizationEvaluationTolerance( 1e-3 )
generator_al.setAdjointElectroionizationGridConvergenceTolerance( 0.5 )
generator_al.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 )
generator_al.setAdjointElectroionizationDistanceTolerance( 1e-9 )

# Set the notes
generator_al.setNotes( notes )

# Generate the data
try:
    generator_al.populateEPRDataContainer( True, True )
except Exception as e:
    print(bcolors.BOLD + bcolors.FAIL + '\nadjoint Al native data FAILED to update: '+ str(e))
    sys.exit(1)

print bcolors.BOLD + bcolors.OKGREEN + "adjoint Al native data updated successfully!\n" + bcolors.ENDC
print "-------------------------------------------\n"

# Save the file
al_data_container = generator_al.getDataContainer()
al_data_container.saveToFile( "test_aepr_13_native.xml", True)

# Update adjoint Silicon data
print bcolors.BOLD + "Updating the adjoint Si native test data ...\n" + bcolors.ENDC

si_epr_data = Native.ElectronPhotonRelaxationDataContainer( "test_epr_14_native.xml" )

generator_si = ElectronPhoton.StandardAdjointElectronPhotonRelaxationDataGenerator( si_epr_data, 1e-3, 20.0, 1e-5, 20.0 )

# Set default photon grid tolerances
generator_si.setDefaultPhotonGridConvergenceTolerance( 1e-3 )
generator_si.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 )
generator_si.setDefaultPhotonGridDistanceTolerance( 1e-16 )

generator_si.setPhotonThresholdEnergyNudgeFactor( 1.0001 )
generator_si.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_si.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_si.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
generator_si.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 )
generator_si.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 )
generator_si.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-5 )
generator_si.setAdjointIncoherentEvaluationTolerance( 1e-2 )
generator_si.setAdjointIncoherentGridConvergenceTolerance( 0.5 )
generator_si.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 )
generator_si.setAdjointIncoherentGridDistanceTolerance( 1e-16 )

# Set default electron grid tolerances
generator_si.setDefaultElectronGridConvergenceTolerance( 2e-2 )
generator_si.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-16 )
generator_si.setDefaultElectronGridDistanceTolerance( 1e-9 )

generator_si.setElectronTabularEvaluationTolerance( 1e-5 )
generator_si.setElectronTwoDInterpPolicy( MonteCarlo.LOGLOGLOG_INTERPOLATION )
generator_si.setElectronTwoDGridPolicy( MonteCarlo.UNIT_BASE_GRID )

generator_si.setCutoffAngleCosine( 0.9 )
generator_si.setNumberOfMomentPreservingAngles( 2 )

generator_si.setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 )
generator_si.setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-2 )
generator_si.setAdjointBremsstrahlungEvaluationTolerance( 1e-3 )
generator_si.setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 )
generator_si.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 )
generator_si.setAdjointBremsstrahlungDistanceTolerance( 1e-9 )

generator_si.setForwardElectroionizationSamplingMode( MonteCarlo.KNOCK_ON_SAMPLING )
generator_si.setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 )
generator_si.setAdjointElectroionizationMaxEnergyNudgeValue( 1e-2 )
generator_si.setAdjointElectroionizationEvaluationTolerance( 1e-3 )
generator_si.setAdjointElectroionizationGridConvergenceTolerance( 0.5 )
generator_si.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 )
generator_si.setAdjointElectroionizationDistanceTolerance( 1e-9 )

# Set the notes
generator_si.setNotes( notes )

# Generate the data
try:
    generator_si.populateEPRDataContainer( True, True )
except Exception as e:
    print(bcolors.BOLD + bcolors.FAIL + '\nadjoint Si native data FAILED to update: '+ str(e))
    sys.exit(1)

print bcolors.BOLD + bcolors.OKGREEN + "adjoint Si native data updated successfully!\n" + bcolors.ENDC
print "-------------------------------------------\n"

# Save the file
si_data_container = generator_si.getDataContainer()
si_data_container.saveToFile( "test_aepr_14_native.xml", True)

# NOTE: The adjoint Pb files are no longer used for testing!

# # Update adjoint Lead data
# print bcolors.BOLD + "Updating the adjoint Pb native test data ...\n" + bcolors.ENDC

# pb_epr_data = Native.ElectronPhotonRelaxationDataContainer( "test_epr_82_native.xml" )

# generator_pb = ElectronPhoton.StandardAdjointElectronPhotonRelaxationDataGenerator( pb_epr_data, 1e-3, 20.0, 1e-5, 20.0 )

# # Set default photon grid tolerances
# generator_pb.setDefaultPhotonGridConvergenceTolerance( 1e-3 )
# generator_pb.setDefaultPhotonGridAbsoluteDifferenceTolerance( 1e-42 )
# generator_pb.setDefaultPhotonGridDistanceTolerance( 1e-16 )

# generator_pb.setPhotonThresholdEnergyNudgeFactor( 1.0001 )
# generator_pb.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
# generator_pb.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 )
# generator_pb.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 )
# generator_pb.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 )
# generator_pb.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 )
# generator_pb.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-5 )
# generator_pb.setAdjointIncoherentEvaluationTolerance( 1e-2 )
# generator_pb.setAdjointIncoherentGridConvergenceTolerance( 0.5 )
# generator_pb.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-42 )
# generator_pb.setAdjointIncoherentGridDistanceTolerance( 1e-16 )

# # Set default electron grid tolerances
# generator_pb.setDefaultElectronGridConvergenceTolerance( 1e-2 )
# generator_pb.setDefaultElectronGridAbsoluteDifferenceTolerance( 1e-16 )
# generator_pb.setDefaultElectronGridDistanceTolerance( 1e-9 )

# generator_pb.setElectronTabularEvaluationTolerance( 1e-7 )
# generator_pb.setElectronTwoDInterpPolicy( MonteCarlo.LOGLOGLOG_INTERPOLATION )
# generator_pb.setElectronTwoDGridPolicy( MonteCarlo.UNIT_BASE_CORRELATED_GRID )

# generator_pb.setCutoffAngleCosine( 0.9 )
# generator_pb.setNumberOfMomentPreservingAngles( 2 )

# generator_pb.setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 )
# generator_pb.setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-2 )
# generator_pb.setAdjointBremsstrahlungEvaluationTolerance( 1e-3 )
# generator_pb.setAdjointBremsstrahlungGridConvergenceTolerance( 0.5 )
# generator_pb.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 )
# generator_pb.setAdjointBremsstrahlungDistanceTolerance( 1e-9 )

# generator_pb.setForwardElectroionizationSamplingMode( MonteCarlo.KNOCK_ON_SAMPLING )
# generator_pb.setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 )
# generator_pb.setAdjointElectroionizationMaxEnergyNudgeValue( 1e-2 )
# generator_pb.setAdjointElectroionizationEvaluationTolerance( 1e-3 )
# generator_pb.setAdjointElectroionizationGridConvergenceTolerance( 0.5 )
# generator_pb.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 )
# generator_pb.setAdjointElectroionizationDistanceTolerance( 1e-9 )

# # Set the notes
# generator_pb.setNotes( notes )

# # Generate the data
# try:
#     generator_pb.populateEPRDataContainer( True, True )
# except Exception as e:
#     print(bcolors.BOLD + bcolors.FAIL + '\nadjoint Pb native data FAILED to update: '+ str(e))
#     sys.exit(1)

# print bcolors.BOLD + bcolors.OKGREEN + "adjoint Pb native data updated successfully!\n" + bcolors.ENDC
# print "-------------------------------------------\n"

# # Save the file
# pb_data_container = generator_pb.getDataContainer()
# pb_data_container.saveToFile( "test_aepr_82_native.xml", True)

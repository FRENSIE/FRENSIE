ADD_EXECUTABLE(tstFissionableIsotopes 
  tstFissionableIsotopes.cpp )
TARGET_LINK_LIBRARIES(tstFissionableIsotopes transmutation)
ADD_TEST(FissionableIsotopes_test tstFissionableIsotopes)

ADD_EXECUTABLE(tstAllIsotopes 
  tstAllIsotopes.cpp )
TARGET_LINK_LIBRARIES(tstAllIsotopes transmutation)
ADD_TEST(AllIsotopes_test tstAllIsotopes --z_number="49")

ADD_EXECUTABLE(tstIsotopesForDepletion 
  tstIsotopesForDepletion.cpp )
TARGET_LINK_LIBRARIES(tstIsotopesForDepletion transmutation)
ADD_TEST(IsotopesForDepletion_test tstIsotopesForDepletion)

ADD_EXECUTABLE(tstDecayMatrix 
  tstDecayMatrix.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstDecayMatrix transmutation)
ADD_TEST(DecayMatrix_test tstDecayMatrix)

ADD_EXECUTABLE(tstReactionRateMatrix 
  tstReactionRateMatrix.cpp )
TARGET_LINK_LIBRARIES(tstReactionRateMatrix transmutation)
ADD_TEST(ReactionRateMatrix_test tstReactionRateMatrix)

ADD_EXECUTABLE(tstCellTransmutationData 
  tstCellTransmutationData.cpp )
TARGET_LINK_LIBRARIES(tstCellTransmutationData transmutation)
ADD_TEST(CellTransmutationData_test tstCellTransmutationData)

ADD_EXECUTABLE(tstModuleInterface_ODESolver 
  tstModuleInterface_ODESolver.cpp )
TARGET_LINK_LIBRARIES(tstModuleInterface_ODESolver transmutation)
ADD_TEST(ModuleInterface_ODESolver_test tstModuleInterface_ODESolver)

#ADD_EXECUTABLE(tstModuleInterface_BoostSolver 
#  tstModuleInterface_BoostSolver.cpp )
#TARGET_LINK_LIBRARIES(tstModuleInterface_BoostSolver transmutation)
#ADD_TEST(ModuleInterfacei_BoostSolver_test tstModuleInterface_BoostSolver)

ADD_EXECUTABLE(tstIsotopesArray 
  tstIsotopesArray.cpp )
TARGET_LINK_LIBRARIES(tstIsotopesArray transmutation)
ADD_TEST(IsotopesArray_test tstIsotopesArray)

# # Create the decay regresssion suite
# ADD_EXECUTABLE(decay_regression_suite decay_regression_suite.cpp)
# TARGET_LINK_LIBRARIES(decay_regression_suite utility_core transmutation)

# # Create a simple decay verification problem
# ADD_EXECUTABLE(decay_verification_simple_problem decay_verification_simple_problem.cpp)
# TARGET_LINK_LIBRARIES(decay_verification_simple_problem utility_core transmutation)

# # Create a simple decay verification problem for boost
# ADD_EXECUTABLE(decay_verification_simple_problem_boost
# decay_verification_simple_problem_boost.cpp)
# TARGET_LINK_LIBRARIES(decay_verification_simple_problem_boost utility_core transmutation)

# # Create an intermediate decay verification problem
# ADD_EXECUTABLE(decay_verification_intermediate_problem decay_verification_intermediate_problem.cpp)
# TARGET_LINK_LIBRARIES(decay_verification_intermediate_problem utility_core transmutation)

# # Create an advanced decay verification problem
# ADD_EXECUTABLE(decay_verification_advanced_problem decay_verification_advanced_problem.cpp)
# TARGET_LINK_LIBRARIES(decay_verification_advanced_problem utility_core transmutation)

# # Create a simple decay verification problem
# ADD_EXECUTABLE(fission_reaction_rate_verification_problem
# fission_reaction_rate_verification_problem.cpp)
# TARGET_LINK_LIBRARIES(fission_reaction_rate_verification_problem utility_core transmutation)
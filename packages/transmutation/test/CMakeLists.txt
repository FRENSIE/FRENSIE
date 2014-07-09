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
  tstDecayMatrix.cpp )
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
ADD_TEST(ModuleInterfacei_ODESolver_test tstModuleInterface_ODESolver)

ADD_EXECUTABLE(tstIsotopesArray 
  tstIsotopesArray.cpp )
TARGET_LINK_LIBRARIES(tstIsotopesArray transmutation)
ADD_TEST(IsotopesArray_test tstIsotopesArray)


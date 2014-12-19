MESSAGE(STATUS "Setting up dashboard client...")
set(CTEST_PROJECT_NAME "FRENSIE")
set(CTEST_NIGHTLY_START_TIME "02:00:00 UTC")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "128.104.184.29")
set(CTEST_DROP_LOCATION "/CDash/submit.php?project=FRENSIE")
set(CTEST_DROP_SITE_CDASH TRUE)
MESSAGE(STATUS "Setting up dashboard client...done")
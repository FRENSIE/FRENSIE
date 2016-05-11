Testing Data
=====

The data files contained in this directory are to be used for testing purposes
only! Many of the unit tests use the data in this directory. Because some of
the files are large it is ideal to store them in a single location (usually
the files needed for testing are stored in the test_files directory, which
is contained in the test directory containing the unit test files for a
package).

## Requirements
1. Ensure that it is **LEGAL** to store the desired data files in the repo.
2. Use cross-platform formats (e.g. ASCII and XML) - no binary data.

## A Note on ACE Files
ACE files that you have personally generated with a tool such as NJOY can be
added to this directory (for testing purposes only). Ideally, the tables should
be modified in such a way where they are useless from a simulation standpoint
(e.g. inaccurate cross section data). 
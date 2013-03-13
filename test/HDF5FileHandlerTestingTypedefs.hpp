//---------------------------------------------------------------------------//
// \file   HDF5FileHandlerTestingTypedefs.hpp
// \author Alex Robinson
// \brief  Typdefs for HDF5FileHandler template unit test
//---------------------------------------------------------------------------//

#ifndef HDF5_FILE_HANDLER_TESTING_TYPEDEFS_HPP
#define HDF5_FILE_HANDLER_TESTING_TYPEDEFS_HPP
				
typedef FACEMC::Pair<int,int> pair_int_int;	
typedef FACEMC::Pair<unsigned int,unsigned int> pair_uint_uint; 
typedef FACEMC::Pair<double,double> pair_double_double; 
typedef FACEMC::Pair<int,unsigned int> pair_int_uint; 
typedef FACEMC::Pair<int,double> pair_int_double; 
typedef FACEMC::Pair<unsigned int,int> pair_uint_int; 
typedef FACEMC::Pair<unsigned int,double> pair_uint_double; 
typedef FACEMC::Pair<double,int> pair_double_int; 
typedef FACEMC::Pair<double,unsigned int> pair_double_uint; 
typedef FACEMC::Trip<int,int,int> trip_int_int_int; 
typedef FACEMC::Trip<unsigned int,unsigned int,unsigned int> trip_uint_uint_uint; 
typedef FACEMC::Trip<double,double,double> trip_double_double_double; 
typedef FACEMC::Trip<int,int,unsigned int> trip_int_int_uint; 
typedef FACEMC::Trip<int,int,double> trip_int_int_double; 
typedef FACEMC::Trip<int,unsigned int,int> trip_int_uint_int; 
typedef FACEMC::Trip<int,double,int> trip_int_double_int; 
typedef FACEMC::Trip<int,unsigned int,unsigned int> trip_int_uint_uint; 
typedef FACEMC::Trip<int,double,double> trip_int_double_double; 
typedef FACEMC::Trip<int,unsigned int,double> trip_int_uint_double; 
typedef FACEMC::Trip<int,double,unsigned int> trip_int_double_uint; 
typedef FACEMC::Trip<unsigned int,unsigned int,int> trip_uint_uint_int; 
typedef FACEMC::Trip<unsigned int,unsigned int,double> trip_uint_uint_double; 
typedef FACEMC::Trip<unsigned int,int,unsigned int> trip_uint_int_uint; 
typedef FACEMC::Trip<unsigned int,double,unsigned int> trip_uint_double_uint; 
typedef FACEMC::Trip<unsigned int,int,int> trip_uint_int_int; 
typedef FACEMC::Trip<unsigned int,double,double> trip_uint_double_double; 
typedef FACEMC::Trip<unsigned int,int,double> trip_uint_int_double; 
typedef FACEMC::Trip<unsigned int,double,int> trip_uint_double_int; 
typedef FACEMC::Trip<double,double,int> trip_double_double_int; 
typedef FACEMC::Trip<double,double,unsigned int> trip_double_double_uint; 
typedef FACEMC::Trip<double,int,double > trip_double_int_double; 
typedef FACEMC::Trip<double,unsigned int,double> trip_double_uint_double; 
typedef FACEMC::Trip<double,int,int> trip_double_int_int; 
typedef FACEMC::Trip<double,unsigned int,unsigned int> trip_double_uint_uint; 
typedef FACEMC::Trip<double,int,unsigned int> trip_double_int_uint; 
typedef FACEMC::Trip<double,unsigned int,int> trip_double_uint_int; 
typedef FACEMC::Quad<int,int,int,int> quad_int_int_int_int; 
typedef FACEMC::Quad<unsigned int,unsigned int,unsigned int,unsigned int> quad_uint_uint_uint_uint; 
typedef FACEMC::Quad<double,double,double,double> quad_double_double_double_double; 
typedef FACEMC::Quad<int,int,int,unsigned int> quad_int_int_int_uint; 
typedef FACEMC::Quad<int,int,int,double> quad_int_int_int_double; 
typedef FACEMC::Quad<int,int,unsigned int,int> quad_int_int_uint_int; 
typedef FACEMC::Quad<int,int,double,int> quad_int_int_double_int; 
typedef FACEMC::Quad<int,unsigned int,int,int> quad_int_uint_int_int; 
typedef FACEMC::Quad<int,double,int,int> quad_int_double_int_int; 
typedef FACEMC::Quad<int,int,unsigned int,unsigned int> quad_int_int_uint_uint; 
typedef FACEMC::Quad<int,int,double,double> quad_int_int_double_double; 
typedef FACEMC::Quad<int,unsigned int,int,unsigned int> quad_int_uint_int_uint; 
typedef FACEMC::Quad<int,double,int,double> quad_int_double_int_double; 
typedef FACEMC::Quad<int,unsigned int,unsigned int,int> quad_int_uint_uint_int; 
typedef FACEMC::Quad<int,double,double,int> quad_int_double_double_int; 
typedef FACEMC::Quad<int,unsigned int,unsigned int,unsigned int> quad_int_uint_uint_uint; 
typedef FACEMC::Quad<int,double,double,double> quad_int_double_double_double; 
typedef FACEMC::Quad<int,int,unsigned int,double> quad_int_int_uint_double; 
typedef FACEMC::Quad<int,int,double,unsigned int> quad_int_int_double_uint; 
typedef FACEMC::Quad<int,unsigned int,double,int> quad_int_uint_double_int; 
typedef FACEMC::Quad<int,double,unsigned int,int> quad_int_double_uint_int; 
typedef FACEMC::Quad<int,unsigned int,unsigned int,double> quad_int_uint_uint_double; 
typedef FACEMC::Quad<int,unsigned int,double,unsigned int> quad_int_uint_double_uint; 
typedef FACEMC::Quad<int,double,unsigned int,unsigned int> quad_int_double_uint_uint; 
typedef FACEMC::Quad<int,double,double,unsigned int> quad_int_double_double_uint; 
typedef FACEMC::Quad<int,double,unsigned int,double> quad_int_double_uint_double; 
typedef FACEMC::Quad<int,unsigned int,double,double> quad_int_uint_double_double; 
typedef FACEMC::Quad<int,unsigned int,unsigned int,unsigned int> quad_int_uint_uint_uint; 
typedef FACEMC::Quad<int,double,double,double> quad_int_double_double_double; 

typedef FACEMC::Quad<unsigned int,unsigned int,unsigned int,int> quad_uint_uint_uint_int; 
typedef FACEMC::Quad<unsigned int,unsigned int,unsigned int,double> quad_uint_uint_uint_double; 
typedef FACEMC::Quad<unsigned int,unsigned int,int,unsigned int> quad_uint_uint_int_uint; 
typedef FACEMC::Quad<unsigned int,unsigned int,double,unsigned int> quad_uint_uint_double_uint; 
typedef FACEMC::Quad<unsigned int,int,unsigned int,unsigned int> quad_uint_int_uint_uint; 
typedef FACEMC::Quad<unsigned int,double,unsigned int,unsigned int> quad_uint_double_uint_uint; 
typedef FACEMC::Quad<unsigned int,unsigned int,int,int> quad_uint_uint_int_int; 
typedef FACEMC::Quad<unsigned int,unsigned int,double,double> quad_uint_uint_double_double; 
typedef FACEMC::Quad<unsigned int,int,unsigned int,int> quad_uint_int_uint_int; 
typedef FACEMC::Quad<unsigned int,double,unsigned int,double> quad_uint_double_uint_double; 
typedef FACEMC::Quad<unsigned int,int,unsigned int,int> quad_uint_int_int_uint; 
typedef FACEMC::Quad<unsigned int,double,double,unsigned int> quad_uint_double_double_uint; 
typedef FACEMC::Quad<unsigned int,int,int,int> quad_uint_int_int_int; 
typedef FACEMC::Quad<unsigned int,double,double,double> quad_uint_double_double_double; 
typedef FACEMC::Quad<unsigned int,unsigned int,int,double> quad_uint_uint_int_double; 
typedef FACEMC::Quad<unsigned int,unsigned int,double,int> quad_uint_uint_double_int; 
typedef FACEMC::Quad<unsigned int,int,double,unsigned int> quad_uint_int_double_uint; 
typedef FACEMC::Quad<unsigned int,double,int,unsigned int> quad_uint_double_int_uint; 
typedef FACEMC::Quad<unsigned int,int,int,double> quad_uint_int_int_double; 
typedef FACEMC::Quad<unsigned int,int,double,int> quad_uint_int_double_int; 
typedef FACEMC::Quad<unsigned int,double,int,int> quad_uint_double_int_int; 
typedef FACEMC::Quad<unsigned int,double,double,int> quad_uint_double_double_int; 
typedef FACEMC::Quad<unsigned int,double,int,double> quad_uint_double_int_double; 
typedef FACEMC::Quad<unsigned int,int,double,double> quad_uint_int_double_double; 
typedef FACEMC::Quad<unsigned int,int,int,int> quad_uint_int_int_int; 
typedef FACEMC::Quad<double,double,double,unsigned int> quad_double_double_double_uint; 
typedef FACEMC::Quad<double,double,double,int> quad_double_double_double_int; 
typedef FACEMC::Quad<double,double,unsigned int,double> quad_doulbe_double_uint_int; 
typedef FACEMC::Quad<double,double,int,double> quad_double_double_int_double; 
typedef FACEMC::Quad<double,unsigned int,double,double> quad_double_uint_double_double; 
typedef FACEMC::Quad<double,int,double,double> quad_double_int_double_double; 
typedef FACEMC::Quad<double,double,unsigned int,unsigned int> quad_double_double_uint_uint; 
typedef FACEMC::Quad<double,double,int,int> quad_double_double_int_int; 
typedef FACEMC::Quad<double,unsigned int,double,unsigned int> quad_double_uint_double_uint; 
typedef FACEMC::Quad<double,int,double,int> quad_double_int_double_int; 
typedef FACEMC::Quad<double,unsigned int,unsigned int,double> quad_double_uint_uint_double; 
typedef FACEMC::Quad<double,int,int,double> quad_double_int_int_double; 
typedef FACEMC::Quad<double,unsigned int,unsigned int,unsigned int> quad_double_uint_uint_uint; 
typedef FACEMC::Quad<double,int,int,int> quad_double_int_int_int; 
typedef FACEMC::Quad<double,double,unsigned int,int> quad_double_double_uint_int; 
typedef FACEMC::Quad<double,double,int,unsigned int> quad_double_double_int_uint; 
typedef FACEMC::Quad<double,unsigned int,int,double> quad_double_uint_int_double; 
typedef FACEMC::Quad<double,int,unsigned int,double> quad_double_int_uint_double; 
typedef FACEMC::Quad<double,unsigned int,unsigned int,int> quad_double_uint_uint_int; 
typedef FACEMC::Quad<double,unsigned int,int,unsigned int> quad_double_uint_int_uint; 
typedef FACEMC::Quad<double,int,unsigned int,unsigned int> quad_double_int_uint_uint; 
typedef FACEMC::Quad<double,int,int,unsigned int> quad_double_int_int_uint; 
typedef FACEMC::Quad<double,int,unsigned int,int> quad_double_int_uint_int; 
typedef FACEMC::Quad<double,unsigned int,int,int> quad_double_uint_int_int; 
typedef FACEMC::Quad<double,int,int,int> quad_double_int_int_int; 
typedef FACEMC::Quad<FACEMC::Pair<unsigned int,unsigned int>,FACEMC::Pair<unsigned int,unsigned int>,FACEMC::Trip<double,double,double>,FACEMC::Quad<unsigned int,unsigned int,double,double> > quad_pair_pair_trip_quad; 

#endif // end HDF5_FILE_HANDLER_TESTING_TYPEDEFS_HPP

//---------------------------------------------------------------------------//
// end HDF5FileHandlerTestingTypedefs.hpp
//---------------------------------------------------------------------------//

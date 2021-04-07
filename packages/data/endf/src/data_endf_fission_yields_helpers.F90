!!---------------------------------------------------------------------------!!
!>
!> @file   data_endf_fission_yields_helpers.F90
!> @author Alex Bennett
!> @brief  ENDF fission yields table reading procedures
!>
!!---------------------------------------------------------------------------!!

module data_endf_fission_yields_helpers

  use iso_c_binding
  use utility_fortran_string_helpers

  implicit none

  private

  public :: skip_endf_fission_yields_first_header
  public :: read_endf_fission_yields_header
  public :: read_endf_fission_yields_data_header
  public :: read_endf_fission_yields_data

  contains

    !> Skip the table header.
    !> \details This function will go through the table header.
    !> The function assumes that the file is already open.
    subroutine skip_endf_fission_yields_first_header( file_id ) &
         bind(c, name='skipEndfFissionYieldsFirstHeader')
      use iso_c_binding

      character(len=80) :: line
      integer(c_int), intent(in), value :: file_id
      integer :: line_number
      logical :: end_of_header

      ! Initialize Variables
      line = ' '
      line_number = 0
      end_of_header = .false.

      ! Loop through the table header
      do while ( end_of_header .eqv. .false.)

        read(file_id,'(A80)') line
        read(line(76:80),'(I5)') line_number

        ! Exit out of loop when final line number is found
        if( line_number == 99999 ) end_of_header = .true.

      end do

    end subroutine skip_endf_fission_yields_first_header

    !> Reads the header
    !> \details This function will read the table header for the data set.
    !> The zaid and the number of energy points point are returned. This
    !> fucntion assumes the first header block has already been skipped.
    subroutine read_endf_fission_yields_header( file_id, zaid, number_energies ) &
         bind(c, name='readEndfFissionYieldsHeader')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: zaid
      integer(c_int), intent(inout) :: number_energies
      real :: zaid_double
      real :: dummy_variable

      ! Initialize Variables
      zaid = 0
      number_energies = 0
      zaid_double = 0.0

      ! Skip first header line
      read(file_id,*)

      ! Reads ZAID
      read(file_id,'(2es11.6,I11)') zaid_double, dummy_variable, number_energies
      zaid = int(zaid_double)

    end subroutine read_endf_fission_yields_header

    !> Reads the header of the current data set.
    !> \details This function will read the energy of the current data set and
    !> number of data sets.
    subroutine read_endf_fission_yields_data_header( file_id, number_data_sets, energy ) &
         bind(c, name='readEndfFissionYieldsDataHeader')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: number_data_sets
      real(c_double), intent(inout) :: energy
      real :: dummy_variable

      ! Initialize Variables
      number_data_sets = 0
      energy = 0.0

      read(file_id,'(5es11.6,I11)') energy,dummy_variable,&
           dummy_variable,dummy_variable,dummy_variable,number_data_sets

    end subroutine read_endf_fission_yields_data_header

    !> Reads the current data section
    !> \details This function will read the data of the current section.
    subroutine read_endf_fission_yields_data( file_id , number_data_sets , zaid , &
         meta_state , yield , std_yield ) bind(c, name='readEndfFissionYieldsData')

      character(len=80) :: line
      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in) :: number_data_sets
      integer(c_int), intent(inout) :: zaid(number_data_sets)
      integer(c_int), intent(inout) :: meta_state(number_data_sets)
      real :: zaid_double(number_data_sets)
      real :: meta_state_double(number_data_sets)
      real(c_double), intent(inout) :: yield(number_data_sets)
      real(c_double), intent(inout) :: std_yield(number_data_sets)

      integer :: i

      ! Initialize Variables
      zaid(:) = 0
      meta_state(:) = 0
      zaid_double(:) = 0.0
      meta_state_double(:) = 0.0
      yield(:) = 0.0
      std_yield(:) = 0.0

      ! Read the data
      read(file_id,'(6es11.6)') (zaid_double(i) , meta_state_double(i) , &
                      yield(i) , std_yield(i) , i = 1,number_data_sets)

      ! Convert doubles into integers.
      zaid(:) = int(zaid_double(:))
      meta_state(:) = int(meta_state_double(:))

    end subroutine read_endf_fission_yields_data

  end module data_endf_fission_yields_helpers

!!---------------------------------------------------------------------------!!
!! end data_endf_fission_yields_helpers.F90
!!---------------------------------------------------------------------------!!

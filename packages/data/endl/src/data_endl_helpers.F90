!!---------------------------------------------------------------------------!!
!>
!> @file   data_endl_helpers.F90
!> @author Luke Kersting
!> @brief  ENDL table reading procedures
!>
!!---------------------------------------------------------------------------!!

module data_endl_table_helpers

  use iso_c_binding
  use utility_fortran_string_helpers

  implicit none

  private

  public :: read_endl_table_header_line_1
  public :: read_endl_table_header_line_2
  public :: read_endl_table_two_column
  public :: read_endl_table_three_column
  public :: read_endl_table_four_column
  public :: read_epics_table_two_column
  public :: read_epics_table_three_column
  public :: read_epics_table_four_column
  public :: skip_endl_table
  public :: read_endl_table_size

  contains

    !> Read the first line of the table header
    !> \detials This function will read the zaids, the incident particle type,
    !> the outgoing particle type, the atomic mass (amu),
    !> the date the table was created and the interpolation flag.
    !> The table name and date arrays must have 10 elements. It is assumed
    !> that the desired table has already been found in the desired ENDL
    !> library.
    subroutine read_endl_table_header_line_1( file_id, zaids, &
         incident_particle_type, outgoing_particle_type, atomic_mass, &
         table_date, interpolation_flag, flag ) &
         bind(c, name='readENDLTableHeaderLine1')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: zaids
      integer(c_int), intent(inout) :: incident_particle_type
      integer(c_int), intent(inout) :: outgoing_particle_type
      real(c_double), intent(inout) :: atomic_mass
      integer(c_int), intent(inout) :: table_date
      integer(c_int), intent(inout) :: interpolation_flag
      integer(c_int), intent(inout) :: flag

      read(file_id, fmt='(I6,1X,I2,1X,I2,1X,E11.4,1X,I6,I1)', iostat=flag ) &
            zaids, incident_particle_type, outgoing_particle_type, &
            atomic_mass, table_date, interpolation_flag


    end subroutine read_endl_table_header_line_1

    !> Read the second line of the table header
    !> \details This function will read the reaction descriptor,
    !> reaction property, reaction modifier and subshell designator. It
    !> is assumed that the first line of the table has already been read.
    subroutine read_endl_table_header_line_2( file_id, reaction_descriptor, &
         reaction_property, reaction_modifier, subshell_designator, flag ) &
         bind(c, name='readENDLTableHeaderLine2')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: reaction_descriptor
      integer(c_int), intent(inout) :: reaction_property
      integer(c_int), intent(inout) :: reaction_modifier
      real(c_double), intent(inout) :: subshell_designator
      integer(c_int), intent(inout) :: flag

      read(file_id, fmt='(I2,2I3,13X,E11.4)', iostat=flag) reaction_descriptor,&
            reaction_property, reaction_modifier, subshell_designator

    end subroutine read_endl_table_header_line_2

    !> Read a two column ENDL table
    !> \details A two column table of data is read into two arrays, one for each
    !> column.
    subroutine read_endl_table_two_column( file_id, table_size, column_one, &
        column_two, flag ) bind(c, name='readENDLTableTwoColumn')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_size
      real(c_double), dimension(table_size), intent(inout) :: column_one
      real(c_double), dimension(table_size), intent(inout) :: column_two
      integer(c_int), intent(inout) :: flag

      integer :: i
      integer :: end_of_table

      do i = 1, table_size
        read(file_id, fmt='(2E11.6,49X, I1)', iostat=flag ) column_one(i), &
        column_two(i), end_of_table
      end do

      read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table

    end subroutine read_endl_table_two_column

    !> Read a two column ENDL EPICS2014 table
    !> \details A two column table of data is read into two arrays, one for each
    !> column.
    subroutine read_epics_table_two_column( file_id, table_size, column_one, &
        column_two, flag ) bind(c, name='readEPICSTableTwoColumn')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_size
      real(c_double), dimension(table_size), intent(inout) :: column_one
      real(c_double), dimension(table_size), intent(inout) :: column_two
      integer(c_int), intent(inout) :: flag

      integer :: i
      integer :: end_of_table

      do i = 1, table_size
        read(file_id, '(2E16.9,39X, I1)', iostat=flag ) column_one(i), &
        column_two(i), end_of_table
      end do

      read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table

    end subroutine read_epics_table_two_column

    !> Read a three column ENDL table
    !> \details A three column table of data is read into three arrays, one for
    !> each column.
    subroutine read_endl_table_three_column( file_id, table_size, column_one, &
        column_two, column_three, flag ) &
        bind(c, name='readENDLTableThreeColumn')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_size
      real(c_double), dimension(table_size), intent(inout) :: column_one
      real(c_double), dimension(table_size), intent(inout) :: column_two
      real(c_double), dimension(table_size), intent(inout) :: column_three
      integer(c_int), intent(inout) :: flag

      integer :: i
      integer :: end_of_table

      do i = 1, table_size
        read(file_id, fmt='(3E11.6,38X, I1)', iostat=flag ) column_one(i), &
        column_two(i), column_three(i), end_of_table
      end do

      read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table

    end subroutine read_endl_table_three_column

    !> Read a three column ENDL EPICS2014 table
    !> \details A three column table of data is read into three arrays, one for
    !> each column.
    subroutine read_epics_table_three_column( file_id, table_size, column_one, &
        column_two, column_three, flag ) &
        bind(c, name='readEPICSTableThreeColumn')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_size
      real(c_double), dimension(table_size), intent(inout) :: column_one
      real(c_double), dimension(table_size), intent(inout) :: column_two
      real(c_double), dimension(table_size), intent(inout) :: column_three
      integer(c_int), intent(inout) :: flag

      integer :: i
      integer :: end_of_table

      do i = 1, table_size
        read(file_id, fmt='(3E16.9,23X, I1)', iostat=flag ) column_one(i), &
        column_two(i), column_three(i), end_of_table
      end do

      read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table

    end subroutine read_epics_table_three_column

    !> Read a four column ENDL table
    !> \details A four column table of data is read into four arrays, one for
    !> each column.
    subroutine read_endl_table_four_column( file_id, table_size, column_one, &
        column_two, column_three, column_four, flag ) &
        bind(c, name='readENDLTableFourColumn')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_size
      real(c_double), dimension(table_size), intent(inout) :: column_one
      real(c_double), dimension(table_size), intent(inout) :: column_two
      real(c_double), dimension(table_size), intent(inout) :: column_three
      real(c_double), dimension(table_size), intent(inout) :: column_four
      integer(c_int), intent(inout) :: flag

      integer :: i
      integer :: end_of_table

      do i = 1, table_size
        read(file_id, fmt='(4E11.6,28X)', iostat=flag) column_one(i), &
        column_two(i), column_three(i), column_four(i)
      end do

      read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table

    end subroutine read_endl_table_four_column

    !> Read a four column ENDL EPICS2014 table
    !> \details A four column table of data is read into four arrays, one for
    !> each column.
    subroutine read_epics_table_four_column( file_id, table_size, column_one, &
        column_two, column_three, column_four, flag ) &
        bind(c, name='readEPICSTableFourColumn')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: table_size
      real(c_double), dimension(table_size), intent(inout) :: column_one
      real(c_double), dimension(table_size), intent(inout) :: column_two
      real(c_double), dimension(table_size), intent(inout) :: column_three
      real(c_double), dimension(table_size), intent(inout) :: column_four
      integer(c_int), intent(inout) :: flag

      integer :: i
      integer :: end_of_table

      do i = 1, table_size
        read(file_id, fmt='(4E16.9, 8X)', iostat=flag) column_one(i), &
        column_two(i), column_three(i), column_four(i)
      end do

      read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table

    end subroutine read_epics_table_four_column

    !> Skip a ENDL table
    !> \details A table of data is skipped over.
    subroutine skip_endl_table( file_id, table_size, flag ) &
         bind(c, name='skipENDLTable')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(inout) :: table_size
      integer(c_int), intent(inout) :: flag

      integer :: end_of_table

      table_size = 0
      do
        read(file_id, fmt='(71X,I1)',iostat=flag) end_of_table
        if (end_of_table.eq.1 ) exit
        table_size = table_size + 1
      end do

    end subroutine skip_endl_table

    !> Read the size of an ENDL table
    !> \details The size of a table is read
    subroutine read_endl_table_size( file_id, current_line, table_size, flag ) &
         bind(c, name='readENDLTableSize')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: current_line
      integer(c_int), intent(inout) :: table_size
      integer(c_int), intent(inout) :: flag

      integer :: table_position, end_of_table, i

      ! Find the number of lines in the table
      table_size = 0
      do
        read(file_id, fmt='(71X,I1)', iostat=flag ) end_of_table
        if (end_of_table.eq.1 ) exit
        table_size = table_size+1
      end do

      ! Move to the beginning of the file
      rewind(file_id)

      ! Move to the desired line
      do i = 1, current_line - 1
         read(file_id, fmt=*)
      end do

    end subroutine read_endl_table_size

  end module data_endl_table_helpers

!!---------------------------------------------------------------------------!!
!! end data_endl_table_helpers.F90
!!---------------------------------------------------------------------------!!

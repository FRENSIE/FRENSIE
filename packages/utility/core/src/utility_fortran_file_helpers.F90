!!---------------------------------------------------------------------------!!
!>
!> @file   utility_fortran_file_helpers.F90
!> @author Alex Robinson, Alex Bennett
!> @brief  Fortran File Helpers
!>
!!---------------------------------------------------------------------------!!

module utility_fortran_file_helpers

  use iso_c_binding
  use utility_fortran_string_helpers

  implicit none

  private

  public :: file_exists_using_fortran
  public :: file_is_readable_using_fortran
  public :: file_is_open_using_fortran
  public :: open_file_using_fortran
  public :: close_file_using_fortran
  public :: rewind_file_using_fortran
  public :: move_to_line_using_fortran
  public :: read_line_using_fortran

  contains


    !> Test if the file name exists
    !> \details The size variable should neglect the null character.
    function file_exists_using_fortran( file_name, file_name_size ) &
         result( file_existence_verified ) &
         bind(c, name='fileExistsUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_name_size
      character(kind=c_char,len=1), dimension(file_name_size), intent(in) :: &
           file_name

      character(file_name_size) :: file_name_fortran
      logical                   :: file_exists_test
      integer(c_int)            :: file_existence_verified ! return value

      ! Convert the file name character array to a fortran character array
      call convert_c_string_to_fortran( file_name, file_name_fortran, &
           file_name_size )

      ! Check if the file exists
      inquire(file=file_name_fortran, exist=file_exists_test)

      if(file_exists_test) then
         file_existence_verified = 1
      else
         file_existence_verified = 0
      end if

    end function file_exists_using_fortran

    !> Test if the file is readable
    function file_is_readable_using_fortran( file_name, file_name_size ) &
         result( file_is_readable_test) &
         bind(c, name='fileIsReadableUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_name_size
      character(kind=c_char,len=1), dimension(file_name_size), intent(in) :: &
           file_name

      character(file_name_size) :: file_name_fortran
      character(7)              :: read_message
      integer(c_int)            :: file_is_readable_test ! return value

      ! Convert the file name character array to a fortran character array
      call convert_c_string_to_fortran( file_name, file_name_fortran, &
           file_name_size )

      inquire(file=file_name_fortran, read=read_message)

      if(read_message(1:3) == 'YES') then
         file_is_readable_test = 1
      else
         file_is_readable_test = 0
      end if

    end function file_is_readable_using_fortran

    !> Check if a file is open
    function file_is_open_using_fortran( file_id ) &
         result( file_open_verified ) &
         bind(c, name='fileIsOpenUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id

      logical        :: file_open
      integer(c_int) :: file_open_verified ! return value

      ! Check if a file is open
      inquire(file_id, opened=file_open)

      if(file_open) then
         file_open_verified = 1
      else
         file_open_verified = 0
      end if

    end function file_is_open_using_fortran

    !> Opens the file
    !> \details Once the file has been opened, it will persist in this
    !> module (unit=1) until it is closed.
    subroutine open_file_using_fortran( file_name, file_name_size, file_id ) &
         bind(c, name='openFileUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_name_size
      character(kind=c_char,len=1), dimension(file_name_size), intent(in) :: &
           file_name
      integer(c_int), intent(in), value :: file_id
      integer :: success
      character(file_name_size) :: file_name_fortran


      ! Convert the file name character array to a fortran character array
      call convert_c_string_to_fortran( file_name, file_name_fortran, &
           file_name_size )

      ! Open the file
      open(file_id, file=file_name_fortran, status='old', action='read', &
                    position='rewind',form='formatted',iostat=success)

      if( success /= 0 ) then
         write(*,*) 'Error when opening file ' , file_name_fortran
         stop
      endif


    end subroutine open_file_using_fortran

    !> Close the file
    !> \details This will free the file unit number (file_id)
    subroutine close_file_using_fortran( file_id ) &
         bind(c, name='closeFileUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer :: success

      close(file_id,iostat=success)

      if( success /= 0 ) then
         write(*,*) 'Error when closing file attached to file id ' , file_id
         stop
      endif

    end subroutine close_file_using_fortran

    !> Rewind the file
    !> \details This will rewind the file back to the start line.
    !> It is assumed that the file has already been opened.
    subroutine rewind_file_using_fortran( file_id) &
         bind(c, name='rewindFileUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer :: success

      ! Move to the beginning of the file
      rewind(file_id,iostat=success)

      if( success /= 0 ) then
         write(*,*) 'Error when rewinding file attached to file id ' , file_id
         stop
      endif

    end subroutine rewind_file_using_fortran

    !> Move to the desired line number in the file
    !> \detials The indexing for the start line should follow FORTRAN
    !> conventions (start at 1). It is assumed that the desired file
    !> has already been opened
    subroutine move_to_line_using_fortran( file_id, start_line ) &
         bind(c, name='moveToLineUsingFortran')
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int), intent(in), value :: start_line

      integer(c_int) :: i

      ! Move to the beginning of the file
      rewind(file_id)

      ! Move to the desired line
      do i = 1, start_line - 1
         read(file_id, fmt=*)
      end do

    end subroutine move_to_line_using_fortran

    !> Read the entire line in the file at your current location.
    !> \details  Assumes file is already open.
    !> Intended use: The c string size should greater then or equal to 100.
    subroutine read_line_using_fortran( file_id, c_string, c_string_size) &
         bind(c, name="readLineUsingFortran")
      use iso_c_binding

      integer(c_int), intent(in), value :: file_id
      integer(c_int) :: string_size
      integer(c_int), intent(in), value :: c_string_size
      character(len=100) :: fortran_string
      character(kind=c_char,len=1), dimension(c_string_size), intent(inout) :: &
           c_string

      read(file_id,'(A)') fortran_string

      string_size = len_trim(fortran_string)

      if( c_string_size < string_size) then
         write(*,*) 'Error: Line length is too large for input string'
         stop
      endif

      call convert_fortran_string_to_c( fortran_string, c_string, string_size)

   end subroutine read_line_using_fortran

end module utility_fortran_file_helpers

!!---------------------------------------------------------------------------!!
!! end utility_fortran_file_helpers.F90
!!---------------------------------------------------------------------------!!

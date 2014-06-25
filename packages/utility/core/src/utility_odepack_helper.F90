!!---------------------------------------------------------------------------!!
!>
!> @file   utility_odepack_helper.F90
!> @author Alex Bennett
!> @brief  ODEPACK Helper
!>
!!---------------------------------------------------------------------------!!

module utility_odepack_helper

  use iso_c_binding

  implicit none

  private

  public :: lsodes_solver

  
  real(c_double), dimension(:,:), allocatable, save :: odepack_matrix


  contains

     ! Solves the set of differenetial equations using lsodes
     subroutine lsodes_solver( matrix, y, matrix_dimension, time, &
           relative_tol, absolute_tol, length_working_array) &
           bind(c, name='lsodesSolver')
      use iso_c_binding
  
        real(c_double), dimension(matrix_dimension,matrix_dimension), intent(in) :: matrix
        real(c_double), dimension(matrix_dimension), intent(inout) :: y
        real(c_double), intent(in) :: time
        real(c_double), intent(in) :: absolute_tol, relative_tol
 
        integer(c_int), intent(in), value :: matrix_dimension
        integer(c_int), intent(inout) :: length_working_array

        double precision :: t_init, tout
        double precision, dimension(:), allocatable :: rwork

        integer :: neq, itol, itask, istate, iopt, mf, liw
        integer, dimension(:), allocatable :: iwork

        if( allocated(odepack_matrix) ) then
             deallocate(odepack_matrix)
        endif

        ! Allocate global matrix
        allocate(odepack_matrix(1:matrix_dimension,1:matrix_dimension))

        ! Fill the global matrix
        odepack_matrix = matrix

        ! Length of rwork array
        ! rwork is the working array
        allocate(rwork(1:length_working_array))
     
        ! Length of iwork array
        ! iwork is the integer working array
        ! set to 30
        liw = 30
        allocate(iwork(liw))
     
        ! Number of differential equations
        neq = matrix_dimension
       
        ! Initial start time
        t_init = 0
    
        ! Final time
        tout = time
 
        ! Specifies tolerance equation
        itol = 1
     
        ! Set to 1 for normal computation
        itask = 1
       
        ! Output flag specifier
        istate = 1
     
        ! Set to 0 for normal inputs
        iopt = 0
     
        ! Method flag
        ! 10 for nonstiff method
        ! 121 for stiff method
        mf = 121
    
        call dlsodes(fex, neq, y, t_init, tout, itol, relative_tol, absolute_tol, &
                     itask, istate, iopt, rwork, length_working_array, iwork, &
                     liw, jex, mf)

        deallocate(odepack_matrix)

     end subroutine lsodes_solver
     
     subroutine fex(neq, t, y, ydot)
     ! Subroutine for the right hand side vector
     
        double precision :: t, y(2), ydot(2)
        integer, intent(inout) :: neq    

        ydot(:) = matmul(odepack_matrix(:,:),y(:))

     end subroutine fex
     
     subroutine jex(neq, t, y, j, ia, ja, pdj)
     ! Sets up the matrix
     
         double precision :: t, y(2), pdj(2)
         integer :: ia(*), ja(*)
         integer, intent(inout) :: neq, j 

         pdj(:) = odepack_matrix(:,j)

     end subroutine jex

  end module utility_odepack_helper

!!---------------------------------------------------------------------------!!
!! end utility_odepack_helper.F90
!!---------------------------------------------------------------------------!!

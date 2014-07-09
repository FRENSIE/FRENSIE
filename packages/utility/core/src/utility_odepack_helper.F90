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
        rwork(:) = 0.0 

        ! Length of iwork array
        ! iwork is the integer working array
        ! set to 30
        liw = 30
        allocate(iwork(liw))
        iwork(:) = 0  

        ! Increase maximum number of steps
        iwork(6) = 10000;  
 
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
        ! Set to 1 for option inputs
        iopt = 1
     
        ! Method flag
        ! 10 for nonstiff method
        ! 121 for stiff method
        mf = 121
    
        call dlsodes(fex, neq, y, t_init, tout, itol, relative_tol, absolute_tol, &
                     itask, istate, iopt, rwork, length_working_array, iwork, &
                     liw, jex, mf)

        if( istate < 0 ) then
            write(*,*) 'Error: Matrix was not solved correctly using DLSODES.'
            write(*,*) 'Error Code: istate = ' , istate
        endif

        deallocate(odepack_matrix)

     end subroutine lsodes_solver
     
     subroutine fex(neq, t, y, ydot)
     ! Subroutine for the right hand side vector
     
        double precision :: t, y(neq), ydot(neq)
        integer, intent(inout) :: neq    

        ydot(:) = matmul(odepack_matrix(:,:),y(:))

     end subroutine fex
     
     subroutine jex(neq, t, y, j, ia, ja, pdj)
     ! Sets up the matrix
     
         double precision :: t, y(neq), pdj(neq)
         integer :: ia(*), ja(*)
         integer, intent(inout) :: neq, j 

         pdj(:) = odepack_matrix(:,j)

     end subroutine jex

  end module utility_odepack_helper

!!---------------------------------------------------------------------------!!
!! end utility_odepack_helper.F90
!!---------------------------------------------------------------------------!!

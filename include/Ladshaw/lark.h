//----------------------------------------
//  Created by Austin Ladshaw on 10/14/14
//  Copyright (c) 2014
//	Austin Ladshaw
//	All rights reserved
//----------------------------------------

#ifndef LARK_HPP_
#define LARK_HPP_

#include "macaw.h"
#include <float.h>

//Data structure for the construction of the Krylov subspaces for a linear system
typedef struct
{
    int k;              // Desired size of the Krylov subspace
    int iter;           // Actual size of the Krylov subspace
    
    double beta;        // Normalization parameter
    double hp1;         // Additional row element of H (separate storage for holding)
	
	bool Output = true; //True = print messages to console
	
  	std::vector< Matrix<double> > Vk; // (N) x (k) orthonormal vector basis stored as a vector of column matrices
    Matrix<double> Hkp1;        	// (k+1) x (k) upper Hessenberg matrix
    Matrix<double> yk;          	// (k) x (1) vector search direction
    Matrix<double>e1;          	// (k) x (1) orthonormal vector with 1 in first position
    Matrix<double> w;           	// (N) x (1) interim result of the matrix_vector multiplication
  	Matrix<double> v;				// (N) x (1) holding cell for the column entries of Vk and other interims
  	Matrix<double> sum;				// (N) x (1) running sum of subspace vectors for use in altering w
	
}ARNOLDI_DATA;

//Data structure for implementation of the Restarted GMRES algorithm with Left Preconditioning
typedef struct
{
    int restart = 20;    		//Restart parameter - default = min(vector_size,20)
    int maxit = 0;          	//Maximum allowable iterations - default = min(vector_size,1000)
    int iter = 0;           	//Number of iterations needed for convergence
  	int steps = 0;				//Total number of gmres iterations and krylov iterations
	
	double tol_rel = 1e-6;		//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;		//Absolution tolerance for convergence - default = 1e-6
  	double res;					//Absolution redisual norm of the linear system
    double relres;      		//Relative residual norm of the linear system
    double relres_base; 		//Initial residual norm of the linear system
	double bestres;				//Best found residual norm of the linear system
	
	bool Output = true;			//True = print messages to console
    
    Matrix<double> x;           		//Solution to the linear system
	Matrix<double> bestx;				//Best found solution to the linear system
  	Matrix<double> r;					//Residual vector for the linear system
	
    ARNOLDI_DATA arnoldi_dat; //Data structure for the kyrlov subspace
    
}GMRESLP_DATA;

//Data structure for the Restarted GMRES algorithm with Right Preconditioning
typedef struct
{
	int restart = 20;			//Restart parameter - default = min(20,vector_size)
	int maxit = 0;				//Maximum allowable outer iterations
	int iter_outer = 0;			//Total number of outer iterations
	int iter_inner = 0;			//Total number of inner iterations
	int iter_total = 0;			//Total number of overall iterations
	
	double tol_rel = 1e-6;		//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;		//Absolute tolerance for convergence - default = 1e-6
	double res;					//Absolute residual norm for linear system
	double relres;				//Relative residual norm for linear system
	double relres_base;			//Initial residual norm of the linear system
	double bestres;				//Best found residual norm of the linear system
	
	bool Output = true;			//True = print messages to console
	
	Matrix<double> x;					//Solution to the linear system
	Matrix<double> bestx;				//Best found solution to the linear system
	Matrix<double> r;					//Residual vector for the linear system
	
	//NOTE: The value of k changes meaning these vectors and matrices grow in size
	std::vector< Matrix<double> > Vk;						// (N x k) orthonormal vector basis
	std::vector< std::vector< double > > H;		// (k+1 x k) upper Hessenberg storage matrix
	std::vector< std::vector< double > > H_bar;	// (k+1 x k) Factorized matrix
	std::vector< double > y;					// (k x 1) Vector search direction
	std::vector< double > e0;					// (k+1 x 1) Normalized vector with residual info
	std::vector< double > e0_bar;				// (k+1 x 1) Factorized normal vector
	
	Matrix<double> w;           	// (N) x (1) interim result of the matrix_vector multiplication
	Matrix<double> v;				// (N) x (1) holding cell for the column entries of Vk and other interims
	Matrix<double> sum;				// (N) x (1) running sum of subspace vectors for use in altering w
	
}GMRESRP_DATA;

//Data structure for implementation of the PCG algorithms for symmetric linear systems
typedef struct
{
  	int maxit = 0;			//Maximum allowable iterations - default = min(vector_size,1000)
  	int iter = 0;				//Actual number of iterations taken
	
  	double alpha;				//Step size for new solution
  	double beta;				//Step size for new search direction
	double tol_rel = 1e-6;		//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;		//Absolution tolerance for convergence - default = 1e-6
	double res;					//Absolute residual norm
	double relres;				//Relative residual norm
	double relres_base;			//Initial residual norm
	double bestres;				//Best found residual norm
	
	bool Output = true;			//True = print messages to console
	
  	Matrix<double> x;						//Solution to the linear system
	Matrix<double> bestx;					//Best found solution to the linear system
  	Matrix<double> r;						//Residual vector for the linear system
  	Matrix<double> r_old;					//Previous residual vector
  	Matrix<double> z;						//Preconditioned residual vector (result of precon function)
  	Matrix<double> z_old;					//Previous preconditioned residual vector
  	Matrix<double> p;						//Search direction
  	Matrix<double> Ap;						//Result of matrix-vector multiplication
	
}PCG_DATA;

//Data structure for the implementation of the BiCGSTAB algorithm for non-symmetric linear systems
typedef struct
{
	int maxit = 0;			//Maximum allowable iterations - default = min(2*vector_size,1000)
	int iter = 0;				//Actual number of iterations
	bool breakdown;				//Boolean to determine if the method broke down
	
	double alpha;				//Step size parameter for next solution
	double beta;				//Step size parameter for search direction
	double rho;					//Scaling parameter for alpha and beta
	double rho_old;				//Previous scaling parameter for alpha and beta
	double omega;				//Scaling parameter and additional step length
	double omega_old;			//Previous scaling parameter and step length
	double tol_rel = 1e-6;		//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;		//Absolution tolerance for convergence - default = 1e-6
	double res;					//Absolute residual norm
	double relres;				//Relative residual norm
	double relres_base;			//Initial residual norm
	double bestres;				//Best found residual norm
	
	bool Output = true;			//True = print messages to console
	
	Matrix<double> x;					//Solution to the linear system
	Matrix<double> bestx;				//Best found solution to the linear system
	Matrix<double> r;					//Residual vector for the linear system
	Matrix<double> r0;					//Initial residual vector
	Matrix<double> v;					//Search direction for p
	Matrix<double> p;					//Search direction for updating
	Matrix<double> y;					//Preconditioned search direction
	Matrix<double> s;					//Residual updating vector
	Matrix<double> z;					//Preconditioned residual updating vector
	Matrix<double> t;					//Search direction for resdidual updates
	
}BiCGSTAB_DATA;

//Data structure for the implementation of the CGS algorithm for non-symmetric linear systems
typedef struct
{
	int maxit = 0;			//Maximum allowable iterations - default = min(2*vector_size,1000)
	int iter = 0;				//Actual number of iterations
	bool breakdown;				//Boolean to determine if the method broke down
	
	double alpha;				//Step size parameter for next solution
	double beta;				//Step size parameter for search direction
	double rho;					//Scaling parameter for alpha and beta
	double sigma;				//Scaling parameter and additional step length
	double tol_rel = 1e-6;		//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;		//Absolution tolerance for convergence - default = 1e-6
	double res;					//Absolute residual norm
	double relres;				//Relative residual norm
	double relres_base;			//Initial residual norm
	double bestres;				//Best found residual norm
	
	bool Output = true;			//True = print messages to console
	
	Matrix<double> x;					//Solution to the linear system
	Matrix<double> bestx;				//Best found solution to the linear system
	Matrix<double> r;					//Residual vector for the linear system
	Matrix<double> r0;					//Initial residual vector
	Matrix<double> u;					//Search direction for v
	Matrix<double> w;					//Updates sigma and u
	Matrix<double> v;					//Search direction for x
	Matrix<double> p;					//Preconditioning result for w, z, and matvec for Ax
	Matrix<double> c;					//Holds the matvec result between A and p
	Matrix<double> z;					//Full search direction for x
	
}CGS_DATA;

//Data structure for the implementation of the GCR algorithm for non-symmetric linear systems
typedef struct
{
	int restart = 20;			//Restart parameter for outer iterations - default = 20
	int maxit = 0;				//Maximum allowable outer iterations
	int iter_outer = 0;			//Number of outer iterations taken
	int iter_inner = 0;			//Number of inner iterations taken
	int total_iter = 0;			//Total number of iterations taken
	bool breakdown = false;		//Boolean to determine if a step has failed
	
	double alpha;				//Inner iteration step size
	double beta;				//Outer iteration step size
	double tol_rel = 1e-6;		//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;		//Absolute tolerance for convergence - default = 1e-6
	double res;					//Absolute residual norm for linear system
	double relres;				//Relative residual norm for linear system
	double relres_base;			//Initial residual norm of the linear system
	double bestres;				//Best found residual norm of the linear system
	
	bool Output = true;			//True = print messages to the console
	
	Matrix<double> x;					//Solution to the linear system
	Matrix<double> bestx;				//Best found solution to the linear system
	Matrix<double> r;					//Residual Vector
	Matrix<double> c_temp;				//Temporary c vector to be updated
	Matrix<double> u_temp;				//Temporary u vector to be updated
	std::vector<Matrix<double> > u;		//Vector span for updating x
	std::vector<Matrix<double> > c;		//Vector span for updating r
	
}GCR_DATA;

//Data structure for the implementation of GCR with Nested GMRES preconditioning (Named GMRESR from literature)
typedef struct
{
	int gcr_restart = 20;		//Number of GCR restarts (default = 20, max = N)
	int gcr_maxit = 0;			//Number of GCR iterations
	int gmres_restart = 0;		//Number of GMRES restarts (max = 20)
	int gmres_maxit = 0;		//Number of GMRES iterations (max = 5)
	int N;						//Dimension of the linear system
	int total_iter;				//Total GMRES and GCR iterations
	int iter_outer;				//Total GCR iterations
	int iter_inner;				//Total GMRES iterations
	
	bool GCR_Output = true;		//True = print GCR messages
	bool GMRES_Output = false;	//True = print GMRES messages
	
	double gmres_tol = 0.1;		//Tolerance relative to GCR iterations
	double gcr_rel_tol = 1e-6;	//Relative outer residual tolerance
	double gcr_abs_tol = 1e-6;	//Absolute outer residual tolerance
	
	Matrix<double> arg;			//Argument matrix passed between preconditioner and iterator
	
	GCR_DATA gcr_dat;			//Data structure for the outer GCR steps
	GMRESRP_DATA gmres_dat;		//Data structure for the inner GMRES steps
	
	//User supplied matrix-vector product function
	int (*matvec) (const Matrix<double> &x, Matrix<double> &Ax, const void *matvec_data);
	//Optional user supplied terminal preconditioner
	int (*terminal_precon) (const Matrix<double> &r, Matrix<double> &p, const void *precon_data);
	
	const void *matvec_data;	//Data structure for the user's matvec function
	const void *term_precon;	//Data structure for the user's terminal preconditioner
	
}GMRESR_DATA;

//Data structure for the implementation of a Picard or Fixed-Point iteration for non-linear systems
typedef struct
{
	int maxit = 0;				//Maximum allowable iterations - default = min(3*vec_size,1000)
	int iter = 0;					//Actual number of iterations
	
	double tol_rel = 1e-6;			//Relative tolerance for convergence - default = 1e-6
	double tol_abs = 1e-6;			//Absolution tolerance for convergence - default = 1e-6
	double res;						//Residual norm of the iterate
	double relres;					//Relative residual norm of the iterate
	double relres_base;				//Initial residual norm
	double bestres;					//Best found residual norm
	
	bool Output = true;			//True = print messages to console
	
	Matrix<double> x0;						//Previous iterate solution vector
	Matrix<double> bestx;					//Best found solution vector
	Matrix<double> r;						//Residual of the non-linear system
	
}PICARD_DATA;

//Data structure for the implementation of Backtracking Linesearch
typedef struct
{
	double alpha = 1e-4;				//Scaling parameter for determination of search step size
	double rho = 0.1;					//Scaling parameter for to change step size by
	double lambdaMin=DBL_EPSILON;	//Smallest allowable step length
	double normFkp1;					//New residual norm of the Newton step
	
	bool constRho = false;				//True = use a constant value for rho
	
	Matrix<double> Fk;							//Old residual vector of the Newton step
	Matrix<double> xk;							//Old solution vector of the Newton step
	
}BACKTRACK_DATA;

//List of macro definitions for linear solver types in PJFNK
#define GMRESLP 0
#define PCG 1
#define BiCGSTAB 2
#define CGS 3
#define FOM 4
#define GMRESRP 5
#define GCR 6
#define GMRESR 7

//Data structure for the implementation of the PJFNK algorithm for non-linear systems
typedef struct
{
	int nl_iter = 0;         	//Number of non-linear iterations
	int l_iter = 0;				//Number of linear iterations
	int nl_maxit = 0;			//Maximum allowable non-linear steps
	int linear_solver = -1;		//Flag to denote which linear solver to use - default = PJFNK Chooses
	
	double nl_tol_abs = 1e-6;   //Absolute Convergence tolerance for non-linear system - default = 1e-6
	double nl_tol_rel = 1e-6;	//Relative Convergence tol for the non-linear system - default = 1e-6
	double lin_tol = 0.1;		//Tolerance of the linear solver - default = 0.1 (Inexact Newton)
	double nl_res;				//Absolute redidual norm for the non-linear system
	double nl_relres;       	//Relative residual for the non-linear system
	double nl_res_base;     	//Initial residual norm for the non-linear system
	double nl_bestres;			//Best found residual norm
	double eps=sqrt(DBL_EPSILON);//Value of epsilon used jacvec - default = sqrt(DBL_EPSILON)
	
	bool NL_Output = true;		//True = print PJFNK messages to console
	bool L_Output = false;		//True = print Linear messages to console
	bool LineSearch = false;	//True = use Backtracking Linesearch for global convergence
	bool Bounce = false;		//True = allow Linesearch to go outside local well, False = Strict local convergence
	
	Matrix<double> F;					//Stored fuction evaluation at x (also the residual)
	Matrix<double> Fv;					//Stored function evaluation at x+eps*v
	Matrix<double> v;					//Stored vector of x+eps*v
	Matrix<double> x;					//Current solution vector for the non-linear system
	Matrix<double> bestx;				//Best found solution vector to the non-linear system
	
	//The PJFNK implementation will choose the linear method best suited for your problem
	GMRESLP_DATA gmreslp_dat;   	//Data structure for the GMRESLP method (solver = 0)
	PCG_DATA pcg_dat;				//Data structure for the PCG method (solver = 1)
	BiCGSTAB_DATA bicgstab_dat;		//Data structure for the BiCGSTAB method (solver = 2)
	CGS_DATA cgs_dat;				//Data structure for the CGS method (solver = 3)
	GMRESRP_DATA gmresrp_dat;		//Data structure for the GMRESRP method (solver = 5)
	GCR_DATA gcr_dat;				//Data structure for the GCR method (solver = 6)
	GMRESR_DATA gmresr_dat;			//Data structure for the GMRESR method (solver = 7)
	
	
	BACKTRACK_DATA backtrack_dat;	//Data structure for the Backtracking Linesearch algorithm
	
	//------------Below is a list of pointers the user must provide---------------
	
	//Data structure pointer for user's residual data
	const void *res_data;
	//Data structure pointer for user's preconditioning data
	const void *precon_data;
	//Function pointer for the user's function F(x) using there data
	int (*funeval) (const Matrix<double> &x, Matrix<double> &F, const void *res_data);
	//Function pointer for the user's preconditioning function for the linear system
	int (*precon) (const Matrix<double> &r, Matrix<double> &p, const void *precon_data);
	
}PJFNK_DATA;

//Data structures used by examples to test the algorithms of LARK
typedef struct
{
    Matrix<double> M;               //(N) x (N) coefficient matrix
    Matrix<double> b;               //(N) x (1) right side vector solution
    
}EX01_DATA;

typedef struct
{
  	Matrix<double> M;               //(N) x (N) coefficient matrix
	Matrix<double> b;               //(N) x (1) right side vector solution
	
}EX02_DATA;

typedef struct
{
  	Matrix<double> M;               //(N) x (N) coefficient matrix
  	Matrix<double> b;               //(N) x (1) right side vector solution
	
}EX04_DATA;

typedef struct
{
	double h;				//Mesh size for non-linear PDE
	double k;				//Scaling factor for non-linear portion of PDE
	int N;					//Number of nodes in mesh
	Matrix<double> x;				//Nx1 solution vector
	Matrix<double> M;				//NxN preconditioning matrix
	Matrix<double> s;				//Search direction for Picard
	Matrix<double> p;				//Conditioned search direction
}EX09_DATA;

typedef struct
{
	int N;					//Number of nodes in the mesh
	int m;					//Dimensional length for natural laplacian
	Matrix<double> b;				//Boundary Conditions for the problem
}EX15_DATA;

//Below are the actual functions available in LARK
int update_arnoldi_solution(Matrix<double>& x, Matrix<double>& x0, ARNOLDI_DATA *arnoldi_dat);

int arnoldi( int (*matvec) (const Matrix<double>& v, Matrix<double> &w, const void *data),
            int (*precon) (const Matrix<double>& b, Matrix<double> &p, const void *data),
            Matrix<double> &r0, ARNOLDI_DATA *arnoldi_dat, const void *matvec_data,
		    const void *precon_data );

int gmresLeftPreconditioned( int (*matvec) (const Matrix<double>& v, Matrix<double> &w, const void *data),
							int (*precon) (const Matrix<double>& b, Matrix<double> &p, const void *data),
							Matrix<double> &b, GMRESLP_DATA *gmreslp_dat, const void *matvec_data,
							const void *precon_data );

int fom( int (*matvec) (const Matrix<double>& v, Matrix<double> &w, const void *data),
		int (*precon) (const Matrix<double>& b, Matrix<double> &p, const void *data),
		Matrix<double> &b, GMRESLP_DATA *gmreslp_dat, const void *matvec_data,
		const void *precon_data );

int gmresRightPreconditioned( int (*matvec) (const Matrix<double>& v, Matrix<double> &w, const void *data),
							 int (*precon) (const Matrix<double>& b, Matrix<double> &p, const void *data),
							 Matrix<double> &b, GMRESRP_DATA *gmresrp_dat, const void *matvec_data,
							 const void *precon_data );

int pcg( int (*matvec) (const Matrix<double>& p, Matrix<double> &Ap, const void *data),
		int (*precon) (const Matrix<double>& r, Matrix<double> &z, const void *data),
		Matrix<double> &b, PCG_DATA *pcg_dat, const void *matvec_data,
		const void *precon_data );

int bicgstab( int (*matvec) (const Matrix<double>& p, Matrix<double> &Ap, const void *data),
			 int (*precon) (const Matrix<double>& r, Matrix<double> &z, const void *data),
			 Matrix<double> &b, BiCGSTAB_DATA *bicg_dat, const void *matvec_data,
			 const void *precon_data );

int cgs( int (*matvec) (const Matrix<double>& p, Matrix<double> &Ap, const void *data),
		int (*precon) (const Matrix<double>& r, Matrix<double> &z, const void *data),
		Matrix<double> &b, CGS_DATA *cgs_dat, const void *matvec_data,
		const void *precon_data );

int gcr( int (*matvec) (const Matrix<double>& x, Matrix<double> &Ax, const void *data),
		int (*precon) (const Matrix<double>& r, Matrix<double> &Mr, const void *data),
		Matrix<double> &b, GCR_DATA *gcr_dat, const void *matvec_data,
		const void *precon_data );

int gmresPreconditioner( const Matrix<double>& r, Matrix<double> &Mr, const void *data);

int gmresr( int (*matvec) (const Matrix<double>& x, Matrix<double> &Ax, const void *data),
		   int (*terminal_precon) (const Matrix<double>& r, Matrix<double> &Mr, const void *data),
		   Matrix<double> &b, GMRESR_DATA *gmresr_dat, const void *matvec_data,
		   const void *term_precon_data );

int picard( int (*res) (const Matrix<double>& x, Matrix<double> &r, const void *data),
		   int (*evalx) (const Matrix<double>& x0, Matrix<double> &x, const void *data),
		   Matrix<double> &x, PICARD_DATA *picard_dat, const void *res_data,
		   const void *evalx_data);

int jacvec( const Matrix<double>& v, Matrix<double>& Jv, const void *data);

int backtrackLineSearch( int (*feval) (const Matrix<double>& x, Matrix<double> &F, const void *data),
						Matrix<double> &Fkp1, Matrix<double> &xkp1, Matrix<double> &pk, double normFk,
						BACKTRACK_DATA *backtrack_dat, const void *feval_data);

int pjfnk( int (*res) (const Matrix<double>& x, Matrix<double> &F, const void *data),
		  int (*precon) (const Matrix<double>& r, Matrix<double>& p, const void *data),
		  Matrix<double> &x, PJFNK_DATA *pjfnk_dat, const void *res_data,
		  const void *precon_data );

#endif

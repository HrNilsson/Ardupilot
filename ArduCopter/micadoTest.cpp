/**********************************************************************************

     This is an Example Call of MIDACO 4.0
     -------------------------------------

     MIDACO solves the general Mixed Integer Non-Linear Program (MINLP):


       Minimize     F(X)           where X(1,...N-NI)   is *CONTINUOUS*
                                   and   X(N-NI+1,...N) is *DISCRETE* 

       Subject to:  G_j(X)  =  0   (j=1,...ME)     Equality Constraints
                    G_j(X) >=  0   (j=ME+1,...M) Inequality Constraints

       And bounds:  XL <= X <= XU


     The problem statement of this example is given below in the function
     'problem_function( f, g, x)'. You can use this example as a template to 
     run MIDACO on your own problem. In order to do so: Replace the objective 
     function 'F' (and in case the constraints 'G') given below with your own 
     problem functions. Then simply follow the instruction steps 1 to 3 given 
     in this file. 

     See the MIDACO Header and MIDACO User Guide for more information.

     Author(C): Dr. Martin Schlueter           
                Information Initiative Center,
                Division of Large Scale Computing Systems,
                Hokkaido University, Japan.

        Email:  info@midaco-solver.com
        URL:    http://www.midaco-solver.com

***********************************************************************************/



#include <AP_Math/midaco.h>

long int iw[1000]; double x[100],xl[100],xu[100],g[100],rw[10000],param[9],f[1];

long int p,n,ni,m,me,i,iflag,istop,liw,lrw; //,maxeval,printeval,save2file,maxtime

void problem_function( double *F, double *G, double *X);
/**********************************************************************************/
//extern"C"{int midaco(long int*,long int*,long int*,long int*,long int*,double*,
  //                   double*,double*,double*,double*,long int*,long int*,double*,
    //                 double*,long int*,long int*,long int*,char*);
/**********************************************************************************/
//int midaco_print(int,long int,long int,long int*,long int*,double*,double*,
  //               double*,double*,double*,long int,long int,long int,long int,
    //             double*,long int,long int,double*,long int,char*); }
/**********************************************************************************/
void midacoTest()
{   
    using namespace Midaco;
/*  *******************************************************************************/
    /* Variable Declarations (Pre-Allocation of X and Workspace RW and IW) */

    /* Specify MIDACO License-Key */    
    char key[] = "MIDACO_LIMITED_VERSION___[CREATIVE_COMMONS_BY-NC-ND_LICENSE]";
/*  *******************************************************************************/

/*  STEP 1.A: Define problem dimensions  */
/*  ***********************************  */ 
    n  = 4; /* Number of variables (in total) */
    ni = 0; /* Number of integer variables (0 <= ni <= n) */
    m  = 3; /* Number of constraints (in total) */
    me = 2; /* Number of equality constraints (0 <= me <= m) */

/*  STEP 1.B: Define lower and upper bounds 'xl' & 'xu'  */
/*  ***************************************************  */
    for( i=0; i<n; i++)
    {
      xl[i] = 1.0;
      xu[i] = 4.0;
    }

/*  STEP 1.C: Define starting point 'X'  */
/*  ***********************************  */
    for( i=0; i<n; i++)
    { 
      x[i] = xl[i]; /* Here for example: starting point = lower bounds */
    } 
/*  *******************************************************************************/

/*  STEP 2.A: Define stopping criteria */
/*  ********************************** */
    //maxeval = 10000;     /* Maximum number of function evaluation (e.g. 1000000) */
    //maxtime = 60*60*24;  /* Maximum time limit in Seconds (e.g. 1 Day = 60*60*24) */

/*  STEP 2.B: Choose printing options  */
/*  *********************************  */
    //printeval = 1000;  /* Print-Frequency for current best solution (e.g. 1000) */
    //save2file = 1;     /* Save SCREEN and SOLUTION to TXT-files [ 0=NO/ 1=YES] */
    
/*  *******************************************************************************/

/*  STEP 3: Choose MIDACO parameters  (ONLY FOR ADVANCED USERS)   
    ********************************/
    param[0] =  0.0;   /*  ACCURACY      (default value is 0.001)      */
    param[1] =  0.0;   /*  RANDOM-SEED   (e.g. 1, 2, 3,... 1000)       */
    param[2] =  0.0;   /*  FSTOP                                       */
    param[3] =  0.0;   /*  AUTOSTOP      (e.g. 1, 5, 20, 100,... 500)  */ 
    param[4] =  0.0;   /*  ORACLE                                      */
    param[5] =  0.0;   /*  FOCUS         (e.g. +/- 10, 500,... 100000) */
    param[6] =  0.0;   /*  ANTS          (e.g. 2, 10, 50, 100,... 500) */
    param[7] =  0.0;   /*  KERNEL        (e.g. 2, 5, 15, 30,... 100)   */
    param[8] =  0.0;   /*  CHARACTER                                   */

/*  Note: The default value for all parameters is 0.   */
/*        See the MIDACO User Manual for more details. */

/*  *******************************************************************************/
         
/*  Call MIDACO by Reverse Communication  */
   
/*  *******************************************************************************/
    /* Workspace declarations */
    p=1;lrw=sizeof(rw)/sizeof(double);liw=sizeof(iw)/sizeof(long int);    
    /* Print midaco headline and basic information */
    //midaco_print(1,printeval,save2file,&iflag,&istop,&*f,&*g,&*x,&*xl,&*xu,
      //           n,ni,m,me,&*rw,maxeval,maxtime,&*param,1,&*key);
    while(istop==0) /*~~~ Start of the reverse communication loop ~~~*/
    {   /* Evaluate objective function */
        problem_function( &*f, &*g, &*x);                   
        /* Call MIDACO */
        midaco(&p,&n,&ni,&m,&me,&*x,&*f,&*g,&*xl,&*xu,&iflag,
               &istop,&*param,&*rw,&lrw,&*iw,&liw,&*key);                  
        /* Print current best solution after every *printeval* evaluation */            
        //midaco_print(2,printeval,save2file,&iflag,&istop,&*f,&*g,&*x,&*xl,&*xu,
          //           n,ni,m,me,&*rw,maxeval,maxtime,&*param,1,&*key);
    } /*~~~End of the reverse communication loop ~~~*/    
/*  *******************************************************************************/
    /* Independent check of MIDACO solution */
    problem_function( &*f, &*g, &*x);
    /* Print the solution */                
    //midaco_print(3,printeval,save2file,&iflag,&istop,&*f,&*g,&*x,&*xl,&*xu,
      //           n,ni,m,me,&*rw,maxeval,maxtime,&*param,1,&*key);
/*  *******************************************************************************/
/*  printf("\n Pause"); getchar(); (Note: getchar() needs #include <stdlib.h>) */ 
   // return 0;
}/* END MAIN PROGRAM */




/***********************************************************************/
/*  Very small example problem (replace F and G with your own problem) */
/***********************************************************************/
void problem_function(double *fp, double *gp, double *xp)
{
    /* Objective function value F(X) (denoted here as f[0]) */
    fp[0] = (xp[0]-1.0)*(xp[0]-1.0)
         + (xp[1]-2.0)*(xp[1]-2.0)
         + (xp[2]-3.0)*(xp[2]-3.0)
         + (xp[3]-4.0)*(xp[3]-4.0)
         + 1.23456789;

    /* Equality constraints G(X) = 0 MUST COME FIRST in g[0:me-1] */
    gp[0] = xp[0] - 1.0;
    gp[1] = xp[1] - 2.0;
    /* Inequality constraints G(X) >= 0 MUST COME SECOND in g[me:m-1] */
    gp[2] = xp[2] - 2.666666666;
}
/* END OF FILE */



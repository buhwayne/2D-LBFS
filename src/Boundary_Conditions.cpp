#include "Boundary_Conditions.h"
#include <stdlib.h>


Boundary_Conditions::Boundary_Conditions(int num_x_nodes, int num_y_nodes)
{
    //ctor

    int total_nodes = num_x_nodes * num_y_nodes;


      // if boundary condition is present for this cell face
      bc = new bool [total_nodes +1];
        if (bc==NULL) exit (1);
     bc_include = new bool [total_nodes +1];
        if (bc_include==NULL) exit (1);
      rho = new double [total_nodes +1];
        if (rho==NULL) exit (1);


      u = new double [total_nodes +1];
        if (u==NULL) exit (1);
      v = new double [total_nodes +1];
        if (v==NULL) exit (1);


        /// integer describing the boundary condition type

        // 1: Dirichlet Boundary Condition i.e. constant value at boundary
        // 2: Neumann boundary condition i.e. gradient = fixed value.
        // 3: Periodic Boundary Condition

     type_rho = new int [total_nodes +1];
        if (type_rho==NULL) exit (1);

     type_vel = new int [total_nodes +1];
        if (type_vel==NULL) exit (1);


     // node u[n] which will source u[0]
     periodic_node = new int [total_nodes +1];
        if (periodic_node==NULL) exit (1);
    neighbour = new int[total_nodes +1];
        if(neighbour == NULL) exit (1);
}

Boundary_Conditions::~Boundary_Conditions()
{
    //dtor
    delete [] (bc);
    bc = NULL;

    delete [] (bc_include);
    bc_include = NULL;
    delete []  (u);
    u = NULL;
    delete []  (v);
    v = NULL;
    delete []  (rho);
    rho = NULL;


    delete [] type_rho;
    type_rho = NULL;


    delete [] type_vel;
    type_vel = NULL;


    delete [] periodic_node;
    periodic_node = NULL;

    delete [] neighbour;
    neighbour = NULL;
}

void Boundary_Conditions::assign_boundary_conditions(int num_x, int num_y, quad_bcs_plus _bc,int testcase){

    /// this method should be user defined to reflect the geometry of the problem
    /// currently set up for quad problem domain-> potential overload of this operator.
    int t = 0;



        //special periodic boundary conditions for Taylor Vortex Flow
        //consists of two layers of ghost cells

    if ( testcase == 3){
          for( int j=0; j < num_y; j++){
            for (int i =0; i < num_x; i++){
                  // default status
                bc[t] = false;
                bc_include[t] = true;

                     // West boundary outer layer
                if( i ==0 || i ==1){
                    bc[t] = true;
                    type_vel[t] = _bc.w_type_vel;
                    type_rho[t] = _bc.w_type_rho;
                    rho[t] = _bc.w_rho;
                    u[t] = _bc.w_u;
                    v[t] = _bc.w_v;

                    periodic_node[t] = (num_x-4 ) + t;
                    neighbour[t] = t + 1;

                    if (j ==0 && i ==0){
                        bc_include[t] = false;
                    }else if( j == (num_y-1) && i ==0){
                        bc_include[t] = false;
                    }else{
                        bc_include[t] = true;
                    }


                    /// east boundary
                }else if( i == (num_x -1) || i == (num_x -2)){
                    bc[t] = true;
                    type_vel[t] = _bc.e_type_vel;
                    type_rho[t] = _bc.e_type_rho;
                    rho[t] = _bc.e_rho;
                    u[t] = _bc.e_u;
                    v[t] = _bc.e_v;


                    periodic_node[t] = t - (num_x-4  ) ;
                    neighbour[t] = t - 1;

                    if (j ==0 && i ==(num_x -1) ){
                        bc_include[t] = false;
                    }else if( j == (num_y-1) && i ==0){
                        bc_include[t] = false;
                    }else{
                        bc_include[t] = true;
                    }


                // south boundary
                }else if(j == 0 || j == 1){
                    bc[t] = true;
                    type_vel[t] = _bc.s_type_vel;
                    type_rho[t] = _bc.s_type_rho;
                    rho[t] = _bc.s_rho;
                    u[t] = _bc.s_u;
                    v[t] = _bc.s_v;

                    periodic_node[t] = t + (num_y-4) *num_x;
                    neighbour[t] = t + num_x;

                    bc_include[t] = true;

                //north boundary

                }else if( j == (num_y-1) || j == (num_y -2)){
                    bc[t] = true;
                    type_vel[t] = _bc.n_type_vel;
                    type_rho[t] = _bc.n_type_rho;
                    rho[t] = _bc.n_rho;
                    u[t] = _bc.n_u;
                    v[t] = _bc.n_v;

                    periodic_node[t] = t - (num_y-4)* num_x;
                    neighbour[t] = t - num_x;
                    bc_include[t] = false;

                }else {
                    bc[t] = false;
                }

               t++;



            }
          }
    }else{


        //lid driven cavity conditions
        for( int j=0; j < num_y; j++){
            for (int i =0; i < num_x; i++){


                // default status
                bc[t] = false;
                bc_include[t] = true;

                // West boundary
                if( i ==0){
                    bc[t] = true;
                    rho[t] = _bc.w_rho;
                    u[t] = _bc.w_u;
                    v[t] = _bc.w_v;
                    type_vel[t] = _bc.w_type_vel;
                    type_rho[t] = _bc.w_type_rho;

                    periodic_node[t] = (num_x-2) + t;
                    neighbour[t] = t + 1;

                    if (j ==0){
                        bc_include[t] = false;
                    }else if( j == (num_y-1)){
                        bc_include[t] = false;
                    }else{
                        bc_include[t] = true;
                    }


                    /// east boundary
                }else if( i == (num_x -1)){
                    bc[t] = true;
                    rho[t] = _bc.e_rho;
                    u[t] = _bc.e_u;
                    v[t] = _bc.e_v;
                    type_vel[t] = _bc.e_type_vel;
                    type_rho[t] = _bc.e_type_rho;


                    periodic_node[t] = t - (num_x-2) ;
                    neighbour[t] = t - 1;
                    bc_include[t] = false;

                // south boundary
                }else if(j == 0){
                    bc[t] = true;
                    rho[t] = _bc.s_rho;
                    u[t] = _bc.s_u;
                    v[t] = _bc.s_v;
                    type_vel[t] = _bc.s_type_vel;
                    type_rho[t] = _bc.s_type_rho;

                    periodic_node[t] = t + (num_y-2) *num_x;
                    neighbour[t] = t + num_x;

                    bc_include[t] = true;

                //north boundary

                }else if( j == (num_y-1)){
                    bc[t] = true;
                    rho[t] = _bc.n_rho;
                    u[t] = _bc.n_u;
                    v[t] = _bc.n_v;
                    type_vel[t] = _bc.n_type_vel;
                    type_rho[t] = _bc.n_type_rho;

                    periodic_node[t] = t - (num_y-2)* num_x;
                    neighbour[t] = t - num_x;
                    bc_include[t] = false;

                }else {
                    bc[t] = false;
                }

                t++;
            }


    }

    }

}
void Boundary_Conditions::assign_boundary_conditions(int num_x, int num_y, quad_bcs _bc){


    /// this method should be user defined to reflect the geometry of the problem
    /// currently set up for quad problem domain-> potential overload of this operator.
    int t = 0;

    //lid driven cavity conditions

        for( int j=0; j < num_y; j++){
            for (int i =0; i < num_x; i++){
             // West boundary
            if( i ==0){
                bc[t] = true;
                rho[t] = _bc.w_rho;
                u[t] = _bc.w_u;
                v[t] = _bc.w_v;
                type_vel[t] = _bc.w_type;
                type_rho[t] = _bc.w_type;

                periodic_node[t] = (num_x-2)  + t;
                neighbour[t] = t + num_y;

                 if (j ==0){
                    bc_include[t] = false;
                }else if( j == (num_y-1)){
                    bc_include[t] = false;
                }else{
                    bc_include[t] = true;
                }


            }else{
                bc[t] =false;
            }

            // east boundary
            if ( i == (num_x -1)){
                bc[t] = true;
                rho[t] = _bc.e_rho;
                u[t] = _bc.e_u;
                v[t] = _bc.e_v;
                type_vel[t] = _bc.e_type;
                type_rho[t] = _bc.e_type;


                periodic_node[t] = t - (num_x-2) ;
                neighbour[t] = t - num_y;

                bc_include[t] = true;

            }else {
                    bc[t] = false;
            }

            // south boundary
            if(j == 0){
                bc[t] = true;
                rho[t] = _bc.s_rho;
                u[t] = _bc.s_u;
                v[t] = _bc.s_v;
                type_vel[t] = _bc.s_type;
                type_rho[t] = _bc.s_type;

                periodic_node[t] = t + (num_y-2) *num_x;
                neighbour[t] = t + 1;

                bc_include[t] = true;


            }else{
                bc[t] = false;
            }

            // north boundary
            if( j == (num_y-1)){
                bc[t] = true;
                rho[t] = _bc.n_rho;
                u[t] = _bc.n_u;
                v[t] = _bc.n_v;
                type_vel[t] = _bc.n_type;
                type_rho[t] = _bc.n_type;

                periodic_node[t] = t - (num_y-2)*num_x;
                neighbour[t] = t - 1;

                bc_include[t] = false;
            }else {
                bc[t] = false;
            }


            t++;
        }


    }

}

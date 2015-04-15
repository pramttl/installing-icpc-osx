#include <stdio.h>
#include <omp.h>
 
int main(void)
{
    // Number of cores available
    int ncores = omp_get_num_procs( );
    omp_set_num_threads(omp_get_num_procs( ));

    #pragma omp parallel default(none)
    {
        printf("Hello, World, from thread #%d ! \n" , omp_get_thread_num( ));
    }
}

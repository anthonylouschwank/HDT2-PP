  GNU nano 6.2                      HDT2_2.c
/*----------------------------------------------------------------------
* Universidad del Valle de Guatemala
* Curso: CC3169 - Computacion Paralela y Distribuida
* Ejercicio: Hoja de Trabajo 02 - Introduccion a Open MPI
* Inciso 2
* Descripcion: simulacion del envio del reporte diario de ventas
* desde una sucursal hacia la oficina central.
*----------------------------------------------------------------------*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;

    float ventas;
    int pedidos;

    // Inicializa el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtener el identificador del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el numero total de procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verificar que existan al menos dos procesos
    if (size < 2) {
        if (rank == 0) {
            printf("Este programa requiere al menos 2 procesos.\n");
        }

        MPI_Finalize();
       return 0;
}

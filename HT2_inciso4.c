/*----------------------------------------------------------------------
 * Universidad del Valle de Guatemala
 * Curso:     CC3169 - Computacion Paralela y Distribuida
 * Ejercicio: Hoja de Trabajo 02 - Introduccion a Open MPI
 *            Inciso 4
 * Descripcion: simulacion de la distribucion de pedidos desde la
 *              Oficina Central hacia las sucursales.
 *
 *              Cada proceso MPI representa una ubicacion diferente:
 *                  rank 0 -> Oficina central
 *                  rank 1 -> Sucursal 1
 *                  rank 2 -> Sucursal 2
 *                  rank 3 -> Sucursal 3
 *
 *              La Oficina Central posee una lista de pedidos y
 *              distribuye una parte a cada proceso utilizando
 *              MPI_Scatter().
 *
 *              Modificacion: cada ubicacion recibe dos datos en lugar
 *              de uno (cantidad de pedidos y empleados disponibles).
 *              El arreglo se organiza por pares consecutivos y se usa
 *              sendcount = recvcount = 2.
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    int size;
    // Pares consecutivos por ubicacion: {pedidos, empleados}
    //   posiciones [0,1] -> rank 0, [2,3] -> rank 1, ...
    int datos[8];
    int datos_recibidos[2];    // [0] = pedidos, [1] = empleados

    // Inicializa el entorno MPI
    MPI_Init(&argc, &argv);

    // Obtener el identificador del proceso actual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtener el numero total de procesos que participan
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Este ejercicio requiere exactamente 4 procesos
    if (size != 4) {

        if (rank == 0) {
            printf("Este programa requiere exactamente 4 procesos.\n");
        }

        MPI_Finalize();
        return 0;
    }

    // La Oficina Central define los pedidos y empleados de cada ubicacion
    if (rank == 0) {

        datos[0] = 120;  datos[1] = 12;   // Oficina Central
        datos[2] = 95;   datos[3] = 8;    // Sucursal 1
        datos[4] = 140;  datos[5] = 15;   // Sucursal 2
        datos[6] = 110;  datos[7] = 10;   // Sucursal 3

        printf("Oficina Central: distribuyendo pedidos...\n");
    }

    // Distribuir dos valores consecutivos del arreglo a cada proceso
    MPI_Scatter(
        datos,
        2,
        MPI_INT,
        datos_recibidos,
        2,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    // Cada proceso muestra los valores que recibio
    if (rank == 0) {
        printf("Oficina Central: %d pedidos asignados, %d empleados disponibles.\n",
               datos_recibidos[0], datos_recibidos[1]);
    } else {
        printf("Sucursal %d: %d pedidos asignados, %d empleados disponibles.\n",
               rank, datos_recibidos[0], datos_recibidos[1]);
    }

    // Finaliza correctamente el entorno MPI
    MPI_Finalize();

    return 0;
}
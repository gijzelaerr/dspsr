//-*-C++-*-

#ifndef __MPITrans_h
#define __MPITrans_h

#include <mpi.h>

#define ACTIVATE_MPI 1
#include "dsp/MPIRoot.h"


namespace dsp {

  //! Loads BitSeries data using the MPI communications protocol
  class MPITrans : public MPIRoot {
    
  public:
    
    //! Construct from MPI_Bcast
    MPITrans (MPI_Comm comm);

    //! Send the next block using MPI_Isend
    void send_data (BitSeries* data, int dest);
    
    //! Load the next block using MPI_Irecv
    void load_data (BitSeries* data);

    //! when mpi_rank == mpi_root, load data from input
    void load_data ();

    //! Returns the rank of the next node ready to receive data
    int next_destination ();

    //! request data from the root
    void request_data ();

  };

}


#endif // !defined(____MPITrans_h)

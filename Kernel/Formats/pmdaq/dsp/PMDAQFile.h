//-*-C++-*-

#ifndef __PMDAQFile_h
#define __PMDAQFile_h

#include "environ.h"

#include "dsp/File.h"
#include "dsp/Observation.h"
#include "dsp/PMDAQ_Observation.h"

namespace dsp {

  //! Loads TimeSeries data from a PMDAQ data file
  class PMDAQFile : public File 
  {
  public:
   
    //! Construct and open file
    PMDAQFile (const char* filename=0);

    //! Returns true if filename appears to name a valid PMDAQ file
    bool is_valid (const char* filename,int NOT_USED=-1) const;

    //! Set which band the bandwidth/centre frequency will be extracted from
    void set_using_second_band(bool _using_second_band)
    { using_second_band = _using_second_band; }
    
    //! Inquire which band the bandwidth/centre frequency will be extracted from
    bool get_using_second_band(){ return using_second_band; } 

  protected:

    //! Open the file
    void open_file (const char* filename);

    // Insert PMDAQ-specific entries here.
    // Overload these because of fortran 4-byte headers and footers to blocks

    //! Loads 'bytes' bytes of data into 'buffer'
    virtual int64 load_bytes (unsigned char * buffer, uint64 bytes);

    //! Seeks over 'bytes' bytes of data
    virtual int64 seek_bytes (uint64 bytes);

    //! Initialises 'pmdaq_header' with the header info
    static int get_header (char* pmdaq_header, const char* filename); 

  private:

    //! If user has use of the second observing band on disk, modify the bandwidth and centre frequency of output
    void modify_info(PMDAQ_Observation* data);

    // Sets the ndat of the file from the filesize
    void work_out_ndat(const char* filename);

    // Helper functions for load_bytes():

    //! Returns how many bytes can be loaded before hitting the end of the file 
    uint64 bytes_available();

    //! Loads in the first partial chunk
    uint64 load_partial_chunk(unsigned char*& buffer, uint64 bytes);
    //! Loads in a full chunk
    uint64 load_chunk(unsigned char*& buffer);
    //! Loads in the last partial chunk
    uint64 load_last_chunk(unsigned char*& buffer, uint64 bytes);

    //! Seeks over header/trailer
    void seek_ahead();

    //! Sets the end_of_data flag
    int64 cleanup(uint64 bytes_loaded);

    // Member functions:

    //! What band the cf/bandwidth should be extracted from
    bool using_second_band;

    //! Should be the same number as return value from lseek(fd,0,SEEK_CUR)- ie number of bytes from start of file
    int64 absolute_position;

  };

}

#endif // !defined(__PMDAQFile_h)
  

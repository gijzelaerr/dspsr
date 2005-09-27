//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Kernel/Classes/dsp/WeightedTimeSeries.h,v $
   $Revision: 1.9 $
   $Date: 2005/09/27 08:15:34 $
   $Author: wvanstra $ */

#ifndef __WeightedTimeSeries_h
#define __WeightedTimeSeries_h

#include "dsp/TimeSeries.h"

namespace dsp {
  
  //! Container of weighted time-major order floating point data.
  /* The WeightedTimeSeries class contains floating point data that
     may be flagged as bad in the time domain. */
  class WeightedTimeSeries : public TimeSeries {

  public:

    //! Default constructor
    WeightedTimeSeries ();

    //! Copy constructor
    WeightedTimeSeries (const WeightedTimeSeries&);

    //! Set this equal to copy
    virtual WeightedTimeSeries& operator = (const WeightedTimeSeries& copy);

    //! Add each value in data to this
    virtual WeightedTimeSeries& operator += (const WeightedTimeSeries& data);

    //! Set the number of time samples per weight
    /*! Set ndat_per_weight to zero to effect no weighting of data */
    void set_ndat_per_weight (unsigned ndat_per_weight);

    //! Get the number of time samples per weight
    unsigned get_ndat_per_weight () const { return ndat_per_weight; }

    //! Set the number of polarizations with independent weights
    void set_npol_weight (unsigned npol_weight);

    //! Get the number of polarizations with independent weights
    unsigned get_npol_weight () const { return npol_weight; }

    //! Set the number of frequency channels with independent weights
    void set_nchan_weight (unsigned nchan_weight);

    //! Get the number of frequency channels with independent weights
    unsigned get_nchan_weight () const { return nchan_weight; }

    //! Cloner (calls new)
    virtual WeightedTimeSeries* clone();

    //! Returns a null-instantiation (calls new)
    virtual WeightedTimeSeries* null_clone();

    //! Copy the configuration of another WeightedTimeSeries instance
    virtual void copy_configuration (const Observation* copy);

    //! Copy the data of another WeightedTimeSeries instance
    virtual void copy_data (const TimeSeries* data, 
			    uint64 idat_start = 0, uint64 ndat = 0);

    //! Allocate the space required to store nsamples time samples.
    virtual void resize (uint64 nsamples);
    
    //! Offset the base pointer by offset time samples
    virtual void seek (int64 offset);

    //! Set all values to zero
    virtual void zero ();

    //! Maybe copy the weights from copy
    void copy_weights (const Observation* copy);

    //! For each zero weight, sets all weights to zero
    void mask_weights ();

    //! Check that each floating point value is zeroed if weight is zero
    void check_weights ();

    //! Set all weights to one
    void neutral_weights ();

    //! Get the number of weights
    uint64 get_nweights () const;

    //! Get the number of weights required for a given number of samples
    uint64 get_nweights (uint64 nsample) const;

    //! Get the offset into the current weight of the first time sample
    uint64 get_weight_idat () const { return weight_idat; }

    //! Get the number of zero weights in the ichan == ipol == 0 array
    uint64 get_nzero () const;

    //! Get the weights array for the specfied polarization and frequency
    unsigned* get_weights (unsigned ichan=0, unsigned ipol=0);

    //! Get the weights array for the specfied polarization and frequency
    const unsigned* get_weights (unsigned ichan=0, unsigned ipol=0) const;

    //! Flag all weights in corrupted transforms
    void convolve_weights (unsigned nfft, unsigned nkeep);

    //! Scrunch the weights
    void scrunch_weights (unsigned nscrunch);

  protected:

    //! Number of polarizations with independent weights
    unsigned npol_weight;

    //! Number of frequency channels with independent weights
    unsigned nchan_weight;

    //! The number of time samples per weight
    unsigned ndat_per_weight;

    //! Copy the weights from copy
    void copy_weights (const WeightedTimeSeries* copy,
		       uint64 idat_start = 0, uint64 copy_ndat = 0);

    //! Resize the weights array
    void resize_weights (uint64 nsamples);

  private:

    //! The base of the weights buffer
    unsigned* base;

    //! The pointer to the current start of weights buffer (can be seeked)
    unsigned* weights;

    //! The index into the first weight of the first time sample
    uint64 weight_idat;

    //! The size of the buffer
    uint64 weight_size;

    //! The size of each division of the buffer
    uint64 weight_subsize;
  };

}

#endif


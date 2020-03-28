#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "signum_func_impl.h"

namespace gr {
  namespace dpd {

    signum_func::sptr
    signum_func::make()
    {
      return gnuradio::get_initial_sptr
        (new signum_func_impl());
    }

    /*
     * The private constructor
     */
    signum_func_impl::signum_func_impl()
      : gr::sync_block("signum_func",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    signum_func_impl::~signum_func_impl()
    {
    }

    int
    signum_func_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      for (int i = 0; i < noutput_items; i++)
        out[i] = ( in[i] > 0.0 ) ? 1.0 : -1.0;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dpd */
} /* namespace gr */


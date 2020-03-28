#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "vec_vec_mul_impl.h"
#include <armadillo>
#define COPY_MEM false  // Do not copy vectors into separate memory
#define FIX_SIZE true // Keep dimensions of vectors constant

using namespace arma;
namespace gr {
  namespace dpd {

    vec_vec_mul::sptr
    vec_vec_mul::make(const std::vector<gr_complex> &const_vec, int vec_len)
    {
      return gnuradio::get_initial_sptr
        (new vector_vector_multiply_impl(const_vec, vec_len));
    }

    /*
     * The private constructor
     */
    vec_vec_mul_impl::vec_vec__multiply_impl(const std::vector<gr_complex> &const_vec, int vec_len)
      : gr::sync_block("vec_vec_mul",
              gr::io_signature::make(1, 1, vec_len*sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
              d_vec_len(vec_len)
    {
      arma_const_vec = conv_to< cx_rowvec >::from(const_vec);      
    }

    /*
     * Our virtual destructor.
     */
    vector_vector_multiply_impl::~vector_vector_multiply_impl()
    {
    }

    int
    vector_vector_multiply_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      for (int item = 0; item < noutput_items; item++) 
      {
        cx_fcolvec input_vec( (gr_complex *) input_items[0]+item*d_vec_len, d_vec_len, COPY_MEM, FIX_SIZE );
        out[item] = as_scalar(arma_const_vec*input_vec);               
      }
      // Multiplying Using armadillo column-vector 
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dpd */
} /* namespace gr */

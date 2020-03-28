#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stream_to_vec_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace blocks {

stream_to_vector::sptr stream_to_vec::make(size_t itemsize, size_t nitems_per_block)
{
    return gnuradio::get_initial_sptr(
        new stream_to_vector_impl(itemsize, nitems_per_block));
}

stream_to_vec_impl::stream_to_vec_impl(size_t itemsize, size_t nitems_per_block)
    : sync_decimator("stream_to_vec",
                     io_signature::make(1, 1, itemsize),
                     io_signature::make(1, 1, itemsize * nitems_per_block),
                     nitems_per_block)
{
}

int stream_to_vec_impl::work(int noutput_items,
                                gr_vector_const_void_star& input_items,
                                gr_vector_void_star& output_items)
{
    size_t block_size = output_signature()->sizeof_stream_item(0);

    const char* in = (const char*)input_items[0];
    char* out = (char*)output_items[0];

    memcpy(out, in, noutput_items * block_size);

    return noutput_items;
}

} /* namespace blocks */
} /* namespace gr */

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import dpd_swig as dpd

class qa_signum_func (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_square_ff(self):
        src_data = (1,2,18,-4,-1)
        expected_result = (1.0,1.0,1.0,-1.0,-1.0)
        src = blocks.vector_source_f(src_data)
        sqr = dpd.signum_func()
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 5)

if __name__ == '__main__':
    gr_unittest.run(qa_signum_func, "qa_signum_func.xml")
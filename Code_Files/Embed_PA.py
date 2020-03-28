"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import numpy as np
from gnuradio import gr


class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """Embedded Python Block example - a simple multiply const"""

    def __init__(self, order1=np.complex(10,0),order3=np.complex(0.0142,-0.0818),order5=np.complex(0,0),order7=np.complex(0,0),order9=np.complex(0,0)):  # only default arguments here
        """arguments to this function show up as parameters in GRC"""
        gr.sync_block.__init__(
            self,
            name="Wiener Power Amplifier",   # will show up in GRC
            in_sig=[np.complex64],
            out_sig=[np.complex64]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.order1 = order1
        self.order3 = order3
        self.order5 = order5
        self.order7 = order7
        self.order9 = order9

    def work(self, input_items, output_items):
        """evaluate the non-linear amplification by odd order coefficients"""
        output_items[0][:] = input_items[0] * self.order1+((input_items[0])**3)*self.order3 +((input_items[0])**5)*self.order5+((input_items[0])**7)*self.order7+((input_items[0])**9)*self.order9
        return len(output_items[0])
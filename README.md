# Keyword Spotting Decoder

Here is an implementation of Keyword Spotting (KWS) decoder in C++ language to speed up decoding in python using pybind11.
KWS indeed is a simple beam search that searches for the desired keywords in a output that is come from acoustic model (AM).
A sample of an acoustic model output is as follows, for the wav file wherein the speaker says: "AT ANY SECOND AND JUST GO AND THEN WATCH EVERYBODY'S MOUTH DROP I WILL NOT BE OVER"

![Sample acoustic model output](tests/data/output.png)

You can see the few first output timesteps of the acoustic model for the given text (for the sake of visibility).

## How to install

the module is available on pypi, so `pip install kws-decoder` is just fine.

### (Optional) run sample python implementation codes

The original code was developed on python. In order to the original implementation, install package like this:
`pip install kws-decoder[ext]`

It installs `pygtrie`, `torch`, and `tqdm`, that are necessary to run original implementation of the beam search algorithm.
Then you can run the script with original python implementation located in test folder, "beam_search.py" more specifically.

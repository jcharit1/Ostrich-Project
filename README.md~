# Ostrich Project

## Description

The objective of the program is to ascertain how well the pattern of information acquisition by a specific investor concerning the valuation of his portfolio (decisions to "look" or "not look") can be replicated by the actions of a hypothetical rational investor with loss averse preferences and rational expectations in the context of a simple dynamic economic model. The notion of rational expectations is the (very strong) assumption that the model agent knows the precise probability distributions governing all economic quantities of interest to him.

As a rational investor, he uses this knowledge to make information acquisition decisions in order to maximize the discounted present value of future utility where, as noted in the introduction to the text, his period utility function is defined over portfolio gains and losses relative to a benchmark rather than the more customary consumption. The present note describes the strategy employed in the numerical solution to this problem. 

Underlying our numerical strategy is the perspective that the individual investor whose behavior we wish to match has held his investor account for a very long time and plans to continue this status for the indefinite future. In effect we are attempting to match the “slice-out-of-time” information acquisition behavior for a specific investor, whom we view as an infinite horizon utility maximizer, for the period 2007-2008.

The structure of the numerical algorithm is the first to use straightforward dynamic programming to compute the option decision rule for the hypothetical investor. When the hypothetical investor is confronted with the same rate of return phenomenon as his actual counterpart, and applies his derived optimal decision rule, he generates a series of hypothetical “look” and “not look” actions which can be  compared to the actual observed decisions of the investor under study. A simple goodness of fit measure is proposed. Some basic knowledge of dynamic programming is assumed.

## Installation

Instructions assume you are using a Linux machine:

1. Download and unzip the repository or run `git clone https://github.com/jcharit1/Ostrich-Project.git`
2. Within the "Ostrich-Project" directory run the following in the command line:
	1. `make clean -f makefile`
	2. `make all -f makefile` 
3. Run test cases using fake data with the following commands: `make test_1 -f makefile` or `make test_2 -f makefile`

Unfortunately, the real data cannot be shared. Please email me at jc4144@columbia.edu to discuss repurposing this code for your research.

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Credits

TODO: Write credits

## License

MIT License

Copyright (c) 2016 Jimmy Charité

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

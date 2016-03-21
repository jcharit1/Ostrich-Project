# Ostrich Project

Code for investigating the Ostrich Effect. 

## Authors
Nachum Sicherman

Carson Family Professor of Business
Graduate School of Business 
Columbia University
New York, NY 10027
ns38@columbia.edu

John Donaldson
Mario J. Gabelli Professor of Finance
Graduate School of Business 
Columbia University
New York, NY 10027
jd34@gsb.columbia.edu

Jimmy Charite
Research Consultant
Graduate School of Business 
Columbia University
New York, NY 10027
jc4144@columbia.edu 

## Description

The objective of the program is to ascertain how well the pattern of information acquisition by a specific investor concerning the valuation of his portfolio (decisions to "look" or "not look") can be replicated by the actions of a hypothetical rational investor with loss averse preferences and rational expectations in the context of a simple dynamic economic model. The notion of rational expectations is the (very strong) assumption that the model agent knows the precise probability distributions governing all economic quantities of interest to him.

As a rational investor, he uses this knowledge to make information acquisition decisions in order to maximize the discounted present value of future utility where, as noted in the introduction to the text, his period utility function is defined over portfolio gains and losses relative to a benchmark rather than the more customary consumption. The present note describes the strategy employed in the numerical solution to this problem. 

Underlying our numerical strategy is the perspective that the individual investor whose behavior we wish to match has held his investor account for a very long time and plans to continue this status for the indefinite future. In effect we are attempting to match the “slice-out-of-time” information acquisition behavior for a specific investor, whom we view as an infinite horizon utility maximizer, for the period 2007-2008.

The structure of the numerical algorithm is the first to use straightforward dynamic programming to compute the option decision rule for the hypothetical investor. When the hypothetical investor is confronted with the same rate of return phenomenon as his actual counterpart, and applies his derived optimal decision rule, he generates a series of hypothetical “look” and “not look” actions which can be  compared to the actual observed decisions of the investor under study. A simple goodness of fit measure is proposed. Some basic knowledge of dynamic programming is assumed.

See 'doc/Description of Program One' for a full description of the model.

## Installation

TODO: Describe the installation process

## Usage

TODO: Write usage instructions

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History

TODO: Write history

## Credits

TODO: Write credits

## License

TODO: Write license

# sbus protocol (FrSky, Futaba) decoder for Saleae Analyzer
This decoder is based on the sample analyzer from Saleae. It would be a fork, but just like on a fancy table, you are allowed only one fork per meal on github.
[https://github.com/saleae/SampleAnalyzer](https://github.com/saleae/SampleAnalyzer)

This sbus decoder is based and tested on the FrSky receiver, paired with the Taranis 9d transmitter. To my knowledge, it should work with other FrSky receivers, and possibly with Futaba receivers as well.

The decoder allows to decode any selected channel from a captured communication. The other channels and any other data in the communication is ignored, for ease of reading, exporting and processing the data.

Feel free to use for whatever you need this.

# Building:
* Follow the instruction from the Saleae Sample Analyzer (linked above).

# Installing (with or without building) Linux and macOS only!:
* Download only the /Release folder
* In Logic, press "options" -> "preferences" -> "developer"
* Add that folder to the path

# Using:
* After installing, add the "sbus" decoder.
* Leave the baud rate at 100,000, unless your receiver works at a different speed
* Pick an RC channel (example, typically 3=throttle, 5=arm state etc)
* The data will be shown ranging from 1000 to 2000. 1500 is "center stick".
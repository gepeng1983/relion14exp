
#include "src/helix.h"
#include "src/image.h"
#include "src/args.h"
#include "src/ml_optimiser.h"

FileName fnin, fnout;

double bfactor, apix;


int main(int argc, char ** argv)
{
	IOParser parser;

	try {
	
		parser.setCommandLine(argc, argv);
	
		parser.addSection("Input / output");
		fnin=parser.getOption("--i", "Input volume", "");
		fnout=parser.getOption("--o", "Output volume", "");
		bfactor=textToFloat(parser.getOption("--bfactor", "B-Factor", "40"));
		apix=textToFloat(parser.getOption("--angpix", "Pixel size in Angstrom per pixel", "1.00"));


		Image<double> im;

		im.read(fnin);

		im.data.setXmippOrigin();

		test1(im.data, bfactor, apix);
		

	
		im.write(fnout);
	}	

	catch (RelionError XE)
	{
		parser.writeUsage(std::cerr);
		std::cerr << XE;
		exit(1);
	}

	exit(0);

}



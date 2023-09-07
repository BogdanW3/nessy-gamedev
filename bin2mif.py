import sys
import numpy as np

from argparse import ArgumentParser
from argparse import RawDescriptionHelpFormatter

DEBUG = 0


def parsefile(filename, wordsize):
    dump = []
    read_data = None
    with open(filename, "rb") as inputfile:
        read_data = np.fromfile(inputfile, dtype=np.uint8)

    wordsizeinbytes = wordsize / 8
    wordcounter = 0
    count = 0
    tempstring = ""
    for byte in read_data:
        s = hex(byte)[2:]
        if len(s) % 2 != 0:
            s = "0" + s
        tempstring += s
        count = (count + 1) % wordsizeinbytes

        if count == 0:
            dump.append(tempstring)
            tempstring = ""
            wordcounter += 1
    return [dump, wordcounter]


def writefile(filename, wordsize, data):
    f = open(filename, "w")

    f.write("WIDTH=")
    f.write(str(wordsize))
    f.write(";\n")
    f.write("DEPTH=")
    f.write(str(len(data)))
    f.write(";\n\n")

    f.write("ADDRESS_RADIX=HEX;\nDATA_RADIX=HEX;\n\nCONTENT BEGIN\n")

    for i in range(0, len(data)):
        f.write("\t")
        f.write(hex(i)[2:])
        f.write("   :   ")
        f.write(data[i])
        f.write(";\n")

    f.write("END;\n")


def main(argv=None):
    if argv is None:
        argv = sys.argv
    else:
        sys.argv.extend(argv)

    try:
        # Setup argument parser
        parser = ArgumentParser(formatter_class=RawDescriptionHelpFormatter)
        parser.add_argument(
            dest="inputfile",
            help="path to input file  [default: %(default)s]",
            metavar="inputfile",
        )
        parser.add_argument(
            dest="outputfile",
            help="path to output file  [default: %(default)s]",
            metavar="outputfile",
        )
        parser.add_argument(
            dest="wordsize",
            help="size of wordsize  [default: %(default)s]",
            metavar="wordsize",
            nargs="?",
            default=8,
        )

        # Process arguments
        args = parser.parse_args()

        inputfile = args.inputfile
        outputfile = args.outputfile
        wordsize = int(args.wordsize)

        print("input:", inputfile)
        print("output:", outputfile)
        print("wordsize:", wordsize)

        result = parsefile(inputfile, wordsize)
        writefile(outputfile, wordsize, result[0])
        return 0
    except KeyboardInterrupt:
        return 0
    except Exception as e:
        if DEBUG:
            raise (e)
        return 2


if __name__ == "__main__":
    sys.exit(main())

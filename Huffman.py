from node import *


if __name__ == "__main__":
    freq = {
        "N":4/15,
        "G":2/15,
        "U":2/15,
        "Y":1/15,
        "E":1/15,
        "D":1/15,
        "I":1/15,
        "H":1/15,
        "T":1/15,
        "R":1/15
    }

    nodes = NodeList(freq)
    nodes.makeTree()

    print(nodes.trace())

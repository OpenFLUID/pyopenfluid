# -*- coding: utf-8 -*-

__author__  = "Jean-Christophe Fabre"
__email__   = "jean-christophe.fabre@inra.fr"
__license__ = "see LICENSE file"


import unittest
from PyOpenFLUID import OpenFLUID
import os


###############################################
###############################################


class MainTest(unittest.TestCase):

  def testDataset(self):
    path = os.path.join(os.path.dirname(os.path.realpath(__file__)),"6fields_3reaches.IN")
    data = OpenFLUID.openDataset(path)
    OpenFLUID.printSimulationInfo(data)


###############################################


  def testProject(self):
    path = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.PRJ")
    data = OpenFLUID.openProject(path)
    OpenFLUID.printSimulationInfo(data)


###############################################
###############################################


if __name__ == '__main__':
  unittest.main()

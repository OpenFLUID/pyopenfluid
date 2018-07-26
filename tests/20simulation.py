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

  def testSimulation(self):
    pathIN = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.IN")
    pathOUT = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.OUT")
    OpenFLUID.setCurrentOutputDir(pathOUT)
    data = OpenFLUID.openDataset(pathIN)
#    self.assertEqual(OpenFLUID.getSimulationOutputDir(data),pathOUT)
    self.assertRaises(Exception,OpenFLUID.runSimulation(data))


###############################################


  def testVerboseSimulation(self):
    pathIN = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.IN")
    pathOUT = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.verbose.OUT")
    data = OpenFLUID.openDataset(pathIN)
    OpenFLUID.setCurrentOutputDir(pathOUT)
    self.assertRaises(Exception,OpenFLUID.runSimulation(data,True))


###############################################


  def testProjectSimulation(self):
    path = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.PRJ")
    pathOUT = os.path.join(os.path.dirname(os.path.realpath(__file__)),"Generators.PRJ","OUT")
    data = OpenFLUID.openProject(path)
    OpenFLUID.setCurrentOutputDir(pathOUT)
    self.assertRaises(Exception,OpenFLUID.runSimulation(data))


###############################################
###############################################


if __name__ == '__main__':
  unittest.main()

# -*- coding: utf-8 -*-

__author__  = "Jean-Christophe Fabre"
__email__   = "jean-christophe.fabre@inra.fr"
__license__ = "see LICENSE file"


import unittest
from PyOpenFLUID import OpenFLUID


###############################################
###############################################


class MainTest(unittest.TestCase):

  def testVersion(self):
    print(OpenFLUID.getVersion())


  ###############################################


  def testBlob(self):
    b = OpenFLUID.newBlob()
    OpenFLUID.deleteBlob(b)


  ###############################################


  def testSimulatorsPaths(self):
    print(OpenFLUID.getSimulatorsPaths())

    self.assertEqual(len(OpenFLUID.getExtraSimulatorsPaths()),0)

    OpenFLUID.addExtraSimulatorsPaths("/path/sim/1")
    self.assertEqual(OpenFLUID.getExtraSimulatorsPaths(),["/path/sim/1"])

    OpenFLUID.addExtraSimulatorsPaths("/path/sim/2")
    self.assertEqual(len(OpenFLUID.getExtraSimulatorsPaths()), 2)
    self.assertEqual(sorted(OpenFLUID.getExtraSimulatorsPaths()),sorted(["/path/sim/1","/path/sim/2"]))

    OpenFLUID.addExtraSimulatorsPaths(["/path/sim/3","/path/sim/4"])
    self.assertEqual(len(OpenFLUID.getExtraSimulatorsPaths()), 4)

    OpenFLUID.resetExtraSimulatorsPaths()
    self.assertEqual(len(OpenFLUID.getExtraSimulatorsPaths()),0)
    self.assertEqual(OpenFLUID.getExtraSimulatorsPaths(),[])

    OpenFLUID.addExtraSimulatorsPaths(["/path/sim/5","/path/sim/5"])
    self.assertEqual(len(OpenFLUID.getExtraSimulatorsPaths()), 1)



  ###############################################


  def testObserversPaths(self):
    print(OpenFLUID.getObserversPaths())

    self.assertEqual(len(OpenFLUID.getExtraObserversPaths()),0)

    OpenFLUID.addExtraObserversPaths("/path/obs/10")
    self.assertEqual(OpenFLUID.getExtraObserversPaths(), ["/path/obs/10"])

    OpenFLUID.addExtraObserversPaths("/path/obs/20")
    self.assertEqual(len(OpenFLUID.getExtraObserversPaths()), 2)
    self.assertEqual(sorted(OpenFLUID.getExtraObserversPaths()),sorted(["/path/obs/10","/path/obs/20"]))

    OpenFLUID.addExtraObserversPaths(["/path/obs/30","/path/obs/40"])
    self.assertEqual(len(OpenFLUID.getExtraObserversPaths()), 4)

    OpenFLUID.resetExtraObserversPaths()
    self.assertEqual(len(OpenFLUID.getExtraObserversPaths()), 0)
    self.assertEqual(OpenFLUID.getExtraObserversPaths(),[])

    OpenFLUID.addExtraObserversPaths(["/path/obs/50","/path/obs/50"])
    self.assertEqual(len(OpenFLUID.getExtraObserversPaths()), 1)


###############################################
###############################################


if __name__ == '__main__':
  unittest.main()

#! /usr/bin/env python3
# -*- coding: utf-8 -*-

__author__  = "Jean-Christophe Fabre"
__email__   = "jean-christophe.fabre@inra.fr"
__license__ = "see LICENSE file"


import os
import libPyOpenFLUID


##############################################################################
##############################################################################


class OpenFLUID:
  """Doc of main PyOpenFLUID class"""

  @staticmethod
  def __cleanPaths(paths):
    cleanedPaths = paths

    # if string : split into string list using system path separator
    if type(cleanedPaths) is str:
      cleanedPaths = cleanedPaths.split()

    # if list : remove duplicates and join into string using system path separator
    if type(cleanedPaths) is list:
      cleanedPaths = list(set(cleanedPaths))
      return os.pathsep.join(cleanedPaths)

    return "";


  ##############################################################################


  @staticmethod
  def getVersion():
    return libPyOpenFLUID.getVersion()


  ##############################################################################


  @staticmethod
  def newBlob():
    return libPyOpenFLUID.newBlob()


  ##############################################################################

  @staticmethod
  def deleteBlob(blob):
    return libPyOpenFLUID.deleteBlob(blob)


  ##############################################################################


  @staticmethod
  def addExtraSimulatorsPaths(paths):
    cleanedPaths = OpenFLUID.__cleanPaths(paths)
    return libPyOpenFLUID.addExtraSimulatorsPaths(cleanedPaths)


  ##############################################################################


  @staticmethod
  def resetExtraSimulatorsPaths():
    return libPyOpenFLUID.resetExtraSimulatorsPaths()


  ##############################################################################


  @staticmethod
  def getExtraSimulatorsPaths():
    return libPyOpenFLUID.getExtraSimulatorsPaths()


  ##############################################################################


  @staticmethod
  def getSimulatorsPaths():
    return libPyOpenFLUID.getSimulatorsPaths()


  ##############################################################################


  @staticmethod
  def addExtraObserversPaths(paths):
    cleanedPaths = OpenFLUID.__cleanPaths(paths)
    return libPyOpenFLUID.addExtraObserversPaths(cleanedPaths)


  ##############################################################################


  @staticmethod
  def resetExtraObserversPaths():
    return libPyOpenFLUID.resetExtraObserversPaths()


  ##############################################################################


  @staticmethod
  def getExtraObserversPaths():
    return libPyOpenFLUID.getExtraObserversPaths()


  ##############################################################################


  @staticmethod
  def getObserversPaths():
    return libPyOpenFLUID.getObserversPaths()


  ##############################################################################


  @staticmethod
  def openDataset(path):
    return libPyOpenFLUID.openDataset(path)


  ##############################################################################


  @staticmethod
  def openProject(path):
    return libPyOpenFLUID.openProject(path)


  ##############################################################################


  @staticmethod
  def printSimulationInfo(blob):
    return libPyOpenFLUID.printSimulationInfo(blob)


  ##############################################################################


  @staticmethod
  def setCurrentOutputDir(path):
    return libPyOpenFLUID.setCurrentOutputDir(path)


  ##############################################################################


  @staticmethod
  def getSimulationOutputDir(blob):
    return libPyOpenFLUID.getSimulationOutputDir(blob)


  ##############################################################################


  @staticmethod
  def runSimulation(blob,verbose = False):
    return libPyOpenFLUID.runSimulation(blob,verbose)

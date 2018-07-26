#! /usr/bin/env python3
# -*- coding: utf-8 -*-

__author__  = "Jean-Christophe Fabre"
__email__   = "jean-christophe.fabre@inra.fr"
__license__ = "see LICENSE file"


import os
import sys
import platform
import subprocess

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext


##############################################################################
##############################################################################


name='PyOpenFLUID'
patchVersion='20180726'
cmakeBuildType='Release'


##############################################################################
##############################################################################


def detectOpenFLUIDVersion():
  try:
    Env = os.environ.copy()
    VersionStr = subprocess.check_output(["openfluid", "--version"],env=Env)
    VersionStr = str(VersionStr, 'utf-8').strip(' \t\n\r').split('~')[0]

    return(VersionStr)
  except OSError as e:
    if e.errno == os.errno.ENOENT:
      print("OpenFLUID command line not found")
      sys.exit(127)
    else:
      print("OpenFLUID command line error")
      sys.exit(126)


##############################################################################
##############################################################################


class CMakeExtension(Extension):
  def __init__(self, name, sourcedir=''):
    Extension.__init__(self, name, sources=[])
    self.sourcedir = os.path.abspath(sourcedir)


##############################################################################


class CMakeBuild(build_ext):
  def run(self):
    try:
      Out = subprocess.check_output(['cmake', '--version'])
    except OSError:
      raise RuntimeError("CMake must be installed to build the PyOpenFLUID package")

    if platform.system() != "Linux":
      raise RuntimeError("PyOpenFLUID package is available on Linux systems only")

    for Ext in self.extensions:
      self.build_extension(Ext)

  def build_extension(self, ext):
    ExtDir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
    CMakeSrcDir = os.path.join(ext.sourcedir,"PyOpenFLUID")
    CMakeConfigArgs = ["-DCMAKE_BUILD_TYPE="+cmakeBuildType,
                       "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(ExtDir)]
    CMakeBuildDir = self.build_temp

    if not os.path.exists(self.build_temp):
      os.makedirs(self.build_temp)

    Env = os.environ.copy()
    subprocess.check_call(['cmake', CMakeSrcDir ] + CMakeConfigArgs,cwd=self.build_temp, env=Env)
    subprocess.check_call(['cmake', '--build', '.'],cwd=self.build_temp)


##############################################################################
##############################################################################


version=detectOpenFLUIDVersion()
release=version+'-'+patchVersion


setup(
  name=name,
  version=version,
  author='Jean-Christophe Fabre',
  author_email='jean-christophe.fabre@inra.fr',
  description='Python package for OpenFLUID',
  long_description='',
  url='https://www.openfluid-project.org/',
  packages=['PyOpenFLUID'],
  ext_modules=[CMakeExtension('PyOpenFLUID')],
  cmdclass={
    'build_ext' : CMakeBuild
  },
  test_suite='tests',
  zip_safe=False
)

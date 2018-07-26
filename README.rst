Overview
========

This Package allows to load, parameterize, run and analyze OpenFLUID simulations from Python.

It is compatible with Python 3 and requires that the `OpenFLUID platform <https://www.openfluid-project.org/>`_ is already installed

*Currently, this package is in early development stage and has only be tested on Linux system*


Installation
============

from PyPI
---------

*TODO*


from sources
------------

Classic installation (main usage)

.. code-block:: shell

    pip3 install .


Installation linked to the current sources (usually for development purposes)

.. code-block:: shell

     pip3 install -e .



Development
===========


Run the following commands from the root of the sources tree.


Check
-----

.. code-block:: shell

   python3 setup.py check


Build
-----

.. code-block:: shell

   python3 setup.py build


Test
----

.. code-block:: shell

   python3 setup.py build test


Packaging
---------

.. code-block:: shell

   python3 setup.py sdist bdist


Misc resources
--------------

* https://stackoverflow.com/questions/42585210/extending-setuptools-extension-to-use-cmake-in-setup-py

* http://intermediate-and-advanced-software-carpentry.readthedocs.io/en/latest/c++-wrapping.html

* https://github.com/avast-tl/yaramod/blob/master/setup.py

* http://www.benjack.io/2017/06/12/python-cpp-tests.html

* https://github.com/dabeaz/python-cookbook/tree/master/src/15/writing_a_simple_c_extension_module

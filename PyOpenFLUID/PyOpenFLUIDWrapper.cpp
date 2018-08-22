/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.

*/

/**
  @file PyOpenFLUIDWrapper.cpp
  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
 */


#include <Python.h>

#include <openfluid/utils/Binding.hpp>


// =====================================================================
// =====================================================================


class PyOutErr : public openfluid::utils::BindingAbstractOutErr
{
  public:

    void printfOut(const char* fmt, ... ) const
    {
      va_list args;
      va_start(args,fmt);
      vprintf(fmt,args);
      va_end(args);
    }

    void printfErr(const char* fmt, ... ) const
    {
      va_list args;
      va_start(args,fmt);
      vfprintf(stderr,fmt,args);
      va_end(args);
    }
};


OPENFLUID_BINDING_DEFINE(PyOutErr);


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUIDError;

static PyObject* PyOpenFLUID_GetVersion(PyObject* self);

static PyObject* PyOpenFLUID_NewBlob(PyObject* self);
static PyObject* PyOpenFLUID_DeleteBlob(PyObject* self, PyObject* Blob);

static PyObject* PyOpenFLUID_AddExtraSimulatorsPaths(PyObject* self, PyObject* Args);
static PyObject* PyOpenFLUID_ResetExtraSimulatorsPaths(PyObject* self);
static PyObject* PyOpenFLUID_GetSimulatorsPaths(PyObject* self);
static PyObject* PyOpenFLUID_GetExtraSimulatorsPaths(PyObject* self);
static PyObject* PyOpenFLUID_AddExtraObserversPaths(PyObject* self, PyObject* Args);
static PyObject* PyOpenFLUID_ResetExtraObserversPaths(PyObject* self);
static PyObject* PyOpenFLUID_GetObserversPaths(PyObject* self);
static PyObject* PyOpenFLUID_GetExtraObserversPaths(PyObject* self);

static PyObject* PyOpenFLUID_OpenProject(PyObject* self, PyObject* Args);
static PyObject* PyOpenFLUID_OpenDataset(PyObject* self, PyObject* Args);
static PyObject* PyOpenFLUID_PrintSimulationInfo(PyObject* self, PyObject* Blob);
static PyObject* PyOpenFLUID_SetCurrentOutputDir(PyObject* self, PyObject* Args);
static PyObject* PyOpenFLUID_GetSimulationOutputDir(PyObject* self, PyObject* Blob);
static PyObject* PyOpenFLUID_RunSimulation(PyObject* self, PyObject *Args);


// =====================================================================
// =====================================================================


static PyMethodDef PyOpenFLUIDMethods[] = {
  {"getVersion", (PyCFunction)PyOpenFLUID_GetVersion, METH_NOARGS, ""},

  {"newBlob", (PyCFunction)PyOpenFLUID_NewBlob, METH_NOARGS, ""},
  {"deleteBlob", (PyCFunction)PyOpenFLUID_DeleteBlob, METH_O, ""},

  {"addExtraSimulatorsPaths", (PyCFunction)PyOpenFLUID_AddExtraSimulatorsPaths, METH_VARARGS, ""},
  {"resetExtraSimulatorsPaths", (PyCFunction)PyOpenFLUID_ResetExtraSimulatorsPaths, METH_NOARGS, ""},
  {"getExtraSimulatorsPaths", (PyCFunction)PyOpenFLUID_GetExtraSimulatorsPaths, METH_NOARGS, ""},
  {"getSimulatorsPaths", (PyCFunction)PyOpenFLUID_GetSimulatorsPaths, METH_NOARGS, ""},
  {"addExtraObserversPaths", (PyCFunction)PyOpenFLUID_AddExtraObserversPaths, METH_VARARGS, ""},
  {"resetExtraObserversPaths", (PyCFunction)PyOpenFLUID_ResetExtraObserversPaths, METH_NOARGS, ""},
  {"getExtraObserversPaths", (PyCFunction)PyOpenFLUID_GetExtraObserversPaths, METH_NOARGS, ""},
  {"getObserversPaths", (PyCFunction)PyOpenFLUID_GetObserversPaths, METH_NOARGS, ""},

  {"openDataset", (PyCFunction)PyOpenFLUID_OpenDataset, METH_VARARGS, ""},
  {"openProject", (PyCFunction)PyOpenFLUID_OpenProject, METH_VARARGS, ""},
  {"setCurrentOutputDir", (PyCFunction)PyOpenFLUID_SetCurrentOutputDir, METH_VARARGS, ""},
  {"getSimulationOutputDir", (PyCFunction)PyOpenFLUID_GetSimulationOutputDir, METH_O, ""},
  {"printSimulationInfo", (PyCFunction)PyOpenFLUID_PrintSimulationInfo, METH_O, ""},
  {"runSimulation", (PyCFunction)PyOpenFLUID_RunSimulation, METH_VARARGS, ""},

  { NULL, NULL, 0, NULL}
};


// =====================================================================
// =====================================================================


static struct PyModuleDef PyOpenFLUIDModule = {
  PyModuleDef_HEAD_INIT,
  "libPyOpenFLUID",
  "",  /* Docstring */
  -1,
  PyOpenFLUIDMethods
};


// =====================================================================
// =====================================================================


PyMODINIT_FUNC PyInit_libPyOpenFLUID(void) {

  openfluid::utils::Binding::init();

  PyObject* Module = PyModule_Create(&PyOpenFLUIDModule);

  // Registering of special exception for PyOpenFLUID package
  PyOpenFLUIDError = PyErr_NewException("PyOpenFLUID.Error", NULL, NULL);
  Py_INCREF(PyOpenFLUIDError);
  PyModule_AddObject(Module,"Error",PyOpenFLUIDError);

  return Module;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_GetVersion(PyObject* self)
{
  const char* Version = openfluid::utils::Binding::getVersion();

  return Py_BuildValue("s",Version);
}


// =====================================================================
// =====================================================================


void DestroyBlob(PyObject* Blob)
{
  openfluid::utils::Binding* Ptr = (openfluid::utils::Binding*)PyCapsule_GetPointer(Blob,"PyOpenFLUIDBlob");
  openfluid::utils::Binding::destroy(Ptr);
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_NewBlob(PyObject* self)
{
  PyObject* Ret = NULL;

  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::make();

  if (Ptr)
  {
    Ret = PyCapsule_New((void*)Ptr,"PyOpenFLUIDBlob",DestroyBlob);
  }
  else
  {
    PyErr_SetString(PyOpenFLUIDError, "unable to create new blob");
    return NULL;
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_DeleteBlob(PyObject* self, PyObject* Blob)
{
  DestroyBlob(Blob);

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_AddExtraSimulatorsPaths(PyObject* self, PyObject* Args)
{
  char* Paths;

  if (!PyArg_ParseTuple(Args, "s",&Paths))
  {
    PyErr_SetString(PyOpenFLUIDError, "wrong data type for paths");
    return NULL;
  }

  openfluid::utils::Binding::addExtraSimulatorsPaths(Paths);

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_ResetExtraSimulatorsPaths(PyObject* self)
{
  openfluid::utils::Binding::resetExtraSimulatorsPaths();

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_GetSimulatorsPaths(PyObject* self)
{
  PyObject* Ret = NULL;

  unsigned int PathsCount = openfluid::utils::Binding::getSimulatorsPathsCount();
  Ret = PyList_New(PathsCount);

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getSimulatorsPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      PyList_SET_ITEM(Ret, i, Py_BuildValue("s",Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
    {
      free (Paths[i]);
    }
    free(Paths);
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_GetExtraSimulatorsPaths(PyObject* self)
{
  PyObject* Ret = NULL;

  unsigned int PathsCount = openfluid::utils::Binding::getExtraSimulatorsPathsCount();
  Ret = PyList_New(PathsCount);

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getExtraSimulatorsPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      PyList_SET_ITEM(Ret, i, Py_BuildValue("s",Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
    {
      free (Paths[i]);
    }
    free(Paths);
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_AddExtraObserversPaths(PyObject* self, PyObject* Args)
{
  char* Paths;

  if (!PyArg_ParseTuple(Args, "s",&Paths))
  {
    PyErr_SetString(PyOpenFLUIDError, "wrong data type for paths");
    return NULL;
  }

  openfluid::utils::Binding::addExtraObserversPaths(Paths);

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_ResetExtraObserversPaths(PyObject* self)
{
  openfluid::utils::Binding::resetExtraObserversPaths();

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_GetObserversPaths(PyObject* self)
{
  PyObject* Ret = NULL;

  unsigned int PathsCount = openfluid::utils::Binding::getObserversPathsCount();
  Ret = PyList_New(PathsCount);

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getObserversPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      PyList_SET_ITEM(Ret, i, Py_BuildValue("s",Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
    {
      free (Paths[i]);
    }
    free(Paths);
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_GetExtraObserversPaths(PyObject* self)
{
  PyObject* Ret = NULL;

  unsigned int PathsCount = openfluid::utils::Binding::getExtraObserversPathsCount();
  Ret = PyList_New(PathsCount);

  if (PathsCount > 0)
  {
    char** Paths = openfluid::utils::Binding::getExtraObserversPaths();

    unsigned int i;
    for (i=0;i<PathsCount;i++)
    {
      PyList_SET_ITEM(Ret, i, Py_BuildValue("s",Paths[i]));
    }

    for (i=0;i<PathsCount;i++)
    {
      free (Paths[i]);
    }
    free(Paths);
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_OpenProject(PyObject* self, PyObject* Args)
{
  char* Path;

  if (!PyArg_ParseTuple(Args, "s",&Path))
  {
    return NULL;
  }

  PyObject* Ret = NULL;
  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::openProject(Path);

  if (Ptr)
  {
    Ret = PyCapsule_New((void*)Ptr,"PyOpenFLUIDBlob",DestroyBlob);
  }
  else
  {
    PyErr_SetString(PyOpenFLUIDError, "Unable to open project");
    return NULL;
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_OpenDataset(PyObject* self, PyObject* Args)
{
  char* Path;

  if (!PyArg_ParseTuple(Args, "s",&Path))
  {
    return NULL;
  }

  PyObject* Ret = NULL;
  openfluid::utils::Binding* Ptr = openfluid::utils::Binding::openDataset(Path);

  if (Ptr)
  {
    Ret = PyCapsule_New((void*)Ptr,"PyOpenFLUIDBlob",DestroyBlob);
  }
  else
  {
    PyErr_SetString(PyOpenFLUIDError, "Unable to open dataset");
    return NULL;
  }

  return Ret;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_PrintSimulationInfo(PyObject* self, PyObject* Blob)
{
  reinterpret_cast<openfluid::utils::Binding*>(PyCapsule_GetPointer(Blob,"PyOpenFLUIDBlob"))->printSimulationInfo();

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_SetCurrentOutputDir(PyObject* self, PyObject* Args)
{
  char* Path;

  if (!PyArg_ParseTuple(Args, "s",&Path))
  {
    return NULL;
  }

  openfluid::utils::Binding::setCurrentOutputDir(Path);

  Py_RETURN_NONE;
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_GetSimulationOutputDir(PyObject* self, PyObject* Blob)
{
  const char* Path =
    reinterpret_cast<openfluid::utils::Binding*>(PyCapsule_GetPointer(Blob,"PyOpenFLUIDBlob"))->
      getSimulationOutputDir();

  return Py_BuildValue("s",Path);
}


// =====================================================================
// =====================================================================


static PyObject* PyOpenFLUID_RunSimulation(PyObject* self, PyObject *Args)
{
  PyObject* Blob;
  int Verbose;

  if (!PyArg_ParseTuple(Args, "Oi",&Blob,&Verbose))
  {
    PyErr_SetString(PyOpenFLUIDError,"Arguments error");
    return NULL;
  }

  if (reinterpret_cast<openfluid::utils::Binding*>(PyCapsule_GetPointer(Blob,"PyOpenFLUIDBlob"))->
       runSimulation((bool)Verbose) != 1)
  {
    PyErr_SetString(PyOpenFLUIDError,openfluid::utils::Binding::getLastError());
    return NULL;
  }

  Py_RETURN_NONE;
}

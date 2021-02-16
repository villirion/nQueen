#include "Python.h"


// vÃ©rifie les diagonales
static PyObject* diagQueen(PyObject* self, PyObject *args) {
    PyObject *py_tuple;
    int nb;
    short int *reines;

    if (!PyArg_ParseTuple(args, "O", &py_tuple)) {
        return NULL;
    }
    nb = PyTuple_Size(py_tuple);
    reines= malloc(nb*sizeof(short int));
    int i;
    i = nb;
    PyObject* temp;
    long elem;
    while (i--){
        temp =  PyTuple_GetItem(py_tuple, i);
        elem = PyLong_AsLong(temp);
        reines[i] = (short int) elem;
    }
    
    int diagPlus[nb];
    int j;
#pragma omp simd
    for (i = 0; i <= nb - 1; i++) {
        diagPlus[i] = reines[i] + i;
     }
     int diagMoins[nb];
#pragma omp simd
     for (i = 0; i <= nb - 1; i++) {
         diagMoins[i] = reines[i] - i;
     }
    free(reines);
     for (i = 0; i <= nb - 1; i++) {
         for (j = i + 1; j <= nb - 1; j++) {
             if (diagMoins[j] == diagMoins[i]) {
                 return Py_BuildValue("i", 0);
             }
             if (diagPlus[j] == diagPlus[i]) {
                 return Py_BuildValue("i", 0);
             }
         }
     }

     return Py_BuildValue("i", 1);
}

static char diag_docs[] = "diag( ): diag verifie si les reines sont sur les mÃªmes diagonales\n";

/*
<function-name in python module>, <actual-function>,
<type-of-args the function expects>, <docstring associated with the function>
*/

/* deprecated :
static PyMethodDef diag_funcs[] = {
    {"diag", (PyCFunction)diag, METH_VARARGS, diag_docs},
    {NULL, NULL, 0, NULL}
};
*/
static PyMethodDef module_methods[] = {
    {"diag", (PyCFunction) diagQueen,
      METH_VARARGS, diag_docs},
    {NULL}
};

/* deprecated :
PyMODINIT_FUNC initdiag(void){
        Py_InitModule3("diag", diag_funcs,
                       "verifie si les diagonales");
};
*/

static struct PyModuleDef diag =
{
    PyModuleDef_HEAD_INIT,
    "diag", /* name of module */
    "usage: diag.diag(lst_reines)\n", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    module_methods
};

PyMODINIT_FUNC PyInit_diag(void)
{
    return PyModule_Create(&diag);
    
}

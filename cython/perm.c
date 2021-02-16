#include "Python.h"

void swapVal(short int *a,short int *b)
{
    short int temp = *a;
    *a = *b;
    *b = temp;
}

static PyObject* nextPerm(PyObject* self, PyObject *args) {
    PyObject *py_tuple;
    int n;
    short int *perm;

    if (!PyArg_ParseTuple(args, "O", &py_tuple)) {
        return NULL;
    }
    n = PyTuple_Size(py_tuple);
    perm= malloc(n*sizeof(short int));
    int i;
    i = n;
    PyObject* temp;
    long elem;
    while (i--){
        temp =  PyTuple_GetItem(py_tuple, i);
        elem = PyLong_AsLong(temp);
        perm[i] = (short int) elem;
    }
    

    if (n<4){
        return Py_BuildValue("i", 0);
    }
    int OK=1;
    int j, k;
    do {
        i = n-1;
        while ( (i >0 ) && (perm[i - 1] > perm[i])){
            i--;
        }
        j = i;
        k = n-1;
        while (j < k){
            swapVal(&perm[j],&perm[k]);
            j++;
            k--;
        }
        if (i == 0){
            return Py_BuildValue("i", 0);
        }else{
            j = i;
            while (perm[j] < perm[i - 1]) {
                j++;
            }
            swapVal(&perm[i - 1],&perm[j]);
            OK=0;
            for (i = 0; i < n-1; i++){
                if ((perm[i] == perm[i+1]+1)||(perm[i] == perm[i+1]-1)){
                    OK=1;
                    break;
                }
            }
        }
    } while (OK==1);
    PyObject *py_perm = PyTuple_New(n);
    for(i=0;i<n;i++){
	elem = perm[i];
	temp = PyLong_FromLong(elem);
	PyTuple_SetItem(py_perm,i,temp);
    }
    return py_perm;
}


static char perm_docs[] = "perm( ): renvoie la permutation suivante (non consecutive)\n";

static PyMethodDef module_methods[] = {
    {"perm", (PyCFunction) nextPerm,
      METH_VARARGS, perm_docs},
    {NULL}
};

static struct PyModuleDef perm =
{
    PyModuleDef_HEAD_INIT,
    "perm", /* name of module */
    "usage: perm.perm(lst_reines)\n", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    module_methods
};

PyMODINIT_FUNC PyInit_perm(void)
{
    return PyModule_Create(&perm);
    
}

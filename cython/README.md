Compilation for cython:

gcc -shared -pthread -fPIC -fwrapv -O2 -fopenmp -Wall -fno-strict-aliasing -I/.../anaconda3/include/python3.8/ -o diag.so diag.c

gcc -shared -pthread -fPIC -fwrapv -O2 -Wall -fno-strict-aliasing -I/.../anaconda3/include/python3.8/ -o perm.so perm.c

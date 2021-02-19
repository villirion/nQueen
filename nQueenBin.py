n = 12

cols = {}
diagl = {} 
diagr = {} 
posibs = {}
num = 0

for q0 in range(n-2): 
    for q1 in range(q0+2,n):
        bit0 = 1<<q0
        bit1 = 1<<q1
        d = 0
        cols[0] = bit0 | bit1 | (-1<<n)
        diagl[0]= (bit0<<1 | bit1)<<1
        diagr[0]= (bit0>>1 | bit1)>>1
        posib = ~(cols[0] | diagl[0] | diagr[0]);
        while (d >= 0):
            while(posib):
                bit = posib & -posib
                ncols = cols[d] | bit
                ndiagl = (diagl[d] | bit) << 1
                ndiagr = (diagr[d] | bit) >> 1
                nposib = ~(ncols | ndiagl | ndiagr)
                posib ^= bit
                num += ncols == -1

                if (nposib):
                    if (posib):
                        posibs[d] = posib
                        d += 1
                    cols[d] = ncols;
                    diagl[d] = ndiagl;
                    diagr[d] = ndiagr;
                    posib = nposib;
            
            d -= 1
            if (d >= 0):
                posib = posibs[d]
            
            
print(num*2)

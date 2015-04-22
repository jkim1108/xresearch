#!/usr/bin/python
from sklearn.svm import SVC
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.cross_validation import StratifiedKFold
from scipy.stats import binom
import numpy as np
import sys
import csv
from multiprocessing import Pool
from sklearn.metrics.pairwise import cosine_similarity

def signtest(filename):
    opt = []
    param_filename = filename.split('/')[-1][:-4]
    with open('params/{}'.format(param_filename)) as pf:
        reader = csv.reader(pf, delimiter=':')
        for line in reader:
            opt.append(line[1])
    dataset = opt[0]
    useDT = bool(opt[2])
    if useDT:
        basefile = param_filename[:-3] + '901'
    else :
        basefile = param_filename[:-3] + '902'

    golden = np.load('flag/golden/%s.npy' % (param_filename))
    ourp = np.load('flag/pred/%s.npy' % (param_filename))
    basep = np.load('flag/pred/%s.npy' % (basefile))

    n, k = 0, 0
    if golden.ndim > 1:
        for i in range(len(golden)) :
            a = (golden[i] == basep[i])
            b = (golden[i] == ourp[i])
            n += sum(a!=b)
            k += sum(b>a)
    else:
        a = (golden == basep)
        b = (golden == ourp)
        n += sum(a!=b)
        k += sum(b>a)

    pval = binom.sf(k-1, n, 0.5)
    print filename, pval

if __name__=='__main__' :
    print sys.argv[1:]
    pool = Pool(3)
    pool.map(signtest, sys.argv[1:])
    pool.close()

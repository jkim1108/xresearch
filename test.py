#!/usr/bin/env python

import numpy as np
import sys
import csv
import sklearn
from multiprocessing import Pool
from sklearn.cross_validation import StratifiedKFold
from sklearn.svm import SVC
from sklearn.metrics import precision_recall_fscore_support
from sklearn.metrics import accuracy_score

def get_index(filename):
    dataset = filename.split('/')[-1][0]

    V1 = {'m':1397, 'p':4000, 's':4000}
    V2 = {'m':3280, 'p':9331, 's':9000}
    MP = {'m':1565, 'p':5331, 's':5000}
    N = {'m':3467, 'p':10662, 's':10000}

    mp  = MP[dataset]
    n = N[dataset]
    flags = np.array([1] * mp + [0] * (n-mp))

    v1 = V1[dataset]
    v2 = V2[dataset]

    train_index = np.concatenate((np.arange(v1), np.arange(mp, v2)))
    test_index = np.concatenate((np.arange(v1, mp), np.arange(v2, n))) 
    return flags, train_index, test_index

def model_test(filename):
    flags, train_index, test_index =  get_index(filename)
    kernel_matrix = np.loadtxt(filename)      

    res = test(kernel_matrix, flags, train_index, test_index)
    opt = []

    param_filename = filename.split('/')[-1][:-4]
    with open('/home/kim/params/{}'.format(param_filename)) as pf:
        reader = csv.reader(pf, delimiter=':')
        reader.next()
        for line in reader:
            opt.append(line[1])

    output = " ".join(map(str, [param_filename] + res + opt))
    print output

    outputf = '/home/kim/score/{}'.format(param_filename)
    with open(outputf, 'w') as f:
        f.write(output)
        f.close()

def model_validation(filename):
    flags, indexset, _ =  get_index(filename)
    flags = flags[indexset]
    full_matrix = np.loadtxt(filename)
    kernel_matrix = full_matrix[indexset][:,indexset]
    del full_matrix

    kfold = StratifiedKFold(flags, 3)
    res = []

    for train_index, test_index in kfold: 
        res.append(test(kernel_matrix, flags, train_index, test_index))
    res = np.array(res)
    res = list(np.average(res, axis = 0))
    opt = []

    param_filename = filename.split('/')[-1][:-4]
    with open('/home/kim/params/{}'.format(param_filename)) as pf:
        reader = csv.reader(pf, delimiter=':')
        reader.next()
        for line in reader:
            opt.append(line[1])

    output = " ".join(map(str, [param_filename] + res + opt))
    print output

    outputf = '/home/kim/score/{}'.format(param_filename)
    with open(outputf, 'w') as f:
        f.write(output)
        f.close()

def test(kernel_matrix, flags, train_index, test_index):
    kernel_train, kernel_test = kernel_matrix[train_index][:,train_index], kernel_matrix[test_index][:,train_index]
    flags_train, flags_test = flags[train_index], flags[test_index]

    clf = SVC(kernel = 'precomputed')
    clf.fit(kernel_train, flags_train)
    flags_pred = clf.predict(kernel_test)

    acc = accuracy_score(flags_test, flags_pred)
    res = precision_recall_fscore_support(flags_test, flags_pred, average='macro')
    return [acc] + list(res[:3])

if __name__=='__main__':
    pool = Pool(4)
    pool.map(model_validation, sys.argv[1:])
    pool.close()

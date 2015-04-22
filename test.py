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

def model_test(filename):
    kernel_matrix = np.loadtxt(filename, dtype=np.float16)
    dataset = filename.split('/')[-1][0]
    if not dataset in ['a', 'e', 'n']:
        for i in range(kernel_matrix.shape[0]):
            div_num = kernel_matrix[i, i]
            if not div_num:
                continue
            kernel_matrix[i, :] = kernel_matrix[i, :] / np.sqrt(div_num)
            kernel_matrix[:, i] = kernel_matrix[:, i] / np.sqrt(div_num)
            kernel_matrix[i, i] = 1

    if dataset == 'n':
        diag = np.loadtxt(filename[:-4] + '_diag.csv')
        for i in range(len(diag)):
            div_num = diag[i]
            if not div_num:
                continue
            if i < kernel_matrix.shape[0]:
                kernel_matrix[i, :] = kernel_matrix[i, :] / np.sqrt(div_num)
            if i < kernel_matrix.shape[1]:
                kernel_matrix[:, i] = kernel_matrix[:, i] / np.sqrt(div_num)
            if i < kernel_matrix.shape[0] and i < kernel_matrix.shape[1]:
                kernel_matrix[i, i] = 1
         
    opt = []
    param_filename = filename.split('/')[-1][:-4]
    with open('params/{}'.format(param_filename)) as pf:
        reader = csv.reader(pf, delimiter=':')
        for line in reader:
            opt.append(line[1])

    flags = np.loadtxt('data/%s/flag' % (opt[0]))
    if dataset == 'p':
        n = 5331
        cut = int(n * 0.8)
        train_index = np.concatenate((np.arange(cut), np.arange(n, n + cut)))
        test_index = np.concatenate((np.arange(cut, n), np.arange(n + cut, 2*n)))
        flags_pred, res = test(kernel_matrix, flags, train_index, test_index)
        golden = flags[test_index]
    
    elif dataset == 'e':
        train_index = np.concatenate((np.arange(3396), np.arange(4677, 9099),\
                                    np.arange(10494, 11878)))
        test_index = np.concatenate((np.arange(3396, 4677), \
                         np.arange(9099, 10494), np.arange(11878, 12348))) 
        flags_pred, res = test(kernel_matrix, flags, train_index, test_index)
        golden = flags[test_index]
    
    elif dataset == 'n':
        train_index = np.arange(16301)
        test_index = np.arange(16301, 32602) 
        flags_pred, res = test(kernel_matrix, flags, train_index, test_index)
        golden = flags[test_index]
    
    else :
        kfold = StratifiedKFold(flags, 5)
        res = []
        golden = []
        flags_pred = []
        for train_index, test_index in kfold: 
            tmp_flags, tmp_res = test(kernel_matrix, flags, train_index, test_index)
            flags_pred.append(tmp_flags)
            golden.append(flags[test_index])
            res.append(tmp_res)
        flags_pred, golden, res = np.array(flags_pred), np.array(golden), np.array(res)
        res = list(np.average(res, axis = 0))
    np.save('flag/pred/%s' % param_filename, flags_pred)
    np.save('flag/golden/%s' % param_filename, golden)
    output = " ".join(map(str, [param_filename] + res + opt[1:]))
    print output

def test(kernel_matrix, flags, train_index, test_index):
    '''
    kernel_train, kernel_test = kernel_matrix[train_index][:,train_index], kernel_matrix[test_index][:,train_index]
    '''
    kernel_train, kernel_test = kernel_matrix[train_index][:,train_index], kernel_matrix[train_index][:,test_index].transpose()
    flags_train, flags_test = flags[train_index], flags[test_index]

    clf = SVC(kernel = 'precomputed')
    clf.fit(kernel_train, flags_train)
    flags_pred = clf.predict(kernel_test)
    del kernel_train
    del kernel_test
    acc = accuracy_score(flags_test, flags_pred)
    res = precision_recall_fscore_support(flags_test, flags_pred, average='macro')
    return flags_pred, [acc] + list(res[:3])

if __name__=='__main__':
    print sys.argv[1:]
    '''
    pool = Pool(3)
    pool.map(model_test, sys.argv[1:])
    pool.close()
    '''
    model_test(sys.argv[1])

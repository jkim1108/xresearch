import numpy as np
import sys
import sklearn
from sklearn.metrics import precision_recall_fscore_support
from sklearn.metrics import accuracy_score

filename = sys.argv[1]
dataset = filename.split('/')[-1][0]

T1 = {'m':1397, 'p':4000, 's':4000}
T2 = {'m':3280, 'p':9331, 's':9000}
MP = {'m':1565, 'p':5331, 's':5000}

t1 = T1[dataset]
t2 = T2[dataset]
mp  = MP[dataset]
kernel_matrix = np.loadtxt(filename)
n = kernel_matrix.shape[0]
flags = np.array([1] * mp + [0] * (n-mp))

train_index = np.concatenate((np.arange(t1), np.arange(mp, t2)))
test_index = np.concatenate((np.arange(t1, mp), np.arange(t2, n)))

kernel_train, kernel_test = kernel_matrix[train_index][:,train_index], kernel_matrix[test_index][:,train_index]
flags_train, flags_test = flags[train_index], flags[test_index]

clf = SVC(kernel = 'precomputed')
clf.fit(kernel_train, flags_train)
flags_pred = clf.predict(kernel_test)

acc = accuracy_score(flags_test, flags_pred)
res = precision_recall_fscore_support(flags_test, flags_pred, average='macro')

print "Accuracy : " + acc
print "Precision : " + res[0]
print "Recall : " + res[1]
print "F1 : " + res[2]

#Plots ROC when a file with responses and probabilities (labels and scores) is provided
#Petko's Code, Modified by Olivera, Feb 2nd, 2016

#python ./plot_ROC.py 10samples_l1_lambda1_chr2 labels_scores_sorted_10samples_l1_lambda1_chr2

import matplotlib
matplotlib.use("Agg")
import os
import pickle
import sys
import numpy as np
#from utils import echo

from sklearn.metrics import roc_curve, auc
import pylab as pl


def mean(array):
    return sum(array) / float(len(array))

if __name__ == '__main__':

    if len(sys.argv) == 1:
        print 'usage: %s output.png roc.pickle-files' % __file__
        exit(1)

    fig = pl.gcf()
    fig.set_size_inches(12, 12)
    fig_name = sys.argv[1]
    fname = open(sys.argv[2], "r")
    probs = []
    responses = []
    for line in fname:
        column = line.strip().split()
	response = column[0]
	responses.append(int(response))
	prob = column[1]
	probs.append(float(prob)) 
    y = np.array(responses)
    scores = np.array(probs) 
    fpr, tpr, thresholds = roc_curve(y, scores, pos_label=1)
    roc_auc = auc(fpr, tpr)
    print "Area under the ROC curve : %f" % roc_auc
    # Plot ROC curve
    pl.plot(fpr, tpr, label=fig_name)
#    pl.plot(fpr, tpr, label=os.path.split(fname)[1]
 #                           .replace('.pickle', '')
  #                          .replace('.wig', '')
   #                         .replace('_roc', '')
    #                        .replace('mark_signal', 'm_sig.')
     #                       .replace('_vs_', '-')
      #                      + ' (AUC=%0.2f, C=%.2f, P=%.2f)' % (roc_auc, mean(responses), mean(probs)))

    pl.plot([0, 1], [0, 1], 'k--')
    pl.xlim([0.0, 1.0])
    pl.ylim([0.0, 1.0])
    pl.xlabel('False Positive Rate')
    pl.ylabel('True Positive Rate')
    pl.title('Receiver operating characteristic example')

    pl.legend(loc="lower right")
    # pl.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

    pl.savefig(fig_name)

#Plots PRC when a file with responses and probabilities (labels and scores) is provided
#Petko's Code for ROC, Modified by Olivera, Jan 1st, 2017

#python ./plot_PRC.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCPi/PRC_chr1 /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Pi_labels_scores/labels_scores_chr1        

import matplotlib
matplotlib.use("Agg")
import os
import pickle
import sys
import numpy as np
#from utils import echo

from sklearn.metrics import precision_score, recall_score, precision_recall_curve, average_precision_score
import pylab as pl
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
avg_pr_scr = average_precision_score(y, scores)
print avg_pr_scr
precision, recall, thresholds = precision_recall_curve(y, scores)
# Plot Precision-Recall curve
pl.clf()
pl.plot(recall, precision, color='navy', label=fig_name)
pl.xlabel('Recall')
pl.ylabel('Precision')
pl.ylim([0.0, 1.05])
pl.xlim([0.0, 1.0])
pl.legend(loc="lower right")
pl.title('Precision-Recall example')
pl.savefig(fig_name)

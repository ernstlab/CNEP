#Plots ROC when a file with responses and probabilities (labels and scores) is provided
#Petko's Code, Modified by Olivera, Feb 2nd, 2016

#python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCPi/ROC_pi_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Pi_labels_scores/labels_scores_chr       
#python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCOmega/ROC_omega_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Omega_labels_scores/labels_scores_chr       
#python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCPhastCons/ROC_phastCons_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PhastCons_labels_scores/labels_scores_chr       
#python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCGERP/ROC_GERP_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/GERP_labels_scores/labels_scores_chr       

import matplotlib
matplotlib.use("Agg")
import os
import sys
import numpy as np
#from utils import echo

from sklearn.metrics import roc_curve, auc
import pylab as pl

def mean(array):
    return sum(array) / float(len(array))

def get_pair(line):
  key, sep, value = line.strip().partition(" ")
  return int(key), value

if __name__ == '__main__':
	if len(sys.argv) == 1:
		print 'usage: %s 10samples_l1_lambda1 labels_scores_sorted_chr'
		exit(1)
fig = pl.gcf()
fig.set_size_inches(12, 12)
fig_name = sys.argv[1]
responses=[]
probs=[]
for i in range(1, 24):
	y=np.array([])
	scores=np.array([])
	fname = open(sys.argv[2]+str(i), "r")
	for line in fname:
		column = line.strip().split()
		response=column[0]
		prob=column[1]
		responses.append(int(response))
		probs.append(float(prob))
	y = np.array(responses)
	scores = np.array(probs) 
fpr, tpr, thresholds = roc_curve(y, scores, pos_label=1)
roc_auc = auc(fpr, tpr)
print "Area under the ROC curve : %f" % roc_auc
# Plot ROC curve
pl.plot(fpr, tpr, label="all chromosomes" + ' (AUC=%0.2f, C=%.2f, P=%.2f)' % (roc_auc, mean(responses), mean(probs)))
pl.plot([0, 1], [0, 1], 'k--')
pl.xlim([0.0, 1.0])
pl.ylim([0.0, 1.0])
pl.xlabel('False Positive Rate')
pl.ylabel('True Positive Rate')
pl.title('Receiver Operating Characteristic')

pl.legend(loc="lower right")
# pl.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

pl.savefig(fig_name)

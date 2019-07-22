#Plots PRC when a file with responses and probabilities (labels and scores) is provided
#Petko's Code for ROC, Modified by Olivera, Jan 1st, 2017

#python ./plot_PRC_Overlay.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCPi/PRC_pi_overlay /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Pi_labels_scores/labels_scores_chr       
#python ./plot_PRC_Overlay.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCOmega/PRC_omega_overlay /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Omega_labels_scores/labels_scores_chr       
#python ./plot_PRC_Overlay.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCPhastCons/PRC_phastCons_overlay /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PhastCons_labels_scores/labels_scores_chr       
#python ./plot_PRC_Overlay.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCGERP/PRC_GERP_overlay /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/GERP_labels_scores/labels_scores_chr       

import matplotlib
matplotlib.use("Agg")
import os
import sys
import numpy as np
#from utils import echo

from sklearn.metrics import precision_recall_curve
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
for i in range(1, 24):
	responses=[]
	probs=[]
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
	precision, recall, thresholds = precision_recall_curve(y, scores)
	# Plot Precision-Recall curve
	pl.plot(recall, precision, color='navy', label=fig_name)
pl.xlabel('Recall')
pl.ylabel('Precision')
pl.ylim([0.0, 1.05])
pl.xlim([0.0, 1.0])
#pl.legend(loc="lower right")
pl.title('Precision-Recall example')
pl.savefig(fig_name)
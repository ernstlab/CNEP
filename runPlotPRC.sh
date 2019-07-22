#!/bin/bash

for i in {4..23};
do
	python ./plot_PRC.py ./PRCPhastCons/PRC_chr$i ./PhastCons_labels_scores/labels_scores_chr$i
done

for i in {1..23};
do
	python ./plot_PRC.py ./PRCGERP/PRC_chr$i ./GERP_labels_scores/labels_scores_chr$i
done

for i in {1..23};
do
	python ./plot_PRC.py ./PRCCNEPAVGPi/PRC_chr$i ./CNEPAVG_Pi_labels_scores/labels_scores_chr$i
done

for i in {1..23};
do
	python ./plot_PRC.py ./PRCCNEPAVGOmega/PRC_chr$i ./CNEPAVG_Omega_labels_scores/labels_scores_chr$i
done

for i in {1..23};
do
	python ./plot_PRC.py ./PRCCNEPAVGPhastCons/PRC_chr$i ./CNEPAVG_PhastCons_labels_scores/labels_scores_chr$i
done

for i in {1..23};
do
	python ./plot_PRC.py ./PRCCNEPAVGGERP/PRC_chr$i ./CNEPAVG_GERP_labels_scores/labels_scores_chr$i
done

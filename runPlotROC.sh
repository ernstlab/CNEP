#!/bin/bash
for i in {1..23};
do
	python ./plot_ROC.py 10samples_l1_lambda1_chr$i labels_scores_sorted_chr$i
done

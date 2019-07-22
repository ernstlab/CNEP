#!/bin/bash
for i in {1..23};
do
	./scorePredictions train_liblinear test_liblinear $i > AUC_10samples_l1_lambda1_chr$i
done

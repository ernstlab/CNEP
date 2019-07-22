#!/bin/bash
. /u/local/Modules/default/init/modules.sh
module load python/2.7.3
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCPi/ROC_pi_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Pi_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCOmega/ROC_omega_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Omega_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCPhastCons/ROC_phastCons_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PhastCons_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCGERP/ROC_GERP_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/GERP_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCCNEPAVGPi/ROC_CNEPAVG_pi_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_Pi_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCCNEPAVGOmega/ROC_CNEPAVG_omega_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_Omega_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCCNEPAVGPhastCons/ROC_CNEPAVG_phastCons_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_PhastCons_labels_scores/labels_scores_chr       
python ./plot_ROC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/ROCCNEPAVGGERP/ROC_CNEPAVG_GERP_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_GERP_labels_scores/labels_scores_chr       

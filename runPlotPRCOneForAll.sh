#!/bin/bash
. /u/local/Modules/default/init/modules.sh
module load python/2.7.3
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCPi/PRC_pi_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Pi_labels_scores/labels_scores_chr       
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCOmega/PRC_omega_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/Omega_labels_scores/labels_scores_chr       
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCPhastCons/PRC_phastCons_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PhastCons_labels_scores/labels_scores_chr       
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCGERP/PRC_GERP_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/GERP_labels_scores/labels_scores_chr   
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCCNEPAVGPi/PRC_CNEPAVG_pi_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_Pi_labels_scores/labels_scores_chr       
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCCNEPAVGOmega/PRC_CNEPAVG_omega_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_Omega_labels_scores/labels_scores_chr       
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCCNEPAVGPhastCons/PRC_CNEPAVG_phastCons_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_PhastCons_labels_scores/labels_scores_chr       
python ./plot_PRC_OneForAll.py /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/PRCCNEPAVGGERP/PRC_CNEPAVG_GERP_all /u/project/ernst/ogrujic/zarlab/scorePredictionsAllBP/CNEPAVG_GERP_labels_scores/labels_scores_chr           

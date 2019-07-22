#!/bin/bash
#./createFeatureVector train_x_filename part[0-12] test_chromosome[0-23] sampleNumber training_sample_file feature_vector_folder
echo $SGE_TASK_ID
./createFeatureVector train_x_liblinear $SGE_TASK_ID 0 82 sampleTrainingPositions ../train_x_rows


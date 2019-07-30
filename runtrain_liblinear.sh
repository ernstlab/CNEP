#!/bin/tcsh

set i = 0
while ($i < 10)
gunzip TRAINDIR_UPDATED/$1_$i.$2.gz
LIBLINEAR/liblinear-2.1/train -s 6 -B 1 -c 1 TRAINDIR_UPDATED/$1_$i.$2 MODELS_UPDATED/$1_$i.$2.model
gzip TRAINDIR_UPDATED/$1_$i.$2
gzip MODELS_UPDATED/$1_$i.$2.model
@ i++
end

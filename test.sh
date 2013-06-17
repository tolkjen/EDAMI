#!/bin/bash

# for report
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.5 > results/naive_binary_0_5.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.5 > results/naive_real_0_5.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.5 > results/triangle_binary_0_5.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.5 > results/triangle_real_0_5.txt

# detailed naive-realbinary tests
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.6 > results/naive_binary_0_6.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.65 > results/naive_binary_0_65.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.7 > results/naive_binary_0_7.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.75 > results/naive_binary_0_75.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.8 > results/naive_binary_0_8.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.85 > results/naive_binary_0_85.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.9 > results/naive_binary_0_9.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i binary -t 0.95 > results/naive_binary_0_95.txt

# detailed naive-real tests
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.6 > results/naive_real_0_6.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.65 > results/naive_real_0_65.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.7 > results/naive_real_0_7.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.75 > results/naive_real_0_75.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.8 > results/naive_real_0_8.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.85 > results/naive_real_0_85.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.9 > results/naive_real_0_9.txt
./tanimoto ~/sports.mat -s all -r all -a naive -i real -t 0.95 > results/naive_real_0_95.txt

# detailed triangle-binary tests
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.6 > results/triangle_binary_0_6.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.65 > results/triangle_binary_0_65.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.7 > results/triangle_binary_0_7.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.75 > results/triangle_binary_0_75.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.8 > results/triangle_binary_0_8.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.85 > results/triangle_binary_0_85.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.9 > results/triangle_binary_0_9.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i binary -t 0.95 > results/triangle_binary_0_95.txt

# detailed triangle-real tests
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.6 > results/triangle_real_0_6.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.65 > results/triangle_real_0_65.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.7 > results/triangle_real_0_7.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.75 > results/triangle_real_0_75.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.8 > results/triangle_real_0_8.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.85 > results/triangle_real_0_85.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.9 > results/triangle_real_0_9.txt
./tanimoto ~/sports.mat -s all -r all -a triangle -i real -t 0.95 > results/triangle_real_0_95.txt


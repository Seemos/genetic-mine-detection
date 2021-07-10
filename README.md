# genetic-mine-detection
A genetic algorithm based approach to the detection of mines based on sonar data. Depending on the parameters chosen, the accuracy of this implementation reaches up to 90% for the training data and up to 87% for the testing data. However, the parameters can be set to achieve an accuracy of 90.6% for the testing set at the expense of reducing the accuracy for the training set. 

Altough this programm has been written with the purpose of mine detection in mind, it can be adapted to work for other tasks, given that they can be represented using sequences of real numbers.

## Code
The code for this repository has been cloned from https://github.com/Seemos/simple-genetic-algorithm and was modified to suit the task of mine detection. The code for reading and writing .csv files has been copied from https://github.com/Seemos/simple-neural-network.

## Data
The data included in this repository is a modified version of the *"Connectionist Bench (Sonar, Mines vs. Rocks)". It has been modified to contain numerical values only. The original data set used is available for download from the machine learning repository of the University of California, Irvine<sup>1</sup> and is licensed under a Creative Commons Attribution 4.0 International [(CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/legalcode) license.


### References
[1] Dua, D. and Graff, C. (2019). UCI Machine Learning Repository [http://archive.ics.uci.edu/ml]. Irvine, CA: University of California, School of Information and Computer Science. 
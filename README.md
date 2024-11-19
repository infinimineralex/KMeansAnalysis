# Hello!

Use 
```
g++ -std=c++2a -I. main.cpp -o kmeans
```
to compile the code. Make sure you have installed gnuplot so that sciplot will function correctly. To install gnuplot (from WSL Ubuntu command line) run these commands:

```
sudo apt-get update -y 
sudo apt-get install -y gnuplot
```

If you aren't on the WSL Ubuntu command line for this, go to http://www.gnuplot.info/download.html, and download+install the right gnuplot version for your device. Then, simply 
```
run_tests kmeans
```
to see the tests and their visualizations (if you have that script)! Some of the tests will take a while, this is normal as there is a high number of data points in those tests.

# EXAMPLE TEST AND TIMING:
```
time ./kmeans < tests/t03.in
How many clusters should there be? (Write below)
What's the name of the file we're using?
Running the algorithm with this many data points: 412
What test number is this? 
The centroid coordinates are: 
Centroid #1: 
X: 23.7465
Y: 88.0645
Centroid #2: 
X: 12.4633
Y: 77.5554
Centroid #3: 
X: 17.6677
Y: 79.9906
Centroid #4: 
X: 21.6491
Y: 73.4359
Centroid #5: 
X: 28.9481
Y: 77.3323

real    0m0.344s
user    0m0.038s
sys     0m0.003s
```
My results match the verified outputs found in the tests folder.

-Alex
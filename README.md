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

-Alex
#include "include/fileutils.h"
#include "include/kmeans.h"
#include "include/centroid.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <ratio>
#include <stdlib.h>
#include <stdio.h>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace fileutils;

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    std::cerr << "Please provide a path to data, the number of max iterations, and the number of clusters to initialize." << std::endl;
    return -1;
  }

  std::string data_path = argv[1];
  int iterations = atoi(argv[2]);
  int K = atoi(argv[3]);


  std::vector<CrimeRecord> records = parseCSV(data_path);
  KMeans kmeans(K, iterations);
  kmeans.Initialize(records);
  kmeans.Run();

  //kmeans.WriteCentroidsToFile("results/CentroidsLocation.txt");
  //kmeans.WriteAllToFile("results/Points.txt");




  return 0;
}

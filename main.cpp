#include "include/fileutils.h"
#include "include/KMeans.h"
#include "include/Centroid.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>



using namespace FileUtils;

int main(int argc, char *argv[])
{
  if(argc < 1)
  {
    std::cerr << "Please provide a path to data." << std::endl;
    return -1;
  }

  std::string data_path = argv[1];
  std::vector<CrimeRecord> records = parseCSV(data_path);

  int K = 5;
  int iterations = 100;

  KMeans kmeans(K, iterations);
  kmeans.initialize(records);



  return 0;
}

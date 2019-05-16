#include "include/fileutils.h"
#include "include/KMeans.h"
#include "include/Centroid.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <unistd.h>
#include <ratio>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

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

  int K = 100;
  int iterations = 100;

  KMeans kmeans(K, iterations);
  kmeans.initialize(records);

  auto start = chrono::steady_clock::now();
  kmeans.run();
  auto end = chrono::steady_clock::now();

  fsec fs = end-start;
  ms d = std::chrono::duration_cast<ms>(fs);
  std::cout << "Elapsed Time in seconds: "<< fs.count() << "\n";
  cout << "Elapsed time in milliseconds : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;


  return 0;
}

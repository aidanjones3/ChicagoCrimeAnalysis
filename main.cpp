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

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace fileutils;

int main(int argc, char *argv[])
{
  if(argc < 1)
  {
    std::cerr << "Please provide a path to data." << std::endl;
    return -1;
  }

  std::string data_path = argv[1];
  std::vector<CrimeRecord> records = parseCSV(data_path);

  //int K = 10;

  std::vector<double> wss;
  double sse;

  for(int i = 1; i < 21; i++)
  {
    int iterations = 50;
    int K = i;
    KMeans kmeans(K, iterations);
    kmeans.Initialize(records);
    kmeans.Run();
    sse = kmeans.WithinClusterSS();
    std::cout << "WSS: " << sse;
    wss.push_back(sse);
    //kmeans.WriteCentroidsToFile("results/CentroidsLocation.txt");
    //kmeans.WriteAllToFile("results/Points.txt");
  }


  ofstream file;
  file.open("results/ElbowMethodResultsFullData.txt");

  if(file.is_open())
  {
    for(int i = 1; i < 21; i++)
    {
      //TODO
      file << i << " ";
      file << wss[i] << " ";
      file << std::endl;
    }
    file.close();
  }
  else
  {
    std::cout << "Can't Write to Output File.";
  }

  return 0;
}

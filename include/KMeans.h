#ifndef KMEANS_H_
#define KMEANS_H_

#pragma once

#include "Centroid.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace FileUtils;

class KMeans
{
public:

  KMeans(int K, int iterations)
  {
    this->K = K;
    this->iterations = iterations;
  }

  void initialize(std::vector<CrimeRecord> &records)
  {
    this->records = records;
    //TODO
    this->num_of_records_ = this->records.size();
    int n = this->records.size();
    std::vector<int> data_ids;

    // We initialze the centroids as random indices of our records.
    for(int i = 0; i < this->K; i++)
    {
      while(true)
      {
        int index = rand() % n;
        if(find(data_ids.begin(), data_ids.end(),index) == data_ids.end()) // NEED BETTER WAY TO CHECK IF NOT IN THERE
        {
          data_ids.push_back(index);
          this->records[index].cid = i;
          Centroid centroid(i, this->records[index].latitude, this->records[index].longitude);
          this->centroids.push_back(centroid);
          break;
        }
      }
    }

    std::cout << "Centroids Succesfully Initialized: " << this->centroids.size() << std::endl;
  }

  void run()
  {
    //TODO
    std::cout << "Running K-Means..." << std::endl;

    // To keep track of number of iterations
    int counter = 1;

    while(true)
    {
      std::cout << "Iteration Number: " << counter << std::endl;

      bool complete = true;

      // First Step (Add All Points To Nearest Centroid)
      for(int i = 0; i < this->num_of_records_; i++)
      {
        int current_cid = records[i].cid;
        int closest_cid = getNearestCentroid(records[i]);

        if(current_cid != closest_cid){

          // If the record is already assigned to a centroid, remove it from that centroid
          if(current_cid != 0){

            for(int j = 0; j < this->K; j++){

              if(centroids[j].clusterId == current_cid){
                centroids[j].removeRecord(records[i].id);
              }
            }
          }

          // Add the record to the corresponding centroid
          for(int j = 0; j < this->K; j++)
          {
            if(centroids[j].clusterId == closest_cid){
              centroids[j].addRecord(records[i]);
            }
          }
          records[i].cid = closest_cid;
          complete = false;

        }
      }

      // Second Step: Update Centroids To Reflect New Record Assignments
      for(int i = 0; i < this->K; i++)
      {
        int num_of_records_in_centroid = centroids[i].data.size();

        double lat_sum = 0;
        double long_sum = 0;

        if(num_of_records_in_centroid > 0)
        {
          for(int z = 0; z < num_of_records_in_centroid; z++)
          {
            lat_sum += centroids[i].data[z].latitude;
            long_sum += centroids[i].data[z].longitude;
          }
          lat_sum /= num_of_records_in_centroid;
          long_sum /= num_of_records_in_centroid;
        }

        centroids[i].longitude = long_sum;
        centroids[i].latitude = lat_sum;
      }

      if(complete || counter >= this->iterations)
      {
        std::cout << "Clustering completed at iteration: " << counter << std::endl;
        break;
      }

      counter++;
    }

    for(int i = 0; i < K; i++)
    {
      std::cout.precision(11);
      std::cout << centroids[i].clusterId << "\t" << centroids[i].latitude << "\t" << centroids[i].longitude << "\n";
    }
  }

  int getNearestCentroid(CrimeRecord record)
  {
    int outputId;
    double min_distance;
    double cur_distance;

    // Initialize Min Distance & outputId as First clusterId
    min_distance = sqrt( pow(centroids[0].longitude - record.longitude, 2.0) + pow(centroids[0].latitude - record.latitude, 2.0) );
    outputId = centroids[0].clusterId;

    // Then Iterate Through the Rest of the Clusters to Check if One is Closer.
    for(int i = 1; i < this->K; i++)
    {
      cur_distance = sqrt( pow(centroids[i].longitude - record.longitude, 2.0) + pow(centroids[i].latitude - record.latitude, 2.0) );

      if(cur_distance < min_distance)
      {
        min_distance = cur_distance;
        outputId = centroids[i].clusterId;
      }


    }

    return outputId;
  }


private:
  std::vector<CrimeRecord> records;
  int num_of_records_;
  int K;
  int iterations;
  std::vector<Centroid> centroids;


};
#endif /* KMEANS_H_ */

#ifndef KMEANS_H_
#define KMEANS_H_

#pragma once

#include "centroid.h"

#include <iostream>
#include <vector>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace fileutils;

class KMeans
{
public:

  KMeans(int K, int iterations)
  {
    this->K = K;
    this->iterations_ = iterations;
    std::cout << "\n" << this->iterations_ << "\n";
  }

  void Initialize(std::vector<CrimeRecord> &records)
  {
    this->records_ = records;
    //TODO
    this->num_of_records_ = this->records_.size();
    int n = this->records_.size();
    std::vector<int> data_ids;

    // We initialze the centroids as random indices of our records.
    for(int i = 0; i < this->K; i++)
    {
      while(true)
      {
        int index = rand() % n;
        if(find(data_ids.begin(), data_ids.end(),index) == data_ids.end())
        {
          data_ids.push_back(index);
          this->records_[index].cid = i;

          Centroid centroid(i, this->records_[index].latitude,
                  this->records_[index].longitude);

          this->centroids_.push_back(centroid);
          break;
        }
      }
    }

    std::cout << "Centroids Succesfully Initialized: "
            << this->centroids_.size() << std::endl;
  }

  void Run()
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
        int current_cid = records_[i].cid;
        int closest_cid = GetNearestCentroid(records_[i]);

        if(current_cid != closest_cid){

          // If the record is already assigned to a centroid,
          // remove it from that centroid
          if(current_cid != 0){

            for(int j = 0; j < this->K; j++){

              if(centroids_[j].cluster_id_ == current_cid){
                centroids_[j].RemoveRecord(records_[i].id);
              }
            }
          }

          // Add the record to the corresponding centroid
          for(int j = 0; j < this->K; j++)
          {
            if(centroids_[j].cluster_id_ == closest_cid){
              centroids_[j].AddRecord(records_[i]);
            }
          }
          records_[i].cid = closest_cid;
          complete = false;

        }
      }

      // Second Step: Update Centroids To Reflect New Record Assignments
      for(int i = 0; i < this->K; i++)
      {
        int num_of_records_in_centroid = centroids_[i].data_.size();

        double lat_sum = 0;
        double long_sum = 0;

        if(num_of_records_in_centroid > 0)
        {
          for(int z = 0; z < num_of_records_in_centroid; z++)
          {
            lat_sum += centroids_[i].data_[z].latitude;
            long_sum += centroids_[i].data_[z].longitude;
          }
          lat_sum /= num_of_records_in_centroid;
          long_sum /= num_of_records_in_centroid;
        }

        centroids_[i].longitude_ = long_sum;
        centroids_[i].latitude_ = lat_sum;
      }

      if(complete || counter >= this->iterations_)
      {
        std::cout << "Clustering completed at iteration: "
                << counter << std::endl;
        break;
      }

      counter++;
    }

    for(int i = 0; i < K; i++)
    {
      std::cout.precision(11);
      std::cout << centroids_[i].cluster_id_ << "\t" << centroids_[i].latitude_
              << "\t" << centroids_[i].longitude_ << "\n";
    }
  }

  int GetNearestCentroid(CrimeRecord record)
  {
    int outputId;
    double min_distance;
    double cur_distance;

    // Initialize Min Distance & outputId as First clusterId
    // min_distance = sqrt( pow(centroids_[0].longitude_ - record.longitude, 2.0)
    //         + pow(centroids_[0].latitude_ - record.latitude, 2.0) );
    min_distance = LatLongDistance(centroids_[0].latitude_,
            centroids_[0].longitude_, record.latitude, record.longitude);
    outputId = centroids_[0].cluster_id_;

    // Then Iterate Through the Rest of the Clusters to Check if One is Closer.
    for(int i = 1; i < this->K; i++)
    {
      // cur_distance = sqrt( pow(centroids_[i].longitude_ - record.longitude, 2.0)
      //         + pow(centroids_[i].latitude_ - record.latitude, 2.0) );

      cur_distance = LatLongDistance(centroids_[i].latitude_,
              centroids_[i].longitude_, record.latitude, record.longitude);

      if(cur_distance < min_distance)
      {
        min_distance = cur_distance;
        outputId = centroids_[i].cluster_id_;
      }


    }

    return outputId;
  }

  double HaversineFormula(double latitude_one, double longitude_one, double latitude_two, double longitude_two)
  {
    double output;

    double term_one = pow(sin( (latitude_two * (M_PI/180)  - latitude_one * (M_PI/180)) / 2 ), 2);
    double term_two = cos(latitude_one * (M_PI/180));
    double term_three = cos(latitude_two * (M_PI/180));
    double term_four = pow(sin( (longitude_two * (M_PI/180) - longitude_one * (M_PI/180))/2 ), 2);

    output = term_one + term_two * term_three * term_four;

    return output;

  }

  double LatLongDistance(double latitude_one, double longitude_one, double latitude_two, double longitude_two)
  {
    double output;
    double haversine_dist = HaversineFormula(latitude_one, longitude_one, latitude_two, longitude_two);

    double term_one = 2 * atan2(sqrt(haversine_dist), sqrt(1-haversine_dist));

    output = kEarthRadius * term_one;

    return output;
  }

  double WithinClusterSS()
  {

    double wss = 0;

    for(int i = 0; i < this->K; i++)
    {
      for(int j = 0; j < this->centroids_[i].data_.size(); j++)
      {

        wss += pow(this->centroids_[i].data_[j].latitude
                - this->centroids_[i].latitude_,2);

        wss += pow(this->centroids_[i].data_[j].longitude
                - this->centroids_[i].longitude_,2);
      }
    }

    return wss;
  }

  void WriteCentroidsToFile(std::string output_file_path)
  {
    ofstream file;
    file.open(output_file_path);

    if(file.is_open())
    {
      for(int i = 0; i < this->centroids_.size(); i++)
      {
        //TODO
        file.precision(11);
        file << this->centroids_[i].cluster_id_ << " ";
        file << this->centroids_[i].latitude_ << " ";
        file << this->centroids_[i].longitude_ << " ";
        file << std::endl;
      }
      file.close();
    }
    else
    {
      std::cout << "Can't Write to Output File.";
    }
  }

  void WriteAllToFile(std::string output_file_path)
  {
    ofstream file;
    file.open(output_file_path);

    if(file.is_open())
    {
      for(int i = 0; i < this->centroids_.size(); i++)
      {
        for(int j = 0; j < centroids_[i].data_.size(); j++)
        {
          //TODO
          file.precision(11);
          file << this->centroids_[i].data_[j].cid << " ";
          file << this->centroids_[i].data_[j].latitude << " ";
          file << this->centroids_[i].data_[j].longitude << " ";
          file << std::endl;
        }
      }
      file.close();
    }
    else
    {
      std::cout << "Can't Write to Output File.";
    }
  }


public:
  std::vector<CrimeRecord> records_;
  int num_of_records_;
  int K;
  int iterations_;
  std::vector<Centroid> centroids_;

  const double kEarthRadius = 6356;


};
#endif /* KMEANS_H_ */

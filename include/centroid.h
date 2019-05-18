#ifndef CENTROID_H_
#define CENTROID_H_

#pragma once

#include "fileutils.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace fileutils;

class Centroid
{
public:
  Centroid(int clusterId, double lat, double longitude)
  {
    this->cluster_id_ = clusterId;
    this->longitude_ = longitude;
    this->latitude_ = lat;
  }

  void AddRecord(CrimeRecord record)
  {
    record.cid = this->cluster_id_;
    this->data_.push_back(record);
  }

  bool RemoveRecord(double id)
  {
    int size = this->data_.size();
    for(int i = 0; i < size; i++)
    {
      if(this->data_[i].id == id)
      {
        this->data_.erase(this->data_.begin() + i);
        return true;
      }
    }
    return false;
  }


public:
  int cluster_id_;
  std::vector<CrimeRecord> data_;
  double longitude_;
  double latitude_;
};

#endif /* CENTROID_H_ */

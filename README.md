---
K-Means Implementation for Chicago Crime Analysis
Estimated Finish Date: May 20
---
This project was meant to be a showcase of a use-case for the common K-Means algorithm. K-Means is used to analyze all recorded crimes in the city of Chicago (dataset found here: https://www.kaggle.com/currie32/crimes-in-chicago#Chicago_Crimes_2012_to_2017.csv), identify high crime zones, and how they have shifted from 2001 to 2017.

Other Libraries Used:
  1. Boost - (input file parsing)
  2. GNUPlot - (visualization of results)

---
Overview
---
*Centroid.h* contains my implementation of a centroid or cluster, and also contains utility functions for the class such as adding and removing a data point from the centroid.

*fileutils.h* contains the definition of the data structure used to store crime records in, as well as a parsing function.

*KMeans.h* contains the actual algorithm implementation using the `Centroid` class and `CrimeRecord` structure.

*utilities.h* contains the function for writing results to a txt file for further visualization.

---
Results
---

Currently in Progress to Provide Performance Plots Using Elbow Method and visualization of centroid locations.

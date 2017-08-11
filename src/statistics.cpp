#include "include/statistics.hpp"

float mean(std::vector<float> dist_true_predicted)
{
	return (std::accumulate(dist_true_predicted.begin(), dist_true_predicted.end(), 0.0) / dist_true_predicted.size());
}

#include "include/toTxt.hpp"

void exportToTxt(std::vector<float> dist_true_predicted,  std::string target_file)
{
	std::ofstream fileStream(target_file, std::ios::out);
	if(fileStream.is_open())
	{
		fileStream << " erreur de prédiction pour chaque point : " << "\n ";
		for(int i = 0; i < dist_true_predicted.size(); i++)
		{
			fileStream << dist_true_predicted[i] << "\n ";
		}
	}
	fileStream << "moyenne des erreurs de prédiction: " << mean(dist_true_predicted);
	fileStream.close ();
}

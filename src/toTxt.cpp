#include "include/toTxt.hpp"

void exportToTxt(std::vector<std::tuple<int, float, float, float>> coefficients, std::string target_file)
{
	std::ofstream fileStream(target_file, std::ios::out);
	if(fileStream.is_open())
	{
		fileStream << " erreur de prédiction pour chaque point : " << "\n ";
		for(int i = 0; i < coefficients.size(); i++)
		{
			fileStream << std::get<0>(coefficients[i]) << " " << std::get<1>(coefficients[i]) << " " << std::get<2>(coefficients[i]) << " " << std::get<3>(coefficients[i]) << "\n ";
		}
	}
	fileStream.close ();
}

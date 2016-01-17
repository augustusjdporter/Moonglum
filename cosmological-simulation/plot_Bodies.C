#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <utility>
#include <fstream>

void plot_Bodies()
{
	const int body_number(5000);
	//const double kPc(3.0857*(10**19));
	double xPosition_start[body_number], yPosition_start[body_number], zPosition_start[body_number];
	double xPosition_end[body_number], yPosition_end[body_number], zPosition_end[body_number];
	string name;
	ifstream file, file2;
	string filename;
	filename = "StartCoords.txt";//(shapename).txt
	file.open ("EndCoords.txt");
	file2.open("StartCoords.txt");

	for (int i=0; i<body_number; i++)
	{
		file >> name >> xPosition_end[i] >> yPosition_end[i] >> zPosition_end[i];
		file2 >> name >> xPosition_start[i] >> yPosition_start[i] >> zPosition_start[i];
	}
	file.close();
	file2.close();

	TGraph2D* plot_start = new TGraph2D(body_number, xPosition_start, yPosition_start, zPosition_start);
	double dummy_x[6] = {plot_start->GetXmax(), plot_start->GetXmin(), 0, 0, 0, 0};
  	double dummy_y[6] = {0, 0, plot_start->GetYmax(), plot_start->GetYmin(), 0, 0};
  	double dummy_z[6] = {0, 0, 0, 0, plot_start->GetXmax(), plot_start->GetXmin()};
  	TGraph2D* dummy = new TGraph2D(6, dummy_x, dummy_y, dummy_z);
	TCanvas *c2 = new TCanvas("before","before",350,400);
	dummy->GetXaxis()->SetTitle("X");
	dummy->GetYaxis()->SetTitle("Y");
	dummy->GetZaxis()->SetTitle("Z");
	
	dummy->Draw("P");
	plot_start->Draw("P same");


	c2->Print("test.eps");
  	c2->Write();
  	
  	

	TGraph2D* plot_end = new TGraph2D(body_number, xPosition_end, yPosition_end, zPosition_end);
	TCanvas *c1 = new TCanvas("after","after",350,400);
	dummy->Draw("P");
	plot_end->Draw("P same");
	c1->Print("test.eps");
  	c1->Write();

  	


	return;
}
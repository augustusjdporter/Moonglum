#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <utility>
#include <fstream>
//convert -delay 20 Plot_It_00*.eps movie.gif
//gs -sDEVICE=epswrite -dNOPAUSE -dBATCH -dSAFER -sOutputFile=sin_800.eps *.eps

void plot_Bodies()
{
	const int body_number(10000);
	int plot_number;

	cout << "Enter timestep (years): ";
	int timestep;
	cin >> timestep;

	cout << "Enter number of plots: " << endl;
	cin >> plot_number;
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
  	
	double dummy_x1d[6] = {plot_start->GetXmax(), plot_start->GetXmin(), 0, 0};
  	double dummy_y1d[6] = {0, 0, plot_start->GetYmax(), plot_start->GetYmin()};
  	TGraph* graph1d_dummy = new TGraph(4, dummy_x1d, dummy_y1d);
  	graph1d_dummy->GetXaxis()->SetTitle("X");
	graph1d_dummy->GetYaxis()->SetTitle("Y");

for(int i = 0; i < plot_number; i++)
{
	int time_now = timestep*i;
	char time_now_string[20];
	sprintf(time_now_string, "%d years", time_now);
	cout << time_now_string << endl;
	double xPosition[body_number], yPosition[body_number], zPosition[body_number];
	string name_dummy;
	stringstream combiner;
	combiner << "Coords/It_" << i << ".txt";
	string file_name;
	combiner >> file_name;
	cout << file_name << endl;
	const char * c = file_name.c_str();
	//canvases.push_back(new TCanvas(file_name, file_name,350,400));
	TCanvas* temp_canvas = new TCanvas(c, c, 6400, 3200);
	temp_canvas->Divide(2,1);
	temp_canvas->cd(1);
	ifstream file_temp;

	file_temp.open(c);

	for (int j=0; j<body_number; j++)
	{
		file_temp >> name_dummy >> xPosition[j] >> yPosition[j] >> zPosition[j];
	}
	file_temp.close();
	

	TGraph2D* graph_temp = new TGraph2D(body_number, xPosition, yPosition, zPosition);
	graph_temp->SetTitle("time_now_string");

	dummy->Draw("P");
	graph_temp->Draw("P same");
	stringstream name_combiner;
	string plot_name;
	if (i < 10)
	{
		name_combiner << "Coords/Plot_It_000" << i << ".eps"; 
		name_combiner >> plot_name;
	}
	else if (i < 100)
	{
		name_combiner << "Coords/Plot_It_00" << i << ".eps"; 
		name_combiner >> plot_name;
	}
	else if (i < 1000)
	{
		name_combiner << "Coords/Plot_It_0" << i << ".eps"; 
		name_combiner >> plot_name;
	}

	cout << plot_name << endl;
	const char * c_save = plot_name.c_str();
	//temp_canvas->Print(c_save);

	
	//delete temp_canvas;
	//delete graph_temp;

	//TCanvas* temp_canvas1d = new TCanvas(c, c, 350, 400);
	
	TGraph* graph_1d = new TGraph(body_number, xPosition, yPosition);
	graph_1d->SetTitle(time_now_string);
	temp_canvas->cd(2);
	graph1d_dummy->Draw("AP");
	graph_1d->Draw("P");
	stringstream name_combiner1d;
	string plot_name1d;
	if (i < 10)
	{
		name_combiner1d << "Coords/Plot_It_000" << i << "_1d.eps"; 
		name_combiner1d >> plot_name1d;
	}
	else if (i < 100)
	{
		name_combiner1d << "Coords/Plot_It_00" << i << "_1d.eps"; 
		name_combiner1d >> plot_name1d;
	}
	else if (i < 1000)
	{
		name_combiner1d << "Coords/Plot_It_0" << i << "_1d.eps"; 
		name_combiner1d >> plot_name1d;
	}

	cout << plot_name1d << endl;
	const char * c_save1d = plot_name1d.c_str();
	//temp_canvas1d->Print(c_save1d);
	temp_canvas->Print(c_save);
	//delete temp_canvas;
	//delete graph_temp;
	//delete graph_1d;

}

	return;
}
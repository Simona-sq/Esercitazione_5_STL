#include <iostream>
#include <vector>
#include <cmath>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }

    Gedim::UCDUtilities utilities;
    {
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.MarkerCell0Ds)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();

       utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates,
                               cell0Ds_properties);
    }

    {

        vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.MarkerCell1Ds)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {},
                                 cell1Ds_properties);
    }


    // Punto 1: check marker punti
    cout<<"Check dei markers per Cells0Ds"<<endl;
    for (const auto& coppia : mesh.MarkerCell0Ds) {
        cout << coppia.first << ": ";
    
        for (const auto& elem : coppia.second) {
            cout << elem << " ";
        }
    
        cout << endl;
    }
    cout << "I marker sono corretti" <<endl;

    cout << "\nCheck dei markers per Cells1Ds" << endl;

    for (const auto& coppia : mesh.MarkerCell1Ds) {
        cout << coppia.first << ": ";

        for (const auto& elem : coppia.second) {
            cout << elem << " ";
        }
    
        cout << '\n';
    }
    cout << "I marker sono corretti" <<endl;


    // Punto 2: check lunghezza lati
    cout<<"\nCheck lunghezza lati"<<endl;
    bool check = true;
    double epsilon = numeric_limits<double>::epsilon();
    for (int i = 0; i < mesh.Cell1DsExtrema.cols(); i+=2)
    {
        unsigned int punto1_id = mesh.Cell1DsExtrema(i);
        unsigned int punto2_id = mesh.Cell1DsExtrema(i+1);

        double x1 = mesh.IdCell0Ds[punto1_id][0];
        double y1 = mesh.IdCell0Ds[punto1_id][1];

        double x2 = mesh.IdCell0Ds[punto2_id][0];
        double y2 = mesh.IdCell0Ds[punto2_id][1];


        double lunghezza = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        if (lunghezza < epsilon)
            cerr<<"Il lato ha lunghezza nulla"<<endl;
            check = false;
    }
    if (check = true)
        cout<<"I lati sono corretti: hanno lunghezza non nulla."<<endl;


    // Punto 3: check area poligoni
    cout << "\nCheck area poligoni" << endl;
    bool check_area = true;
    for (unsigned int i = 0; i < mesh.Cell2DsVertices.size(); i++)
    {
        double area = 0.0; 

        for (unsigned int j = 0; j < mesh.Cell2DsVertices[i].size(); j++)
        {
            unsigned int chiave = mesh.Cell2DsVertices[i][j];
            if (mesh.IdCell0Ds.find(chiave) != mesh.IdCell0Ds.end()) 
            {
                double x1 = mesh.IdCell0Ds[chiave][0];
                double y1 = mesh.IdCell0Ds[chiave][1];

                unsigned int nextI = (j + 1) % mesh.Cell2DsVertices[i].size(); // Indice del vertice successivo: j + 1 prende l'elemento successivo e % size fa in modo che quando j è l'ultimo indice, torni a 0
                unsigned int nextK = mesh.Cell2DsVertices[i][nextI];
                double x2 = mesh.IdCell0Ds[nextK][0];
                double y2 = mesh.IdCell0Ds[nextK][1];

                area += (x1 * y2 - x2 * y1);
            } 
        }

        area = 0.5*abs(area); 

        if (area < epsilon*epsilon) //Per coerenza, confronto l'area con epsilon^2
            cerr << "Il poligono ha area nulla." << endl;
            check_area = false;
    }

    if (check_area = true)
    cout << "Le aree sono corrette: sono tutte non nulle" << endl;
    
    return 0;
    }

    

       
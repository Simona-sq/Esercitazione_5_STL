#pragma once

#include <iostream>
#include "Eigen/Eigen"

// creo la struttura PolygonalMesh

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumCell0Ds = 0; // numero di punti
    std::vector<unsigned int> Cell0DsId = {}; // Cell0DsId è un vettore con dimensione 1xNumCell0Ds
    Eigen::MatrixXd Cell0DsCoordinates = {}; // Cell0DCoordinates è una matrice con dimensione 2 x NumCell0Ds (x,y)
    std::map<unsigned int, list<unsigned int>> MarkerCell0Ds = {}; // Cell0D è un dizionario di markers
    std::map<unsigned int, vector<double>> IdCell0Ds = {}; // Cell0D è un dizionario di id_punto - coordinate_punto


    unsigned int NumCell1Ds = 0; // numero di segmenti
    std::vector<unsigned int> Cell1DsId = {}; // Cell1DsId è un vettore con dimensione 1xNumCell1Ds
    Eigen::MatrixXi Cell1DsExtrema = {}; // Cell1DExtrema è una matrice con dimensione 2 x NumCell1Ds (fromId,toId)
    std::map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; // Cell1D è un dizionario di markers
    
    unsigned int NumCell2Ds = 0; // numero di poligoni
    std::vector<unsigned int> Cell2DsId = {}; // Cell2DId è un vettore con dimensione 1xNumCell2Ds
    //visto che il numero di lati è variabile, uso un vettore dinamico
    std::vector<std::vector<unsigned int>> Cell2DsVertices = {}; // Cell2DsVertices è una matrice con dimensione 1 x NumberCell2DVertices[NumberCell2D]
    std::vector<std::vector<unsigned int>> Cell2DsEdges = {}; // Cell2DsEdges è una matrice con dimensione 1 x NumberCell2DEdges[NumberCell2D]
    std::map<unsigned int, std::list<unsigned int>> MarkerCell2Ds = {}; // Cell2D è un dizionario di markers
};

}

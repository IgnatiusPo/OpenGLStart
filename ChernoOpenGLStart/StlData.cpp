#define  _CRT_SECURE_NO_WARNINGS
#include "StlData.h"
#include <iostream>
#include <map>
#include <set>
#include <functional>
#define  HEADER_BUFF_SIZE 80


StlData::StlData(const std::string & FilePath, bool isInNewThread) : TargetFilePath(FilePath), ParseThread(nullptr), _isInNewThread(isInNewThread)//, IsSizeKnown(false)
{
	if (isInNewThread)
		ParseThread = new std::thread(&StlData::ParseData, this);
	else
		ParseData();
}


void StlData::ParseData()
{
	_mutex.lock();
	FILE * file = fopen(TargetFilePath.c_str(), "rb");
	char  aBuff[HEADER_BUFF_SIZE];
	fread(aBuff, sizeof(char), HEADER_BUFF_SIZE, file);
	HeaderInfo = aBuff;
	fread(reinterpret_cast<void*>(&NumberOfTriangles), sizeof(NumberOfTriangles), 1, file);
	std::cout << NumberOfTriangles;
	Vertices.reserve(NumberOfTriangles);
	MainGraph.Points.reserve(NumberOfTriangles * 2);
	MainGraph.PointsInfo.reserve(NumberOfTriangles * 2);

	//todo get rid of that shit moron
	PositionsAndNormals.reserve(NumberOfTriangles * 3);
	//todo memory and compiler barrier
	//IsSizeKnown = true;
	_mutex.unlock();
	for (size_t i = 0; i < NumberOfTriangles; ++i)
	{
		
		//fseek(file, sizeof(float) * 3, SEEK_CUR);
		vec3 normalBuff;
		fread(&normalBuff, sizeof(float) * 3, 1, file);
		IndexType IndexArr[3];
		vec3 vBuff;
		fread(&vBuff, sizeof(float) * 3, 1, file);

		PositionsAndNormals.emplace_back(vBuff, normalBuff);

		auto It_1 = Vertices.insert(std::make_pair(vBuff, 0));
		if (It_1.second)
		{
			MainGraph.Points.push_back(vBuff);
			IndexArr[0] = MainGraph.Points.size() - 1;
			It_1.first->second = IndexArr[0];
			MainGraph.PointsInfo.push_back(VertexInfo());
		}
		else
			IndexArr[0] = It_1.first->second;

		fread(&vBuff, sizeof(float) * 3, 1, file);


		PositionsAndNormals.emplace_back(vBuff, normalBuff);

		auto It_2 = Vertices.insert(std::make_pair(vBuff, 0));
		if (It_2.second)
		{
			MainGraph.Points.push_back(vBuff);
			IndexArr[1] = MainGraph.Points.size() - 1;
			It_2.first->second = IndexArr[1];
			MainGraph.PointsInfo.push_back(VertexInfo());
		}
		else
			IndexArr[1] = It_2.first->second;

		fread(&vBuff, sizeof(float) * 3, 1, file);


		PositionsAndNormals.emplace_back(vBuff, normalBuff);

		auto It_3 = Vertices.insert(std::make_pair(vBuff, 0));
		if (It_3.second)
		{
			MainGraph.Points.push_back(vBuff);
			IndexArr[2] = MainGraph.Points.size() - 1;
			It_3.first->second = IndexArr[2];
			MainGraph.PointsInfo.push_back(VertexInfo());
		}
		else
			IndexArr[2] = It_3.first->second;
		//////////////////////////////////////////////////
		MainGraph.PointsInfo[IndexArr[0]].AdjacentVertices.insert(IndexArr[1]);
		MainGraph.PointsInfo[IndexArr[0]].AdjacentVertices.insert(IndexArr[2]);
		MainGraph.PointsInfo[IndexArr[1]].AdjacentVertices.insert(IndexArr[0]);
		MainGraph.PointsInfo[IndexArr[1]].AdjacentVertices.insert(IndexArr[2]);
		MainGraph.PointsInfo[IndexArr[2]].AdjacentVertices.insert(IndexArr[0]);
		MainGraph.PointsInfo[IndexArr[2]].AdjacentVertices.insert(IndexArr[1]);

		fseek(file, sizeof(uint16_t), SEEK_CUR);
	}
	fclose(file);
	std::cout << "Parsed\n";
}


float StlData::DijkstraAlgo(vec3 Start, vec3 End)
{
	auto ItStart = Vertices.find(Start);
	if (ItStart == Vertices.end()) {
		std::cerr << "Start point doesn't exist\n";
		return -1;
	}
	auto ItEnd = Vertices.find(End);
	if (ItEnd == Vertices.end()) {
		std::cerr << "End point doesn't exist\n";
		return -1;
	}
	/////////////////////////////////////////////////////
	IndexType CurrentIndex = (*ItStart).second;
	VertexInfo *CurrentPointInfo = &MainGraph.PointsInfo[CurrentIndex];
	
	CurrentPointInfo->Score = 0;
		
	std::set<IndexType> UnvisitedPoints;
	UnvisitedPoints.insert(CurrentIndex);
	//for (auto& It : CurrentPointInfo.AdjacentVertices)
	//{
	//	float VertexScore = MainGraph.PointsInfo[It].Score = FindDistance(MainGraph.Points[It], MainGraph.Points[CurrentIndex]);
	//	UnvisiblePoints.insert(It);
	//}


	//DijkstraPathPositions.push_back(MainGraph.Points[CurrentIndex]);


	CurrentPointInfo = &MainGraph.PointsInfo[CurrentIndex];
	while (CurrentPointInfo->IsVisited != true && UnvisitedPoints.size() != 0)
	{

		for (auto& It : CurrentPointInfo->AdjacentVertices)
		{
			if (MainGraph.PointsInfo[It].IsVisited != true)
			{
				float NewScore = FindDistance(MainGraph.Points[It], MainGraph.Points[CurrentIndex]) + CurrentPointInfo->Score;
				if (NewScore < MainGraph.PointsInfo[It].Score) {
					MainGraph.PointsInfo[It].Score = NewScore;
					MainGraph.PointsInfo[It].PrevVertexIndex = CurrentIndex;
				}
				UnvisitedPoints.insert(It);
			}
			
		}
		CurrentPointInfo->IsVisited = true;
		
		UnvisitedPoints.erase(CurrentIndex);



		if ((*ItEnd).second == CurrentIndex)
		{
			// push_back all prev vertexIndecies in reverse order
			float pathLenght = CurrentPointInfo->Score;
			while (CurrentPointInfo->PrevVertexIndex != - 1) {
				DijkstraPathPositions.push_back(MainGraph.Points[CurrentPointInfo->PrevVertexIndex]);
				CurrentPointInfo = &MainGraph.PointsInfo[CurrentPointInfo->PrevVertexIndex];
			}

			DijkstraPathPositions.push_back(MainGraph.Points[(*ItStart).second]);
			return pathLenght;
		}
		//////////////////////////////// find minimal score
		float Min = INFINITY;
		for (auto& It : UnvisitedPoints)
		{
			if (MainGraph.PointsInfo[It].Score < Min) {
				Min = MainGraph.PointsInfo[It].Score;
				CurrentIndex = It;
				CurrentPointInfo = &MainGraph.PointsInfo[CurrentIndex];
			}
		}
		

	}
	
	return -1;

}

float StlData::FindDistance(vec3 Point1, vec3 Point2)
{
	return sqrt(pow(Point1.X - Point2.X, 2) + pow(Point1.Y - Point2.Y, 2) + pow(Point1.Z - Point2.Z, 2));
}

void* StlData::GetPositionsAndNormals(unsigned int &realSize) 
{
	realSize = PositionsAndNormals.size();
	return PositionsAndNormals.data();
}

unsigned int StlData::GetFullVerticesSize() const
{
	_mutex.lock();
	unsigned int retVal = PositionsAndNormals.capacity();
	_mutex.unlock();
	return retVal;
}

unsigned int* StlData::GetIndicies(unsigned int &count) const
{
	count = NumberOfTriangles * 3;
	std::vector<unsigned int> vec;
	for (auto vertex : MainGraph.PointsInfo)
	{
		for (auto Adjacent : vertex.AdjacentVertices)
		{
			vec.push_back(Adjacent);
		}
	}
	return vec.data();
}

void* StlData::GetDijkstraPositions(unsigned int &size) 
{
	size = DijkstraPathPositions.size() * sizeof(vec3);

	return DijkstraPathPositions.data();
}

StlData::~StlData()
{
	if(ParseThread)
		ParseThread->join();
}

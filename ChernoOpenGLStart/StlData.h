#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <thread>
#include <mutex>
typedef unsigned int IndexType;

class StlData
{
public:
	struct vec3 {
		float X, Y, Z;
		bool operator==(const vec3 & RVal) const
		{
			return (RVal.X == X) && (RVal.Y == Y) && (RVal.Z == Z);
		}
		vec3(const float& x,const float& y,const float& z) : X(x), Y(y), Z(z) {};
		vec3() : X(0), Y(0), Z(0) {};
	};
	struct Vertex {
		vec3 _position;
		vec3 _normal;
		Vertex(const vec3& position,const vec3& normal) : _position(position), _normal(normal) {};
		Vertex() = default;
	};
	mutable std::mutex _mutex;
	//bool IsSizeKnown;
private:
	struct VertexInfo
	{
		std::set<IndexType> AdjacentVertices;
		float				Score;
		bool				IsVisited;
		int					PrevVertexIndex; /* Vertex index in MainGraph of the Vertex, that was previous in Dijkstra path*/
		VertexInfo() : Score(INFINITY), IsVisited(false), PrevVertexIndex(-1) {};
	};

	struct  VerticesData
	{
		std::vector<vec3>		 Points;
		std::vector<VertexInfo>	 PointsInfo;
	};

	struct VertexHashFunctor
	{
		size_t operator()(const vec3 & Value) const
		{
			std::hash<float> Hasher;
			return (Hasher(Value.X) << 1) ^ ((Hasher(Value.Y) << 1) >> 1) ^ (Hasher(Value.Z) << 1);
		}
	}; 
private:
	VerticesData MainGraph;
	std::unordered_map<vec3,IndexType, VertexHashFunctor> Vertices;
	std::string TargetFilePath;
	std::string HeaderInfo;
	uint32_t NumberOfTriangles;
	std::vector<Vertex> PositionsAndNormals;
	std::vector<vec3> DijkstraPathPositions;
	std::thread* ParseThread;
	bool _isInNewThread;
public:
	StlData(const std::string & FilePath, bool isInNewThread = false);
	void ParseData();
	float DijkstraAlgo(vec3 Start, vec3 End);
	static float FindDistance(vec3 Point1, vec3 Point2);

	void* GetPositionsAndNormals(unsigned int &realSize) ;
	/* blocking function. Returns only when vertices will finish reserve*/
	unsigned int GetFullVerticesSize() const;
	unsigned int* GetIndicies(unsigned int &count) const;
	void* GetDijkstraPositions(unsigned int &size);

	~StlData();
	
};






#pragma once

#include "Cell.h"

class Graph //HC - COMPLETED
{
public:
	Graph(uint32_t vertices);

	void AddEdge(uint32_t vertex, Cell* adjacentCell);

	void BreadthFirstSearch(Cell* cell);

private:
	uint32_t m_Vertices;
	std::vector<std::vector<Cell*>> m_AdjacencyList;

	friend class Pollution;
};

class Pollution //HC - COMPLETED
{
public:
	using Matrix = std::vector<std::vector<Cell>>;

	Pollution(Matrix& matrix, uint32_t vertices);

	static void UpdateCellPollution(Cell* cell, uint32_t level);
   
	static void GetAdjacencyList(Matrix& matrix, size_t i, size_t j, std::vector<Cell*>& list);                // Returns a list of ids to its adjacent cells

	void OnUpdate(Matrix& matrix);

private:
	std::unique_ptr<Graph> m_PollutionNet;
};
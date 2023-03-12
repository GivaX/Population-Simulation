#include "Pollution.h"

Graph::Graph(uint32_t vertices)
	: m_Vertices(vertices)
{
	m_AdjacencyList.resize(vertices);
}

void Graph::AddEdge(uint32_t vertex, Cell* adjacentCell)
{
	m_AdjacencyList[vertex].push_back(adjacentCell);
}

void Graph::BreadthFirstSearch(Cell* cell)
{
	Cell null;
	uint32_t level = 0;
	std::vector<bool> Visited;
	Visited.resize(m_Vertices, false);
	Cell* temp = cell;

	std::queue<Cell*> BFSQueue;

	Visited[cell->id] = true;
	BFSQueue.push(cell);
	null.id = -1;
	BFSQueue.push(&null);

	while (!BFSQueue.empty())
	{
		cell = BFSQueue.front();
		Pollution::UpdateCellPollution(BFSQueue.front(), level);
		BFSQueue.pop();

		if (cell->id == -1)
		{
			level++;
			BFSQueue.push(&null);
			if (BFSQueue.front()->id == -1)
				break;
			
			continue;
		}

		for (auto adjCell : m_AdjacencyList[cell->id])
		{
			if (!Visited[adjCell->id])
			{
				Visited[adjCell->id] = true;
				BFSQueue.push(adjCell);
			}
		}
	}
	cell = temp;
}

Pollution::Pollution(Matrix& matrix, uint32_t vertices)
{
	m_PollutionNet = std::make_unique<Graph>(vertices);
	uint32_t VertexIndex = 0;

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			GetAdjacencyList(matrix, i, j, m_PollutionNet->m_AdjacencyList.at(VertexIndex));
			VertexIndex++;
		}

	}
}

void Pollution::UpdateCellPollution(Cell* cell, uint32_t level)
{
	static uint32_t CurrentPollution = 0;

	if (cell->id == -1)
		return;

	if (level == 0)
	{
		cell->pol = cell->pop;
		CurrentPollution = cell->pol;
		return;
	}

	if (CurrentPollution - level <= 0) //the pollution spread has reached zero
	{
		CurrentPollution = 0;
		return;
	}

	if (CurrentPollution == 0)
		return;

	if (cell->pol > CurrentPollution - level)
		return;

	cell->pol = CurrentPollution - level;
}

void Pollution::OnUpdate(Matrix& matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j].type == "I")
			{
				m_PollutionNet->BreadthFirstSearch(&matrix[i][j]);
			}
		}
	}
}

void Pollution::GetAdjacencyList(Matrix& matrix, size_t i, size_t j, std::vector<Cell*>& list)                // Returns a list of ids to its adjacent cells
{
	if (i - 1 >= 0 && i - 1 < matrix.size() && j + 1 >= 0 && j + 1 < matrix[i].size()) //top right neighbor
	{
		if (matrix[i - 1][j + 1].name != " ")
			list.push_back(&matrix[i - 1][j + 1]);
	}

	if (i >= 0 && i < matrix.size() && j + 1 >= 0 && j + 1 < matrix[i].size()) //mid right neighbor
	{
		if (matrix[i][j + 1].name != " ")
			list.push_back(&matrix[i][j + 1]);
	}

	if (i + 1 >= 0 && i + 1 < matrix.size() && j + 1 >= 0 && j + 1 < matrix[i].size()) //bottom right neighbor
	{
		if (matrix[i + 1][j + 1].name != " ")
			list.push_back(&matrix[i + 1][j + 1]);
	}

	if (i - 1 >= 0 && i - 1 < matrix.size() && j >= 0 && j < matrix[i].size()) //top mid neighbor
	{
		if (matrix[i - 1][j].name != " ")
			list.push_back(&matrix[i - 1][j]);
	}

	if (i - 1 >= 0 && i - 1 < matrix.size() && j - 1 >= 0 && j - 1 < matrix[i].size()) //top left neighbor
	{
		if (matrix[i - 1][j - 1].name != " ")
			list.push_back(&matrix[i - 1][j - 1]);
	}

	if (i >= 0 && i < matrix.size() && j - 1 >= 0 && j - 1 < matrix[i].size()) //mid left neighbor
	{
		if (matrix[i][j - 1].name != " ")
			list.push_back(&matrix[i][j - 1]);
	}

	if (i + 1 >= 0 && i + 1 < matrix.size() && j - 1 >= 0 && j - 1 < matrix[i].size()) //bottom left neighbor
	{
		if (matrix[i + 1][j - 1].name != " ")
			list.push_back(&matrix[i + 1][j - 1]);
	}

	if (i + 1 >= 0 && i + 1 < matrix.size() && j >= 0 && j < matrix[i].size()) //bottom mid neighbor
	{
		if (matrix[i + 1][j].name != " ")
			list.push_back(&matrix[i + 1][j]);
	}
}



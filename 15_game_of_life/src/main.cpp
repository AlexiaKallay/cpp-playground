#include <iostream>
#include <vector>
#include <cstdlib>

const int GRID_ROWS = 20;
const int GRID_COLUMNS = 30;
std::vector<std::vector<int>> universe(GRID_ROWS, std::vector<int>(GRID_COLUMNS, 0));

enum class Patterns
{
	BLOCK,
	BOAT,
	BLINKER,
	BEACON,
	GLIDER
};

bool isWithinUniverse(const int row, const int column)
{
	if (column < 0 || row < 0)
	{
		return false;
	}
	if (column >= GRID_ROWS || row >= GRID_COLUMNS)
	{
		return false;
	}
	return true;
}

void DrawShape(Patterns shape, int startRow, int startColumn)
{
	switch (shape)
	{
	case Patterns::BLOCK:
		if (isWithinUniverse(startRow, startColumn) &&
			isWithinUniverse(startRow, startColumn + 1) &&
			isWithinUniverse(startRow + 1, startColumn) &&
			isWithinUniverse(startRow + 1, startColumn + 1))
		{
			universe[startRow][startColumn] = 1;
			universe[startRow][startColumn + 1] = 1;
			universe[startRow + 1][startColumn] = 1;
			universe[startRow + 1][startColumn + 1] = 1;
		}
		break;
	case Patterns::BOAT:
		if (isWithinUniverse(startRow, startColumn + 2) &&
			isWithinUniverse(startRow + 2, startColumn) &&
			isWithinUniverse(startRow, startColumn) &&
			isWithinUniverse(startRow + 2, startColumn + 2))
		{
			universe[startRow][startColumn] = 1;
			universe[startRow][startColumn + 1] = 1;
			universe[startRow + 1][startColumn] = 1;
			universe[startRow + 1][startColumn + 2] = 1;
			universe[startRow + 2][startColumn + 1] = 1;
		}
		break;
	case Patterns::BLINKER:
		if (isWithinUniverse(startRow, startColumn) &&
			isWithinUniverse(startRow, startColumn + 2))
		{
			universe[startRow][startColumn] = 1;
			universe[startRow][startColumn + 1] = 1;
			universe[startRow][startColumn + 2] = 1;
		}
		break;
	case Patterns::BEACON:
		if (isWithinUniverse(startRow, startColumn) &&
			isWithinUniverse(startRow, startColumn + 3) &&
			isWithinUniverse(startRow + 3, startColumn) &&
			isWithinUniverse(startRow + 3, startColumn + 3))
		{
			universe[startRow][startColumn] = 1;
			universe[startRow][startColumn + 1] = 1;
			universe[startRow + 1][startColumn] = 1;
			universe[startRow + 2][startColumn + 3] = 1;
			universe[startRow + 3][startColumn + 2] = 1;
			universe[startRow + 3][startColumn + 3] = 1;
		}
		break;
	case Patterns::GLIDER:
		if (isWithinUniverse(startRow, startColumn) &&
			isWithinUniverse(startRow, startColumn + 2) &&
			isWithinUniverse(startRow + 2, startColumn) &&
			isWithinUniverse(startRow + 2, startColumn + 2))
		{
			universe[startRow][startColumn + 1] = 1;
			universe[startRow + 1][startColumn + 2] = 1;
			universe[startRow + 2][startColumn] = 1;
			universe[startRow + 2][startColumn + 1] = 1;
			universe[startRow + 2][startColumn + 2] = 1;
		}
		break;
	default:
		std::cout << "Unexpected pattern.";
		break;
	}
}


void setNumberOfNeighbors(std::vector<std::vector<int>>& neighborsMatrix)
{
	for (int row = 0; row < GRID_ROWS; ++row)
	{
		for (int column = 0; column < GRID_COLUMNS; ++column)
		{
			if (universe[row][column] == 1)
			{
				int neighbors = 0;
				if (isWithinUniverse(row + 1, column + 1) && universe[row + 1][column + 1] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row, column - 1) && universe[row][column - 1] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row + 1, column - 1) && universe[row + 1][column - 1] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row - 1, column) && universe[row - 1][column] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row - 1, column + 1) && universe[row - 1][column + 1] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row, column + 1) && universe[row][column + 1] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row + 1, column - 2) && universe[row + 1][column - 2] == 1)
				{
					neighbors += 1;
				}
				if (isWithinUniverse(row + 1, column) && universe[row + 1][column] == 1)
				{
					neighbors += 1;
				}

				neighborsMatrix.at(row).at(column) = neighbors;
			}
		}
	}
}


void createRandomFirstGeneration()
{
	srand(time(NULL));

	for (int cycle = 0; cycle < universe.size() / 2; ++cycle)
	{
		int randomRow = rand() % (universe.size() - 1);
		int randomColumn = rand() % (universe[randomRow].size() - 1);

		DrawShape(Patterns::BEACON, randomRow, randomColumn);
	}
}

void createNewGeneration(const std::vector<std::vector<int>>& neighborsMatrix)
{
	std::vector<std::vector<int>> newUniverse(GRID_ROWS, std::vector<int>(GRID_COLUMNS, 0));

	for (int row = 0; row < GRID_ROWS; ++row)
	{
		for (int column = 0; column < GRID_COLUMNS; ++column)
		{
			if (universe[row][column] == 1)
			{
				if (neighborsMatrix[row][column] < 2) // alive cell with fewer than two live neighbors dies
				{
					newUniverse[row][column] = 0;
				}
				else if (neighborsMatrix[row][column] == 2 || neighborsMatrix[row][column] == 3) // alive cell with two or three live neighbors lives on to the next generation
				{
					newUniverse[row][column] = 1;
				}
				else if (neighborsMatrix[row][column] > 3) // alive cell with more than three live neighbors dies
				{
					newUniverse[row][column] = 0;
				}
			}
			else
			{
				if (neighborsMatrix[row][column] == 3) // dead cell with exactly three live neighbors becomes a live cell
				{
					newUniverse[row][column] = 1;
				}
			}
		}
	}

	universe = newUniverse;
}

void displayUniverse()
{
	for (auto& row : universe)
	{
		for (int column : row)
		{
			std::cout << column << " ";
		}
		std::cout << "\n";
	}
}

int main()
{
	int ticksNumber;

	std::cout << "Number of ticks: ";
	std::cin >> ticksNumber;

	std::vector<std::vector<int>> neighborsMatrix(GRID_ROWS, std::vector<int>(GRID_COLUMNS, 0));

	createRandomFirstGeneration();
	std::cout << "GENERATION 0\n";
	displayUniverse();
	std::cout << "\n";

	for (int gen = 1; gen < ticksNumber; ++gen)
	{
		setNumberOfNeighbors(neighborsMatrix);
		createNewGeneration(neighborsMatrix);
		std::cout << "GENERATION " << gen << ": \n";
		displayUniverse();
		std::cout << "\n";
	}
	return 0;
}
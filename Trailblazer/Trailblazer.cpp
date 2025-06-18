/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Set<Loc> neighbourCost(Grid<double>& world, Loc current) {
    Set<Loc> result;
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
        for (int colOffset = -1; colOffset <= 1; colOffset++) {
            if (rowOffset == 0 && colOffset == 0) {
                continue;
            }
            int neighborRow = current.row + rowOffset;
            int neighborCol = current.col + colOffset;

            if (world.inBounds(neighborRow, neighborCol)) {
                Loc loc = makeLoc(neighborRow, neighborCol);
                result.add(loc);
            }
        }
    }
    return result;
}

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {

	Vector<Loc> path;
	Map<Loc, Color> nodeColors;
	Map<Loc, Loc> parents;
    TrailblazerPQueue<Loc> pq;
    Map<Loc, double> distances;

    nodeColors[start] = YELLOW;
    colorCell(world, start, YELLOW);

    distances[start] = 0;
    pq.enqueue(start, heuristic(start, end, world));

    // Generate the shortest path with dijkstra's algorithm
    while (!pq.isEmpty()) {
        Loc current = pq.dequeueMin();

        nodeColors[current] = GREEN;
        colorCell(world, current, GREEN);

        if (current == end) {
            end = current;
            break;
        }

        Set<Loc> neighbors = neighbourCost(world, current);

        foreach(Loc neighbor in neighbors) {
            double edgeCost = costFn(current, neighbor, world);
			double currentDistance = distances[current];
			double dist = currentDistance + edgeCost;
            if (!nodeColors.containsKey(neighbor)) {
                nodeColors[neighbor] = YELLOW;
                colorCell(world, neighbor, YELLOW);
                distances[neighbor] = dist;
                parents[neighbor] = current;
                pq.enqueue(neighbor, distances[neighbor] + heuristic(neighbor, end, world));
            }
			else if (nodeColors[neighbor] == YELLOW && distances[neighbor] > dist) {
                distances[neighbor] = dist;
                parents[neighbor] = current;
                pq.decreaseKey(neighbor, distances[neighbor] + heuristic(neighbor, end, world));
            }
        }
    }

	Loc current = end;
    while (current != start) {
		path.push_back(current);
        current = parents[current];
    }
	path.push_back(start);

	//reverse path 
	int left = 0;
    int right = path.size() - 1;
    while (left < right) {
        swap(path[left], path[right]);
        left++;
        right--;
    }
    return path;
}

Set<Edge> edgeGenerator(Set<Edge> mazeEdges, int numRows, int numCols){
	for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols-1; j++) {
            Loc start = {i, j};
            Loc right = {i, j + 1};
            Loc down = {i + 1, j};

            if (j + 1 < numCols) {
                Edge edge = {start, right};
                mazeEdges.insert(edge);
            }

            if (i + 1 < numRows) {
                Edge edge = {start, down};
                mazeEdges.insert(edge);
            }
        }
    }
	return mazeEdges;
}

Set<Edge> createMaze(int numRows, int numCols) {
	TrailblazerPQueue<Edge> priorityQueue;
	Set<Edge> mazeEdges;

	edgeGenerator(mazeEdges, numRows, numCols);

	foreach (Edge edge in mazeEdges) {
		priorityQueue.enqueue(edge, randomInteger(0, 10));
	}
	Set<Edge> tree;
	Set<Loc> ends;
	while (!priorityQueue.isEmpty()) {
		Edge e = priorityQueue.dequeueMin();
		if (ends.contains(e.start) && ends.contains(e.end)) {
			continue;
		}
		ends.add(e.start);
		tree.add(e);
	}
	return tree;
}



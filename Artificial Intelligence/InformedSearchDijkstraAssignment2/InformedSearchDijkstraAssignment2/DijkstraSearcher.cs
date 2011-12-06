using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InformedSearchDijkstraAssignment2
{
    class DijkstraSearcher
    {
        private Graph graph = new Graph();
        private Queue<Node> queue = new Queue<Node>();
        private List<Node> visited = new List<Node>();
        private Node goal;

        public void initializeSearcher()
        {
            // Initalize Graph and populate     
	        #region Add Nodes to the Graph
            // Add Nodes to Graph
            graph.AddNode("Arad");      //0
            graph.AddNode("Bucharest"); //1 
            graph.AddNode("Craiova");   //2 
            graph.AddNode("Dobreta");   //3 
            graph.AddNode("Eforie");    //4 
            graph.AddNode("Fagaras");   //5 
            graph.AddNode("Giurgiu");   //6
            graph.AddNode("Hirsova");   //7
            graph.AddNode("Iasi");      //8
            graph.AddNode("Lugoj");     //9 
            graph.AddNode("Mehadia");   //10 
            graph.AddNode("Neamt");     //11 
            graph.AddNode("Oradea");    //12 
            graph.AddNode("Pitesti");   //13 
            graph.AddNode("Rimnicu");   //14 
            graph.AddNode("Sibiu");     //15 
            graph.AddNode("Timisoara"); //16 
            graph.AddNode("Urziceni");  //17 
            graph.AddNode("Vaslui");    //18 
            graph.AddNode("Zerind");    //19
	        #endregion
            #region Add Connections
            // Add Neighbors
            graph.AddNeihbors(graph.Nodes.ElementAt(0), graph.Nodes.ElementAt(19), 75);//   A <-> Z     -75
            graph.AddNeihbors(graph.Nodes.ElementAt(0), graph.Nodes.ElementAt(16), 118);//  A <-> T     -118
            graph.AddNeihbors(graph.Nodes.ElementAt(0), graph.Nodes.ElementAt(15), 140);//  A <-> S     -140
            graph.AddNeihbors(graph.Nodes.ElementAt(19), graph.Nodes.ElementAt(12), 71);//  Z <-> O     -71
            graph.AddNeihbors(graph.Nodes.ElementAt(12), graph.Nodes.ElementAt(15), 151);// O <-> S     -151   
            graph.AddNeihbors(graph.Nodes.ElementAt(16), graph.Nodes.ElementAt(9), 111);//  T <-> L     -111
            graph.AddNeihbors(graph.Nodes.ElementAt(9), graph.Nodes.ElementAt(10), 70);//   L <-> M     -70
            graph.AddNeihbors(graph.Nodes.ElementAt(10), graph.Nodes.ElementAt(3), 75);//   M <-> D     -75
            graph.AddNeihbors(graph.Nodes.ElementAt(3), graph.Nodes.ElementAt(2), 120);//   D <-> C     -120
            graph.AddNeihbors(graph.Nodes.ElementAt(2), graph.Nodes.ElementAt(14), 146);//  C <-> R     -146
            graph.AddNeihbors(graph.Nodes.ElementAt(2), graph.Nodes.ElementAt(13), 138);//  C <-> P     -138
            graph.AddNeihbors(graph.Nodes.ElementAt(14), graph.Nodes.ElementAt(15), 80);//  R <-> S     -80
            graph.AddNeihbors(graph.Nodes.ElementAt(14), graph.Nodes.ElementAt(13), 97);//  R <-> P     -97
            graph.AddNeihbors(graph.Nodes.ElementAt(15), graph.Nodes.ElementAt(5), 99);//   S <-> F     -99
            graph.AddNeihbors(graph.Nodes.ElementAt(5), graph.Nodes.ElementAt(1), 211);//   F <-> B     -211
            graph.AddNeihbors(graph.Nodes.ElementAt(13), graph.Nodes.ElementAt(1), 101);//  P <-> B     -101
            graph.AddNeihbors(graph.Nodes.ElementAt(1), graph.Nodes.ElementAt(6), 90);//    B <-> G     -90
            graph.AddNeihbors(graph.Nodes.ElementAt(1), graph.Nodes.ElementAt(17), 85);//   B <-> U     -85
            graph.AddNeihbors(graph.Nodes.ElementAt(17), graph.Nodes.ElementAt(7), 98);//   U <-> H     -98
            graph.AddNeihbors(graph.Nodes.ElementAt(7), graph.Nodes.ElementAt(4), 86);//    H <-> E     -86
            graph.AddNeihbors(graph.Nodes.ElementAt(17), graph.Nodes.ElementAt(18), 142);// U <-> V     -142
            graph.AddNeihbors(graph.Nodes.ElementAt(18), graph.Nodes.ElementAt(8), 92);//   V <-> I     -92
            graph.AddNeihbors(graph.Nodes.ElementAt(8), graph.Nodes.ElementAt(11), 87);//   I <-> N     -87
            #endregion
         }

        // Clear Searcher
        public void Clear()
        {
            graph.Clear();
            queue.Clear();
            visited.Clear();
            goal = new Node();
        }

        public void EnqueueStartLocation(int startLocationIndex)
        {
            queue.Enqueue(graph.Nodes.ElementAt(startLocationIndex));
            graph.Nodes.ElementAt(startLocationIndex).DistanceFromStart = 0;
        }

        public void SetGoal(int goalIndex)
        {
            goal = graph.Nodes.ElementAt(goalIndex);
        }

        public Node Finalize()
        {
            return goal;
        }

        public void StartSearch()
        {
            Console.WriteLine("Search has Begun!");
            
            // Holder nodes
            Node node;
            Node neighbor;

            while (queue.Count > 0)
            {
                node = queue.Dequeue();

                // Check to see if node is the goal
                if (node == goal)
                {
                    //If its the goal check if all of the neighbors have been visited
                    // and check if all the parent's have their neighbors visited
                }

                // If its not the goal add it to visited
                visited.Add(node);

                // loop through neighbors
                int neighborCount = 0;
                while (node.NeighborsAndValues.Count > neighborCount)
                {
                    // set the neighbor to the current nodes neighbor
                    neighbor = node.NeighborsAndValues.Keys.ElementAt(neighborCount);
                    int distance = node.NeighborsAndValues.Values.ElementAt(neighborCount) + node.DistanceFromStart;
                    bool isQueued = false;
                    int queueIndex = -1;

                    if (neighbor.DistanceFromStart > distance)
                    {
                        // check if it was visited.
                        if (visited.Contains(neighbor))
                        {
                            visited.Remove(neighbor);
                        }
                        // Check to see if it was queued
                        if (queue.Contains(neighbor))
                        {
                            isQueued = true;
                            for (int index = 0; index < queue.Count(); index++)
                            {
                                if(neighbor.ToString() == queue.ElementAt(index).ToString())
                                {  
                                    queueIndex = index;
                                    queue.ToList().RemoveAt(index);
                                }
                            }
                        }
                        // set distance and parent
                        neighbor.DistanceFromStart = distance;
                        neighbor.Parent = node;
                        
                        // if it was queued, at it to where it was queued before
                        if (isQueued && queueIndex >= 0)
                            queue.ToList().Insert(queueIndex, neighbor);
                        else
                            queue.Enqueue(neighbor);
                    }
                    // increment neighbor count
                    neighborCount++;


                }// End Neighbor While
            }// End Queue While
        }// End Search method
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UninformedSearches_AI_Assignement1
{
    class Graph
    {
        // Private Variables
        private List<Node> graphNodes;

        // Constructors
        public Graph()
        {
        }
        public Graph(List<Node> graphNodes)
        {
            if (graphNodes == null)
                this.graphNodes = new List<Node>();
            else
                this.graphNodes = graphNodes;
        }
        // Add a Node
        public void AddNode(Node node)
        {
            // Adds a node to the graph.
            graphNodes.Add(node);
        }

        // Add a Node by Name
        public void AddNode(string name)
        {
            graphNodes.Add(new Node(name));
        }

        // Add a Neighbor
        public void AddNeighbor(Node home, Node newNeighbor)
        {
            // Give home a neighbor
            home.Neighbors.Add(newNeighbor);

            // Becuase this is undirected, and home has a neighbor of newNeighbor
            // newNeighbor has a neighbor of home
            newNeighbor.Neighbors.Add(home);
        }

        // GraphNodes Getter
        public List<Node> Nodes
        {
            get
            {
                return graphNodes;
            }
        }

        // Size of graph
        public int Count
        {
            get
            {
                return graphNodes.Count;
            }
        }

    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InformedSearchDijkstraAssignment2
{
    class Graph
    {
        // Private Variables
        private List<Node> graphNodes;

        // Default Constructor 
        public Graph()
        {
            this.graphNodes = new List<Node>();
        }
        // Constructor Overload with nodeSet
        public Graph(List<Node> nodeSet)
        {
            if (nodeSet == null)
                this.graphNodes = new List<Node>();
            else
                this.graphNodes = nodeSet;
        }

        // Clear Function
        public void Clear()
        {
            graphNodes.Clear();
        }

        // Add Node from a Node
        public void AddNode(Node node)
        {
            graphNodes.Add(node);
        }
        // Add Node from a name
        public void AddNode(string name)
        {
            graphNodes.Add(new Node(name));
        }
        
        // Add Neighbors
        public void AddNeihbors(Node baseNode, Node newNeighbor, int distance)
        {
            // Because this is an undirected Graph, both the base and the 'newNeighbor' become each others neighbors
            baseNode.NeighborsAndValues.Add(newNeighbor, distance);

            newNeighbor.NeighborsAndValues.Add(baseNode, distance);
        }

        // Node getter
        public List<Node> Nodes
        {
            get { return graphNodes; }
        }
        
        // Node Count Getter
        public int NodeCount
        {
            get { return graphNodes.Count; }
        }
    }
}

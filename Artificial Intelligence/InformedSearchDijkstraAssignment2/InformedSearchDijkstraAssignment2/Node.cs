using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InformedSearchDijkstraAssignment2
{
    class Node
    {
        // Private Variables
        private string name;
        private Dictionary<Node, int> neighborsAndValues;
        private Node parent;
        private int distanceFromStart;

        // Default Constructor
        public Node()
        {
            this.neighborsAndValues = new Dictionary<Node, int>();
            distanceFromStart = 9999;
        }
        // Constructor Overload with Name
        public Node(string name)
        {
            this.name = name;
            this.neighborsAndValues = new Dictionary<Node, int>();
            distanceFromStart = 9999;
        }
        // Constructor Overlaod with Name and Neighbors
        public Node(string name, Dictionary<Node, int> neighbors)
        {
            this.name = name;
            this.neighborsAndValues = neighbors;
            distanceFromStart = 9999;
        }

        public void Clear()
        {
            neighborsAndValues.Clear();
            name = "Default";
            parent = new Node();
            distanceFromStart = 9999;
        }

        // Name getter and setter
        public string Name
        {
            get { return name; }

            set { name = value; }
        }

        // Parent getter and setter
        public Node Parent
        {
            get { return parent; }

            set { parent = value; }
        }

        // DistanceFromStart getter and setter
        public int DistanceFromStart
        {
            get { return distanceFromStart; }

            set { distanceFromStart = value; }
        }

        // Neighbors getter and setter
        public Dictionary<Node, int> NeighborsAndValues
        {
            get { return neighborsAndValues; }

            set { neighborsAndValues = value; }
        }

        // Override of ToString()
        public override string ToString()
        {
            return name;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UninformedSearches_AI_Assignement1
{
    class Node
    {
        // Private Variables
        private List<Node> neighbors;
        private string name;

        // Constructors
        public Node() 
        { 
        }
        public Node(string name)
        {
            this.name = name;
        }
        public Node(string name, List<Node> neighbors)
        {
            this.name = name;
            this.neighbors = neighbors;
        }

        // Name Getter and Setter
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }

        // Neighbor Getter and Setter
        public List<Node> Neighbors
        {
            get
            {
                return neighbors;
            }
            set
            {
                neighbors = value;
            }
        }

    }
}

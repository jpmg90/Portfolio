using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace UninformedSearches_AI_Assignement1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnStartSearch_Click(object sender, EventArgs e)
        {
            //check for which Search to run
            if (rbtnBreadth.Checked == true)
            {
                //Run Breadth First Search
            }
            if (rbtnDepth.Checked == true)
            {
                //Run Depth First Search
            }
        }
    }
}

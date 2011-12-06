using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace InformedSearchDijkstraAssignment2
{
    public partial class Form1 : Form
    {
        // Create Searcher
        DijkstraSearcher dijkstraSearcher = new DijkstraSearcher();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void btnStartSearch_Click(object sender, EventArgs e)
        {
            // Clear Searcher and Initialize it
            dijkstraSearcher.Clear();
            dijkstraSearcher.initializeSearcher();

            // Set Visibility to false and reset Labels
            SetVisibility(false);
            ResetLabels();            

            // Start timer
            Stopwatch time = new Stopwatch();
            time.Start();
            
            // TODO: search!
            dijkstraSearcher.EnqueueStartLocation(cmbStartPoint.SelectedIndex);
            dijkstraSearcher.SetGoal(cmbGoal.SelectedIndex);
            dijkstraSearcher.StartSearch();
            Node FinalGoal = dijkstraSearcher.Finalize();
            
            time.Stop();
            // Display stuff
            lblTimeTaken.Text = time.Elapsed.TotalSeconds + " Seconds";
            lblDistance.Text = FinalGoal.DistanceFromStart.ToString();
            Node parent = FinalGoal.Parent;
            while (parent != null)
            {
                lblPathTaken.Text += parent.ToString() + ", ";
                parent = parent.Parent;
            }

            // Set Visibility to true
            SetVisibility(true);


        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            // Quit Application
            Application.Exit();
        }

        // Methods
        private void SetVisibility(bool isVisible)
        {
            // Make Lables Visible or invisible
            lblPathTaken.Visible = isVisible;
            lblTimeTaken.Visible = isVisible;
            lblDistance.Visible = isVisible;
        }

        private void ResetLabels()
        {
            // Reset Labels
            lblPathTaken.Text = "";
            lblTimeTaken.Text = "";
            lblDistance.Text = "";
        }
    }
}

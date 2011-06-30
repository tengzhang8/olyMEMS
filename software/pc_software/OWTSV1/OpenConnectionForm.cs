using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace OWTSV1
{
    public partial class OpenConnectionForm : Form
    {
        public OpenConnectionForm()
        {
            InitializeComponent();
        }

        public string Port
        {
            get 
            {
                if (portComboBox.SelectedItem == null) return null;
                return portComboBox.SelectedItem.ToString();
            }
        }

        private void OpenConnectionForm_Load(object sender, EventArgs e)
        {
            foreach (string port in SerialPort.GetPortNames())
            {
                portComboBox.Items.Add(port);
            }
        }



        private void okButton_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }


    }
}
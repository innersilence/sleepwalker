namespace Sleepwalker
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.collectorStartStopButton = new System.Windows.Forms.Button();
            this.serialPortsComboBox = new System.Windows.Forms.ComboBox();
            this.heartRateLabel = new System.Windows.Forms.Label();
            this.display = new GraphLib.PlotterDisplayEx();
            this.graphPanel = new System.Windows.Forms.Panel();
            this.graphPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // collectorStartStopButton
            // 
            this.collectorStartStopButton.Location = new System.Drawing.Point(194, 23);
            this.collectorStartStopButton.Name = "collectorStartStopButton";
            this.collectorStartStopButton.Size = new System.Drawing.Size(75, 23);
            this.collectorStartStopButton.TabIndex = 0;
            this.collectorStartStopButton.Text = "Start";
            this.collectorStartStopButton.UseVisualStyleBackColor = true;
            this.collectorStartStopButton.Click += new System.EventHandler(this.collectorStartStopButton_Click);
            // 
            // serialPortsComboBox
            // 
            this.serialPortsComboBox.FormattingEnabled = true;
            this.serialPortsComboBox.Location = new System.Drawing.Point(58, 25);
            this.serialPortsComboBox.Name = "serialPortsComboBox";
            this.serialPortsComboBox.Size = new System.Drawing.Size(121, 21);
            this.serialPortsComboBox.TabIndex = 1;
            // 
            // heartRateLabel
            // 
            this.heartRateLabel.AutoSize = true;
            this.heartRateLabel.Font = new System.Drawing.Font("Courier New", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.heartRateLabel.Location = new System.Drawing.Point(12, 9);
            this.heartRateLabel.Name = "heartRateLabel";
            this.heartRateLabel.Size = new System.Drawing.Size(40, 41);
            this.heartRateLabel.TabIndex = 2;
            this.heartRateLabel.Text = ".";
            // 
            // display
            // 
            this.display.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.display.BackColor = System.Drawing.Color.Transparent;
            this.display.BackgroundColorBot = System.Drawing.Color.White;
            this.display.BackgroundColorTop = System.Drawing.Color.White;
            this.display.DashedGridColor = System.Drawing.Color.DarkGray;
            this.display.DoubleBuffering = false;
            this.display.Location = new System.Drawing.Point(3, 3);
            this.display.Name = "display";
            this.display.PlaySpeed = 0.5F;
            this.display.Size = new System.Drawing.Size(492, 311);
            this.display.SolidGridColor = System.Drawing.Color.DarkGray;
            this.display.TabIndex = 4;
            // 
            // graphPanel
            // 
            this.graphPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.graphPanel.Controls.Add(this.display);
            this.graphPanel.Location = new System.Drawing.Point(2, 57);
            this.graphPanel.Name = "graphPanel";
            this.graphPanel.Size = new System.Drawing.Size(498, 317);
            this.graphPanel.TabIndex = 5;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(502, 408);
            this.Controls.Add(this.graphPanel);
            this.Controls.Add(this.heartRateLabel);
            this.Controls.Add(this.serialPortsComboBox);
            this.Controls.Add(this.collectorStartStopButton);
            this.Name = "MainForm";
            this.Text = "Form1";
            this.graphPanel.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button collectorStartStopButton;
        private System.Windows.Forms.ComboBox serialPortsComboBox;
        private System.Windows.Forms.Label heartRateLabel;
        private GraphLib.PlotterDisplayEx display;
        private System.Windows.Forms.Panel graphPanel;
    }
}


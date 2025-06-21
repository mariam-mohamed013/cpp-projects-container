#pragma once

namespace GraphTraversal {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::IContainer^ components;
        System::Windows::Forms::Button^ buttonNextStep;
        System::Windows::Forms::ComboBox^ comboBoxTraversal;
        System::Windows::Forms::ComboBox^ comboBoxGraphs;
        System::Windows::Forms::Panel^ panelGraphVisualizer;
        int currentNodeIndex = -1;
        int startNodeX = 0, startNodeY = 0;  // Default start position
        int endNodeX = 4, endNodeY = 4;      // Default end position
        array<int>^ nodeOrder;
        array<bool>^ visited ;
        array<array<int>^>^ adj;  // Adjacency matrix (array of arrays)

        void InitializeComponent(void)
        {
            this->buttonNextStep = (gcnew System::Windows::Forms::Button());
            this->comboBoxTraversal = (gcnew System::Windows::Forms::ComboBox());
            this->comboBoxGraphs = (gcnew System::Windows::Forms::ComboBox());
            this->panelGraphVisualizer = (gcnew System::Windows::Forms::Panel());
            this->SuspendLayout();

            // comboBoxGraphs
            this->comboBoxGraphs->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
                L"Graph 1", L"Graph 2", L"Graph 3", L"Graph 4", L"Graph 5", L"Graph 6", L"Graph 7", L"Graph 8", L"Graph 9", L"Graph 10"
            });
            this->comboBoxGraphs->Location = System::Drawing::Point(150, 20);
            this->comboBoxGraphs->Name = L"comboBoxGraphs";
            this->comboBoxGraphs->Size = System::Drawing::Size(200, 24);
            this->comboBoxGraphs->TabIndex = 0;
            this->comboBoxGraphs->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBoxGraphs_SelectedIndexChanged);

            // comboBoxTraversal
            this->comboBoxTraversal->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"BFS", L"DFS" });
            this->comboBoxTraversal->Location = System::Drawing::Point(150, 70);
            this->comboBoxTraversal->Name = L"comboBoxTraversal";
            this->comboBoxTraversal->Size = System::Drawing::Size(200, 24);
            this->comboBoxTraversal->TabIndex = 1;
            this->comboBoxTraversal->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBoxTraversal_SelectedIndexChanged);


            // buttonNextStep
            this->buttonNextStep->Location = System::Drawing::Point(150, 110);
            this->buttonNextStep->Name = L"buttonNextStep";
            this->buttonNextStep->Size = System::Drawing::Size(75, 23);
            this->buttonNextStep->TabIndex = 3;
            this->buttonNextStep->Text = L"Next Step";
            this->buttonNextStep->UseVisualStyleBackColor = true;
            this->buttonNextStep->Click += gcnew System::EventHandler(this, &MainForm::buttonNextStep_Click);


            // panelGraphVisualizer
            this->panelGraphVisualizer->Location = System::Drawing::Point(400, 150);
            this->panelGraphVisualizer->Name = L"panelGraphVisualizer";
            this->panelGraphVisualizer->Size = System::Drawing::Size(350, 350);
            this->panelGraphVisualizer->TabIndex = 4;
            this->panelGraphVisualizer->Visible = true;
            this->panelGraphVisualizer->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panelGraphVisualizer_Paint);

            // MainForm
            this->ClientSize = System::Drawing::Size(800, 450);
            this->Controls->Add(this->comboBoxGraphs);
            this->Controls->Add(this->comboBoxTraversal);  // Moved ComboBox for traversal
            this->Controls->Add(this->buttonNextStep);
            this->Controls->Add(this->panelGraphVisualizer);
            this->Name = L"MainForm";
            this->Text = L"Graph Traversal";
            this->ResumeLayout(false);
            this->PerformLayout();

            // Initializing Node Order
            int MAX = 25;
            nodeOrder = gcnew array<int>(MAX);
            visited = gcnew array<bool>(MAX);

            // Initialize adjacency matrix as array of arrays (5 nodes)
            adj = gcnew array<array<int>^>(MAX);
            for (int i = 0; i < MAX; i++)
            {
                adj[i] = gcnew array<int>(MAX);
            }
        }

        void comboBoxGraphs_SelectedIndexChanged(Object^ sender, EventArgs^ e)
        {
            // Run BFS based on selected graph
            int selectedGraph = comboBoxGraphs->SelectedIndex;


            // Depending on the selected graph, set the start and end nodes
            switch (selectedGraph)
            {
            case 0: // Graph 1
                // Test case 1: Graph 1 with start and end nodes at (0, 0) and (2, 0)
                startNodeX = 0; startNodeY = 0;  // Set start node for Graph 1
                endNodeX = 2; endNodeY = 0;     // Set end node for Graph 1
                break;

            case 1: // Graph 2
                // Test case 2: Graph 2 with start and end nodes at (0, 0) and (3, 0)
                startNodeX = 0; startNodeY = 0;  // Set start node for Graph 2
                endNodeX = 3; endNodeY = 0;     // Set end node for Graph 2
                break;

            case 2: // Graph 3
                // Test case 3: Graph 3 with start and end nodes at (0, 0) and (1, 0)
                startNodeX = 0; startNodeY = 0;  // Set start node for Graph 3
                endNodeX = 1; endNodeY = 0;     // Set end node for Graph 3
                break;

            case 3: // Graph 4
                // Test case 4: Graph 4 with start and end nodes at (1, 0) and (3, 0)
                startNodeX = 1; startNodeY = 0;  // Set start node for Graph 4
                endNodeX = 3; endNodeY = 0;     // Set end node for Graph 4
                break;

            case 4: // Graph 5
                // Test case 5: Graph 5 with start and end nodes at (2, 0) and (4, 0)
                startNodeX = 2; startNodeY = 0;  // Set start node for Graph 5
                endNodeX = 4; endNodeY = 0;     // Set end node for Graph 5
                break;

            case 5: // Graph 6
                // Test case 6: Graph 6 with start and end nodes at (0, 0) and (4, 0)
                startNodeX = 0; startNodeY = 0;  // Set start node for Graph 6
                endNodeX = 4; endNodeY = 0;     // Set end node for Graph 6
                break;

            case 6: // Graph 7
                // Test case 7: Graph 7 with start and end nodes at (2, 0) and (0, 1)
                startNodeX = 2; startNodeY = 0;  // Set start node for Graph 7
                endNodeX = 0; endNodeY = 1;     // Set end node for Graph 7
                break;

            case 7: // Graph 8
                // Test case 8: Graph 8 with start and end nodes at (1, 1) and (3, 1)
                startNodeX = 1; startNodeY = 1;  // Set start node for Graph 8
                endNodeX = 3; endNodeY = 1;     // Set end node for Graph 8
                break;

            case 8: // Graph 9
                // Test case 9: Graph 9 with start and end nodes at (0, 2) and (4, 2)
                startNodeX = 0; startNodeY = 2;  // Set start node for Graph 9
                endNodeX = 4; endNodeY = 2;     // Set end node for Graph 9
                break;

            case 9: // Graph 10
                // Test case 10: Graph 10 with start and end nodes at (1, 2) and (3, 3)
                startNodeX = 1; startNodeY = 2;  // Set start node for Graph 10
                endNodeX = 3; endNodeY = 3;     // Set end node for Graph 10
                break;

            default:
                break;
            }

            currentNodeIndex = -1; 

            int selectedTraversal = comboBoxTraversal->SelectedIndex;
            if (selectedTraversal == 0) {
                // Now run BFS on the selected graph
                BFS(startNodeX, startNodeY, endNodeX, endNodeY);
            }
            else {
                // Now run BFS on the selected graph
                DFS(startNodeX, startNodeY, endNodeX, endNodeY);
            }


            panelGraphVisualizer->Invalidate(); // Trigger repaint for new graph visualization
        }

        void comboBoxTraversal_SelectedIndexChanged(Object^ sender, EventArgs^ e)
        {

            // Reset the visited nodes
            for (int i = 0; i < 5; i++) {
                visited[i] = false;
            }

            int selectedTraversal = comboBoxTraversal->SelectedIndex;
            if (selectedTraversal == 0) {
                // Now run BFS on the selected graph
                BFS(startNodeX, startNodeY, endNodeX, endNodeY);
            }
            else {
                // Now run BFS on the selected graph
                DFS(startNodeX, startNodeY, endNodeX, endNodeY);
            }

            currentNodeIndex = -1;

            panelGraphVisualizer->Invalidate(); // Trigger repaint for new graph visualization
        }

        void buttonNextStep_Click(Object^ sender, EventArgs^ e)
        {
            if (currentNodeIndex < nodeOrder->Length - 1)
            {
                currentNodeIndex++;
                panelGraphVisualizer->Invalidate(); // Repaint the graph
            }
        }

        void BFS(int startX, int startY, int endX, int endY) {
            // Directions for moving in the grid (up, down, left, right)
            int dx[] = { -1, 1, 0, 0 };  // Row directions
            int dy[] = { 0, 0, -1, 1 };  // Column directions

            // Queue for BFS
            array<int>^ queueX = gcnew array<int>(25); // Assuming max 25 elements in the queue
            array<int>^ queueY = gcnew array<int>(25); // Separate queues for X and Y coordinates
            int front = 0, back = 0;

            // Initialize the visited array
            array<bool>^ visited = gcnew array<bool>(5 * 5); // Assume a 5x5 grid
            visited[startX * 5 + startY] = true; // Mark the starting cell as visited

            // Enqueue the starting node
            queueX[back] = startX;
            queueY[back] = startY;
            back++;

            int orderIndex = 0;  // Index to store the order in the nodeOrder array

            while (front < back) {
                int x = queueX[front];
                int y = queueY[front];
                front++;

                // Store the current node in the nodeOrder array
                nodeOrder[orderIndex++] = x * 5 + y;

                // If the current node is the end node, stop the search
                if (x == endX && y == endY) {
                    // Optional: store the final path or simply return
                    Console::WriteLine("End node reached!");
                    return;
                }

                // Explore the 4 possible directions (up, down, left, right)
                for (int i = 0; i < 4; i++) {
                    int newX = x + dx[i];
                    int newY = y + dy[i];

                    // Check if the new position is within bounds and not visited
                    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5 && !visited[newX * 5 + newY]) {
                        visited[newX * 5 + newY] = true;  // Mark the new position as visited
                        queueX[back] = newX;  // Enqueue the new x-coordinate
                        queueY[back] = newY;  // Enqueue the new y-coordinate
                        back++;
                    }
                }
            }

            Console::WriteLine("End node not reachable.");
        }

        void DFSRecursive(int x, int y, int endX, int endY,array<bool>^& visited, int numCols, int& orderIndex, bool% goalReached) {
            // Directions for moving in the grid (up, down, left, right)
            int dx[] = { -1, 1, 0, 0 };  // Row directions
            int dy[] = { 0, 0, -1, 1 };  // Column directions

            // Up - Down - Left - Right 

            // Base case: if the current node is the end node, set goalReached to true and return
            if (x == endX && y == endY) {
                nodeOrder[orderIndex++] = x * numCols + y;
                Console::WriteLine("End node reached!");
                goalReached = true; // Update the goalReached flag
                return;
            }

            // Mark the current node as visited and store it in nodeOrder
            visited[x * numCols + y] = true;
            nodeOrder[orderIndex++] = x * numCols + y;

            // If goal has already been reached, return
            if (goalReached) return;

            // Explore the 4 possible directions (up, down, left, right)
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];

                // Check if the new position is within bounds and not visited
                if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5 && !visited[newX * numCols + newY]) {
                    DFSRecursive(newX, newY, endX, endY, visited, numCols, orderIndex, goalReached);
                }

                // If goal is reached, no need to explore further
                if (goalReached) return;
            }
        }

        void DFS(int startX, int startY, int endX, int endY) {
            int numCols = 5;
            int numRows = 5;

            // Initialize the visited array and nodeOrder array
            array<bool>^ visited = gcnew array<bool>(numRows * numCols);

            int orderIndex = 0; // Keep track of the order in nodeOrder
            bool goalReached = false; // Flag to check if the goal is reached

            // Call the recursive DFS function starting from the start node
            DFSRecursive(startX, startY, endX, endY, visited, numCols, orderIndex, goalReached);

            // Print out the nodes visited during DFS
            for (int i = 0; i < orderIndex; i++) {
                Console::Write(nodeOrder[i].ToString() + " ");
            }

            if (goalReached) {
                Console::WriteLine("\nGoal found during DFS traversal.");
            }
            else {
                Console::WriteLine("\nGoal not found during DFS traversal.");
            }
        }


        void panelGraphVisualizer_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            Pen^ pen = gcnew Pen(Color::Black);
            Brush^ textBrush = Brushes::Black;

            int gridSize = 50; // Size of each grid cell
            int numRows = 5;  // Number of rows in the grid
            int numCols = 5;  // Number of columns in the grid

            // Draw horizontal grid lines
            for (int i = 0; i <= numRows; i++)
            {
                g->DrawLine(pen, 0, i * gridSize, numCols * gridSize, i * gridSize);
            }

            // Draw vertical grid lines
            for (int i = 0; i <= numCols; i++)
            {
                g->DrawLine(pen, i * gridSize, 0, i * gridSize, numRows * gridSize);
            }

            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 8);

            // Draw row labels (on the left)
            for (int i = 0; i < numRows; i++)
            {
                g->DrawString(i.ToString(), font, textBrush, -20, i * gridSize + 5);
            }

            // Draw column labels (on the top)
            for (int i = 0; i < numCols; i++)
            {
                g->DrawString(i.ToString(), font, textBrush, i * gridSize + 5, -20);
            }

            // Define the starting node
            int startingNode = 0;

            bool goalReached = false;  // Flag to track when the goal is reached
            // If the current node is the end node and the traversal is finished, set goalReached flag
            if (currentNodeIndex >= 0 && endNodeX * numCols + endNodeY == nodeOrder[currentNodeIndex]) {
                goalReached = true;
            }

            // Create an array to track visited nodes
            array<bool>^ visited = gcnew array<bool>(numRows * numCols);
            for (int i = 0; i < numRows * numCols; i++) {
                visited[i] = false;  // Initialize all nodes as not visited
            }

            // Mark visited nodes during traversal
            if (currentNodeIndex >= 0) {
                for (int i = 0; i <= currentNodeIndex; i++) {
                    visited[nodeOrder[i]] = true;  // Mark node as visited
                }
            }

            for (int i = 0; i < numRows * numCols; i++) {
                int x = (i % numCols) * gridSize + gridSize / 2;
                int y = (i / numCols) * gridSize + gridSize / 2;

                // Determine the brush color based on the node index
                Brush^ nodeBrush;

                if (i == endNodeX * numCols + endNodeY) {
                    if (goalReached) {
                        nodeBrush = Brushes::Purple; // Change goal node color when reached
                    }
                    else {
                        nodeBrush = Brushes::Blue; // Default color for the end node
                    }
                }
                else if (currentNodeIndex >= 0 &&  i == nodeOrder[currentNodeIndex]) {
                    nodeBrush = Brushes::Green; // Color for the current node
                }
                else if (i == startNodeX * numCols + startNodeY) {
                    nodeBrush = Brushes::Red; // Color for the current node
                }
                else if (visited[i]) {
                    nodeBrush = Brushes::Gray; // Color for visited nodes
                }
                else {
                    nodeBrush = Brushes::White; // Default color for unvisited nodes
                }

                // Draw the ellipse and fill it with the determined color
                g->DrawEllipse(pen, x - 15, y - 15, 30, 30);
                g->FillEllipse(nodeBrush, x - 15, y - 15, 30, 30);

                // Draw the node index in black
                g->DrawString(i.ToString(), font, Brushes::Black, x - 5, y - 5);
            }

            // Optionally, show a message when the goal is reached
            if (goalReached) {
                currentNodeIndex = -1;
                g->DrawString("Goal Reached!", font, Brushes::Black, numCols * gridSize + 5, numRows * gridSize - 20);
            }
        }



    };
}

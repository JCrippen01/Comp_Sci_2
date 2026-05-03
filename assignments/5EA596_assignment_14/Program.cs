/*
Assignment 14: The Agent Dashboard
Author: 5EA596

Reflection:
Throughout this course, we used vectors, linked lists, and binary search trees
to understand how data can be stored, searched, inserted, and removed in memory.
Even though databases permanently store data, they still rely on the same basic
ideas of organization and efficient searching. Learning memory-based data
structures helps explain what databases are doing behind the scenes.

A database index relates to a binary search tree because both organize keys so
the system does not need to search every record one by one. Instead of a slow
linear scan, the database can follow an organized path to find records faster.
Many real databases use B-tree style indexes, which are related to the same
ordered-search concept as binary search trees but are better suited for large
amounts of stored data.

AI Statement:
AI was used to help organize the C# WinForms structure, parameterized SQLite
queries, transaction pattern, and documentation formatting. 

Jet Brains IDE was used for all DB testing and work (did not use AI, but has AI capabilitys)

Thank you for the course, I have learned a lot and had lots of fun solving these.
*/

using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Data.Sqlite;

namespace GlobalRoamAgentDashboard
{
    /// <summary>
    /// Main program entry point for the Global Roam Agent Dashboard.
    /// </summary>
    internal static class Program
    {
        /// <summary>
        /// Starts the Windows Forms application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            ApplicationConfiguration.Initialize();
            Application.Run(new AgentDashboardForm());
        }
    }

    /// <summary>
    /// GUI form that allows agents to search clients and view booking history.
    /// </summary>
    public class AgentDashboardForm : Form
    {
        private readonly string connectionString = "Data Source=global_roam.db";

        private TextBox txtFirstName;
        private TextBox txtLastName;
        private Label lblClientInfo;
        private DataGridView dgvBookings;
        private ComboBox cmbFlights;
        private Button btnSearch;
        private Button btnNewBooking;

        private int currentClientId = -1;

        /// <summary>
        /// Initializes the dashboard form and GUI controls.
        /// </summary>
        public AgentDashboardForm()
        {
            Text = "Global Roam Agent Dashboard";
            Width = 850;
            Height = 600;
            StartPosition = FormStartPosition.CenterScreen;

            BuildInterface();
            LoadFlights();
        }

        /// <summary>
        /// Builds the user interface controls for the application.
        /// </summary>
        private void BuildInterface()
        {
            Label lblTitle = new Label
            {
                Text = "Global Roam Agent Dashboard",
                Font = new Font("Arial", 16, FontStyle.Bold),
                Location = new Point(20, 15),
                AutoSize = true
            };

            Label lblFirst = new Label
            {
                Text = "First Name:",
                Location = new Point(20, 65),
                AutoSize = true
            };

            txtFirstName = new TextBox
            {
                Location = new Point(100, 60),
                Width = 150
            };

            Label lblLast = new Label
            {
                Text = "Last Name:",
                Location = new Point(270, 65),
                AutoSize = true
            };

            txtLastName = new TextBox
            {
                Location = new Point(350, 60),
                Width = 150
            };

            btnSearch = new Button
            {
                Text = "Search Client",
                Location = new Point(520, 58),
                Width = 120
            };
            btnSearch.Click += BtnSearch_Click;

            lblClientInfo = new Label
            {
                Text = "Client profile will appear here.",
                Location = new Point(20, 110),
                Width = 780,
                Height = 60,
                BorderStyle = BorderStyle.FixedSingle
            };

            Label lblBookings = new Label
            {
                Text = "Booking History:",
                Location = new Point(20, 190),
                AutoSize = true,
                Font = new Font("Arial", 10, FontStyle.Bold)
            };

            dgvBookings = new DataGridView
            {
                Location = new Point(20, 220),
                Width = 780,
                Height = 230,
                ReadOnly = true,
                AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill
            };

            Label lblNewBooking = new Label
            {
                Text = "New Booking:",
                Location = new Point(20, 475),
                AutoSize = true,
                Font = new Font("Arial", 10, FontStyle.Bold)
            };

            cmbFlights = new ComboBox
            {
                Location = new Point(120, 470),
                Width = 350,
                DropDownStyle = ComboBoxStyle.DropDownList
            };

            btnNewBooking = new Button
            {
                Text = "Create Booking",
                Location = new Point(500, 468),
                Width = 140
            };
            btnNewBooking.Click += BtnNewBooking_Click;

            Controls.Add(lblTitle);
            Controls.Add(lblFirst);
            Controls.Add(txtFirstName);
            Controls.Add(lblLast);
            Controls.Add(txtLastName);
            Controls.Add(btnSearch);
            Controls.Add(lblClientInfo);
            Controls.Add(lblBookings);
            Controls.Add(dgvBookings);
            Controls.Add(lblNewBooking);
            Controls.Add(cmbFlights);
            Controls.Add(btnNewBooking);
        }

        /// <summary>
        /// Handles the client search button click event.
        /// </summary>
        private void BtnSearch_Click(object? sender, EventArgs e)
        {
            string firstName = txtFirstName.Text.Trim();
            string lastName = txtLastName.Text.Trim();

            if (firstName == "" || lastName == "")
            {
                MessageBox.Show("Please enter both first and last name.");
                return;
            }

            SearchClient(firstName, lastName);
        }

        /// <summary>
        /// Searches for a client using a parameterized SQL query.
        /// </summary>
        /// <param name="firstName">Client first name.</param>
        /// <param name="lastName">Client last name.</param>
        private void SearchClient(string firstName, string lastName)
        {
            using SqliteConnection conn = new SqliteConnection(connectionString);
            conn.Open();

            string clientQuery = @"
                SELECT ClientID, FirstName, LastName, Email, City
                FROM Clients
                WHERE FirstName = @FirstName AND LastName = @LastName;
            ";

            using SqliteCommand cmd = new SqliteCommand(clientQuery, conn);
            cmd.Parameters.AddWithValue("@FirstName", firstName);
            cmd.Parameters.AddWithValue("@LastName", lastName);

            using SqliteDataReader reader = cmd.ExecuteReader();

            if (!reader.Read())
            {
                currentClientId = -1;
                lblClientInfo.Text = "Client not found.";
                dgvBookings.DataSource = null;
                return;
            }

            currentClientId = Convert.ToInt32(reader["ClientID"]);

            lblClientInfo.Text =
                $"Client ID: {reader["ClientID"]}\n" +
                $"Name: {reader["FirstName"]} {reader["LastName"]}\n" +
                $"Email: {reader["Email"]} | City: {reader["City"]}";

            reader.Close();

            LoadBookingHistory(currentClientId);
        }

        /// <summary>
        /// Loads a client's booking history using a JOIN between Bookings and Flights.
        /// </summary>
        /// <param name="clientId">Unique client identifier.</param>
        private void LoadBookingHistory(int clientId)
        {
            using SqliteConnection conn = new SqliteConnection(connectionString);
            conn.Open();

            string bookingQuery = @"
                SELECT Flights.Destination, Flights.DepartureTime
                FROM Bookings
                JOIN Flights ON Bookings.FlightID = Flights.FlightID
                WHERE Bookings.ClientID = @ClientID
                ORDER BY Flights.DepartureTime DESC;
            ";

            using SqliteCommand cmd = new SqliteCommand(bookingQuery, conn);
            cmd.Parameters.AddWithValue("@ClientID", clientId);

            using SqliteDataReader reader = cmd.ExecuteReader();

            DataTable table = new DataTable();
            table.Load(reader);

            dgvBookings.DataSource = table;
        }

        /// <summary>
        /// Loads available flights into the new booking combo box.
        /// </summary>
        private void LoadFlights()
        {
            using SqliteConnection conn = new SqliteConnection(connectionString);
            conn.Open();

            string flightQuery = @"
                SELECT FlightID, Destination, DepartureTime, SeatsRemaining
                FROM Flights
                ORDER BY Destination ASC;
            ";

            using SqliteCommand cmd = new SqliteCommand(flightQuery, conn);
            using SqliteDataReader reader = cmd.ExecuteReader();

            DataTable table = new DataTable();
            table.Load(reader);

            cmbFlights.DisplayMember = "DisplayText";
            cmbFlights.ValueMember = "FlightID";

            DataTable displayTable = new DataTable();
            displayTable.Columns.Add("FlightID");
            displayTable.Columns.Add("DisplayText");

            foreach (DataRow row in table.Rows)
            {
                string flightId = row["FlightID"].ToString() ?? "";
                string destination = row["Destination"].ToString() ?? "";
                string departure = row["DepartureTime"].ToString() ?? "";
                string seats = row["SeatsRemaining"].ToString() ?? "";

                displayTable.Rows.Add(
                    flightId,
                    $"{flightId} - {destination} - {departure} | Seats: {seats}"
                );
            }

            cmbFlights.DataSource = displayTable;
        }

        /// <summary>
        /// Handles the new booking button click event.
        /// </summary>
        private void BtnNewBooking_Click(object? sender, EventArgs e)
        {
            if (currentClientId == -1)
            {
                MessageBox.Show("Search for a valid client before creating a booking.");
                return;
            }

            if (cmbFlights.SelectedValue == null)
            {
                MessageBox.Show("Select a flight before creating a booking.");
                return;
            }

            string flightId = cmbFlights.SelectedValue.ToString() ?? "";

            CreateBookingTransaction(currentClientId, flightId);
        }

        /// <summary>
        /// Creates a booking and updates seat count inside a single transaction.
        /// </summary>
        /// <param name="clientId">Client receiving the booking.</param>
        /// <param name="flightId">Flight being booked.</param>
        private void CreateBookingTransaction(int clientId, string flightId)
        {
            using SqliteConnection conn = new SqliteConnection(connectionString);
            conn.Open();

            using SqliteTransaction transaction = conn.BeginTransaction();

            try
            {
                string insertBooking = @"
                    INSERT INTO Bookings (ClientID, FlightID, BookingDate)
                    VALUES (@ClientID, @FlightID, @BookingDate);
                ";

                using SqliteCommand insertCmd = new SqliteCommand(insertBooking, conn, transaction);
                insertCmd.Parameters.AddWithValue("@ClientID", clientId);
                insertCmd.Parameters.AddWithValue("@FlightID", flightId);
                insertCmd.Parameters.AddWithValue("@BookingDate", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
                insertCmd.ExecuteNonQuery();

                string updateSeats = @"
                    UPDATE Flights
                    SET SeatsRemaining = SeatsRemaining - 1
                    WHERE FlightID = @FlightID AND SeatsRemaining > 0;
                ";

                using SqliteCommand updateCmd = new SqliteCommand(updateSeats, conn, transaction);
                updateCmd.Parameters.AddWithValue("@FlightID", flightId);

                int rowsUpdated = updateCmd.ExecuteNonQuery();

                if (rowsUpdated == 0)
                {
                    throw new Exception("No seats remaining or invalid flight.");
                }

                transaction.Commit();

                MessageBox.Show("Booking created successfully.");

                LoadBookingHistory(clientId);
                LoadFlights();
            }
            catch (Exception ex)
            {
                transaction.Rollback();
                MessageBox.Show("Booking failed: " + ex.Message);
            }
        }
    }
}
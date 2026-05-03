/*
Lab 14: SQL Practice Bench
Author: 5EA596

Reflection:
The WHERE clause is dangerous in UPDATE and DELETE statements because it
controls which rows are affected. If a DBA forgets the WHERE clause,
the command will apply to every row in the table. This could result in
all records being modified or completely deleted, causing serious data loss.

AI Statement:
AI was used to assist with understanding how to interact with the SQLite3
command line and to verify SQL syntax. All queries were written, tested,
and adjusted by the me to match the provided database schema.

Software AI Statement:
I used Jet Brains DataGrip IDE to check and test written queries. SQLLITE3 CLI was used to write the queries.
*/

-- Ticket 1: Marketing Outreach
SELECT FirstName, LastName, Email
FROM Clients
WHERE City = 'Barcelona';

-- Ticket 2: New Client Onboarding
INSERT INTO Clients (FirstName, LastName, City, Email)
VALUES ('Diana', 'Prince', 'Themyscira', 'diana@watchtower.com');

-- Ticket 3: Account Security Update
UPDATE Clients
SET Email = 'batman@wayneent.com'
WHERE ClientID = 55;

-- Ticket 4: Schedule Adjustment
DELETE FROM Flights
WHERE FlightID = 'GR-909';

-- Ticket 5: Logistics Report
SELECT *
FROM Flights
ORDER BY DepartureTime DESC;
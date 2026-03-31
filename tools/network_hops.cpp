/**
 * @file justin_crippen_module_11_network_tool.cpp
 * @brief Lightweight networking tool using a graph and BFS to simulate DNS resolution and routing.
 * @author Justin Crippen
 * @date 2026-03-30
 *
 * This program allows a user to enter a domain name, resolves it to an IP address
 * using a simple DNS table, and then finds a path from a client machine to the
 * destination using Breadth First Search (BFS) on a graph of network connections.
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

class NetworkGraph
{
private:
    map<string, vector<string>> graph;   // adjacency list (IP -> neighbors)
    map<string, string> dnsTable;        // domain -> IP

public:

    /**
     * @brief Adds a device (node) to the network graph.
     */
    void addDevice(const string& ip)
    {
        graph[ip];
    }

    /**
     * @brief Adds a connection between two devices (undirected).
     */
    void addConnection(const string& from, const string& to)
    {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    /**
     * @brief Adds a domain name mapping to an IP address.
     */
    void addDomain(const string& domain, const string& ip)
    {
        dnsTable[domain] = ip;
    }

    /**
     * @brief Prints the network graph.
     */
    void printNetwork() const
    {
        cout << "Network Connections:\n";
        for (const auto& pair : graph)
        {
            cout << pair.first << " -> ";
            for (const string& neighbor : pair.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    /**
     * @brief Finds and prints the shortest path between two IPs using BFS.
     */
    bool findPathBFS(const string& start, const string& target)
    {
        if (graph.find(start) == graph.end() || graph.find(target) == graph.end())
        {
            cout << "Start or target device not found.\n";
            return false;
        }

        set<string> visited;
        queue<string> q;
        map<string, string> parent;

        visited.insert(start);
        q.push(start);
        parent[start] = "";

        while (!q.empty())
        {
            string current = q.front();
            q.pop();

            if (current == target)
            {
                vector<string> path;
                string step = target;

                while (step != "")
                {
                    path.push_back(step);
                    step = parent[step];
                }

                reverse(path.begin(), path.end());

                cout << "Path found:\n";
                for (size_t i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if (i < path.size() - 1)
                        cout << " -> ";
                }
                cout << endl;

                cout << "Hop count: " << path.size() - 1 << endl;
                return true;
            }

            for (const string& neighbor : graph[current])
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        cout << "No path found.\n";
        return false;
    }

    /**
     * @brief Resolves a domain name and traces the path from client to destination.
     */
    void resolveAndTrace(const string& domain)
    {
        if (dnsTable.find(domain) == dnsTable.end())
        {
            cout << "Domain not found in DNS table.\n";
            return;
        }

        string destinationIp = dnsTable[domain];

        cout << "Domain: " << domain << endl;
        cout << "Resolved IP: " << destinationIp << endl;
        cout << "Tracing route from client...\n";

        findPathBFS("192.168.1.10", destinationIp);
    }
};

int main()
{
    NetworkGraph net;
    string domainName;

    // Devices (nodes)
    net.addDevice("192.168.1.10");   // client
    net.addDevice("192.168.1.1");
    net.addDevice("10.0.0.1");
    net.addDevice("172.16.0.2");
    net.addDevice("8.8.8.8");
    net.addDevice("1.1.1.1");

    // Connections (edges - undirected)
    net.addConnection("192.168.1.10", "192.168.1.1");
    net.addConnection("192.168.1.1", "10.0.0.1");
    net.addConnection("10.0.0.1", "172.16.0.2");
    net.addConnection("172.16.0.2", "8.8.8.8");
    net.addConnection("172.16.0.2", "1.1.1.1");

    // DNS table
    net.addDomain("google.com", "8.8.8.8");
    net.addDomain("cloudflare.com", "1.1.1.1");

    cout << "=== Lightweight Network Tool ===" << endl;

    // User input loop
    while (true)
    {
        cout << "\nEnter a domain (or type 'exit' to quit): ";
        getline(cin, domainName);

        if (domainName == "exit")
        {
            cout << "Goodbye!" << endl;
            break;
        }

        cout << endl;
        net.resolveAndTrace(domainName);
    }

    return 0;
}

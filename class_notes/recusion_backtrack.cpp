#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

class SocialGraph
{
private:
    map<string, vector<string>> graph;

public:
    void addUser(const string& user)
    {
        graph[user];
    }

    void addFriend(const string& user1, const string& user2)
    {
        graph[user1].push_back(user2);
        graph[user2].push_back(user1);
    }

    void printGraph() const
    {
        for (const auto& pair : graph)
        {
            cout << pair.first << " -> ";

            for (const string& name : pair.second)
            {
                cout << name << " ";
            }

            cout << endl;
        }
    }

    void dfsHelper(const string& current,
                   const string& start,
                   set<string>& visited,
                   set<string>& suggestions)
    {
        visited.insert(current);

        for (const string& neighbor : graph[current])
        {
            if (neighbor == start)
            {
                continue;
            }

            if (visited.find(neighbor) == visited.end())
            {
                if (find(graph[start].begin(), graph[start].end(), neighbor) == graph[start].end())
                {
                    suggestions.insert(neighbor);
                }

                dfsHelper(neighbor, start, visited, suggestions);
            }
        }
    }

    void suggestFriendsDFS(const string& user)
    {
        set<string> visited;
        set<string> suggestions;

        dfsHelper(user, user, visited, suggestions);

        cout << "Friend suggestions for " << user << ": ";

        for (const string& name : suggestions)
        {
            cout << name << " ";
        }

        cout << endl;
    }

    void suggestFriendsBFS(const string& user)
    {
        set<string> visited;
        set<string> suggestions;
        queue<string> q;

        visited.insert(user);
        q.push(user);

        while (!q.empty())
        {
            string current = q.front();
            q.pop();

            for (const string& neighbor : graph[current])
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    q.push(neighbor);

                    if (neighbor != user &&
                        find(graph[user].begin(), graph[user].end(), neighbor) == graph[user].end())
                    {
                        suggestions.insert(neighbor);
                    }
                }
            }
        }

        cout << "BFS suggestions for " << user << ": ";

        for (const string& name : suggestions)
        {
            cout << name << " ";
        }

        cout << endl;
    }
};

int main()
{
    SocialGraph sg;

    sg.addUser("A");
    sg.addUser("B");
    sg.addUser("C");
    sg.addUser("D");
    sg.addUser("E");

    sg.addFriend("A", "B");
    sg.addFriend("A", "C");
    sg.addFriend("B", "D");
    sg.addFriend("C", "E");

    sg.printGraph();

    sg.suggestFriendsDFS("A");
    sg.suggestFriendsBFS("A");

    return 0;
}
//Time Complexity = O(V + E) order of n squared.
//
//what is std::map>
//how it works
//

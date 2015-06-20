#include <bits/stdc++.h>
using namespace std;

vector<set<int> > getConnections(int guests, vector<vector<int> > connections) {
    vector<set<int> > conn;
    for (int i = 0; i < guests; i++) {
        set<int> c;
        conn.push_back(c);
    }

    for (unsigned i = 0; i < connections.size(); i++) {
        conn[connections[i][0] - 1].insert(connections[i][1]);
        conn[connections[i][1] - 1].insert(connections[i][0]);
    }

    //    for (unsigned i = 0; i < conn.size(); i++) {
    //        set<int>::iterator j;
    //        for (j = conn[i].begin(); j != conn[i].end(); ++j) {
    //            cout << *j << " ";
    //        }
    //        cout << endl;
    //    }

    return conn;
}

map<int, set<int> > formatConnections(vector<set<int> > conn) {
    map<int, set<int> > m;

    for (unsigned i = 0; i < conn.size(); i++) {
        m[i + 1] = conn[i];
    }

    //    map<int, set<int> >::iterator i;
    //    for (i = m.begin(); i != m.end(); ++i) {
    //        cout << i->first << ": ";
    //        set<int>::iterator j;
    //        for (j = i->second.begin(); j != i->second.end(); ++j) {
    //            cout << *j << " ";
    //        }
    //        cout << endl;
    //    }

    return m;
}

vector<int> getInvalidGuests(map<int, set<int> > party, int known, int unknown) {
    vector<int> invalid;
    int number = party.size();
    map<int, set<int> >::iterator i;
    for (i = party.begin(); i != party.end(); ++i) {
        int guestsKnown = i->second.size();
        if (guestsKnown < known or number - guestsKnown - 1 < unknown) {
            invalid.push_back(i->first);
        }
    }
    return invalid;
}

map<int, set<int> > removeGuests(vector<int> invalidGuests, map<int, set<int> > party) {
    for (unsigned i = 0; i < invalidGuests.size(); i++) {
        party.erase(invalidGuests[i]);
        map<int, set<int> >::iterator j;
        for (j = party.begin(); j != party.end(); ++j) {
            j->second.erase(invalidGuests[i]);
        }
    }
    return party;
}

int main() {
    int guests, conn, known, unknown;
    freopen("partyin.txt", "r", stdin);
    scanf("%d %d %d %d", &guests, &conn, &known, &unknown);

    vector<vector<int> > connections;
    for (int i = 0; i < conn; i++) {
        int j, k;
        scanf("%d %d", &j, &k);
        vector<int> c;
        c.push_back(j);
        c.push_back(k);
        connections.push_back(c);
    }
    fclose(stdin);

    //    cout << guests << endl;
    //    cout << conn << endl;
    //    cout << known << endl;
    //    cout << unknown << endl;

    //    for (unsigned i = 0; i < connections.size(); i++) {
    //        printf("%d %d\n", connections[i][0], connections[i][1]);
    //    }

    map<int, set<int> > party = formatConnections(getConnections(guests, connections));

    while (true) {
        vector<int> invalidGuests = getInvalidGuests(party, known, unknown);
        if (invalidGuests.size() == 0) {
            break;
        }
        //        for (unsigned i = 0; i < invalidGuests.size(); i++) {
        //            cout << invalidGuests[i] << " ";
        //        }
        //        cout << endl;
        party = removeGuests(invalidGuests, party);
    }

    //    cout << party.size() << endl;

    freopen("partyout.txt", "w", stdout);
    printf("%lu", party.size());
    fclose(stdout);
    return 0;
}

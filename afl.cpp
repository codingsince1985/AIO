#include <bits/stdc++.h>
using namespace std;

map<int, vector<int> > segments;

int populate(int size, int pos) {
    if (segments.count(size) == 0) {
        vector<int> segment;
        segment.push_back(pos);
        segments[size] = segment;
    } else {
        segments[size].push_back(pos);
    }
}

int getKeyOfMaxSize(int booking) {
    int max = 0;
    map<int, vector<int> >::iterator i;
    for (i = segments.begin(); i != segments.end(); ++i) {
        if (max < i->first and i->second.size() > 0) {
            max = i->first;
        }
    }
    return max;
}

vector<int> compute(vector<int> bookings) {
    vector<int> results;

    for (int i = 0; i < bookings.size(); i++) {
        int booking = bookings[i];
        int keyOfMaxSize = getKeyOfMaxSize(booking);

        vector<int> pos = segments[keyOfMaxSize];
        sort(pos.begin(), pos.end());
        results.push_back(pos[0]);

        int newSize = keyOfMaxSize - booking;
        int newPos = pos[0] + booking;
        populate(newSize, newPos);

        pos.erase(pos.begin());
        segments[keyOfMaxSize] = pos;
    }
    return results;
}

void getEmptySizeAndPosition(vector<int> takens, int totalSeats) {
    int index = 1;
    for (int i = 0; i < takens.size(); i++) {
        int taken = takens[i];
        if (taken - index > 0) {
            //            cout << "pos " << index << " segment " << taken - index << endl;
            populate(taken - index, index);
        }
        index = taken + 1;
    }

    if (totalSeats + 1 - index > 0) {
        //        cout << "pos " << index << " segment " << totalSeats + 1 - index << endl;
        populate(totalSeats + 1 - index, index);
    }
}

int main() {
    int totalSeats, totalTaken, totalBookings;
    freopen("aflin.txt", "r", stdin);
    scanf("%d %d", &totalSeats, &totalTaken);

    vector<int> takens;
    for (int i = 0; i < totalTaken; i++) {
        int taken;
        scanf("%d", &taken);
        takens.push_back(taken);
    }

    int totalBooking;
    scanf("%d", &totalBooking);
    vector<int> bookings;
    for (int i = 0; i < totalBooking; i++) {
        int booking;
        scanf("%d", &booking);
        bookings.push_back(booking);
    }
    fclose(stdin);

    getEmptySizeAndPosition(takens, totalSeats);
    //    map<int, vector<int> >::iterator i;
    //    for (i = segments.begin(); i != segments.end(); ++i) {
    //        cout << i->first << endl;
    //        vector<int> pos = i->second;
    //        for (int j = 0; j < pos.size(); j++) {
    //            cout << "  " << pos[j] << endl;
    //        }
    //    }

    vector<int> results = compute(bookings);

    freopen("aflout.txt", "w", stdout);
    for (int i = 0; i < results.size(); i++) {
        printf("%d\n", results[i]);
    }
    fclose(stdout);
    return 0;
}
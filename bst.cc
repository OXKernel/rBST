/*
 * Copyright (C) 2023. Roger Doss. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#include <time.h>
#include <stdlib.h>

#include <list>
#include <set>
#include "bst.h"

using std::list;
using std::set;

//#define TRIALS 1000000
//#define TRIALS 5000000
//#define TRIALS 100
//#define TRIALS 100000
//#define TRIALS 4000000 // 4 m
#define TRIALS 10000000 // 10 m
//#define TRIALS 100000000
//#define TRIALS 50000000
#define BILLION 1000000000L

#define _RANDOMIZED_INSERT 1
#define _SEARCH 1
#define _DELETE 1

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::make_pair;
using std::map;
using std::unordered_map;

char *istr(int i)
{
    static char buf[2048]={0};
    sprintf(buf,"%d",i);
    return buf;
}

int
main()
{
    BinarySearchTree bst;
#ifdef _RANDOMIZED_INSERT
    int count = 0, val = 0;
    set<int> orders;
    srand(time(0));
    while(count != TRIALS) {
        val = rand();
        if(orders.find(val) != orders.end()) {
            continue;
        }
        orders.insert(val);
        count++;
    }
#endif
    // Use standard high res timers.
    struct timespec start, stop;
    double accum;// time.h
    printf ("starting test\n");
    if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
      cout << "error getting time" << endl;
      return -1;
    }
    // insert

#ifdef _RANDOMIZED_INSERT
    set<int>::iterator j = orders.begin();
    for(int i = 0; i < TRIALS; ++i, ++j) {
        if (bst.add((*j)) == false) {
            cout << "error adding values" << endl;
            cout << " line= " << __LINE__ << endl;
            exit(0);
        }
    }
#else
    for(int i = 0; i < TRIALS; ++i) {
        if (bst.add(i) == false) {
            cout << "error adding values" << endl;
            cout << " line= " << __LINE__ << endl;
            exit(0);
        }
    }
#endif
#ifdef _SEARCH
#ifdef _RANDOMIZED_INSERT
    for(set<int>::iterator i = orders.begin(); i != orders.end(); ++i) {
        bool val = bst.search((*i));
        if(val == false) {
             cout << "error retrieving values" << endl;
             cout << " line= " << __LINE__ << endl;
             exit(0);
        }
    }
#else
    // retrieve
    for(int i = 0; i < TRIALS; ++i) {
        bool val = bst.search(i);
        if(val == false) {
             cout << "error retrieving values" << endl;
             cout << " line= " << __LINE__ << endl;
             exit(0);
        }
    }
#endif
#endif
    // delete
#ifdef _DELETE
#ifdef _RANDOMIZED_INSERT
    for(set<int>::iterator i = orders.begin(); i != orders.end(); ++i) {
        bst.remove((*i));
    }
#else
    for(int i = 0; i < TRIALS; ++i) {
        bst.remove(i);
    }
#endif
#endif
    if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
      cout << "error getting time" << endl;
      return -1;
    }
    accum = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    printf( "rBST %lf\n", accum );

    // unordered_map
    if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
      cout << "error getting time" << endl;
      return -1;
    }
    unordered_map<string, int> test_map1;
    //map<string, int> test_map1;
#ifdef _RANDOMIZED_INSERT
    set<int>::iterator j1 = orders.begin();
    for(int i = 0; i < TRIALS; ++i, ++j1) {
        test_map1.insert(make_pair(istr((*j1)),(*j1)));
    }
#else
    for(int i = 0; i < TRIALS; ++i) {
        test_map1.insert(make_pair(istr(i),i));
    }
#endif
#ifdef _SEARCH
#ifdef _RANDOMIZED_INSERT
    for(set<int>::iterator i = orders.begin(); i != orders.end(); ++i) {
        int val = test_map1[istr((*i))];
        val++;
        if(val < 0) {
            cout << "error retrieving values" << endl;
            cout << " line= " << __LINE__ << endl;
            exit(0);
        }
    }
#else
    for(int i = 0; i < TRIALS; ++i) {
        int val = test_map1[istr(i)];
        val++;
        if(val < 0) {
            cout << "error retrieving values" << endl;
            cout << " line= " << __LINE__ << endl;
            exit(0);
        }
    }
#endif
#endif
#ifdef _DELETE
#ifdef _RANDOMIZED_INSERT
    for(set<int>::iterator i = orders.begin(); i != orders.end(); ++i) {
	    test_map1.erase(istr((*i)));  // Delete.
    }
#else
    for(int i = 0; i < TRIALS; i++) {
	    test_map1.erase(istr(i));  // Delete.
    }
#endif
#endif
    if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
      cout << "error getting time" << endl;
      return -1;
    }
    accum = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    printf( "unordered_map %lf\n", accum );
    // std::map
    if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
      cout << "error getting time" << endl;
      return -1;
    }
    map<string, int> test_map;
#ifdef _RANDOMIZED_INSERT
    set<int>::iterator j2 = orders.begin();
    for(int i = 0; i < TRIALS; ++i, ++j2) {
        test_map.insert(make_pair(istr((*j2)),(*j2)));
    }
#else
    for(int i = 0; i < TRIALS; ++i) {
        test_map.insert(make_pair(istr(i),i));
    }
#endif
#ifdef _SEARCH
#ifdef _RANDOMIZED_INSERT
    for(set<int>::iterator i = orders.begin(); i != orders.end(); ++i) {
        int val = test_map[istr((*i))];
        val++;
        if(val < 0) {
            cout << "error retrieving values" << endl;
            cout << " line= " << __LINE__ << endl;
            exit(0);
        }
    }
#else
    for(int i = 0; i < TRIALS; ++i) {
        int val = test_map[istr(i)];
        val++;
        if(val < 0) {
            cout << "error retrieving values" << endl;
            cout << " line= " << __LINE__ << endl;
            exit(0);
        }
    }
#endif
#endif
#ifdef _DELETE
#ifdef _RANDOMIZED_INSERT
    for(set<int>::iterator i = orders.begin(); i != orders.end(); ++i) {
	    test_map.erase(istr((*i)));  // Delete.
    }
#else
    for(int i = 0; i < TRIALS; i++) {
	    test_map.erase(istr(i));  // Delete.
    }
#endif
#endif
    if(clock_gettime(CLOCK_REALTIME, &stop) == -1) {
      cout << "error getting time" << endl;
      return -1;
    }
    accum = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    printf( "std::map %lf\n", accum );
    return 0;
}

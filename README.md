# Robot Path Finding Using A* Algorithm

Run the following command to clone the repository:
```
    git clone https://github.com/fanxiule/path_finding_challenge
```

Compile the program:
```
    g++ -std=c++11 path_finding.cpp node.cpp -o Prog
```

Run the program:
```
    ./Prog
```

After the program starts, type in the waypoints in the form of column_index row_index penalty. E.g.:
```
    5 5 10
```

After all of the waypoints are typed in, type FINISH to start the calculations. The program will return the time required to finish the task
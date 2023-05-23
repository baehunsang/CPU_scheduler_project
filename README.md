# CPU_scheduler_project
---

## Sample output
```
process 0
process pid: 0
process arrival_time: 1
process cpu_burst_time: 4
process io_start_time: 1
process io_burst_time: 5
process priority: 5
process remainint_cpu_time: 4
process remaining_io_time: 5
process is_end: 0

process 1
process pid: 1
process arrival_time: 4
process cpu_burst_time: 4
process io_start_time: 3
process io_burst_time: 3
process priority: 0
process remainint_cpu_time: 4
process remaining_io_time: 3
process is_end: 0

process 2
process pid: 2
process arrival_time: 5
process cpu_burst_time: 4
process io_start_time: 1
process io_burst_time: 5
process priority: 2
process remainint_cpu_time: 4
process remaining_io_time: 5
process is_end: 0

process 3
process pid: 3
process arrival_time: 5
process cpu_burst_time: 5
process io_start_time: 1
process io_burst_time: 1
process priority: 9
process remainint_cpu_time: 5
process remaining_io_time: 1
process is_end: 0



FCFS
P0 scheduled at: 1 , terminated at: 2
P1 scheduled at: 4 , terminated at: 7
P3 scheduled at: 7 , terminated at: 8
P2 scheduled at: 8 , terminated at: 9
P0 scheduled at: 9 , terminated at: 12
P3 scheduled at: 12 , terminated at: 16
P1 scheduled at: 16 , terminated at: 17
P2 scheduled at: 17 , terminated at: 20
AWT is : 8.250000
ATT is : 12.500000


Nonpreemptive SJF
P0 scheduled at: 1 , terminated at: 2
P1 scheduled at: 4 , terminated at: 7
P0 scheduled at: 7 , terminated at: 10
P1 scheduled at: 10 , terminated at: 11
P2 scheduled at: 11 , terminated at: 12
P3 scheduled at: 12 , terminated at: 13
P3 scheduled at: 14 , terminated at: 18
P2 scheduled at: 18 , terminated at: 21
AWT is : 7.000000
ATT is : 11.250000


Nonpreemptive Priority
P0 scheduled at: 1 , terminated at: 2
P1 scheduled at: 4 , terminated at: 7
P3 scheduled at: 7 , terminated at: 8
P0 scheduled at: 8 , terminated at: 11
P3 scheduled at: 11 , terminated at: 15
P2 scheduled at: 15 , terminated at: 16
P1 scheduled at: 16 , terminated at: 17
P2 scheduled at: 21 , terminated at: 24
AWT is : 8.750000
ATT is : 13.000000


Preemptive SJF
P0 scheduled at: 1 , terminated at: 2
P1 scheduled at: 4 , terminated at: 7
P0 scheduled at: 7 , terminated at: 10
P1 scheduled at: 10 , terminated at: 11
P2 scheduled at: 11 , terminated at: 12
P3 scheduled at: 12 , terminated at: 13
P3 scheduled at: 14 , terminated at: 18
P2 scheduled at: 18 , terminated at: 21
AWT is : 7.000000
ATT is : 11.250000


Preemptive Priority
P0 scheduled at: 1 , terminated at: 2
P1 scheduled at: 4 , terminated at: 5
P3 scheduled at: 5 , terminated at: 6
P2 scheduled at: 6 , terminated at: 7
P3 scheduled at: 7 , terminated at: 11
P0 scheduled at: 11 , terminated at: 14
P2 scheduled at: 14 , terminated at: 17
P1 scheduled at: 17 , terminated at: 19
P1 scheduled at: 22 , terminated at: 23
AWT is : 8.250000
ATT is : 12.500000


Round Robin
P0 scheduled at: 1 , terminated at: 2
P1 scheduled at: 4 , terminated at: 6
P3 scheduled at: 6 , terminated at: 7
P2 scheduled at: 7 , terminated at: 8
P1 scheduled at: 8 , terminated at: 9
P0 scheduled at: 9 , terminated at: 11
P3 scheduled at: 11 , terminated at: 13
P0 scheduled at: 13 , terminated at: 14
P1 scheduled at: 14 , terminated at: 15
P2 scheduled at: 15 , terminated at: 17
P3 scheduled at: 17 , terminated at: 19
P2 scheduled at: 19 , terminated at: 20
AWT is : 9.000000
ATT is : 13.250000
```
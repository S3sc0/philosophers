# Philosophers

![](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/An_illustration_of_the_dining_philosophers_problem.png/800px-An_illustration_of_the_dining_philosophers_problem.png)

## Project Overview

Philosophers is a school project for discovering the world of process multi-threading, and that's through developing a program that solves a classical problem of synchronization called [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). In our program the philosophers go through couple of states `eating`, `sleeping` and `thinking`, and with the help of [mutex](https://learn.microsoft.com/en-us/dotnet/standard/threading/mutexes) philosophers secure their forks while eating and drop them down when they finish.

> :memo: **Note:** The project is fully written in **C** programming Language.

## What I Learned

- Learned to create multiple threads in a single process.
- Learned to manage resouces shared between threads without causing a [Deadlock](https://en.wikipedia.org/wiki/Deadlock).
- Learned to create a program that automates the whole procces mentioned above.

## How To Use

Simply run `make` command to compile the necessary files. 

```console
make
```

Then run executable `philo` with the necessary arguments.

```console
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```

- **number_of_philosophers**: The number of philosophers and also the number
of forks.
- **time_to_die** (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat** (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

> ### The Ideology
>
>- One or more philosophers sit at a round table.<br>There is a large bowl of spaghetti in the middle of the table.
>- The philosophers alternatively **eat**, **think**, or **sleep**.<br>
While they are eating, they are not thinking nor sleeping;<br>
while thinking, they are not eating nor sleeping;<br>
and, of course, while sleeping, they are not eating nor thinking.
>- There are also forks on the table. **There are as many forks as philosophers**.
>- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
>- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
>- Every philosopher needs to eat and should never starve.
>- Philosophers don’t speak with each other.
>- Philosophers don’t know if another philosopher is about to die.
>- No need to say that philosophers should avoid dying!

### Screencasts

![](https://media.giphy.com/media/7HIGNeTVOZlHfIaaea/giphy.gif)

**Figure 01:** *One of the philosophers dies from starvation.*


![](https://media.giphy.com/media/Feo4OSQdR79vFsL41m/giphy.gif)

**Figure 02:** *The philosophers continue the simulation.*

> :memo: **Note:** The project has been tested both in 🍏 **macOS** and 🐧 **Linux** machines.

## Resources

- [Introduction to Parallel Computing Tutorial](https://hpc.llnl.gov/documentation/tutorials/introduction-parallel-computing-tutorial)
- [Unix Threads In C](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Mutex lock for Linux Thread Synchronization](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

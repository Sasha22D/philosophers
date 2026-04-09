*This project has been created as part of the 42 curriculum by sadaniel.*

# Philosophers

## Description

Philosophers is a concurrency project based on the classic **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra. The goal is to simulate a set of philosophers sitting at a round table, each alternating between eating, sleeping, and thinking. A philosopher needs two forks (one on each side) to eat, but there is exactly one fork between each pair of adjacent philosophers — meaning philosophers must share resources without causing deadlocks or starvation.

The project is a practical introduction to **multithreading** and **mutex synchronization** in C. Each philosopher is represented by a POSIX thread, and each fork is protected by a mutex. A separate monitor thread watches for deaths and meal completion.

### Program behavior

- Each philosopher is a thread running a routine: **take forks → eat → drop forks → sleep → think → repeat**
- A philosopher dies if he has not started eating within `time_to_die` milliseconds of his last meal
- The simulation stops when a philosopher dies or when all philosophers have eaten `nb_meals` times (optional argument)
- Only one message is printed at a time (protected by `print_mutex`)

---

## Instructions

### Compilation

```bash
cd philo
make
```

This produces a `philo` executable in the `philo/` directory.

### Execution

```bash
./philo <nb_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [nb_meals]
```

| Argument | Description |
|---|---|
| `nb_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in ms before a philosopher dies if he hasn't eaten |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `nb_meals` *(optional)* | If set, simulation stops when all philosophers have eaten this many times |

### Examples

```bash
./philo 5 800 200 200          # 5 philos, no meal limit
./philo 5 800 200 200 7        # stops after each philo eats 7 times
./philo 1 800 200 200          # edge case: single philosopher
```

### Cleanup

```bash
make clean    # removes object files
make fclean   # removes object files and binary
make re       # full recompile
```

---

## Implementation details

### Data structures

- **`t_data`** — global simulation parameters (times, flags, mutexes for death/print/start synchronization)
- **`t_fork`** — one per fork, contains a `pthread_mutex_t fork_mutex`
- **`t_thread`** — one per philosopher thread: id, last meal time, meals left, pointers to left/right forks, `meal_mutex`
- **`t_monitor`** — monitor thread struct, holds a reference to the philosopher array and shared data

### Synchronization model

Three global mutexes in `t_data` handle cross-thread coordination:

| Mutex | Purpose |
|---|---|
| `print_mutex` | Ensures only one message is printed at a time |
| `death_mutex` | Protects `has_a_philo_died` flag (read by all, written by monitor) |
| `start_mutex` | Used by the spinlock barrier to synchronize thread startup |

Each fork has its own `fork_mutex`, and each philosopher has a `meal_mutex` protecting `last_meal` and `meals_left`.

### Startup barrier (spinlock)

All philosopher threads call `philo_spinlock()` before starting their routine. Each thread increments `ready_count` under `start_mutex`. The last thread to arrive sets `start_time` and raises `all_ready`. All threads then spin-wait until `all_ready == 1`, ensuring every philosopher starts as simultaneously as possible. Once a thread finishes initialization, it increments `initialized_count`.

The monitor thread calls `monitor_spinlock()` and waits until `initialized_count == nb_philo` before beginning to watch for deaths, giving all philosophers time to record their initial `last_meal`.

### Philosopher routine

Even-numbered philosophers take the left fork first, odd-numbered take the right fork first. This avoids a symmetric deadlock where every philosopher picks up one fork and waits forever for the other.

Odd philosophers also start with a call to `odds_think()` (a sleep of `time_to_eat` ms) to offset their start and further reduce fork contention.

```
[spinlock barrier]
→ (odd philos: odds_think)
→ loop:
    take fork A → take fork B → eat → drop forks → sleep → think
```

After `eat()`, forks are always dropped unconditionally via `drop_forks()`. If a philosopher detects death during `take_fork_*`, it does not drop the fork inside that function — instead it signals failure back to the caller, which handles the unlock before exiting the loop.

### Monitor routine

The monitor thread runs `monitor_routine()` which loops every 1 ms:
1. Calls `check_meals()` — if all philosophers have `meals_left == 0`, calls `set_death()` to end the simulation
2. Iterates over every philosopher, reads `last_meal` under `meal_mutex`, and calls `death_message()` if `now - last_meal >= time_to_die`

`death_message()` calls `set_death()` (sets `has_a_philo_died = 1` under `death_mutex`) then prints the death message under `print_mutex`.

### Edge case: single philosopher

When `nb_philo == 1`, no monitor is created and a dedicated `one_philo_routine` is used: the philosopher picks up their only fork, prints the message, and waits to die.

---

## Resources

### Documentation & references

- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/) — comprehensive pthreads reference
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — problem statement and classical solutions
- [`pthread_mutex_lock` man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [`gettimeofday` man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Helgrind: a thread error detector — Valgrind docs](https://valgrind.org/docs/manual/hg-manual.html) — used extensively to detect data races and lock errors

### AI usage

**Perplexity AI** was used during the debugging phase of this project, specifically for:
- **Understanding Helgrind error messages** — interpreting `unlocked a not-locked lock`, `still holds N locks`, and `possible data race` reports and tracing them back to their source in the code
- **Reasoning about mutex invariants** — identifying cases where `drop_forks` could attempt to unlock a mutex that was never locked, and designing a cleaner lock/unlock ownership model
- **No code was generated by AI** — all implementation decisions and written code are the author's own

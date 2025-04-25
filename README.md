<div style="background: white; display: inline-block; padding: 10px; border-radius: 8px;">
  <img src="./docs/logo.png" alt="logo" style="width: 25%; display: block; margin: 0 auto;" />
</div>



**tpool** is a minimal, efficient, and portable **thread pool library written in C (C11)**. It allows developers to manage a pool of worker threads that execute tasks concurrently, providing a lightweight way to parallelize CPU-bound and I/O-bound workloads in C projects.

## 🚀 Features

- Simple and clean API
- Create and destroy thread pools with custom thread counts
- Submit tasks with user-defined data
- Wait for all tasks to finish (`join`)
- Thread-safe task queue with mutex and condition variables
- Graceful shutdown
- Optional work-stealing or priority support (future)
- Fully C11 compliant and POSIX-compliant
- Portable to Linux/macOS/BSD

---

## 📦 Getting Started

### 🔧 Build

You can include `tpool` as part of your own project or build it standalone.

#### Build with CMake (Recommended)

```bash
git clone https://github.com/lvntky/tpool.git
cd tpool
mkdir build && cd build
cmake ..
make
```

#### Manual Build

```bash
gcc -std=c11 -pthread -o example example.c tpool.c
```

---

## 🧠 How It Works

`tpool` maintains a fixed number of threads waiting for tasks on a shared task queue. When a task is submitted, it’s enqueued and picked up by one of the idle threads. This avoids the overhead of creating/destroying threads for each task and improves throughput for many short-lived jobs.

---

## 🧪 Example Usage

```c
#include "tpool.h"
#include <stdio.h>

void hello_task(void* arg) {
    int id = *(int*)arg;
    printf("Hello from task %d\n", id);
}

int main() {
    tpool_t* pool = tpool_create(4); // create thread pool with 4 threads

    int ids[10];
    for (int i = 0; i < 10; ++i) {
        ids[i] = i;
        tpool_submit(pool, hello_task, &ids[i]);
    }

    tpool_join(pool);    // wait for all tasks to complete
    tpool_destroy(pool); // clean up

    return 0;
}
```

---

## 📁 Project Structure

```
tpool/
├── include/
│   └── tpool.h          # Public header
├── src/
│   └── tpool.c          # Implementation
├── examples/
│   └── example.c        # Demo usage
├── tests/
│   └── tpool_test.c     # Unit tests
├── CMakeLists.txt       # Build system
└── README.md
```

---

## 🛠 Internals

- **Task Queue**: Circular buffer with mutex/cond for enqueue/dequeue  
- **Worker Threads**: Each thread runs a loop waiting for new tasks  
- **Synchronization**: `pthread_mutex_t`, `pthread_cond_t`  
- **Shutdown**: A graceful flag ensures no task is dropped during shutdown

---

## ⚙️ Configuration

You can tweak various options by editing `tpool_config.h` (optional):

```c
#define TPOOL_QUEUE_SIZE 1024
#define TPOOL_DEBUG 1
```

---

## ✅ Testing

Unit tests are provided in the `tests/` directory. To build and run:

```bash
make test
./tpool_test
```

---

## 📦 Install

To install system-wide:

```bash
make install
```

Headers will go to `/usr/local/include`, library to `/usr/local/lib`.

---

## 🤝 Contributing

1. Fork the repository  
2. Create a feature branch: `git checkout -b my-feature`  
3. Commit your changes: `git commit -am 'Add feature'`  
4. Push to the branch: `git push origin my-feature`  
5. Open a pull request

---

## 📄 License

MIT License. See [LICENSE](LICENSE) for details.

---

## 🧩 Future Work

- [ ] Thread affinity support  
- [ ] Delayed/scheduled tasks  
- [ ] Task prioritization  
- [ ] Work stealing model  
- [ ] C++ wrapper (optional)

---

## 💬 Acknowledgements

Inspired by various thread pool designs in systems libraries and C++ STL.

---

## 📞 Contact

Maintained by [Levent Kaya](https://github.com/lvntky)

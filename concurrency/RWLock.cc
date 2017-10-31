class RWLock
{
public:
    RWLock() = default;
    RWLock(const RWLock&) = delete;
    RWLock& operator=(const RWLock&) = delete;
    ~RWLock() = default;

    void read_lock()
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (writer) {
            read_waiter++;
            while (writer) {
                read_cv.wait(lock);
            }
            read_waiter--;
        }
        readers++;
    }

    void read_unlock()
    {
        std::unique_lock<std::mutex> lock(mtx);
        readers--;
        if (readers == 0) {
            write_cv.notify_one();
        }
    }

    void write_lock()
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (readers > 0 || writer) {
            write_waiter++;
            while (readers > 0 || writer) {
                write_cv.wait(lock);
            }
            write_waiter--;
        }
        writer = true;
    }

    void write_unlock()
    {
        std::unique_lock<std::mutex> lock(mtx);
        writer = false;
        if (write_waiter > 0) {
            write_cv.notify_one();
        } else if (read_waiter > 0) {
            read_cv.notify_all();
        }
    }

private:
    std::mutex mtx;
    std::condition_variable read_cv, write_cv;
    u_int32_t readers = 0, read_waiter = 0, write_waiter = 0;
    bool writer = false;
};
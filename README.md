THE MAIN PART OF THE TASK#1 is if thread1.detach(); so, thread1 will start when future.get(); if join() thread1 will finish before future.get()
		
std::promise<int> promise;
std::future<int> future = promise.get_future();
std::thread thread1(set_min_in_promise, dest_array, i, size, std::move(promise));
thread1.detach();// if detach() thread1 will start when future.get(); if join() thread1 will finish before future.get()
int imin = future.get();

THE MAIN PART OF THE TASK#2 is std::async(std::launch::async, ...); - launch "task" in a new thread

std::async(std::launch::deferred, ...); - launch "task" in the same thread
#pragma once
#include "System.h"

namespace ic {






    class MtSystemThreadPool {
    public:
        MtSystemThreadPool(size_t threads) : stop(false) {
            for (size_t i = 0; i < threads; ++i)
                workers.emplace_back([this] {
                for (;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
                    });
        }

        //returns a future return type
        template<class F, class... Args>
        std::future<bool> enqueue(F&& f, Args&&... args) {


            auto task = std::make_shared< std::packaged_task<bool()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );

            std::future<bool> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(queue_mutex);

                // don't allow enqueueing after stopping the pool
                if (stop)
                    throw std::runtime_error("enqueue on stopped ThreadPool");

                tasks.emplace([task]() { (*task)(); });
            }
            condition.notify_one();
            return res;
        }

        ~MtSystemThreadPool() {
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                stop = true;
            }
            condition.notify_all();
            for (std::thread& worker : workers)
                worker.join();
        }
    private:
        // need to keep track of threads so we can join them
        std::vector<std::thread> workers;
        // the task queue
        std::queue<std::function<void()>> tasks;

        // synchronization
        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;
    };


    extern std::unique_ptr<MtSystemThreadPool> mtSysPool;


	template<typename... ComponentTypes>
	class MtSystem : public System {
    public:

		MtSystem(Scene* scene) : System(scene),
			view(std::make_shared<SceneView<ComponentTypes...>>(scene)) {

            if (mtSysPool.get() == nullptr) {
                const auto processor_count = std::thread::hardware_concurrency();
                mtSysPool = std::make_unique<MtSystemThreadPool>(processor_count / 2);
            }
        
        }

		virtual void excecute() {
			BenchmarkLogger::get()->beginBenchmark(this->getName() + "_mt");

			for (auto actor : *view) {
                results.emplace_back(
                    mtSysPool->enqueue([this, actor] {
                        std::tuple<ComponentTypes*...> comps = scene->compManager->getComponents<ComponentTypes...>(actor);
                        excecutionFunction(actor, comps);
                        return (bool)true;
                    })
                );
			}

            for (auto& b : results) {
                (void)b.get();
            }

            results.clear();

			BenchmarkLogger::get()->endBenchmark(this->getName() + "_mt");
		}
	protected:

        std::vector<std::future<bool>> results;

		MtSystem() {}
		virtual void excecutionFunction(std::shared_ptr<ActorEntry> entry, std::tuple<ComponentTypes*...> comps) = 0;

		virtual std::string toString() const override {
			std::string types[] = { "", (typeid(ComponentTypes).name())... ,"" };
			std::string printval = getName()
				+ ":(MtSystem<";

			for (auto str : types) {
				std::string::size_type i = str.find("struct");
				if (i != std::string::npos) {
					str.erase(i, 6);
				}

				printval += str;
			}

			printval += " >)->Type="
				+ getSysTypeName();
			return printval;
		}

		std::shared_ptr<SceneView<ComponentTypes...>> view;

        std::mutex scene_mutex;
	};
}
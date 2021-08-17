#pragma once

namespace spdlog {
	class stopwatch;
	class logger;
}

namespace ic {
	class BenchmarkLogger {
	public:

		BenchmarkLogger();
		~BenchmarkLogger();

		void beginBenchmark(const std::string& benchmarkname);
		void endBenchmark(const std::string& benchmarkname);

		void dump();

		static decltype(auto) get() {
			if (instance.get() == nullptr) {
				instance = std::make_shared<BenchmarkLogger>();
			}
			return instance;
		}

		static void shutdown() {
			instance.reset();
		}

	private:
		std::map<std::string, long double> totals;
		std::map<std::string, long double> averages;
		std::map<std::string, unsigned long long> iterations;
		//long double totaltime = 0;
		int numRunning = 0;

		std::map<std::string, std::shared_ptr<spdlog::stopwatch>> timers;

		std::unique_ptr<spdlog::logger> benchmarkLogger;
		static inline std::shared_ptr<BenchmarkLogger> instance;
	};
}
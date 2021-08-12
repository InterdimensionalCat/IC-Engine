#include "BenchmarkLogger.h"


#include <spdlog/stopwatch.h>
#include <spdlog/spdlog.h>
#include <spdlog\sinks\stdout_color_sinks.h>
#include <spdlog\sinks\basic_file_sink.h>

using namespace ic;

BenchmarkLogger::BenchmarkLogger() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    console_sink->set_pattern("[console][%^Benchmark-%l%$] %v");

    fs::path filepath(fs::current_path());
    filepath /= "logs";
    filepath /= "latest_benchmark.txt";

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filepath.string(), true);
    file_sink->set_pattern("[%Y-%m-%d : %H:%M:%S][%^Benchmark-%l%$] %v");

    //spdlog::logger lgr("cout_file_benchmark", )

    benchmarkLogger = std::make_unique<spdlog::logger>("cout_file_benchmark",
        spdlog::sinks_init_list{ console_sink, file_sink });
    benchmarkLogger->set_level(spdlog::level::trace);


    Logger::info("Benchmark Logger starting up.");
}

BenchmarkLogger::~BenchmarkLogger() {
    Logger::info("Benchmark Logger shutting down.");
    dump();
}

void BenchmarkLogger::beginBenchmark(const std::string& benchmarkname) {
    //benchmarkLogger->info("Starting benchmark timer for benchmark: {}", benchmarkname);
    if (timers.find(benchmarkname) == timers.end()) {
        timers.insert(std::pair(benchmarkname, std::unique_ptr<spdlog::stopwatch>()));
        totals.insert(std::pair(benchmarkname, 0));
        averages.insert(std::pair(benchmarkname, 0));
        iterations.insert(std::pair(benchmarkname, 0));
    }

    numRunning++;
    timers[benchmarkname] = std::make_shared<spdlog::stopwatch>();
}
void BenchmarkLogger::endBenchmark(const std::string& benchmarkname) {
    auto dur = timers[benchmarkname]->elapsed().count();
    timers[benchmarkname]->reset();
    timers[benchmarkname].reset();
    numRunning--;

    iterations[benchmarkname]++;

    totals[benchmarkname] += dur;
    if (numRunning >= 0) {
        //totaltime += dur;
    }
    averages[benchmarkname] = totals[benchmarkname] / (long double)iterations[benchmarkname];

    //benchmarkLogger->info("Ending benchmark timer for benchmark: {}", benchmarkname);
}

void BenchmarkLogger::dump() {
    benchmarkLogger->debug("Benchmark Dump:");
    benchmarkLogger->debug("{:*^50}", "*");

    auto totaltime = totals["Game"];

    std::vector<std::string> keys;

    for (auto [key, val] : timers) {
        keys.push_back(key);
    }

    std::sort(keys.begin(), keys.end(), [this, &totaltime](const auto a, const auto b) {
        return (totals[a] / totaltime) * 100.0 > (totals[b] / totaltime) * 100.0;
        });

    for (auto& key: keys) {
        benchmarkLogger->debug("Benchmark {}: ", key);
        benchmarkLogger->debug("Total time: {} microseconds ({:03.2f}% of benchmark runtime)", (long long)(totals[key] * 1000000l), (totals[key] / totaltime) * 100.0);
        benchmarkLogger->debug("Average time: {} microseconds ({} iterations)", (long long)(averages[key] * 1000000l), iterations[key]);
        benchmarkLogger->debug("{:*^50}", "*");
    }
}
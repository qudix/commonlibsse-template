#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

void InitLogging()
{
	auto path = logs::log_directory();
	if (!path)
		return;

	*path /= "commonlibsse-template.log";

	spdlog::sinks_init_list sinks{
		std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true),
		std::make_shared<spdlog::sinks::msvc_sink_mt>()
	};

	auto logger = std::make_shared<spdlog::logger>("global", sinks);
	logger->set_level(spdlog::level::info);
	logger->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(logger));
	spdlog::set_pattern("[%^%L%$] %v");
}

extern "C" __declspec(dllexport)
bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	InitLogging();

	logs::info("commonlibsse-template is loading...");

	SKSE::Init(a_skse);

	logs::info("commonlibsse-template loaded.");

	return true;
}

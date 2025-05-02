#pragma once
#include <vector>
#include <string>
#include <memory>

namespace Lobster
{
	enum class LogLevel : unsigned char
	{
		Debug = 0,
		Info = 1,
		Warning = 2,
		Error = 3,
		Critical = 4
	};

	class Logger
	{
	public:
		virtual ~Logger() = default;
		virtual void Log(LogLevel level,const std::string& message) = 0;
		virtual void Attach() = 0;
		virtual void Detach() = 0;

		inline void Debug(const std::string& message){Log(LogLevel::Debug,message);}
		inline void Info(const std::string& message){Log(LogLevel::Info,message);}
		inline void Warning(const std::string& message){Log(LogLevel::Warning,message);}
		inline void Error(const std::string& message){Log(LogLevel::Error,message);}
		inline void Critical(const std::string& message){Log(LogLevel::Critical,message);}
	protected:
		std::string LevelToString(LogLevel level)
		{
			switch(level)
			{
			case LogLevel::Debug:
				return "DEBUG";
			case LogLevel::Info:
				return "INFO";
			case LogLevel::Warning:
				return "WARNING";
			case LogLevel::Error:
				return "ERROR";
			case LogLevel::Critical:
				return "CRITICAL";
			default: return "UNKNOWN";
			}
		}
	};

	class ConsoleLogger : public Logger
	{
	public:
		void Log(LogLevel level,const std::string& message) override;

		inline void Attach() override {}
		inline void Detach() override {}
	};

	class ImGuiConsoleLogger : public Logger
	{
	public:
		void Log(LogLevel level,const std::string& message) override;

		inline void Attach() override { _attached = true; }
		inline void Detach() override { _attached = false; }

		void Draw();
	private:
		struct LogEntry
		{
			LogLevel level;
			std::string message;
		};

		const unsigned int _max_logs = 1024;

		bool _attached = false;
		bool _autoscroll = true;

		std::vector<LogEntry> _logs;
	};

	class LoggerManager
	{
	public:
		static void AddLogger(std::shared_ptr<Logger> logger);

		static void Log(LogLevel level,const std::string& message);

		static void Attach();
		static void Detach();
	};

}

#define LOG(lvl,msg) Lobster::LoggerManager::Log(lvl,msg + std::string(" (File: ") + std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\") + 1) + ", Line: " + std::to_string(__LINE__) + ")")
#define LOG_CLEAN(lvl,msg) Lobster::LoggerManager::Log(lvl,msg)

#define LOG_DEBUG(msg) LOG_CLEAN(Lobster::LogLevel::Debug,msg)
#define LOG_INFO(msg) LOG_CLEAN(Lobster::LogLevel::Info,msg)
#define LOG_WARNING(msg) LOG(Lobster::LogLevel::Warning,msg)
#define LOG_ERROR(msg) LOG(Lobster::LogLevel::Error,msg)
#define LOG_CRITICAL(msg) LOG(Lobster::LogLevel::Critical,msg)


#define ASSERT(condition,message) \
	if(!(condition)){ \
	LOG_ERROR(message); \
	std::abort(); \
	}

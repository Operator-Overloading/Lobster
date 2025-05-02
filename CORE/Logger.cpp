#include "Logger.h"

#include <chrono>
#include <iostream>
#include <iomanip>

#include "imgui/imgui.h"

namespace Lobster
{
	void ConsoleLogger::Log(LogLevel level,const std::string& message)
	{
		auto now = std::chrono::system_clock::now();
		auto now_time = std::chrono::system_clock::to_time_t(now);

		std::string color_code = "\033[97m";

		switch(level)
		{
		case LogLevel::Debug:
			color_code = "\033[97m";
			break;
		case LogLevel::Info:
			color_code = "\033[37m";
			break;
		case LogLevel::Warning:
			color_code = "\033[93m";
			break;
		case LogLevel::Error:
			color_code = "\033[91m";
			break;
		case LogLevel::Critical:
			color_code = "\033[31m";
			break;
		default:
			break;
		}

		tm current_time;
		_localtime64_s(&current_time,&now_time);

		std::cout << color_code << std::put_time(&current_time,"%Y-%m-%d %X") << " [" << LevelToString(level) << "] " << message << std::endl;
		std::cout << "\033[37m";
	}


	void ImGuiConsoleLogger::Log(LogLevel level,const std::string& message)
	{
		auto now = std::chrono::system_clock::now();
		auto now_time = std::chrono::system_clock::to_time_t(now);

		tm current_time;
		_localtime64_s(&current_time,&now_time);

		std::stringstream time;
		time << std::put_time(&current_time,"%Y-%m-%d %X");
		time << " ";

		std::string formatted = time.str() + "[" + LevelToString(level) + "] " + message;

		_logs.push_back({level,formatted});

		if(_logs.size() > _max_logs)
		{
			_logs.erase(_logs.begin());
		}
	}

	void ImGuiConsoleLogger::Draw()
	{
		if(!_attached)
			return;

		ImGui::Begin("Console");

		if(ImGui::Button("Clear"))
			_logs.clear();

		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");

		ImGui::SameLine();
		if(ImGui::Button("Options"))
			ImGui::OpenPopup("Options");

		if(ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll",&_autoscroll);
			ImGui::EndPopup();
		}

		ImGui::Separator();

		ImGui::BeginChild("Scrolling",ImVec2(0,0),false,ImGuiWindowFlags_HorizontalScrollbar);

		if(copy)
			ImGui::LogToClipboard();

		for(const auto& log : _logs)
		{
			ImVec4 color = ImVec4(1.0f,1.0f,1.0f,1.0f);

			switch(log.level)
			{
				case LogLevel::Debug: color = ImVec4(1.0f,1.0f,1.0f,1.0f);
					break;
				case LogLevel::Info: color = ImVec4(0.8f,0.8f,0.8f,1.0f);
					break;
				case LogLevel::Warning: color = ImVec4(1.0f,1.0f,0.0f,1.0f);
					break;
				case LogLevel::Error: color = ImVec4(1.0f,0.3f,0.3f,1.0f);
					break;
				case LogLevel::Critical: color = ImVec4(1.0f,0.0f,0.0f,1.0f);
					break;
			}

			ImGui::PushStyleColor(ImGuiCol_Text,color);
			ImGui::TextUnformatted(log.message.c_str());
			ImGui::PopStyleColor();
		}

		if(_autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}

	static std::vector<std::shared_ptr<Logger>> _loggers;

	void LoggerManager::AddLogger(std::shared_ptr<Logger> logger)
	{
		_loggers.push_back(logger);
	}

	void LoggerManager::Log(LogLevel level,const std::string& message)
	{
		if(_loggers.empty())
			return;

		auto now = std::chrono::system_clock::now();
		auto now_time = std::chrono::system_clock::to_time_t(now);

		tm current_time;
		_localtime64_s(&current_time,&now_time);

		for(auto& logger : _loggers)
		{
			logger->Log(level,message);
		}
	}

	void LoggerManager::Attach()
	{
		for(auto& logger : _loggers)
		{
			logger->Attach();
		}
	}

	void LoggerManager::Detach()
	{
		for(auto& logger : _loggers)
		{
			logger->Detach();
		}
	}
}
#pragma once
#include "etherpch.h"
#include "Ether/Window.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Ether {

	//Windows Specific Glfw Window
	//This is a wrapper for GLFWwindow.
	class ETHER_API WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();
		
		virtual void OnUpdate() override;
	
		virtual uint32_t GetWidth() const override
		{
			return m_Data.Width;
		}
		virtual uint32_t GetHeight() const override
		{
			return m_Data.Height;
		}

		virtual void SetEventCallback(EventCallbackFn callback) override
		{
			m_Data.Callback = callback;
		}
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() override
		{
			return m_Window;
		}
	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			uint32_t Width;
			uint32_t Height;
			bool VSync;
			EventCallbackFn Callback;
		};

		WindowData m_Data;
	};

}
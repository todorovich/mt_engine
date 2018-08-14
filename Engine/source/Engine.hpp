// Copyright 2018 Micho Todorovich, all rights reserved.

#pragma once

#include "precompiled.hpp"

#include "TimerManager.hpp"
#include "DirectXRenderer.hpp"
#include "WindowsMessageManager.hpp"
#include "CommandManager.hpp"
#include "InputManager.hpp"


namespace mt
{
	class Engine
	{
	protected:
		static std::unique_ptr<Engine> _instance;
	
		std::thread _engine_tick_thread;
	
	public:	
		// ACCESSOR
	
		static	Engine& 				GetEngine()					{ return *Engine::_instance.get(); };
		static	TimerManager&			GetTimerManager()			{ return GetEngine()._time_manager; };
		static	DirectXRenderer&		GetRenderer()				{ return GetEngine()._direct_x_renderer; };
		static  InputManager&			GetInputHandler()			{ return GetEngine()._input_manager; }
		static  Camera&					GetCurrentCamera()			{ return GetEngine()._direct_x_renderer.GetCurrentCamera(); }
		static	WindowsMessageManager&	GetWindowsMessageManager()	{ return GetEngine()._windows_message_manager; };
		static	CommandManager&			GetCommandManager()			{ return GetEngine()._command_manager; }

		static	HINSTANCE				GetInstanceHandle()			{ return GetEngine()._GetInstanceHandle(); };
		static	HWND					GetMainWindowHandle()		{ return GetEngine()._GetMainWindowHandle(); };

		static	float					GetWindowAspectRatio()		{ return GetEngine()._GetWindowAspectRatio(); };
		static	int						GetWindowWidth()			{ return GetEngine()._GetWindowWidth(); };
		static	int						GetWindowHeight()			{ return GetEngine()._GetWindowHeight(); };

		static	bool					IsWindowMaximized()			{ return GetEngine()._GetIsWindowMaximized(); };
		static	bool					IsWindowMinimized()			{ return GetEngine()._GetIsWindowMinimized(); };
		static	bool					IsWindowResizing()			{ return GetEngine()._GetIsWindowResizing(); };
		static	bool					IsWindowFullscreen()		{ return GetEngine()._GetIsWindowFullscreen(); };

		static	bool					IsDestroyed()				{ return _instance.get() == nullptr; };

		// MUTATOR
	
		static Status Run() 
		{ 
			return (_instance.get() == nullptr) ? Status::failure : GetEngine()._Run(); 
		};
		
		static bool Initialize(HINSTANCE hInstance)
		{	
			return GetEngine()._Initialize(hInstance);;
		};
		
		static void Resize(int width, int height)
		{ 
			return GetEngine()._resize(width, height); 
		};
	
		static void SetIsWindowResizing(bool is_resizing)
		{
			return GetEngine()._set_is_resizing(is_resizing);
		}
	
		static void SetIsWindowMaximized(bool is_maximized)
		{
			return GetEngine()._set_is_maximized(is_maximized);
		}
		
		static void SetIsWindowMinimized(bool is_resizing)
		{
			return GetEngine()._set_is_minimized(is_resizing);
		}
	
		static void SetWindowDimensions(const int& width, const int& height)
		{
			GetEngine()._window_width = width;
			GetEngine()._window_height = height;
			GetEngine()._window_aspect_ratio = (float)width / (float)height;
		}
	
		// Called to begin orderly shutdown.
		static void Shutdown()
		{
			GetEngine()._shutdown();
			OutputDebugStringW(L"Engine Shutdown Initiated\n");
		}
	
		static void Destroy()
		{
			if (_instance.get() != nullptr)
			{
				GetEngine()._destroy();
			}

			OutputDebugStringW(L"Engine Destroyed\n");
		}

		Engine()
			: _direct_x_renderer()
			, _windows_message_manager()
			, _command_manager()
			, _input_manager()
			, _time_manager()
		{

		}
	
		virtual ~Engine() 
		{
			if (!IsDestroyed())
			{
				Destroy();
			}
		};

		Engine(const Engine&  other) = delete;
	
		Engine(Engine&& other) = delete;
	
		Engine& operator=(const Engine&  other) = delete;
	
		Engine& operator=(Engine&& other) = delete;
	
	protected:	

		// CALLBACKS
		virtual void OnResize() { };
		virtual void Update() { };
		virtual void Draw() { };

		// ACCESSORS
	
		HINSTANCE _GetInstanceHandle()		const	{ return _instance_handle; };
		HWND      _GetMainWindowHandle()	const	{ return _main_window_handle; };

		float	  _GetWindowAspectRatio()	const	{ return _window_aspect_ratio; };
		int		  _GetWindowWidth()			const	{ return _window_width; };
		int		  _GetWindowHeight()		const	{ return _window_height; };

		bool	  _GetIsWindowMaximized()	const	{ return _is_window_maximized; };
		bool	  _GetIsWindowMinimized()	const	{ return _is_window_minimized; };
		bool	  _GetIsWindowResizing()	const	{ return _is_window_resizing; };
		bool	  _GetIsWindowFullscreen()	const	{ return _is_window_fullscreen; };
	
	
		virtual bool	_Initialize(HINSTANCE hInstance);
		Status			_Run();
		void			_Tick();
		
		bool			_InitializeMainWindow();
		void			_UpdateFrameStatistics();
		void			_UpdateFrameStatisticsNoTimeCheck();
	
	protected:
	
		static void Tick();
	
		void _resize(int width, int height)
		{
			// This flag should prevent futher rendering after the current frame finishes
			_set_is_resizing(true);
	
			// wait until rendering is finished.
			while (_direct_x_renderer.get_is_rendering()) {};
	
			_window_width = width;
			_window_height = height;
			_window_aspect_ratio = static_cast<float>(_window_width) / _window_height;
	
			_direct_x_renderer.Resize(width, height);
			
			// Trigger callback
			OnResize();
			// Continue rendering.
			_set_is_resizing(false);
		}
	
		void _set_is_resizing(bool is_resizing)
		{
			_is_window_resizing = is_resizing;
		}
	
		void _set_is_maximized(bool is_maximized)
		{
			_is_window_maximized = is_maximized;
		}
	
		void _set_is_minimized(bool is_minimized)
		{
			_is_window_minimized = is_minimized;
		}
	
		void _shutdown()
		{
			_time_manager.Pause();

			_is_shutting_down = true;

			// Destroy the window
			DestroyWindow(GetEngine()._GetMainWindowHandle());
		}
	
		void _destroy()
		{
			delete _instance.release();
		}

	private:
		DirectXRenderer				_direct_x_renderer;
		WindowsMessageManager		_windows_message_manager;
		CommandManager				_command_manager;
		InputManager				_input_manager;
		TimerManager				_time_manager;

		std::wstring				_main_window_caption = L"mt_engine";
	
		std::chrono::nanoseconds	_time_since_stat_update = 0ns;

		HINSTANCE					_instance_handle	= nullptr;	// application instance handle
		HWND						_main_window_handle	= nullptr;	// main window handle

		int		_window_width			= 0;
		int		_window_height			= 0;
		float	_window_aspect_ratio	= _window_height ? static_cast<float>(_window_width) / _window_height : 0;
		
		volatile bool	_is_window_minimized	= false;	// is the application minimized?
		volatile bool	_is_window_maximized	= false;	// is the application maximized?
		volatile bool	_is_window_resizing		= false;	// are the Resize bars being dragged?
		volatile bool	_is_window_fullscreen	= false;	// fullscreen enabled
		volatile bool	_is_shutting_down		= false;	// Shutdown is checked to see if Tick should keep ticking, on true ticking stops and Tick() returns
		
	};
}

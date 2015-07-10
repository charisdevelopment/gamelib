#include "pch.h"
#include <thread>

// For Jobs:
//	Need a Task object - this is a single Task that gets assigned to a Single Thread.
//	Need a Group object that contains a Group of Tasks that can run concurrently.
//	Need a Chain object that is a logical sequence of Groups
// When the Chain is finished, the Job is done.

namespace glib {
	//---------------------------------------------------
	// glib::IJobTask (abstract)
	// Interface for a task - please inherit from glib::Task
	//---------------------------------------------------
	class IJobTask {
	public:
		virtual void Execute() = 0;
	};

	//---------------------------------------------------
	// glib::JobTask (abstract)
	// Template Parameters - 
	//	_parameter: Class that holds parameters to the task.
	//	_output: Class that holds output from the task.
	//---------------------------------------------------
	template <typename _parameter, typename _output>
	class JobTask: public IJobTask {
	public:
		JobTask() {
		}

		_parameter & GetParameters() { return m_param; }
		_output	& GetOutput() { return m_output; }

		virtual void Execute() = 0;

	private:
		_parameter	m_param;
		_output		m_output;
	};

	//---------------------------------------------------
	// glib::JobGroup
	// Group of tasks
	//---------------------------------------------------
	class JobGroup {
	private:
		List< IJobTask * > tasks;
	};

	//---------------------------------------------------
	// glib::Job
	// A chain of Job Groups
	//---------------------------------------------------
	class Job {
	private:
		List< JobGroup > groups;
	};

	//---------------------------------------------------
	// glib::JobThread
	// A chain of Job Groups
	//---------------------------------------------------
	class JobThread {
	public:
		JobThread(): m_task( nullptr ) {
		}

		void Assign( IJobTask * m_task ) {
		}

	private:
		void Execute() {
			glibAssert( m_task != nullptr );
			m_task->Execute();
		}

		std::thread	m_thread;
		IJobTask * m_task;
	};

	//---------------------------------------------------
	// glib::JobThreadPool
	// This is a pool of available threads for execution.
	//---------------------------------------------------
	template < int _thread_count >
	class JobThreadPool {
	public:
		JobThreadPool() {}

	private:
		JobThread	m_threads[ _thread_count ];
	};
}
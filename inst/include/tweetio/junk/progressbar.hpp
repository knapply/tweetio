// Copyright (C) 2019 Brendan Knapp
// This file is part of tweetio.
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef TWEETIO_PROGRESS_BAR_H
#define TWEETIO_PROGRESS_BAR_H

// #include <progress.hpp>

// #include <R_ext/Print.h>
// #include <Rcpp.h>

namespace tweetio {

#include "interruptable_progress_monitor.hpp"

// e.g. for  Rf_error
#include <R_ext/Error.h>

#include "progress_bar.hpp"

#include <R_ext/Print.h>

// for unices only
#if !defined(WIN32) && !defined(__WIN32) && !defined(__WIN32__)
#include <Rinterface.h>
#endif



inline void msg(std::string x, bool appendLF = true) { 
    Rcpp::Function msg("message"); 
    msg(x, Rcpp::_["appendLF"] = appendLF);
}


class ProgressMessage: public ProgressBar{
  public: // ====== LIFECYCLE =====

    /**
    * Main constructor
    */
    ProgressMessage()  { reset(); }

    ~ProgressMessage() {}

  public: // ===== main methods =====

    void display() {
      msg("0%  10  20  30  40  50  60  70  80  90  100%");
      msg("[---|---|---|---|---|---|---|---|---|---|");
      flush_console();
    }

    // will finalize display if needed
    void update(float progress) {
      _update_ticks_display(progress);
      if (_ticks_displayed >= _max_ticks)
        _finalize_display();
    }

    void end_display() {
      update(1);
      reset();
    }

    void reset() {
      _max_ticks = 40;
      _ticks_displayed = 0;
      _finalized = false;
    }


  protected: // ==== other instance methods =====

    // update the ticks display corresponding to progress
    void _update_ticks_display(float progress) {
      int nb_ticks = _compute_nb_ticks(progress);
      int delta = nb_ticks - _ticks_displayed;
      if (delta > 0) {
        _display_ticks(delta);
        _ticks_displayed = nb_ticks;
      }

    }

    void _finalize_display() {
      if (_finalized) return;

      msg("|");
      flush_console();
      _finalized = true;
    }

    int _compute_nb_ticks(float progress) {
      return int(progress * _max_ticks);
    }

    void _display_ticks(int nb) {
      for (int i = 0; i < nb; ++i) {
        msg("*", this->_finalized);
        R_FlushConsole();
      }
    }

    // N.B: does nothing on windows
    void flush_console() {
#if !defined(WIN32) && !defined(__WIN32) && !defined(__WIN32__)
       R_FlushConsole();
#endif
    }

  private:
    int _max_ticks;   		// the total number of ticks to print
    int _ticks_displayed; 	// the nb of ticks already displayed
    bool _finalized;

};





class Progress {
public:
	/**
	 *
	 * Main constructor
	 * @param max the expected number of tasks to perform
	 * @param display_progress whether to display a progress bar in the console
	 * @param pb  the ProgressBar instance to use
	 */
	Progress(
	  unsigned long max,
	  bool display_progress = true,
    ProgressBar& pb = default_progress_bar()
  ) {
    if ( monitor_singleton() != 0) { // something is wrong, two simultaneous Progress monitoring
      Rf_error("ERROR: there is already an InterruptableProgressMonitor instance defined");
    }
    monitor_singleton() = new InterruptableProgressMonitor(max, display_progress, pb);
	}

	~Progress() { cleanup(); 	}

public: // ==== USER INTERFACE =====
	/**
	 * cleanup
	 *
	 *  should normally not be called, unless a something bad happens (
	 *  a process/thread that crashes).
	 *
	 */
	void cleanup() {
    if (monitor_singleton() != 0) delete monitor_singleton();
    monitor_singleton() = 0;
	}

	/**
	 * increment the current progress.
	 *
	 * This method should preferably be used intead of update in a OpenMP context.
	 *
	 * Iff called by the master thread, it will also update the display if needed
	 *
	 * @param amount the number of newly performed tasks to report
	 *
	 * @return false iff the computation is aborted
	 */
	bool increment(unsigned long amount=1) { return monitor().increment(amount); }

	/**
	 * set the current progress indicator
	 *
	 * Iff called by the master thread, it will also update the display if needed
	 *
	 * @param current the total number of performed tasks so far (by all threads)
	 *
	 * @return false iff the computation is aborted
	 */
	bool update(unsigned long current) { return monitor().update(current); }

	/**
	 * return if the computation has been aborted.
	 * N.B: do not perform any check by itselfd
	 */
	bool is_aborted() const { return monitor().is_aborted(); }

	/**
	 * check that the no interruption has been requested and return the current status
	 *
	 * Iff called by the master thread, it will check for R-user level interruption.
	 *
	 * @return true iff the computation is aborted
	 */
	static bool check_abort() { return monitor().check_abort(); }

private:
	static InterruptableProgressMonitor*& monitor_singleton() {
		static InterruptableProgressMonitor* p = 0;
		return p;
	}

	// trick to provide a default static member in a header file
	static ProgressMessage& default_progress_bar() {
	  static ProgressMessage pb;
	  pb.reset();
	  return pb;
	}

public: // ==== OTHER PUBLIC INTERFACE =====
	static InterruptableProgressMonitor& monitor() { return *monitor_singleton(); }

};



} // namespace tweetio


#endif

# SeqTimer

[![author](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/auth_SMFSW.json)](https://github.com/SMFSW)
![badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/SeqTimer_status_badge.json)
[![license](https://img.shields.io/badge/License-BSD3-darkred.svg)](LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/smfsw/seqtimer/badge)](https://www.codefactor.io/repository/github/smfsw/seqtimer)

![platform](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/platform_INO.json)

[![doxy](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_DOXY.json)](https://smfsw.github.io/SeqTimer)
[![re_note](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_RN.json)](ReleaseNotes.md)


Arduino sequential timer library (multi purpose small lib to handle timers without modifying any hw timer)

The purpose here is to have a small piece of lib being able to manipulate simple timers (does not modify hw timers).

Keep in mind that this type of timer is not as accurate as a hw timer.
This library is not intended to be used as a PWM generator for example, but to avoid using delay(s).

## Usage

- Automatic class (can handle timers of 2^32 ms max with 1 ms granularity)
  - `init(period)` or `setPeriod(period)` if you want to execute the first step right away
  - in loop: if `getTimer()` returns `true`, period has elapsed

- Manual class (can handle every uint16 type as time base)
  - `init(period, actual time)` to set the period and load the compare register with the given actual time
  - in loop: if `getTimer(actual time)` returns `true`, period has elapsed
    - possibility to use `reloadTimer(actual time)` to reload compare register manually (finite running counters)

## Examples included

- [SequentialBlink.ino](examples/SequentialBlink/SequentialBlink.ino): a proper way to handle simple timing on a blinking LED
- [CascadingTimers.ino](examples/CascadingTimers/CascadingTimers.ino): a demonstration how to use own base timers & cascading them to obtain a TimeCounter (not to be used as a real RTC)

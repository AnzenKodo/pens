// Copyright (c) 2026 - snd module
// Minimal base layer: linkage keywords, in the style of RAD Debugger's base_core.h
// If you already have a base layer (e.g. from raddebugger) with these defined,
// skip this file entirely and just include snd_core.h after your own base.h.

#ifndef SND_BASE_H
#define SND_BASE_H

// `function`  -> external linkage; marks a symbol that is part of a module's
//                public API and defined in exactly one translation unit.
// `internal`  -> file-local linkage; marks helpers private to a .c file.
// `global`    -> file-local linkage for file-scope variables.
// `local_persist` -> static storage duration for a function-local variable.
// `read_only` -> file-local, immutable, initialized-at-load-time data.
#if !defined(function)
# define function
#endif
#if !defined(internal)
# define internal       static
#endif
#if !defined(global)
# define global         static
#endif
#if !defined(local_persist)
# define local_persist  static
#endif
#if !defined(read_only)
# define read_only      static const
#endif

#endif // SND_BASE_H

# SDLite Version 1.2.3


SDLite is a lightweight C / C++ framework built on top of **SDL3**, designed to simplify common SDL workflows while providing game-oriented utilities such as sprites, animation, audio handling, timing, input helpers, and collision functions.

This framework is intended to be a **generic SDL helper library**, slightly tailored toward 2D game development.


---

## Patch Notes

- Put all SDLite header files in a folder called 'SDLite' in the include folder. This help keeps a global environment clean.

---

## Dependencies

The included folder **`SDL_libs_all`** contains all required SDL libraries used by this framework:

- SDL3 v3.5  
- SDL3_image v3.2  
- SDL3_mixer v3.2  
- SDL3_ttf v3.3  

You must link against these libraries to build projects using SDLite.

---

## SDLite Builds

Two prebuilt DLL versions of the framework are included:

- **SDLite.dll**  
  Standard release build.  
  No memory allocation tracking.  
  Intended for normal application or game builds.

- **debugSDLite.dll**  
  Debug build with **MemTrack** memory allocation tracking enabled.  
  Can detect memory leaks and track allocations during development.

I would recommmend using debugSDLite.dll during development, and SDLite.dll for release builds

---

## Documentation

All public functions are documented in their header files.  
Additionally, the included **MemTrack** library header contains documentation for memory tracking utilities and necessary macros.

---

## Prerequisites

This framework assumes you already have a basic understanding of SDL, and are comfortable with C / C++.  
Knowing how SDL works internally will make the SDLite much easier to understand and use effectively.

---

## Examples

Only one example project as of right is included:

- **Template Example**  
  Opens a window and displays the current FPS.

---

## License

This project is licensed under the MIT License.  
See the LICENSE file for details.

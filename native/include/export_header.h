// ExportHeader.h
#pragma once

#if defined(_WIN32) || defined(__WIN32__)
    // Windows platforms
    #if defined(OPTIKLAVI_EXPORT)
        #define OPTIKLAVI_API __declspec(dllexport)
    #else
        #define OPTIKLAVI_API __declspec(dllimport)
    #endif
    #define CALLING_CONVENTION __cdecl
#else
    // Non-Windows platforms like Linux and macOS use visibility attributes
    #if defined(OPTIKLAVI_EXPORT)
        #define OPTIKLAVI_API __attribute__((visibility("default")))
    #else
        #define OPTIKLAVI_API
    #endif
    #define CALLING_CONVENTION
#endif

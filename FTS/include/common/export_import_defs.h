#pragma once

#if defined(FTS_EXPORTS)
#  define FTS_EXPORT __declspec( dllexport )
#elif defined(FTS_IMPORTS)
#  define FTS_EXPORT __declspec( dllimport )
#else
#  define FTS_EXPORT   /**/
#endif 
